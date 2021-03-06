/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "dae_fx_technique.h"

#include "../core/dae_asset.h"
#include "../core/dae_annotate.h"

#include "../1.4/dae14_image.h"

#include "dae_fx_blinn_phong.h"
#include "dae_fx_constant.h"
#include "dae_fx_lambert.h"
#include "dae_fx_pass.h"

AkResult _assetkit_hide
dae_techniqueFx(AkXmlState * __restrict xst,
                void * __restrict memParent,
                AkTechniqueFx ** __restrict dest) {
  AkTechniqueFx *technique;
  AkAnnotate    *last_annotate;
  AkXmlElmState  xest;

  technique = ak_heap_calloc(xst->heap,
                             memParent,
                             sizeof(*technique));
  ak_setypeid(technique, AKT_TECHNIQUE_FX);

  ak_xml_readid(xst, technique);
  ak_xml_readsid(xst, technique);

  last_annotate = NULL;

  ak_xest_init(xest, _s_dae_technique)

  do {
    if (ak_xml_begin(&xest))
      break;

    if (ak_xml_eqelm(xst, _s_dae_asset)) {
      (void)dae_assetInf(xst, technique, NULL);
    } else if (ak_xml_eqelm(xst, _s_dae_annotate)) {
      AkAnnotate *annotate;
      AkResult    ret;

      ret = dae_annotate(xst, technique, &annotate);

      if (ret == AK_OK) {
        if (last_annotate)
          last_annotate->next = annotate;
        else
          technique->annotate = annotate;

        last_annotate = annotate;
      }
    } else if (ak_xml_eqelm(xst, _s_dae_pass)) {
      AkPass * pass;
      AkResult ret;

      ret = dae_fxPass(xst, technique, &pass);
      if (ret == AK_OK)
        technique->pass = pass;

    }  else if (ak_xml_eqelm(xst, _s_dae_phong)) {
      AkTechniqueFxCommon *phong;
      AkResult             ret;

      ret = dae_phong(xst,
                      technique,
                      (const char *)xst->nodeName,
                      &phong);
      if (ret == AK_OK) {
        phong->type        = AK_MATERIAL_PHONG;
        technique->common = phong;
      }
    } else if (ak_xml_eqelm(xst, _s_dae_blinn)) {
      AkTechniqueFxCommon *blinn;
      AkResult             ret;

      ret = dae_phong(xst,
                      technique,
                      (const char *)xst->nodeName,
                      &blinn);
      if (ret == AK_OK) {
        blinn->type       = AK_MATERIAL_BLINN;
        technique->common = blinn;
      }
    } else if (ak_xml_eqelm(xst, _s_dae_lambert)) {
      AkTechniqueFxCommon *lambert;
      AkResult             ret;

      ret = dae_fxLambert(xst, technique, &lambert);
      if (ret == AK_OK) {
        lambert->type     = AK_MATERIAL_LAMBERT;
        technique->common = lambert;
      }
    } else if (ak_xml_eqelm(xst, _s_dae_constant)) {
      AkTechniqueFxCommon *constantfx;
      AkResult             ret;

      ret = dae_fxConstant(xst, technique, &constantfx);
      if (ret == AK_OK) {
        constantfx->type  = AK_MATERIAL_CONSTANT;
        technique->common = constantfx;
      }
    } else if (xst->version < AK_COLLADA_VERSION_150
               && ak_xml_eqelm(xst, _s_dae_image)) {
      /* migration from 1.4 */
      dae14_fxMigrateImg(xst, NULL);
    } else if (ak_xml_eqelm(xst, _s_dae_extra)) {
      dae_extra(xst, technique, &technique->extra);
    } else {
      ak_xml_skipelm(xst);
    }

    /* end element */
    if (ak_xml_end(&xest))
      break;
  } while (xst->nodeRet);
  
  *dest = technique;
  
  return AK_OK;
}
