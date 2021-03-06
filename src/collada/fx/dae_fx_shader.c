/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "dae_fx_shader.h"
#include "dae_fx_enums.h"
#include "dae_fx_binary.h"
#include "dae_fx_uniform.h"

AkResult _assetkit_hide
dae_fxShader(AkXmlState * __restrict xst,
             void * __restrict memParent,
             AkShader ** __restrict dest) {
  AkShader      *shader;
  AkCompiler    *last_compiler;
  AkBindUniform *last_bind_uniform;
  AkXmlElmState  xest;

  shader = ak_heap_calloc(xst->heap,
                          memParent,
                          sizeof(*shader));

  shader->stage = ak_xml_attrenum(xst,
                                  _s_dae_stage,
                                  dae_fxEnumShaderStage);

  last_compiler     = NULL;
  last_bind_uniform = NULL;

  ak_xest_init(xest, _s_dae_shader)

  do {
    if (ak_xml_begin(&xest))
      break;

    if (ak_xml_eqelm(xst, _s_dae_sources)) {
      AkSources    *sources;
      AkInline     *last_inline;
      AkImport     *last_import;
      AkXmlElmState xest2;

      sources = ak_heap_calloc(xst->heap,
                               shader,
                               sizeof(*sources));
      sources->entry = ak_xml_attr(xst, sources, _s_dae_entry);

      last_inline = NULL;
      last_import = NULL;

      ak_xest_init(xest2, _s_dae_sources)

      do {
        if (ak_xml_begin(&xest2))
          break;

        if (ak_xml_eqelm(xst, _s_dae_inline)) {
          AkInline *nInline;

          nInline = ak_heap_calloc(xst->heap,
                                   shader,
                                   sizeof(*nInline));
           nInline->val = ak_xml_val(xst, nInline);

          if (last_inline)
            last_inline->next = nInline;
          else
            sources->inlines = nInline;

          last_inline = nInline;
        } else if (ak_xml_eqelm(xst, _s_dae_import)) {
          AkImport *nImport;

          nImport = ak_heap_calloc(xst->heap,
                                   shader,
                                   sizeof(*nImport));
          nImport->ref = ak_xml_val(xst, nImport);

          if (last_import)
            last_import->next = nImport;
          else
            sources->imports = nImport;

          last_import = nImport;
        } else {
          ak_xml_skipelm(xst);
        }
        
        /* end element */
        if (ak_xml_end(&xest2))
          break;
      } while (xst->nodeRet);

      shader->sources = sources;
    } else if (ak_xml_eqelm(xst, _s_dae_compiler)) {
      AkCompiler   *compiler;
      AkXmlElmState xest2;

      compiler = ak_heap_calloc(xst->heap,
                                shader,
                                sizeof(*compiler));

      compiler->platform = ak_xml_attr(xst, compiler, _s_dae_platform);
      compiler->target   = ak_xml_attr(xst, compiler, _s_dae_target);
      compiler->options  = ak_xml_attr(xst, compiler, _s_dae_options);

      ak_xest_init(xest2, _s_dae_compiler)

      do {
        if (ak_xml_begin(&xest2))
          break;

        if (ak_xml_eqelm(xst, _s_dae_binary)) {
          AkBinary *binary;
          AkResult  ret;

          ret = dae_fxBinary(xst, compiler, &binary);
          if (ret == AK_OK)
            compiler->binary = binary;
        } else {
          ak_xml_skipelm(xst);
        }

        /* end element */
        if (ak_xml_end(&xest2))
          break;
      } while (xst->nodeRet);

      if (last_compiler)
        last_compiler->next = compiler;
      else
        shader->compiler = compiler;

      last_compiler = compiler;
    } else if (ak_xml_eqelm(xst, _s_dae_bind_uniform)) {
      AkBindUniform *bindUniform;
      AkResult ret;

      ret = dae_fxBindUniform(xst, shader, &bindUniform);
      if (ret == AK_OK) {
        if (last_bind_uniform)
          last_bind_uniform->next = bindUniform;
        else
          shader->bindUniform = bindUniform;

        last_bind_uniform = bindUniform;
      }
    } else if (ak_xml_eqelm(xst, _s_dae_extra)) {
      dae_extra(xst, shader, &shader->extra);
    } else {
      ak_xml_skipelm(xst);
    }

    /* end element */
    if (ak_xml_end(&xest))
      break;
  } while (xst->nodeRet);

  *dest = shader;
  
  return AK_OK;
}
