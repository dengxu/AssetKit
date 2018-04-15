/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "dae_vertices.h"
#include "dae_enums.h"

AkResult _assetkit_hide
ak_dae_vertices(AkXmlState * __restrict xst,
                void * __restrict memParent,
                AkVertices ** __restrict dest) {
  AkVertices   *vertices;
  AkInputBasic *last_input;
  AkXmlElmState xest;

  vertices = ak_heap_calloc(xst->heap,
                            memParent,
                            sizeof(*vertices));

  ak_xml_readid(xst, vertices);
  vertices->name = ak_xml_attr(xst, vertices, _s_dae_name);

  last_input = NULL;

  ak_xest_init(xest, _s_dae_vertices)

  do {
    if (ak_xml_begin(&xest))
      break;

    if (ak_xml_eqelm(xst, _s_dae_input)) {
      AkInputBasic *input;

      input = ak_heap_calloc(xst->heap, vertices, sizeof(*input));

      input->semanticRaw = ak_xml_attr(xst, input, _s_dae_semantic);

      ak_xml_attr_url(xst,
                      _s_dae_source,
                      input,
                      &input->source);

      if (!input->semanticRaw || !input->source.url) {
        ak_free(input);
      } else {
        input->semantic = ak_dae_enumInputSemantic(input->semanticRaw);

        if (last_input)
          last_input->next = input;
        else
          vertices->input = input;

        last_input = input;

        vertices->inputCount++;
      }
    } else if (ak_xml_eqelm(xst, _s_dae_extra)) {
      xmlNodePtr nodePtr;
      AkTree   *tree;

      nodePtr = xmlTextReaderExpand(xst->reader);
      tree = NULL;

      ak_tree_fromXmlNode(xst->heap,
                          vertices,
                          nodePtr,
                          &tree,
                          NULL);
      vertices->extra = tree;

      ak_xml_skipelm(xst);
    }

    /* end element */
    if (ak_xml_end(&xest))
      break;
  } while (xst->nodeRet);

  *dest = vertices;

  return AK_OK;
}