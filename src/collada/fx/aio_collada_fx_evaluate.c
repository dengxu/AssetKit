/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "aio_collada_fx_evaluate.h"
#include "../aio_collada_common.h"
#include "../aio_collada_param.h"
#include "../aio_collada_color.h"
#include "aio_collada_fx_enums.h"
#include "aio_collada_fx_image.h"

#define k_s_dae_color_target   1
#define k_s_dae_depth_target   2
#define k_s_dae_stencil_target 3
#define k_s_dae_color_clear    4
#define k_s_dae_depth_clear    5
#define k_s_dae_stencil_clear  6
#define k_s_dae_draw           7

static aio_enumpair evaluateMap[] = {
  {_s_dae_color_target,   k_s_dae_color_target},
  {_s_dae_depth_target,   k_s_dae_depth_target},
  {_s_dae_stencil_target, k_s_dae_stencil_target},
  {_s_dae_color_clear,    k_s_dae_color_clear},
  {_s_dae_depth_clear,    k_s_dae_depth_clear},
  {_s_dae_stencil_clear,  k_s_dae_stencil_clear},
  {_s_dae_draw,           k_s_dae_draw}
};

static size_t evaluateMapLen = 0;

int _assetio_hide
aio_dae_fxEvaluate(xmlTextReaderPtr __restrict reader,
                   aio_evaluate ** __restrict dest) {
  aio_evaluate  *evaluate;
  const xmlChar *nodeName;
  int            nodeType;
  int            nodeRet;

  evaluate = aio_calloc(sizeof(*evaluate), 1);

  if (evaluateMapLen == 0) {
    evaluateMapLen = AIO_ARRAY_LEN(evaluateMap);
    qsort(evaluateMap,
          evaluateMapLen,
          sizeof(evaluateMap[0]),
          aio_enumpair_cmp);
  }
  
  do {
    const aio_enumpair *found;

    _xml_beginElement(_s_dae_evaluate);

    found = bsearch(nodeName,
                    evaluateMap,
                    evaluateMapLen,
                    sizeof(evaluateMap[0]),
                    aio_enumpair_cmp2);

    switch (found->val) {
      case k_s_dae_color_target:
      case k_s_dae_depth_target:
      case k_s_dae_stencil_target: {
        aio_evaluate_target *evaluate_target;
        const xmlChar *targetNodeName;

        evaluate_target = aio_calloc(sizeof(*evaluate_target), 1);

        _xml_readAttrUsingFn(evaluate_target->index,
                             _s_dae_index,
                             strtol, NULL, 10);

        _xml_readAttrUsingFn(evaluate_target->slice,
                             _s_dae_slice,
                             strtol, NULL, 10);

        _xml_readAttrUsingFn(evaluate_target->mip,
                             _s_dae_mip,
                             strtol, NULL, 10);

        _xml_readAttrAsEnum(evaluate_target->face,
                            _s_dae_face,
                            aio_dae_fxEnumFace);

        targetNodeName = nodeName;

        do {
          _xml_beginElement(targetNodeName);

          if (_xml_eqElm(_s_dae_param)) {
            aio_param * param;
            int         ret;

            ret = aio_dae_param(reader,
                                AIO_PARAM_TYPE_BASIC,
                                &param);

            if (ret == 0)
              evaluate_target->param = param;
          } else if (_xml_eqElm(_s_dae_instance_image)) {
            aio_image_instance *imageInst;
            int ret;

            ret = aio_dae_fxImageInstance(reader, &imageInst);

            if (ret == 0)
              evaluate_target->image_inst = imageInst;
          } else {
            _xml_skipElement;
          }

          /* end element */
          _xml_endElement;
        } while (nodeRet);

        switch (found->val) {
          case k_s_dae_color_target:
            evaluate->color_target = evaluate_target;
            break;
          case k_s_dae_depth_target:
            evaluate->depth_target = evaluate_target;
            break;
          case k_s_dae_stencil_target:
            evaluate->stencil_target = evaluate_target;
            break;
          default: break;
        }
      }
      case k_s_dae_color_clear: {
        aio_color_clear *color_clear;
        color_clear = aio_calloc(sizeof(*color_clear), 1);

        _xml_readAttrUsingFn(color_clear->index,
                             _s_dae_index,
                             strtol, NULL, 10);

        aio_dae_color(reader, false, &color_clear->val);

        evaluate->color_clear = color_clear;
        break;
      }
      case k_s_dae_depth_clear:{
        aio_depth_clear *depth_clear;
        depth_clear = aio_calloc(sizeof(*depth_clear), 1);

        _xml_readAttrUsingFn(depth_clear->index,
                             _s_dae_index,
                             strtol, NULL, 10);

        _xml_readTextUsingFn(depth_clear->val,
                             strtof, NULL);

        evaluate->depth_clear = depth_clear;
        break;
      }
      case k_s_dae_stencil_clear:{
        aio_stencil_clear *stencil_clear;
        stencil_clear = aio_calloc(sizeof(*stencil_clear), 1);

        _xml_readAttrUsingFn(stencil_clear->index,
                             _s_dae_index,
                             strtol, NULL, 10);

        _xml_readTextUsingFn(stencil_clear->val,
                             strtoul, NULL, 10);

        evaluate->stencil_clear = stencil_clear;
        break;
      }
      case k_s_dae_draw: {
        char *strVal;
        _xml_readText(strVal);

        if (strVal) {
          evaluate->draw.str_val = strVal;
          evaluate->draw.enum_draw = aio_dae_fxEnumDraw(strVal);
        }
      }
      default:
         _xml_skipElement;
        break;
    }

    /* end element */
    _xml_endElement;
  } while (nodeRet);

  *dest = evaluate;
  
  return 0;
}
