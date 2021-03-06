/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "dae_geometry.h"
#include "../core/dae_asset.h"
#include "dae_mesh.h"
#include "dae_spline.h"
#include "../brep/dae_brep.h"

AkResult _assetkit_hide
dae_geometry(AkXmlState * __restrict xst,
             void       * __restrict memParent,
             void      ** __restrict dest) {
  AkGeometry   *geometry;
  AkXmlElmState xest;

  geometry = ak_heap_calloc(xst->heap,
                            memParent,
                            sizeof(*geometry));
  geometry->materialMap = ak_map_new(ak_cmp_str);

  /* destroy heap with this object */
  ak_setAttachedHeap(geometry,
                     geometry->materialMap->heap);

  ak_xml_readid(xst, geometry);
  geometry->name = ak_xml_attr(xst, geometry, _s_dae_name);

  ak_setypeid(geometry, AKT_GEOMETRY);
  ak_xest_init(xest, _s_dae_geometry)

  do {
    if (ak_xml_begin(&xest))
      break;

    if (ak_xml_eqelm(xst, _s_dae_asset)) {
      (void)dae_assetInf(xst, geometry, NULL);
    } else if (ak_xml_eqelm(xst, _s_dae_mesh)
               || ak_xml_eqelm(xst, _s_dae_convex_mesh)) {
      AkMesh  *mesh;
      AkResult ret;

      ret = dae_mesh(xst,
                     geometry,
                     (const char *)xst->nodeName,
                     &mesh,
                     true);
      if (ret == AK_OK)
        geometry->gdata = ak_objFrom(mesh);

    } else if (ak_xml_eqelm(xst, _s_dae_spline)) {
      AkSpline *spline;
      AkResult  ret;

      ret = dae_spline(xst, geometry, true, &spline);
      if (ret == AK_OK)
        geometry->gdata = ak_objFrom(spline);

    } else if (ak_xml_eqelm(xst, _s_dae_brep)) {
      AkBoundryRep *brep;
      AkResult      ret;

      ret = dae_brep(xst, geometry, true, &brep);
      if (ret == AK_OK)
        geometry->gdata = ak_objFrom(brep);

    } else if (ak_xml_eqelm(xst, _s_dae_extra)) {
      dae_extra(xst, geometry, &geometry->extra);
    }

    /* end element */
    if (ak_xml_end(&xest))
      break;
  } while (xst->nodeRet);
  
  *dest = geometry;
  
  return AK_OK;
}
