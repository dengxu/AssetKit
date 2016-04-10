/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "ak_collada_skin.h"
#include "../../ak_array.h"
#include "ak_collada_source.h"
#include "ak_collada_enums.h"

AkResult _assetkit_hide
ak_dae_skin(void * __restrict memParent,
            xmlTextReaderPtr reader,
            bool asObject,
            AkSkin ** __restrict dest) {
  AkObject       *obj;
  AkSkin         *skin;
  AkSource       *last_source;
  void           *memPtr;
  const xmlChar  *nodeName;
  int             nodeType;
  int             nodeRet;

  if (asObject) {
    obj = ak_objAlloc(memParent,
                      sizeof(*skin),
                      0,
                      true);

    skin = ak_objGet(obj);

    memPtr = obj;
  } else {
    skin = ak_calloc(memParent, sizeof(*skin), 1);
    memPtr = skin;
  }

  _xml_readAttr(skin, skin->baseMesh, _s_dae_source);

  last_source = NULL;

  do {
    _xml_beginElement(_s_dae_skin);

    if (_xml_eqElm(_s_dae_bind_shape_matrix)) {
      char *content;
      _xml_readMutText(content);

      if (content) {
        AkDoubleArray *doubleArray;
        AkResult ret;

        ret = ak_strtod_array(skin, content, &doubleArray);
        if (ret == AK_OK)
          skin->bindShapeMatrix = doubleArray;
      }
    } else if (_xml_eqElm(_s_dae_source)) {
      AkSource *source;
      AkResult ret;

      ret = ak_dae_source(skin, reader, &source);
      if (ret == AK_OK) {
        if (last_source)
          last_source->next = source;
        else
          skin->source = source;

        last_source = source;
      }
    } else if (_xml_eqElm(_s_dae_joints)) {
      AkJoints     *joints;
      AkInputBasic *last_input;

      joints = ak_calloc(skin, sizeof(*joints), 1);

      last_input = NULL;

      do {
        _xml_beginElement(_s_dae_joints);

        if (_xml_eqElm(_s_dae_input)) {
          AkInputBasic *input;

          input = ak_calloc(joints, sizeof(*input), 1);

          _xml_readAttr(input, input->semanticRaw, _s_dae_semantic);
          _xml_readAttr(input, input->source, _s_dae_source);

          if (!input->semanticRaw || !input->source)
            ak_free(input);
          else {
            AkEnum inputSemantic;
            inputSemantic = ak_dae_enumInputSemantic(input->semanticRaw);

            if (inputSemantic < 0)
              inputSemantic = AK_INPUT_SEMANTIC_OTHER;

            input->semantic = inputSemantic;
          }

          if (last_input)
            last_input->next = input;
          else
            joints->input = input;

          last_input = input;
        } else if (_xml_eqElm(_s_dae_extra)) {
          xmlNodePtr nodePtr;
          AkTree   *tree;

          nodePtr = xmlTextReaderExpand(reader);
          tree = NULL;

          ak_tree_fromXmlNode(joints, nodePtr, &tree, NULL);
          joints->extra = tree;

          _xml_skipElement;

        } else {
          _xml_skipElement;
        }
        
        /* end element */
        _xml_endElement;
      } while (nodeRet);
      
      skin->joints = joints;
    } else if (_xml_eqElm(_s_dae_vertex_weights)) {
      AkVertexWeights *vertexWeights;
      AkInput         *last_input;

      vertexWeights = ak_calloc(skin, sizeof(*vertexWeights), 1);

      last_input = NULL;

      do {
        _xml_beginElement(_s_dae_vertex_weights);

        if (_xml_eqElm(_s_dae_input)) {
          AkInput *input;
          input = ak_calloc(vertexWeights, sizeof(*input), 1);

          _xml_readAttr(input, input->base.semanticRaw, _s_dae_semantic);
          _xml_readAttr(input, input->base.source, _s_dae_source);

          if (!input->base.semanticRaw || !input->base.source)
            ak_free(input);
          else {
            AkEnum inputSemantic;
            inputSemantic = ak_dae_enumInputSemantic(input->base.semanticRaw);

            if (inputSemantic < 0)
              inputSemantic = AK_INPUT_SEMANTIC_OTHER;

            input->base.semantic = inputSemantic;
          }

          _xml_readAttrUsingFn(input->offset,
                               _s_dae_offset,
                               strtoul, NULL, 10);

          _xml_readAttrUsingFn(input->set,
                               _s_dae_set,
                               strtoul, NULL, 10);

          if (last_input)
            last_input->base.next = &input->base;
          else
            vertexWeights->input = input;
          
          last_input = input;
        } else if (_xml_eqElm(_s_dae_vcount)) {
          char *content;
          _xml_readMutText(content);

          if (content) {
            AkIntArray *intArray;
            AkResult    ret;

            ret = ak_strtoi_array(vertexWeights, content, &intArray);
            if (ret == AK_OK)
              vertexWeights->vcount = intArray;
            
            xmlFree(content);
          }
        } else if (_xml_eqElm(_s_dae_v)) {
          char *content;
          _xml_readMutText(content);

          if (content) {
            AkDoubleArray *doubleArray;
            AkResult       ret;

            ret = ak_strtod_array(vertexWeights, content, &doubleArray);
            if (ret == AK_OK)
              vertexWeights->v = doubleArray;

            xmlFree(content);
          }
        } else if (_xml_eqElm(_s_dae_extra)) {
          xmlNodePtr nodePtr;
          AkTree   *tree;

          nodePtr = xmlTextReaderExpand(reader);
          tree = NULL;

          ak_tree_fromXmlNode(vertexWeights, nodePtr, &tree, NULL);
          vertexWeights->extra = tree;

          _xml_skipElement;

        } else {
          _xml_skipElement;
        }
        
        /* end element */
        _xml_endElement;
      } while (nodeRet);
      
      skin->vertexWeights = vertexWeights;
    } else if (_xml_eqElm(_s_dae_extra)) {
      xmlNodePtr nodePtr;
      AkTree   *tree;

      nodePtr = xmlTextReaderExpand(reader);
      tree = NULL;

      ak_tree_fromXmlNode(skin, nodePtr, &tree, NULL);
      skin->extra = tree;

      _xml_skipElement;
    } else {
      _xml_skipElement;
    }

    /* end element */
    _xml_endElement;
  } while (nodeRet);

  *dest = skin;
  
  return AK_OK;
}