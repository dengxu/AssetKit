/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ak_geom_h
#define ak_geom_h
#ifdef __cplusplus
extern "C" {
#endif

#include "map.h"
#include "bbox.h"
#include "map.h"

struct RBTree;
struct AkGeometry;
struct AkMesh;

typedef enum AkGeometryType {
  AK_GEOMETRY_TYPE_MESH   = 0,
  AK_GEOMETRY_TYPE_SPLINE = 1,
  AK_GEOMETRY_TYPE_BREP   = 2
} AkGeometryType;

typedef enum AkGeometryEditFlags {
  AK_GEOM_EDIT_FLAG_ARRAYS  = 1,
  AK_GEOM_EDIT_FLAG_INDICES = 2,
  AK_GEOM_EDIT_FLAG_MUTEX   = 3
} AkGeometryEditFlags;

typedef enum AkMeshPrimitiveType {
  AK_MESH_PRIMITIVE_TYPE_LINES      = 1,
  AK_MESH_PRIMITIVE_TYPE_POLYGONS   = 2,
  AK_MESH_PRIMITIVE_TYPE_TRIANGLES  = 3,
  AK_MESH_PRIMITIVE_TYPE_POINTS     = 4
} AkMeshPrimitiveType;

typedef enum AkTriangleMode {
  AK_TRIANGLE_MODE_TRIANGLES      = 0,
  AK_TRIANGLE_MODE_TRIANGLE_STRIP = 1,
  AK_TRIANGLE_MODE_TRIANGLE_FAN   = 2
} AkTriangleMode;

typedef enum AkLineMode {
  AK_LINE_MODE_LINES      = 0,
  AK_LINE_MODE_LINE_LOOP  = 1,
  AK_LINE_MODE_LINE_STRIP = 2
} AkLineMode;

typedef enum AkPolygonMode {
  AK_POLYGON_MODE_POLYLIST = 0,
  AK_POLYGON_MODE_POLYGONS = 1
} AkPolygonMode;

typedef struct AkVertices {
  /* const char   * id; */
  const char   *name;
  AkTree       *extra;
  AkInput      *input;
  uint32_t      inputCount;
} AkVertices;

typedef struct AkMeshPrimitive {
  AkMeshPrimitiveType     type;
  struct AkMesh          *mesh;
  AkBoundingBox          *bbox; /* per-primitive bbox */
  const char             *name;
  const char             *material;
  AkInput                *input;
  AkInput                *pos;
  AkUIntArray            *indices;
  AkTree                 *extra;
  void                   *udata;
  struct AkMeshPrimitive *next;
  uint32_t                count;
  uint32_t                inputCount;
  uint32_t                indexStride;
  uint32_t                reserved1; /* private member */
  uint32_t                reserved2; /* private member */
  void                   *reserved3;
  AkFloat3                center;
} AkMeshPrimitive;

typedef struct AkLines {
  AkMeshPrimitive base;
  AkLineMode      mode;
} AkLines;

typedef struct AkPolygon {
  AkMeshPrimitive base;
  AkDoubleArrayL *holes;
  AkUIntArray    *vcount;
  AkPolygonMode   mode;
  AkBool          haveHoles;
} AkPolygon;

typedef struct AkTriangles {
  AkMeshPrimitive base;
  AkTriangleMode  mode;
} AkTriangles;

typedef struct AkMeshEditHelper {
  AkGeometryEditFlags flags;
  struct RBTree      *buffers;         /* new buffers               */
  struct RBTree      *indices;         /* new indices               */
  AkMap              *inputBufferMap;  /* input-accessor-buffer map */
  void               *mutex;
  void               *duplicator;
  size_t              refc;
} AkMeshEditHelper;

typedef struct AkMesh {
  struct AkGeometry *geom;
  const char        *convexHullOf;
  AkSource          *source;
  AkMeshPrimitive   *primitive;
  AkBoundingBox     *bbox;
  AkTree            *extra;
  AkMeshEditHelper  *edith;
  uint32_t           primitiveCount;
  AkFloat3           center;
} AkMesh;

typedef struct AkControlVerts {
  AkInput *input;
  AkTree  *extra;
} AkControlVerts;

typedef struct AkSpline {
  AkSource       *source;
  AkControlVerts *cverts;
  AkTree         *extra;
  AkBool          closed;
} AkSpline;

typedef struct AkLine {
  AkFloat3 origin;
  AkFloat3 direction;
  AkTree  *extra;
} AkLine;

typedef struct AkCircle {
  AkFloat radius;
  AkTree *extra;
} AkCircle;

typedef struct AkEllipse {
  AkFloat2 radius;
  AkTree  *extra;
} AkEllipse;

typedef struct AkParabola {
  AkFloat focal;
  AkTree *extra;
} AkParabola;

typedef struct AkHyperbola {
  AkFloat2 radius;
  AkTree  *extra;
} AkHyperbola;

typedef struct AkNurbs {
  AkSource       *source;
  AkControlVerts *cverts;
  AkTree         *extra;
  AkUInt          degree;
  AkBool          closed;
} AkNurbs;

typedef struct AkCurve {
  AkFloatArrayL *orient;
  AkFloat3       origin;
  AkObject       *curve;
  struct AkCurve *next;
} AkCurve;

typedef struct AkCurves {
  AkCurve *curve;
  AkTree  *extra;
} AkCurves;

typedef struct AkCone {
  AkFloat radius;
  AkFloat angle;
  AkTree *extra;
} AkCone;

typedef struct AkPlane {
  AkFloat4 equation;
  AkTree  *extra;
} AkPlane;

typedef struct AkCylinder {
  AkFloat2 radius;
  AkTree  *extra;
} AkCylinder;

typedef struct AkNurbsSurface {
  AkSource       *source;
  AkControlVerts *cverts;
  AkTree         *extra;
  AkUInt          degree_u;
  AkUInt          degree_v;
  AkBool          closed_u;
  AkBool          closed_v;
} AkNurbsSurface;

typedef struct AkSphere {
  AkFloat radius;
  AkTree *extra;
} AkSphere;

typedef struct AkTorus {
  AkFloat2 radius;
  AkTree * extra;
} AkTorus;

typedef struct AkSweptSurface {
  AkCurve *curve;
  AkFloat3 direction;
  AkFloat3 origin;
  AkFloat3 axis;
  AkTree  *extra;
} AkSweptSurface;

typedef struct AkSurface {
  /* const char * sid; */

  const char       *name;
  AkObject         *surface;
  AkFloatArrayL    *orient;
  AkFloat3          origin;
  struct AkSurface *next;
} AkSurface;

typedef struct AkSurfaces {
  AkSurface *surface;
  AkTree    *extra;
} AkSurfaces;

typedef struct AkEdges {
  /* const char    * id; */
  const char    *name;
  AkInput       *input;
  AkUIntArray   *primitives;
  AkTree        *extra;
  AkUInt         count;
} AkEdges;

typedef struct AkWires {
  /* const char    * id; */
  const char  *name;
  AkInput     *input;
  AkUIntArray *vcount;
  AkUIntArray *primitives;
  AkTree      *extra;
  AkUInt       count;
} AkWires;

typedef struct AkFaces {
  /* const char    * id; */
  const char  *name;
  AkInput     *input;
  AkUIntArray *vcount;
  AkUIntArray *primitives;
  AkTree      *extra;
  AkUInt       count;
} AkFaces;

typedef struct AkPCurves {
  /* const char    * id; */
  const char  *name;
  AkInput     *input;
  AkUIntArray *vcount;
  AkUIntArray *primitives;
  AkTree      *extra;
  AkUInt       count;
} AkPCurves;

typedef struct AkShells {
  /* const char    * id; */
  const char  *name;
  AkInput     *input;
  AkUIntArray *vcount;
  AkUIntArray *primitives;
  AkTree      *extra;
  AkUInt       count;
} AkShells;

typedef struct AkSolids {
  /* const char    * id; */
  const char  *name;
  AkInput     *input;
  AkUIntArray *vcount;
  AkUIntArray *primitives;
  AkTree      *extra;
  AkUInt       count;
} AkSolids;

typedef struct AkBoundryRep {
  AkCurves   * curves;
  AkCurves   * surfaceCurves;
  AkSurfaces * surfaces;
  AkSource   * source;
  AkVertices * vertices;
  AkEdges    * edges;
  AkWires    * wires;
  AkFaces    * faces;
  AkPCurves  * pcurves;
  AkShells   * shells;
  AkSolids   * solids;
  AkTree     * extra;
} AkBoundryRep;

typedef struct AkGeometry {
  /* const char * id; */
  const char        *name;
  AkObject          *gdata;
  AkTree            *extra;
  AkMap             *materialMap;
  AkBoundingBox     *bbox;
  struct AkGeometry *next;
} AkGeometry;

/*!
 * @brief Total input count except VERTEX input
 *
 * returns primitive.inputCount - 1 + primitive.vertices.inputCount
 *
 * @return total input count
 */
AK_EXPORT
uint32_t
ak_meshInputCount(AkMesh * __restrict mesh);

/*!
 * @brief set material (symbol) for primitive
 *        actual material will set with bind_material/instance material
 *
 * @param prim     mesh primitive
 * @param material material
 *
 * @return result
 */
AK_EXPORT
AkResult
ak_meshSetMaterial(AkMeshPrimitive *prim,
                   const char      *material);

/*!
 * @brief triangulate all mesh primitives
 *
 * @param mesh mesh
 *
 * @return new triangles/faces count
 */
AK_EXPORT
uint32_t
ak_meshTriangulate(AkMesh * __restrict mesh);

/*!
 * @brief triangulate polygon
 *
 * @param poly polygon primitive
 *
 * @return new triangles/faces count
 */
AK_EXPORT
uint32_t
ak_meshTriangulatePoly(AkPolygon * __restrict poly);

/*!
 * @brief returns true if least one primitive doesn't have normals
 *
 * @param mesh mesh
 *
 * @return boolean
 */
AK_EXPORT
bool
ak_meshNeedsNormals(AkMesh * __restrict mesh);

/*!
 * @brief returns true if primitive doesn't have normals
 *
 * @param prim primitive
 *
 * @return boolean
 */
AK_EXPORT
bool
ak_meshPrimNeedsNormals(AkMeshPrimitive * __restrict prim);

/*!
 * @brief generate normals for all pritimives of mesh
 *
 * @param mesh mesh
 */
AK_EXPORT
void
ak_meshGenNormals(AkMesh * __restrict mesh);

/*!
 * @brief prepare mesh for edit, or enable edit mode with default attribs
 *
 * @param mesh mesh
 */
AK_EXPORT
void
ak_meshBeginEdit(AkMesh * __restrict mesh);

/*!
 * @brief prepare mesh for edit, or enable edit mode
 *
 * @param mesh  meshs
 * @param flags flags needed while edit mode
 */
AK_EXPORT
void
ak_meshBeginEditA(AkMesh  * __restrict mesh,
                  AkGeometryEditFlags flags);

/*!
 * @brief finish edit, disable edit mode, relese allocated memory for editing
 *
 * @param mesh mesh
 */
AK_EXPORT
void
ak_meshEndEdit(AkMesh * __restrict mesh);

/*!
 * @brief this func returns array of input, because if you want to get array
 *        you need to traverse though input -> source -> technique -> array
 *
 * @param mesh  mesh
 * @param input input
 *
 * @return buffer object
 */
AK_EXPORT
AkObject*
ak_meshArrayOf(AkMesh   * __restrict mesh,
               AkInput  * __restrict input);

/*!
 * @brief collect buffer infos, altername would be ak_meshArrayInfos
 *        this function collects buffer usage (count, stride) in specified mesh
 *        this is useful for shrink buffer
 *
 * @param[in]  mesh     mesh
 * @param[in]  arrayURL buffer URL
 * @param[out] stride   stride (for mesh)
 * @param[out] count    count  (for mesh)
 */
void
ak_meshInspectArray(AkMesh   * __restrict mesh,
                    AkURL    * __restrict arrayURL,
                    uint32_t * __restrict stride,
                    size_t   * __restrict count);

AK_EXPORT
AkUIntArray*
ak_meshIndicesArrayFor(AkMesh          * __restrict mesh,
                       AkMeshPrimitive * __restrict prim,
                       bool                         readonly);

AK_EXPORT
AkSourceBuffState*
ak_meshReserveBuffer(AkMesh * __restrict mesh,
                     void   * __restrict buffid,
                     size_t              itemSize,
                     uint32_t            stride,
                     size_t              acc_count);

AK_EXPORT
void
ak_meshReserveBufferForInput(AkMesh   * __restrict mesh,
                             AkInput  * __restrict input,
                             size_t                count);

AK_EXPORT
void
ak_meshReserveBuffers(AkMesh          * __restrict mesh,
                      AkMeshPrimitive * __restrict prim,
                      size_t                       count);

AK_EXPORT
AkResult
ak_meshFillBuffers(AkMesh * __restrict mesh);

AK_EXPORT
void
ak_moveIndices(AkMesh * __restrict mesh);

AK_EXPORT
void
ak_meshMoveBuffers(AkMesh * __restrict mesh);

AK_EXPORT
AkSourceEditHelper*
ak_meshSourceEditHelper(AkMesh  * __restrict mesh,
                        AkInput * __restrict input);

AK_EXPORT
AkDuplicator*
ak_meshDuplicatorForIndices(AkMesh          * __restrict mesh,
                            AkMeshPrimitive * __restrict prim);

AK_EXPORT
void
ak_meshFixIndexBuffer(AkMesh          * __restrict mesh,
                      AkMeshPrimitive * __restrict prim,
                      AkDuplicator    * __restrict duplicator);

void
ak_inputNameIndexed(AkInput * __restrict input,
                    char    * __restrict buf);

void
ak_meshReIndexInputs(AkMesh * __restrict mesh);

AkInput*
ak_meshInputGet(AkMeshPrimitive *prim,
                const char      *inputSemantic,
                uint32_t         set);

#ifdef __cplusplus
}
#endif
#endif /* ak_geom_h */
