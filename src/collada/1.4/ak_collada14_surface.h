/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ak_surface_h
#define ak_surface_h

#include "../../../include/assetkit.h"
#include "../ak_collada_common.h"
#include "ak_collada14.h"

AkResult _assetkit_hide
ak_dae14_fxSurface(AkXmlState      * __restrict xst,
                   void            * __restrict memParent,
                   AkDae14Surface ** __restrict dest);

#endif /* ak_surface_h */
