/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "dae_fx_evaluate.h"
#include "../core/dae_param.h"
#include "../core/dae_color.h"
#include "dae_fx_enums.h"
#include "dae_fx_image.h"

#define k_s_dae_color_target   1
#define k_s_dae_depth_target   2
#define k_s_dae_stencil_target 3
#define k_s_dae_color_clear    4
#define k_s_dae_depth_clear    5
#define k_s_dae_stencil_clear  6
#define k_s_dae_draw           7

static ak_enumpair evaluateMap[] = {
  {_s_dae_color_target,   k_s_dae_color_target},
  {_s_dae_depth_target,   k_s_dae_depth_target},
  {_s_dae_stencil_target, k_s_dae_stencil_target},
  {_s_dae_color_clear,    k_s_dae_color_clear},
  {_s_dae_depth_clear,    k_s_dae_depth_clear},
  {_s_dae_stencil_clear,  k_s_dae_stencil_clear},
  {_s_dae_draw,           k_s_dae_draw}
};

static size_t evaluateMapLen = 0;

AkResult _assetkit_hide
dae_fxEvaluate(AkXmlState * __restrict xst,
               void * __restrict memParent,
               AkEvaluate ** __restrict dest) {
  AkEvaluate   *evaluate;
  AkXmlElmState xest;

  evaluate = ak_heap_calloc(xst->heap,
                            memParent,
                            sizeof(*evaluate));

  if (evaluateMapLen == 0) {
    evaluateMapLen = AK_ARRAY_LEN(evaluateMap);
    qsort(evaluateMap,
          evaluateMapLen,
          sizeof(evaluateMap[0]),
          ak_enumpair_cmp);
  }

  ak_xest_init(xest, _s_dae_evaluate)

  do {
    const ak_enumpair *found;

    if (ak_xml_begin(&xest))
      break;

    found = bsearch(xst->nodeName,
                    evaluateMap,
                    evaluateMapLen,
                    sizeof(evaluateMap[0]),
                    ak_enumpair_cmp2);
    if (!found) {
      ak_xml_skipelm(xst);
      goto skip;
    }

    switch (found->val) {
      case k_s_dae_color_target:
      case k_s_dae_depth_target:
      case k_s_dae_stencil_target: {
        AkEvaluateTarget *evaluate_target;
        const xmlChar    *targetNodeName;
        AkXmlElmState     xest2;

        evaluate_target = ak_heap_calloc(xst->heap,
                                         evaluate,
                                         sizeof(*evaluate_target));

        evaluate_target->index = ak_xml_attrui(xst, _s_dae_index);
        evaluate_target->slice = ak_xml_attrui(xst, _s_dae_slice);
        evaluate_target->mip   = ak_xml_attrui(xst, _s_dae_mip);

        evaluate_target->face  = ak_xml_attrenum(xst,
                                                 _s_dae_face,
                                                 dae_fxEnumFace);

        targetNodeName = xst->nodeName;

        ak_xest_init(xest2, (char *)targetNodeName)

        do {
          if (ak_xml_begin(&xest2))
            break;

          if (ak_xml_eqelm(xst, _s_dae_param)) {
            AkParam * param;
            AkResult   ret;

            ret = dae_param(xst, evaluate_target,  &param);

            if (ret == AK_OK)
              evaluate_target->param = param;
          } else if (ak_xml_eqelm(xst, _s_dae_instance_image)) {
            AkInstanceBase *instanceImage;
            AkResult        ret;

            ret = dae_fxInstanceImage(xst,
                                      evaluate_target,
                                      &instanceImage);

            if (ret == AK_OK)
              evaluate_target->instanceImage = instanceImage;
          } else {
            ak_xml_skipelm(xst);
          }

          /* end element */
          if (ak_xml_end(&xest2))
            break;
        } while (xst->nodeRet);

        switch (found->val) {
          case k_s_dae_color_target:
            evaluate->colorTarget = evaluate_target;
            break;
          case k_s_dae_depth_target:
            evaluate->depthTarget = evaluate_target;
            break;
          case k_s_dae_stencil_target:
            evaluate->stencilTarget = evaluate_target;
            break;
          default: break;
        }
      }
      case k_s_dae_color_clear: {
        AkColorClear *colorClear;
        colorClear = ak_heap_calloc(xst->heap,
                                    evaluate,
                                    sizeof(*colorClear));

        colorClear->index = ak_xml_attrui(xst, _s_dae_index);

        dae_color(xst, colorClear, false, false, &colorClear->val);

        evaluate->colorClear = colorClear;
        break;
      }
      case k_s_dae_depth_clear:{
        AkDepthClear *depthClear;
        depthClear = ak_heap_calloc(xst->heap,
                                    evaluate,
                                    sizeof(*depthClear));

        depthClear->index = ak_xml_attrui(xst, _s_dae_index);
        depthClear->val   = ak_xml_valf(xst);

        evaluate->depthClear = depthClear;
        break;
      }
      case k_s_dae_stencil_clear:{
        AkStencilClear *stencilClear;
        stencilClear = ak_heap_calloc(xst->heap,
                                      evaluate,
                                      sizeof(*stencilClear));

        stencilClear->index = ak_xml_attrui(xst, _s_dae_index);
        stencilClear->val   = ak_xml_valul(xst);

        evaluate->stencilClear = stencilClear;
        break;
      }
      case k_s_dae_draw: {
        const char *strVal;
        
        if ((strVal = ak_xml_val(xst, evaluate))) {
          evaluate->draw.strVal = strVal;
          evaluate->draw.enumDraw = dae_fxEnumDraw(strVal);
        }
      }
      default:
         ak_xml_skipelm(xst);
        break;
    }

  skip:
    /* end element */
    if (ak_xml_end(&xest))
      break;
  } while (xst->nodeRet);

  *dest = evaluate;
  
  return AK_OK;
}
