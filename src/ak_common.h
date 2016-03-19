/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ak_common_h
#define ak_common_h

#include "../include/assetkit.h"
#include <stddef.h>
#include <sys/types.h>
#include <string.h>

#ifdef _MSC_VER
#  define strncasecmp _strnicmp
#  define strcasecmp _stricmp
#endif

#ifdef __GNUC__
#  define ak_DESTRUCTOR __attribute__((destructor))
#  define ak_CONSTRUCTOR __attribute__((constructor))
#else
#  define ak_DESTRUCTOR
#  define ak_CONSTRUCTOR
#endif

typedef struct ak_enumpair_s ak_enumpair;
struct ak_enumpair_s {
  const char * key;
  AkEnum val;
};

int _assetkit_hide
ak_enumpair_cmp(const void * a, const void * b);

int _assetkit_hide
ak_enumpair_cmp2(const void * a, const void * b);

#endif /* ak_common_h */
