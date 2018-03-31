/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ak_transform_h
#define ak_transform_h
#ifdef __cplusplus
extern "C" {
#endif

typedef enum AkTransformType {
  AK_TRANSFORM_LOOKAT    = 1,
  AK_TRANSFORM_MATRIX    = 2,
  AK_TRANSFORM_ROTATE    = 3,
  AK_TRANSFORM_SCALE     = 4,
  AK_TRANSFORM_SKEW      = 5,
  AK_TRANSFORM_TRANSLATE = 6,
  AK_TRANSFORM_QUAT      = 7 /* quaternion */
} AkTransformType;

typedef struct AkTransform {
  AkObject *base; /* fixup transform */
  AkObject *item;
} AkTransform;

typedef struct AkLookAt {
  /* const char * sid; */

  AkFloat3     val[3];
} AkLookAt;

typedef struct AkMatrix {
  /* const char * sid; */

  AK_ALIGN(16) AkFloat val[4][4];
} AkMatrix;

typedef struct AkRotate {
  /* const char * sid; */
  AK_ALIGN(16) AkFloat val[4];
} AkRotate;

typedef struct AkScale {
  /* const char * sid; */
  AkFloat      val[3];
} AkScale;

typedef struct AkSkew {
  /* const char * sid; */
  AkFloat      angle;
  AkFloat3     rotateAxis;
  AkFloat3     aroundAxis;
} AkSkew;

typedef struct AkTranslate {
  /* const char * sid; */
  AkFloat      val[3];
} AkTranslate;

typedef struct AkQuaternion {
  AK_ALIGN(16) AkFloat val[4];
} AkQuaternion;

/*!
 * @brief build skew matrix from AkSkew
 *
 * @param skew   skew element
 * @param matrix skew matrix (must be aligned 16)
 */
AK_EXPORT
void
ak_transformSkewMatrix(AkSkew * __restrict skew,
                       float  * matrix);

/*!
 * @brief combines all node's transform elements
 *
 * if there is no transform then this returns identity matrix
 *
 * @param node   node
 * @param matrix combined transform (must be aligned 16)
 */
AK_EXPORT
void
ak_transformCombine(AkNode * __restrict node,
                    float  * matrix);

/*!
 * @brief combines all node's transform elements in **world coord sys**
 *
 * this func walks/traverses to top node to get world coord
 * this is not cheap op, obviously.
 *
 * @param node   node
 * @param matrix combined transform (must be aligned 16)
 */
AK_EXPORT
void
ak_transformCombineWorld(AkNode * __restrict node,
                         float  * matrix);

/*!
 * @brief duplicate all transforms of node1 to node2
 * 
 * @warning duplicated transform will alloc extra memory
 */
AK_EXPORT
void
ak_transformDup(AkNode * __restrict srcNode,
                AkNode * __restrict destNode);

AK_EXPORT
void
ak_transformFreeBase(AkTransform * __restrict transform);

#ifdef __cplusplus
}
#endif
#endif /* ak_transform_h */
