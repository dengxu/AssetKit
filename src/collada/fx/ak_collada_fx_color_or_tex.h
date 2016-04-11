/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libassetkit__ak_collada_color_or_tex__h_
#define __libassetkit__ak_collada_color_or_tex__h_

#include "../../../include/assetkit.h"
#include "../ak_collada_common.h"

AkResult _assetkit_hide
ak_dae_colorOrTex(void * __restrict memParent,
                   xmlTextReaderPtr reader,
                   const char * elm,
                   AkFxColorOrTex ** __restrict dest);

#endif /* __libassetkit__ak_collada_color_or_tex__h_ */
