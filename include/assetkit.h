/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef __libassetkit__assetkit__h_
#define __libassetkit__assetkit__h_

#include <stdlib.h>
#include <time.h>

/* since C99 or compiler ext */
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
//extern "C" {
#endif

#if defined(_WIN32)
#  ifdef _assetkit_dll
#    define _assetkit_export __declspec(dllexport)
#  else
#    define _assetkit_export __declspec(dllimport)
#  endif
# define _assetkit_hide
#else
#  define _assetkit_export __attribute__((visibility("default")))
#  define _assetkit_hide   __attribute__((visibility("hidden")))
#endif

#if DEBUG
#  define __ak_assert(x) assert(x)
#else
#  define __ak_assert(x) /* do nothing */
#endif

#define __ak_restrict __restrict

#define ak_ARRAY_LEN(ARR) sizeof(ARR) / sizeof(ARR[0]);

/* Core Value types based on COLLADA specs 1.5 */
typedef int32_t AkEnum;
typedef const char *  ak_string;
typedef char       *  ak_mut_string;
typedef const char *  ak_str;
typedef char       *  ak_mutstr;
typedef unsigned const char * ak_ustr;
typedef bool          ak_bool;
typedef ak_bool      ak_bool2[2];
typedef ak_bool      ak_bool3[3];
typedef ak_bool      ak_bool4[4];
typedef double        ak_float;
typedef ak_float     ak_float2[2];
typedef ak_float     ak_float3[3];
typedef ak_float2    ak_float2x2[2];
typedef ak_float2    ak_float2x3[3];
typedef ak_float2    ak_float2x4[4];
typedef ak_float     ak_float3[3];
typedef ak_float3    ak_float3x2[2];
typedef ak_float3    ak_float3x3[3];
typedef ak_float3    ak_float3x4[4];
typedef ak_float     ak_float4[4];
typedef ak_float4    ak_float4x2[2];
typedef ak_float4    ak_float4x3[3];
typedef ak_float4    ak_float4x4[4];
typedef ak_float     ak_float7[7];
typedef int           ak_int;
typedef unsigned int  ak_uint;
typedef ak_int       ak_hexBinary;
typedef ak_int       ak_int2[2];
typedef ak_int2      ak_int2x2[2];
typedef ak_int       ak_int3[3];
typedef ak_int3      ak_int3x3[3];
typedef ak_int       ak_int4[4];
typedef ak_int4      ak_int4x4[4];
typedef ak_bool      ak_list_of_bools[];
typedef ak_float     ak_list_of_floats[];
typedef ak_int       ak_list_of_ints[];
typedef ak_uint      ak_list_of_uints[];
typedef ak_hexBinary ak_list_of_hexBinary[];
typedef ak_string  * ak_list_of_string;

/* End Core Value Types */

/** 
 * @brief library time type
 */
typedef time_t ak_time_t;

typedef enum AkValueType {
  AK_VALUE_TYPE_UNKNOWN  = 0,
  AK_VALUE_TYPE_BOOL     = 1,
  AK_VALUE_TYPE_BOOL2    = 2,
  AK_VALUE_TYPE_BOOL3    = 3,
  AK_VALUE_TYPE_BOOL4    = 4,
  AK_VALUE_TYPE_INT      = 5,
  AK_VALUE_TYPE_INT2     = 6,
  AK_VALUE_TYPE_INT3     = 7,
  AK_VALUE_TYPE_INT4     = 8,
  AK_VALUE_TYPE_FLOAT    = 9,
  AK_VALUE_TYPE_FLOAT2   = 10,
  AK_VALUE_TYPE_FLOAT3   = 11,
  AK_VALUE_TYPE_FLOAT4   = 12,
  AK_VALUE_TYPE_FLOAT2x2 = 13,
  AK_VALUE_TYPE_FLOAT3x3 = 14,
  AK_VALUE_TYPE_FLOAT4x4 = 15,
  AK_VALUE_TYPE_STRING   = 16
} AkValueType;

typedef enum AkModifier {
  AK_MODIFIER_CONST    = 1,
  AK_MODIFIER_UNIFORM  = 2,
  AK_MODIFIER_VARYING  = 3,
  AK_MODIFIER_STATIC   = 4,
  AK_MODIFIER_VOLATILE = 5,
  AK_MODIFIER_EXTERN   = 6,
  AK_MODIFIER_SHARED   = 7
} AkModifier;

typedef enum AkProfileType {
  AK_PROFILE_TYPE_UNKOWN = 0,
  AK_PROFILE_TYPE_COMMON = 1,
  AK_PROFILE_TYPE_CG     = 2,
  AK_PROFILE_TYPE_GLES   = 3,
  AK_PROFILE_TYPE_GLES2  = 4,
  AK_PROFILE_TYPE_GLSL   = 5,
  AK_PROFILE_TYPE_BRIDGE = 6
} AkProfileType;

typedef enum AkTechniqueCommonType {
  AK_TECHNIQUE_COMMON_CAMERA_PERSPECTIVE  = 1,
  AK_TECHNIQUE_COMMON_CAMERA_ORTHOGRAPHIC = 2,
  AK_TECHNIQUE_COMMON_LIGHT_AMBIENT       = 3,
  AK_TECHNIQUE_COMMON_LIGHT_DIRECTIONAL   = 4,
  AK_TECHNIQUE_COMMON_LIGHT_POINT         = 5,
  AK_TECHNIQUE_COMMON_LIGHT_SPOT          = 6
} AkTechniqueCommonType;

typedef enum AkFileType {
  AK_FILE_TYPE_AUTO      = 0,
  AK_FILE_TYPE_COLLADA   = 1,
  AK_FILE_TYPE_WAVEFRONT = 2,
  AK_FILE_TYPE_FBX       = 3
} AkFileType;

typedef enum AkAssetType {
  AK_ASSET_TYPE_UNKNOWN
} AkAssetType;

typedef enum AkUpAxis {
  AK_UP_AXIS_Y = 0,
  AK_UP_AXIS_X = 1,
  AK_UP_AXIS_Z = 2
} AkUpAxis;

typedef enum AkAltitudeMode {
  AK_ALTITUDE_RELATIVETOGROUND = 0,
  AK_ALTITUDE_ABSOLUTE         = 1
} AkAltitudeMode;

typedef enum AkOpaque {
  AK_OPAQUE_A_ONE    = 0,
  AK_OPAQUE_RGB_ZERO = 1,
  AK_OPAQUE_A_ZERO   = 2,
  AK_OPAQUE_RGB_ONE  = 3
} AkOpaque;

typedef enum AkParamType {
  AK_PARAM_TYPE_BASIC    = 0,
  AK_PARAM_TYPE_EXTENDED = 1
} AkParamType;

typedef enum AkWrapMode {
  AK_WRAP_MODE_WRAP        = 0,
  AK_WRAP_MODE_MIRROR      = 1,
  AK_WRAP_MODE_CLAMP       = 2,
  AK_WRAP_MODE_BORDER      = 3,
  AK_WRAP_MODE_MIRROR_ONCE = 4
} AkWrapMode;

typedef enum AkMinFilter {
  AK_MINFILTER_LINEAR      = 0,
  AK_MINFILTER_NEAREST     = 1,
  AK_MINFILTER_ANISOTROPIC = 2
} AkMinFilter;

typedef enum AkMagFilter {
  AK_MAGFILTER_LINEAR  = 0,
  AK_MAGFILTER_NEAREST = 1
} AkMagFilter;

typedef enum AkMipFilter {
  AK_MIPFILTER_LINEAR  = 0,
  AK_MIPFILTER_NONE    = 1,
  AK_MIPFILTER_NEAREST = 2
} AkMipFilter;

typedef enum AkFace {
  AK_FACE_POSITIVE_X = 1,
  AK_FACE_NEGATIVE_X = 2,
  AK_FACE_POSITIVE_Y = 3,
  AK_FACE_NEGATIVE_Y = 4,
  AK_FACE_POSITIVE_Z = 5,
  AK_FACE_NEGATIVE_Z = 6
} AkFace;

typedef enum AkChannelFormat {
  AK_CHANNEL_FORMAT_RGB  = 1,
  AK_CHANNEL_FORMAT_RGBA = 2,
  AK_CHANNEL_FORMAT_RGBE = 3,
  AK_CHANNEL_FORMAT_L    = 4,
  AK_CHANNEL_FORMAT_LA   = 5,
  AK_CHANNEL_FORMAT_D    = 6
} AkChannelFormat;

typedef enum AkRangeFormat {
  AK_RANGE_FORMAT_SNORM = 1,
  AK_RANGE_FORMAT_UNORM = 2,
  AK_RANGE_FORMAT_SINT  = 3,
  AK_RANGE_FORMAT_UINT  = 4,
  AK_RANGE_FORMAT_FLOAT = 5
} AkRangeFormat;

typedef enum AkPrecisionFormat {
  AK_PRECISION_FORMAT_DEFAULT = 1,
  AK_PRECISION_FORMAT_LOW     = 2,
  AK_PRECISION_FORMAT_MID     = 3,
  AK_PRECISION_FORMAT_HIGHT   = 4,
  AK_PRECISION_FORMAT_MAX     = 5
} AkPrecisionFormat;

typedef enum AkDrawType {
  AK_DRAW_READ_STR_VAL                     = 0,
  AK_DRAW_GEOMETRY                         = 1,
  AK_DRAW_SCENE_GEOMETRY                   = 2,
  AK_DRAW_SCENE_IMAGE                      = 3,
  AK_DRAW_FULL_SCREEN_QUAD                 = 4,
  AK_DRAW_FULL_SCREEN_QUAD_PLUS_HALF_PIXEL = 5
} AkDrawType;

typedef enum AkPipelineStage {
  AK_PIPELINE_STAGE_VERTEX      = 1,
  AK_PIPELINE_STAGE_FRAGMENT    = 2,
  AK_PIPELINE_STAGE_TESSELATION = 3,
  AK_PIPELINE_STAGE_GEOMETRY    = 4
} AkPipelineStage;

/**
 * Almost all assets includes this fields. 
 * This macro defines base fields of assets
 */
#define ak_asset_base                                                        \
  ak_assetinf  * inf;                                                        \
  AkAssetType   type;

typedef struct AkTreeNodeAttr {
  const char * name;
  char       * val;

  struct AkTreeNodeAttr * next;
  struct AkTreeNodeAttr * prev;
} AkTreeNodeAttr;


typedef struct AkTreeNode {
  const char    * name;
  char          * val;
  unsigned long   attrc;
  unsigned long   chldc;

  AkTreeNodeAttr * attr;

  struct AkTreeNode * chld;
  struct AkTreeNode * parent;
  struct AkTreeNode * next;
  struct AkTreeNode * prev;
} AkTreeNode;

typedef struct AkTreeNode AkTree;

#ifdef _ak_DEF_BASIC_ATTR
#  undef _ak_DEF_BASIC_ATTR
#endif

#define _ak_DEF_BASIC_ATTR(T, P)                                             \
typedef struct ak_basic_attr ## P ## _s ak_basic_attr ## P;                 \
struct ak_basic_attr ## P ## _s {                                            \
  const char * sid;                                                           \
  T            val;                                                           \
}

_ak_DEF_BASIC_ATTR(float, f);
_ak_DEF_BASIC_ATTR(double, d);
_ak_DEF_BASIC_ATTR(long, l);
_ak_DEF_BASIC_ATTR(const char *, s);

#undef _ak_DEF_BASIC_ATTR

typedef struct ak_unit_s ak_unit;
struct ak_unit_s {
  const char * name;
  double       dist;
};

typedef struct ak_color_s ak_color;
struct ak_color_s {
  const char * sid;
  union {
    ak_float4 vec;

    struct {
      float R;
      float G;
      float B;
      float A;
    };
  };
};

typedef struct ak_contributor_s ak_contributor;
struct ak_contributor_s {
  const char * author;
  const char * author_email;
  const char * author_website;
  const char * authoring_tool;
  const char * comments;
  const char * copyright;
  const char * source_data;

  ak_contributor * next;
  ak_contributor * prev;
};

typedef struct ak_altitude_s ak_altitude;
struct ak_altitude_s {
  AkAltitudeMode mode;
  double            val;
};

typedef struct ak_geo_loc_s ak_geo_loc;
struct ak_geo_loc_s {
  double       lng;
  double       lat;
  ak_altitude alt;
};

typedef struct ak_coverage_s ak_coverage;
struct ak_coverage_s {
  ak_geo_loc geo_loc;
};

typedef struct ak_assetinf_s ak_assetinf;
struct ak_assetinf_s {
  ak_contributor * contributor;
  ak_coverage    * coverage;
  const char      * subject;
  const char      * title;
  const char      * keywords;

  ak_unit        * unit;
  AkTree        * extra;
  ak_time_t        created;
  ak_time_t        modified;
  unsigned long     revision;
  AkUpAxis        upaxis;
};

typedef struct ak_docinf_s ak_docinf;
struct ak_docinf_s {
  ak_assetinf   base;
  const char   * fname;
  AkFileType   ftype;
};

/*
 * TODO:
 * There should be an option (ak_load) to prevent optional 
 * load unsed / non-portable techniques. 
 * This may increase parse performance and reduce memory usage
 */
typedef struct ak_technique_s ak_technique;
struct ak_technique_s {
  const char * profile;

  /**
   * @brief
   * COLLADA Specs 1.5:
   * This XML Schema namespace attribute identifies an additional schema 
   * to use for validating the content of this instance document. Optional.
   */
  const char * xmlns;
  AkTree   * chld;

  ak_technique * prev;
  ak_technique * next;
};

typedef struct ak_technique_common_s ak_technique_common;
struct ak_technique_common_s {
  ak_technique_common      * next;
  void                      * technique;
  AkTechniqueCommonType   technique_type;
};

typedef struct ak_perspective_s ak_perspective;
struct ak_perspective_s {
  ak_basic_attrd * xfov;
  ak_basic_attrd * yfov;
  ak_basic_attrd * aspect_ratio;
  ak_basic_attrd * znear;
  ak_basic_attrd * zfar;
};

typedef struct ak_orthographic_s ak_orthographic;
struct ak_orthographic_s {
  ak_basic_attrd * xmag;
  ak_basic_attrd * ymag;
  ak_basic_attrd * aspect_ratio;
  ak_basic_attrd * znear;
  ak_basic_attrd * zfar;
};

typedef struct ak_optics_s ak_optics;
struct ak_optics_s {
  ak_technique_common * technique_common;
  ak_technique        * technique;
};

typedef struct ak_imager_s ak_imager;
struct ak_imager_s {
  ak_technique * technique;
  AkTree      * extra;
};

/**
 * Declares a view of the visual scene hierarchy or scene graph.
 * The camera contains elements that describe the camera’s optics and imager.
 */
typedef struct ak_camera_s ak_camera;
struct ak_camera_s {
  ak_asset_base

  const char * id;
  const char * name;

  ak_optics * optics;
  ak_imager * imager;
  AkTree   * extra;

  ak_camera * next;
};

/**
 * ambient light
 */
typedef struct ak_ambient_s ak_ambient;
struct ak_ambient_s {
  ak_color color;
};

/**
 * directional light
 */
typedef struct ak_directional_s ak_directional;
struct ak_directional_s {
  ak_color color;
};

/**
 * point light
 */
typedef struct ak_point_s ak_point;
struct ak_point_s {
  ak_color         color;
  ak_basic_attrd * constant_attenuation;
  ak_basic_attrd * linear_attenuation;
  ak_basic_attrd * quadratic_attenuation;
};

/**
 * spot light
 */
typedef struct ak_spot_s ak_spot;
struct ak_spot_s {
  ak_color         color;
  ak_basic_attrd * constant_attenuation;
  ak_basic_attrd * linear_attenuation;
  ak_basic_attrd * quadratic_attenuation;
  ak_basic_attrd * falloff_angle;
  ak_basic_attrd * falloff_exponent;
};

/**
 * Declares a light source that illuminates a scene.
 */
typedef struct ak_light_s ak_light;
struct ak_light_s {
  ak_asset_base

  const char * id;
  const char * name;

  ak_technique_common * technique_common;
  ak_technique        * technique;
  AkTree             * extra;

  ak_light * next;
};

/* FX */
/* Effects */
/*
 * base type of param
 */
typedef struct ak_param_s ak_param;
struct ak_param_s {
  AkParamType  param_type;
  const char * ref;

  ak_param * next;
};

typedef struct ak_param_ex_s ak_param_ex;
struct ak_param_ex_s {
  ak_param        base;
  const char     * name;
  const char     * sid;
  const char     * semantic;
  const char     * type_name;
  AkValueType   type;
};

typedef struct ak_hex_data_s ak_hex_data;
struct ak_hex_data_s {
  const char * format;
  const char * val;
};

typedef struct ak_init_from_s ak_init_from;
struct ak_init_from_s {
  const char   * ref;
  ak_hex_data * hex;
  
  AkFace     face;
  ak_uint     mip_index;
  ak_uint     depth;
  ak_int      array_index;
  ak_bool     mips_generate;

  ak_init_from * prev;
  ak_init_from * next;
};

typedef struct ak_size_exact_s ak_size_exact;
struct ak_size_exact_s {
  ak_float width;
  ak_float height;
};

typedef struct ak_size_ratio_s ak_size_ratio;
struct ak_size_ratio_s {
  ak_float width;
  ak_float height;
};

typedef struct ak_mips_s ak_mips;
struct ak_mips_s {
  ak_uint levels;
  ak_bool auto_generate;
};

typedef struct ak_image_format_s ak_image_format;
struct ak_image_format_s {
  struct {
    AkChannelFormat    channel;
    AkRangeFormat      range;
    AkPrecisionFormat  precision;
    const char          * space;
  } hint;

  const char * exact;
};

typedef struct ak_image2d_s ak_image2d;
struct ak_image2d_s {
  ak_size_exact   * size_exact;
  ak_size_ratio   * size_ratio;
  ak_mips         * mips;
  const char       * unnormalized;
  long               array_len;
  ak_image_format * format;
  ak_init_from    * init_from;
};

typedef struct ak_image3d_s ak_image3d;
struct ak_image3d_s {
  struct {
    ak_uint width;
    ak_uint height;
    ak_uint depth;
  } size;

  ak_mips           mips;
  long               array_len;
  ak_image_format * format;
  ak_init_from    * init_from;
};

typedef struct ak_image_cube_s ak_image_cube;
struct ak_image_cube_s {
  struct {
    ak_uint width;
  } size;

  ak_mips           mips;
  long               array_len;
  ak_image_format * format;
  ak_init_from    * init_from;
};

typedef struct ak_image_s ak_image;
struct ak_image_s {
  ak_asset_base
  
  const char * id;
  const char * sid;
  const char * name;

  ak_init_from  * init_from;
  ak_image2d    * image2d;
  ak_image3d    * image3d;
  ak_image_cube * cube;
  AkTree       * extra;

  ak_image * prev;
  ak_image * next;
  
  struct {
    ak_bool share;
  } renderable;

};

typedef struct ak_image_instance_s ak_image_instance;
struct ak_image_instance_s {
  const char * url;
  const char * sid;
  const char * name;

  AkTree * extra;
};

/*!
 * base type for these types:
 * sampler1D
 * sampler2D
 * sampler3D
 * samplerCUBE
 * samplerDEPTH
 * samplerRECT
 * samplerStates
 */
typedef struct ak_fx_sampler_common_s ak_fx_sampler_common;
struct ak_fx_sampler_common_s {
  ak_asset_base
  ak_image_instance * image_inst;

  struct {
    const char * semantic;
  } texcoord;

  AkWrapMode wrap_s;
  AkWrapMode wrap_t;
  AkWrapMode wrap_p;

  AkMinFilter minfilter;
  AkMagFilter magfilter;
  AkMipFilter mipfilter;

  unsigned long mip_max_level;
  unsigned long mip_min_level;
  float         mip_bias;
  unsigned long max_anisotropy;

  ak_color * border_color;
  AkTree  * extra;
};

typedef ak_fx_sampler_common ak_sampler1D;
typedef ak_fx_sampler_common ak_sampler2D;
typedef ak_fx_sampler_common ak_sampler3D;
typedef ak_fx_sampler_common ak_samplerCUBE;
typedef ak_fx_sampler_common ak_samplerDEPTH;
typedef ak_fx_sampler_common ak_samplerRECT;
typedef ak_fx_sampler_common ak_samplerStates;

typedef struct ak_fx_texture_s ak_fx_texture;
struct ak_fx_texture_s {
  const char * texture;
  const char * texcoord;
  AkTree   * extra;
};

typedef struct ak_fx_color_or_tex_s ak_fx_color_or_tex;
struct ak_fx_color_or_tex_s {
  AkOpaque       opaque;
  ak_color      * color;
  ak_param      * param;
  ak_fx_texture * texture;
};

typedef ak_fx_color_or_tex ak_ambient_fx;
typedef ak_fx_color_or_tex ak_diffuse;
typedef ak_fx_color_or_tex ak_emission;
typedef ak_fx_color_or_tex ak_reflective;
typedef ak_fx_color_or_tex ak_specular;
typedef ak_fx_color_or_tex ak_transparent;

typedef struct ak_fx_float_or_param_s ak_fx_float_or_param;
struct ak_fx_float_or_param_s {
  ak_basic_attrf * val;
  ak_param       * param;
};

typedef ak_fx_float_or_param ak_index_of_refraction;
typedef ak_fx_float_or_param ak_reflectivity;
typedef ak_fx_float_or_param ak_shininess;
typedef ak_fx_float_or_param ak_transparency;

typedef struct ak_annotate_s ak_annotate;
struct ak_annotate_s {
  const char     * name;
  void           * val;
  AkValueType   val_type;

  ak_annotate * next;
};

typedef struct ak_newparam_s ak_newparam;
struct ak_newparam_s {
  const char     * sid;
  ak_annotate   * annotate;
  const char     * semantic;
  AkModifier     modifier;
  void           * val;
  AkValueType   val_type;

  ak_newparam * next;
};

typedef struct ak_setparam_s ak_setparam;
struct ak_setparam_s {
  const char     * ref;
  void           * val;
  AkValueType   val_type;

  ak_setparam * next;
};

typedef struct ak_code_s ak_code;
struct ak_code_s {
  const char * sid;
  const char * val;

  ak_code * next;
};

typedef struct ak_include_s ak_include;
struct ak_include_s {
  const char * sid;
  const char * url;

  ak_include * next;
};

typedef struct ak_blinn_s ak_blinn;
struct ak_blinn_s {
  ak_emission            * emission;
  ak_ambient_fx          * ambient;
  ak_diffuse             * diffuse;
  ak_specular            * specular;
  ak_shininess           * shininess;
  ak_reflective          * reflective;
  ak_reflectivity        * reflectivity;
  ak_transparent         * transparent;
  ak_transparency        * transparency;
  ak_index_of_refraction * index_of_refraction;
};

typedef struct ak_constant_fx_s ak_constant_fx;
struct ak_constant_fx_s {
  ak_emission            * emission;
  ak_reflective          * reflective;
  ak_reflectivity        * reflectivity;
  ak_transparent         * transparent;
  ak_transparency        * transparency;
  ak_index_of_refraction * index_of_refraction;
};

typedef struct ak_lambert_s ak_lambert;
struct ak_lambert_s {
  ak_emission            * emission;
  ak_ambient_fx          * ambient;
  ak_diffuse             * diffuse;
  ak_reflective          * reflective;
  ak_reflectivity        * reflectivity;
  ak_transparent         * transparent;
  ak_transparency        * transparency;
  ak_index_of_refraction * index_of_refraction;
};

typedef struct ak_phong_s ak_phong;
struct ak_phong_s {
  ak_emission            * emission;
  ak_ambient_fx          * ambient;
  ak_diffuse             * diffuse;
  ak_specular            * specular;
  ak_shininess           * shininess;
  ak_reflective          * reflective;
  ak_reflectivity        * reflectivity;
  ak_transparent         * transparent;
  ak_transparency        * transparency;
  ak_index_of_refraction * index_of_refraction;
};

typedef struct AkRenderState AkRenderState;
typedef struct ak_states_s ak_states;
struct ak_states_s {
  AkRenderState * next;
  long               count;
};

typedef struct ak_evaluate_target_s ak_evaluate_target;
struct ak_evaluate_target_s {
  unsigned long index;
  unsigned long slice;
  unsigned long mip;
  AkFace      face;

  ak_param          * param;
  ak_image_instance * image_inst;
};

typedef struct ak_color_clear_s ak_color_clear;
struct ak_color_clear_s {
  unsigned long index;
  ak_color     val;
};

typedef struct ak_depth_clear_s ak_depth_clear;
struct ak_depth_clear_s {
  unsigned long index;
  ak_float     val;
};

typedef struct ak_stencil_clear_s ak_stencil_clear;
struct ak_stencil_clear_s {
  unsigned long index;
  unsigned long val;
};

typedef struct AK_DRAW_s ak_draw;
struct AK_DRAW_s {
  AkDrawType enum_draw;
  const char    * str_val;
};

typedef struct ak_evaluate_s ak_evaluate;
struct ak_evaluate_s {
  ak_evaluate_target * color_target;
  ak_evaluate_target * depth_target;
  ak_evaluate_target * stencil_target;
  ak_color_clear     * color_clear;
  ak_depth_clear     * depth_clear;
  ak_stencil_clear   * stencil_clear;
  ak_draw              draw;
};

typedef struct ak_inline_s ak_inline;
struct ak_inline_s {
  const char * val;
  ak_inline * next;
};

typedef struct ak_import_s ak_import;
struct ak_import_s {
  const char * ref;
  ak_import * next;
};

typedef struct ak_sources_s ak_sources;
struct ak_sources_s {
  const char * entry;

  ak_inline * inlines;
  ak_import * imports;
};

typedef struct ak_binary_s ak_binary;
struct ak_binary_s {
  const char * ref;
  ak_hex_data * hex;

  ak_binary * next;
};

typedef struct ak_compiler_s ak_compiler;
struct ak_compiler_s {
  const char * platform;
  const char * target;
  const char * options;
  ak_binary * binary;

  ak_compiler * next;
};

typedef struct ak_bind_uniform_s ak_bind_uniform;
struct ak_bind_uniform_s {
  const char * symbol;

  ak_param       * param;
  void            * val;
  AkValueType    val_type;

  ak_bind_uniform * next;
};

typedef struct ak_bind_attrib_s ak_bind_attrib;
struct ak_bind_attrib_s {
  const char * symbol;
  const char * semantic;

  ak_bind_attrib * next;
};

typedef struct ak_shader_s ak_shader;
struct ak_shader_s {
  AkPipelineStage stage;

  ak_sources      * sources;
  ak_compiler     * compiler;
  ak_bind_uniform * bind_uniform;
  AkTree         * extra;

  ak_shader * prev;
  ak_shader * next;
};

typedef struct ak_linker_s ak_linker;
struct ak_linker_s {
  const char * platform;
  const char * target;
  const char * options;

  ak_binary * binary;

  ak_linker * prev;
  ak_linker * next;
};

typedef struct ak_program_s ak_program;
struct ak_program_s {
  ak_shader       * shader;
  ak_bind_attrib  * bind_attrib;
  ak_bind_uniform * bind_uniform;
  ak_linker       * linker;
};

typedef struct ak_pass_s ak_pass;
struct ak_pass_s {
  ak_asset_base

  const char * sid;

  ak_annotate     * annotate;
  ak_states       * states;
  ak_evaluate     * evaluate;
  ak_program      * program;
  AkTree         * extra;

  ak_pass * prev;
  ak_pass * next;
};

typedef struct ak_technique_fx_s ak_technique_fx;
struct ak_technique_fx_s {
  ak_asset_base

  const char * id;
  const char * sid;

  ak_annotate    * annotate;
  ak_blinn       * blinn;
  ak_constant_fx * constant;
  ak_lambert     * lambert;
  ak_phong       * phong;
  ak_pass        * pass;

  AkTree        * extra;

  ak_technique_fx * next;
};

typedef struct ak_profile_s ak_profile;
struct ak_profile_s {
  ak_asset_base                                                           
  AkProfileType   profile_type;
  const char       * id;
  ak_newparam     * newparam;
  ak_technique_fx * technique;
  AkTree         * extra;
  ak_profile      * prev;
  ak_profile      * next;
};

typedef ak_profile ak_profile_common;

typedef struct ak_profile_cg_s ak_profile_CG;
struct ak_profile_cg_s {
  ak_profile base;

  ak_code      * code;
  ak_include   * include;
  const char    * platform;
};

typedef struct ak_profile_gles_s ak_profile_GLES;
struct ak_profile_gles_s {
  ak_profile base;

  const char * platform;
};

typedef struct ak_profile_gles2_s ak_profile_GLES2;
struct ak_profile_gles2_s {
  ak_profile base;

  ak_code    * code;
  ak_include * include;
  const char  * language;
  const char  * platforms;
};

typedef struct ak_profile_glsl_s ak_profile_GLSL;
struct ak_profile_glsl_s {
  ak_profile base;

  ak_code    * code;
  ak_include * include;
  const char  * platform;
};

typedef struct ak_profile_bridge_s ak_profile_BRIDGE;
struct ak_profile_bridge_s {
  ak_profile base;
  
  const char * platform;
  const char * url;
};

typedef struct ak_effect_s ak_effect;
struct ak_effect_s {
  ak_asset_base

  const char * id;
  const char * name;

  ak_annotate * annotate;
  ak_newparam * newparam;
  ak_profile  * profile;

  AkTree   * extra;

  ak_effect * prev;
  ak_effect * next;
};

typedef struct ak_technique_hint_s ak_technique_hint;
struct ak_technique_hint_s {
  const char * platform;
  const char * ref;
  const char * profile;

  ak_technique_hint * next;
};

typedef struct ak_effect_instance_s ak_effect_instance;
struct ak_effect_instance_s {
  const char * url;
  const char * sid;
  const char * name;

  ak_technique_hint *techniqueHint;
  ak_setparam       *setparam;

  AkTree * extra;
};

typedef struct ak_material_s ak_material;
struct ak_material_s {
  ak_asset_base
  const char * id;
  const char * name;
  ak_effect_instance *effect_inst;
  AkTree * extra;

  ak_material * next;
};

#undef _ak_DEF_LIB

#define _ak_DEF_LIB(T)                                                       \
  typedef struct ak_lib_ ## T ## _s  ak_lib_ ## T;                          \
  struct ak_lib_ ## T ## _s {                                                \
    ak_assetinf  * inf;                                                      \
    const char    * id;                                                       \
    const char    * name;                                                     \
    ak_##T       * chld;                                                     \
    AkTree      * extra;                                                    \
    unsigned long   count;                                                    \
    ak_lib_##T   * next;                                                     \
  }

_ak_DEF_LIB(camera);
_ak_DEF_LIB(light);
_ak_DEF_LIB(effect);
_ak_DEF_LIB(image);
_ak_DEF_LIB(material);

#undef _ak_DEF_LIB

typedef struct ak_lib_s ak_lib;
struct ak_lib_s {
  ak_lib_camera   * cameras;
  ak_lib_light    * lights;
  ak_lib_effect   * effects;
  ak_lib_image    * images;
  ak_lib_material * materials;
};

typedef struct ak_doc_s ak_doc;
struct ak_doc_s {
  ak_docinf docinf;
  ak_lib    lib;
};

typedef struct ak_asset_s ak_asset;
struct ak_asset_s {
  ak_asset_base
  void * ak_data;
};

#include "assetkit-states.h"
#include "assetkit-string.h"

extern void ak_cleanup();

int
_assetkit_export
ak_load(ak_doc ** __restrict dest,
         const char * __restrict file, ...);

#ifdef __cplusplus
//}
#endif
#endif /* __libassetkit__assetkit__h_ */