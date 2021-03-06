/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "dae_accessor.h"
#include "dae_param.h"

#include <ds/forward-list-sep.h>

AkResult _assetkit_hide
dae_accessor(AkXmlState * __restrict xst,
             void * __restrict memParent,
             AkAccessor ** __restrict dest) {
  AkAccessor   *accessor;
  AkDataParam  *last_param;
  AkXmlElmState xest;
  uint32_t      paramOffset;

  accessor = ak_heap_calloc(xst->heap,
                            memParent,
                            sizeof(*accessor));

  accessor->count  = ak_xml_attrui(xst, _s_dae_count);
  accessor->offset = ak_xml_attrui(xst, _s_dae_offset);
  accessor->stride = ak_xml_attrui_def(xst, _s_dae_stride, 1);

  ak_xml_attr_url(xst,
                  _s_dae_source,
                  accessor,
                  &accessor->source);

  ak_setypeid(accessor, AKT_ACCESSOR);

  if (xmlTextReaderIsEmptyElement(xst->reader))
    goto done;

  last_param  = NULL;
  paramOffset = 0;

  ak_xest_init(xest, _s_dae_accessor)

  do {
    if (ak_xml_begin(&xest))
      break;

    if (ak_xml_eqelm(xst, _s_dae_param)) {
      AkDataParam *dataParam;
      AkResult     ret;

      ret = dae_dataparam(xst, accessor, &dataParam);
      if (ret == AK_OK) {
        if (last_param)
          last_param->next = dataParam;
        else
          accessor->param = dataParam;

        last_param = dataParam;

        if (dataParam->name) {
          accessor->bound++;
          dataParam->offset = paramOffset++;
        }
      }
    }

    /* end element */
    if (ak_xml_end(&xest))
      break;
  } while (xst->nodeRet);

done:
  *dest = accessor;

  /* append accessor to global list */
  flist_sp_insert(&xst->accessors, accessor);

  return AK_OK;
}
