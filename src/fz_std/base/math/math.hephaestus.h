#ifndef MATH_HEPHAESTUS_H
#define UI_HEPHAESTUS_H

/*
@Hephaestus generated code
*/

// Vector 2 types
// --------------
typedef union Vec2u32 { u32 data[2]; struct { u32 x, y; }; } Vec2u32;
#define vec2u32(x,y) (vec2u32){(x),(y)}
#define vec2u32_zero() vec2f32(0,0)
typedef union Vec2u64 { u64 data[2]; struct { u64 x, y; }; } Vec2u64;
#define vec2u64(x,y) (vec2u64){(x),(y)}
#define vec2u64_zero() vec2f32(0,0)
typedef union Vec2s32 { s32 data[2]; struct { s32 x, y; }; } Vec2s32;
#define vec2s32(x,y) (vec2s32){(x),(y)}
#define vec2s32_zero() vec2f32(0,0)
typedef union Vec2s64 { s64 data[2]; struct { s64 x, y; }; } Vec2s64;
#define vec2s64(x,y) (vec2s64){(x),(y)}
#define vec2s64_zero() vec2f32(0,0)
typedef union Vec2f32 { f32 data[2]; struct { f32 x, y; }; } Vec2f32;
#define vec2f32(x,y) (vec2f32){(x),(y)}
#define vec2f32_zero() vec2f32(0,0)
typedef union Vec2f64 { f64 data[2]; struct { f64 x, y; }; } Vec2f64;
#define vec2f64(x,y) (vec2f64){(x),(y)}
#define vec2f64_zero() vec2f32(0,0)

// Vector 3 types
// --------------
typedef union Vec3u32 { u32 data[3]; struct { u32 x, y, z; }; } Vec3u32;
#define vec3u32(x,y,z) (vec3u32){(x),(y),(z)}
#define vec3u32_zero() vec3f32(0,0)
typedef union Vec3u64 { u64 data[3]; struct { u64 x, y, z; }; } Vec3u64;
#define vec3u64(x,y,z) (vec3u64){(x),(y),(z)}
#define vec3u64_zero() vec3f32(0,0)
typedef union Vec3s32 { s32 data[3]; struct { s32 x, y, z; }; } Vec3s32;
#define vec3s32(x,y,z) (vec3s32){(x),(y),(z)}
#define vec3s32_zero() vec3f32(0,0)
typedef union Vec3s64 { s64 data[3]; struct { s64 x, y, z; }; } Vec3s64;
#define vec3s64(x,y,z) (vec3s64){(x),(y),(z)}
#define vec3s64_zero() vec3f32(0,0)
typedef union Vec3f32 { f32 data[3]; struct { f32 x, y, z; }; } Vec3f32;
#define vec3f32(x,y,z) (vec3f32){(x),(y),(z)}
#define vec3f32_zero() vec3f32(0,0)
typedef union Vec3f64 { f64 data[3]; struct { f64 x, y, z; }; } Vec3f64;
#define vec3f64(x,y,z) (vec3f64){(x),(y),(z)}
#define vec3f64_zero() vec3f32(0,0)

// Vector 4 types
// --------------
typedef union Vec4u32 { u32 data[4]; struct { u32 x, y, z, w; }; } Vec4u32;
#define vec4u32(x,y,z,w) (vec4u32){(x),(y),(z),(w)}
#define vec4u32_zero() vec4f32(0,0)
typedef union Vec4u64 { u64 data[4]; struct { u64 x, y, z, w; }; } Vec4u64;
#define vec4u64(x,y,z,w) (vec4u64){(x),(y),(z),(w)}
#define vec4u64_zero() vec4f32(0,0)
typedef union Vec4s32 { s32 data[4]; struct { s32 x, y, z, w; }; } Vec4s32;
#define vec4s32(x,y,z,w) (vec4s32){(x),(y),(z),(w)}
#define vec4s32_zero() vec4f32(0,0)
typedef union Vec4s64 { s64 data[4]; struct { s64 x, y, z, w; }; } Vec4s64;
#define vec4s64(x,y,z,w) (vec4s64){(x),(y),(z),(w)}
#define vec4s64_zero() vec4f32(0,0)
typedef union Vec4f32 { f32 data[4]; struct { f32 x, y, z, w; }; } Vec4f32;
#define vec4f32(x,y,z,w) (vec4f32){(x),(y),(z),(w)}
#define vec4f32_zero() vec4f32(0,0)
typedef union Vec4f64 { f64 data[4]; struct { f64 x, y, z, w; }; } Vec4f64;
#define vec4f64(x,y,z,w) (vec4f64){(x),(y),(z),(w)}
#define vec4f64_zero() vec4f32(0,0)

// Matrix4 types
// --------------
/*
  Column major:
  Type m0, m4, m8,  m12,
       m1, m5, m9,  m13,
       m2, m6, m10, m14,
       m3, m7, m11, m15;
*/
typedef union Mat4u32 { u32 data[4][4]; struct { u32 m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15; }; } Mat4u32;
#define mat4u32(diagonal) (Mat4u32) {(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal)}
#define mat4u32_identity() mat4u32(1.0f)
typedef union Mat4u64 { u64 data[4][4]; struct { u64 m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15; }; } Mat4u64;
#define mat4u64(diagonal) (Mat4u64) {(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal)}
#define mat4u64_identity() mat4u64(1.0f)
typedef union Mat4s32 { s32 data[4][4]; struct { s32 m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15; }; } Mat4s32;
#define mat4s32(diagonal) (Mat4s32) {(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal)}
#define mat4s32_identity() mat4s32(1.0f)
typedef union Mat4s64 { s64 data[4][4]; struct { s64 m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15; }; } Mat4s64;
#define mat4s64(diagonal) (Mat4s64) {(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal)}
#define mat4s64_identity() mat4s64(1.0f)
typedef union Mat4f32 { f32 data[4][4]; struct { f32 m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15; }; } Mat4f32;
#define mat4f32(diagonal) (Mat4f32) {(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal)}
#define mat4f32_identity() mat4f32(1.0f)
typedef union Mat4f64 { f64 data[4][4]; struct { f64 m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15; }; } Mat4f64;
#define mat4f64(diagonal) (Mat4f64) {(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal),0.0f,0.0f,0.0f,0.0f,(diagonal)}
#define mat4f64_identity() mat4f64(1.0f)

// Quaternion types
// ----------------
typedef union Quatu32 { u32 data[2]; struct { u32 x, y, z, w; }; } Quatu32;
#define quatu32(x,y,z,w) (vec2u32){(x),(y),(z),(w)}
#define quatu32_identity() quatu32(0.0f,0.0f,0.0f,1.0f)
typedef union Quatu64 { u64 data[2]; struct { u64 x, y, z, w; }; } Quatu64;
#define quatu64(x,y,z,w) (vec2u64){(x),(y),(z),(w)}
#define quatu64_identity() quatu64(0.0f,0.0f,0.0f,1.0f)
typedef union Quats32 { s32 data[2]; struct { s32 x, y, z, w; }; } Quats32;
#define quats32(x,y,z,w) (vec2s32){(x),(y),(z),(w)}
#define quats32_identity() quats32(0.0f,0.0f,0.0f,1.0f)
typedef union Quats64 { s64 data[2]; struct { s64 x, y, z, w; }; } Quats64;
#define quats64(x,y,z,w) (vec2s64){(x),(y),(z),(w)}
#define quats64_identity() quats64(0.0f,0.0f,0.0f,1.0f)
typedef union Quatf32 { f32 data[2]; struct { f32 x, y, z, w; }; } Quatf32;
#define quatf32(x,y,z,w) (vec2f32){(x),(y),(z),(w)}
#define quatf32_identity() quatf32(0.0f,0.0f,0.0f,1.0f)
typedef union Quatf64 { f64 data[2]; struct { f64 x, y, z, w; }; } Quatf64;
#define quatf64(x,y,z,w) (vec2f64){(x),(y),(z),(w)}
#define quatf64_identity() quatf64(0.0f,0.0f,0.0f,1.0f)

// Transform 2 types
// -----------------
typedef struct Transform2u32 { Vec2u32 translation; f32 rotation; Vec2u32 scale; } Transformu32;
typedef struct Transform2u64 { Vec2u64 translation; f32 rotation; Vec2u64 scale; } Transformu64;
typedef struct Transform2s32 { Vec2s32 translation; f32 rotation; Vec2s32 scale; } Transforms32;
typedef struct Transform2s64 { Vec2s64 translation; f32 rotation; Vec2s64 scale; } Transforms64;
typedef struct Transform2f32 { Vec2f32 translation; f32 rotation; Vec2f32 scale; } Transformf32;
typedef struct Transform2f64 { Vec2f64 translation; f32 rotation; Vec2f64 scale; } Transformf64;

// Transform 3 types
// -----------------
typedef struct Transform3u32 { Vec3u32 translation; Quatf32 rotation; Vec3u32 scale; } Transformu32;
typedef struct Transform3u64 { Vec3u64 translation; Quatf32 rotation; Vec3u64 scale; } Transformu64;
typedef struct Transform3s32 { Vec3s32 translation; Quatf32 rotation; Vec3s32 scale; } Transforms32;
typedef struct Transform3s64 { Vec3s64 translation; Quatf32 rotation; Vec3s64 scale; } Transforms64;
typedef struct Transform3f32 { Vec3f32 translation; Quatf32 rotation; Vec3f32 scale; } Transformf32;
typedef struct Transform3f64 { Vec3f64 translation; Quatf32 rotation; Vec3f64 scale; } Transformf64;

// Rects types
// -----------
typedef struct Rectu32 { Vec2u32 top_left; Vec2u32 size; } Rectu32;
#define rectu32(top_left,size) ((Rectu32){top_left,size})
typedef struct Rectu64 { Vec2u64 top_left; Vec2u64 size; } Rectu64;
#define rectu64(top_left,size) ((Rectu64){top_left,size})
typedef struct Rects32 { Vec2s32 top_left; Vec2s32 size; } Rects32;
#define rects32(top_left,size) ((Rects32){top_left,size})
typedef struct Rects64 { Vec2s64 top_left; Vec2s64 size; } Rects64;
#define rects64(top_left,size) ((Rects64){top_left,size})
typedef struct Rectf32 { Vec2f32 top_left; Vec2f32 size; } Rectf32;
#define rectf32(top_left,size) ((Rectf32){top_left,size})
typedef struct Rectf64 { Vec2f64 top_left; Vec2f64 size; } Rectf64;
#define rectf64(top_left,size) ((Rectf64){top_left,size})

// Vec2u32
function Vec2u32 vec2u32_add(Vec2u32 a, Vec2u32 b);
function Vec2u32 vec2u32_subtract(Vec2u32 a, Vec2u32 b);
function Vec2u32 vec2u32_multiply(Vec2u32 a, Vec2u32 b);
function Vec2u32 vec2u32_divide(Vec2u32 a, Vec2u32 b);
function Vec2u32 vec2u32_scale(Vec2u32 vector, f32 scalar);
function Vec2u32 vec2u32_negate(Vec2u32 vector);
function Vec2u32 vec2u32_rotate(Vec2u32 vector, f32 radians);
function Vec2u32 vec2u32_normalize(Vec2u32 vector);
function Vec2u32 vec2u32_linear_interpolate(Vec2u32 a, Vec2u32 b, f32 t);
function Vec2u32 vec2u32_clamp(Vec2u32 vector, Vec2u32 minimum, Vec2u32 maximum);
function Vec2u32 vec2u32_absolute(Vec2u32 vector);
function Vec2u32 vec2u32_perpendicular(Vec2u32 vector);
function Vec2u32 vec2u32_reflect(Vec2u32 incident, Vec2u32 normal);
function Vec2u32 vec2u32_project(Vec2u32 vector, Vec2u32 onto);
function Vec2u32 vec2u32_snap_to_grid(Vec2u32 vector, f32 grid_size);
function f32 vec2u32_dot_product(Vec2u32 a, Vec2u32 b);
function f32 vec2u32_cross_product(Vec2u32 a, Vec2u32 b);
function f32 vec2u32_length(Vec2u32 vector);
function f32 vec2u32_length_squared(Vec2u32 vector);
function f32 vec2u32_distance(Vec2u32 a, Vec2u32 b);
function f32 vec2u32_distance_squared(Vec2u32 a, Vec2u32 b);
function f32 vec2u32_angle_between(Vec2u32 a, Vec2u32 b);
function f32 vec2u32_signed_angle_between(Vec2u32 a, Vec2u32 b);

// Vec2u64
function Vec2u64 vec2u64_add(Vec2u64 a, Vec2u64 b);
function Vec2u64 vec2u64_subtract(Vec2u64 a, Vec2u64 b);
function Vec2u64 vec2u64_multiply(Vec2u64 a, Vec2u64 b);
function Vec2u64 vec2u64_divide(Vec2u64 a, Vec2u64 b);
function Vec2u64 vec2u64_scale(Vec2u64 vector, f32 scalar);
function Vec2u64 vec2u64_negate(Vec2u64 vector);
function Vec2u64 vec2u64_rotate(Vec2u64 vector, f32 radians);
function Vec2u64 vec2u64_normalize(Vec2u64 vector);
function Vec2u64 vec2u64_linear_interpolate(Vec2u64 a, Vec2u64 b, f32 t);
function Vec2u64 vec2u64_clamp(Vec2u64 vector, Vec2u64 minimum, Vec2u64 maximum);
function Vec2u64 vec2u64_absolute(Vec2u64 vector);
function Vec2u64 vec2u64_perpendicular(Vec2u64 vector);
function Vec2u64 vec2u64_reflect(Vec2u64 incident, Vec2u64 normal);
function Vec2u64 vec2u64_project(Vec2u64 vector, Vec2u64 onto);
function Vec2u64 vec2u64_snap_to_grid(Vec2u64 vector, f32 grid_size);
function f32 vec2u64_dot_product(Vec2u64 a, Vec2u64 b);
function f32 vec2u64_cross_product(Vec2u64 a, Vec2u64 b);
function f32 vec2u64_length(Vec2u64 vector);
function f32 vec2u64_length_squared(Vec2u64 vector);
function f32 vec2u64_distance(Vec2u64 a, Vec2u64 b);
function f32 vec2u64_distance_squared(Vec2u64 a, Vec2u64 b);
function f32 vec2u64_angle_between(Vec2u64 a, Vec2u64 b);
function f32 vec2u64_signed_angle_between(Vec2u64 a, Vec2u64 b);

// Vec2s32
function Vec2s32 vec2s32_add(Vec2s32 a, Vec2s32 b);
function Vec2s32 vec2s32_subtract(Vec2s32 a, Vec2s32 b);
function Vec2s32 vec2s32_multiply(Vec2s32 a, Vec2s32 b);
function Vec2s32 vec2s32_divide(Vec2s32 a, Vec2s32 b);
function Vec2s32 vec2s32_scale(Vec2s32 vector, f32 scalar);
function Vec2s32 vec2s32_negate(Vec2s32 vector);
function Vec2s32 vec2s32_rotate(Vec2s32 vector, f32 radians);
function Vec2s32 vec2s32_normalize(Vec2s32 vector);
function Vec2s32 vec2s32_linear_interpolate(Vec2s32 a, Vec2s32 b, f32 t);
function Vec2s32 vec2s32_clamp(Vec2s32 vector, Vec2s32 minimum, Vec2s32 maximum);
function Vec2s32 vec2s32_absolute(Vec2s32 vector);
function Vec2s32 vec2s32_perpendicular(Vec2s32 vector);
function Vec2s32 vec2s32_reflect(Vec2s32 incident, Vec2s32 normal);
function Vec2s32 vec2s32_project(Vec2s32 vector, Vec2s32 onto);
function Vec2s32 vec2s32_snap_to_grid(Vec2s32 vector, f32 grid_size);
function f32 vec2s32_dot_product(Vec2s32 a, Vec2s32 b);
function f32 vec2s32_cross_product(Vec2s32 a, Vec2s32 b);
function f32 vec2s32_length(Vec2s32 vector);
function f32 vec2s32_length_squared(Vec2s32 vector);
function f32 vec2s32_distance(Vec2s32 a, Vec2s32 b);
function f32 vec2s32_distance_squared(Vec2s32 a, Vec2s32 b);
function f32 vec2s32_angle_between(Vec2s32 a, Vec2s32 b);
function f32 vec2s32_signed_angle_between(Vec2s32 a, Vec2s32 b);

// Vec2s64
function Vec2s64 vec2s64_add(Vec2s64 a, Vec2s64 b);
function Vec2s64 vec2s64_subtract(Vec2s64 a, Vec2s64 b);
function Vec2s64 vec2s64_multiply(Vec2s64 a, Vec2s64 b);
function Vec2s64 vec2s64_divide(Vec2s64 a, Vec2s64 b);
function Vec2s64 vec2s64_scale(Vec2s64 vector, f32 scalar);
function Vec2s64 vec2s64_negate(Vec2s64 vector);
function Vec2s64 vec2s64_rotate(Vec2s64 vector, f32 radians);
function Vec2s64 vec2s64_normalize(Vec2s64 vector);
function Vec2s64 vec2s64_linear_interpolate(Vec2s64 a, Vec2s64 b, f32 t);
function Vec2s64 vec2s64_clamp(Vec2s64 vector, Vec2s64 minimum, Vec2s64 maximum);
function Vec2s64 vec2s64_absolute(Vec2s64 vector);
function Vec2s64 vec2s64_perpendicular(Vec2s64 vector);
function Vec2s64 vec2s64_reflect(Vec2s64 incident, Vec2s64 normal);
function Vec2s64 vec2s64_project(Vec2s64 vector, Vec2s64 onto);
function Vec2s64 vec2s64_snap_to_grid(Vec2s64 vector, f32 grid_size);
function f32 vec2s64_dot_product(Vec2s64 a, Vec2s64 b);
function f32 vec2s64_cross_product(Vec2s64 a, Vec2s64 b);
function f32 vec2s64_length(Vec2s64 vector);
function f32 vec2s64_length_squared(Vec2s64 vector);
function f32 vec2s64_distance(Vec2s64 a, Vec2s64 b);
function f32 vec2s64_distance_squared(Vec2s64 a, Vec2s64 b);
function f32 vec2s64_angle_between(Vec2s64 a, Vec2s64 b);
function f32 vec2s64_signed_angle_between(Vec2s64 a, Vec2s64 b);

// Vec2f32
function Vec2f32 vec2f32_add(Vec2f32 a, Vec2f32 b);
function Vec2f32 vec2f32_subtract(Vec2f32 a, Vec2f32 b);
function Vec2f32 vec2f32_multiply(Vec2f32 a, Vec2f32 b);
function Vec2f32 vec2f32_divide(Vec2f32 a, Vec2f32 b);
function Vec2f32 vec2f32_scale(Vec2f32 vector, f32 scalar);
function Vec2f32 vec2f32_negate(Vec2f32 vector);
function Vec2f32 vec2f32_rotate(Vec2f32 vector, f32 radians);
function Vec2f32 vec2f32_normalize(Vec2f32 vector);
function Vec2f32 vec2f32_linear_interpolate(Vec2f32 a, Vec2f32 b, f32 t);
function Vec2f32 vec2f32_clamp(Vec2f32 vector, Vec2f32 minimum, Vec2f32 maximum);
function Vec2f32 vec2f32_absolute(Vec2f32 vector);
function Vec2f32 vec2f32_perpendicular(Vec2f32 vector);
function Vec2f32 vec2f32_reflect(Vec2f32 incident, Vec2f32 normal);
function Vec2f32 vec2f32_project(Vec2f32 vector, Vec2f32 onto);
function Vec2f32 vec2f32_snap_to_grid(Vec2f32 vector, f32 grid_size);
function f32 vec2f32_dot_product(Vec2f32 a, Vec2f32 b);
function f32 vec2f32_cross_product(Vec2f32 a, Vec2f32 b);
function f32 vec2f32_length(Vec2f32 vector);
function f32 vec2f32_length_squared(Vec2f32 vector);
function f32 vec2f32_distance(Vec2f32 a, Vec2f32 b);
function f32 vec2f32_distance_squared(Vec2f32 a, Vec2f32 b);
function f32 vec2f32_angle_between(Vec2f32 a, Vec2f32 b);
function f32 vec2f32_signed_angle_between(Vec2f32 a, Vec2f32 b);

// Vec2f64
function Vec2f64 vec2f64_add(Vec2f64 a, Vec2f64 b);
function Vec2f64 vec2f64_subtract(Vec2f64 a, Vec2f64 b);
function Vec2f64 vec2f64_multiply(Vec2f64 a, Vec2f64 b);
function Vec2f64 vec2f64_divide(Vec2f64 a, Vec2f64 b);
function Vec2f64 vec2f64_scale(Vec2f64 vector, f32 scalar);
function Vec2f64 vec2f64_negate(Vec2f64 vector);
function Vec2f64 vec2f64_rotate(Vec2f64 vector, f32 radians);
function Vec2f64 vec2f64_normalize(Vec2f64 vector);
function Vec2f64 vec2f64_linear_interpolate(Vec2f64 a, Vec2f64 b, f32 t);
function Vec2f64 vec2f64_clamp(Vec2f64 vector, Vec2f64 minimum, Vec2f64 maximum);
function Vec2f64 vec2f64_absolute(Vec2f64 vector);
function Vec2f64 vec2f64_perpendicular(Vec2f64 vector);
function Vec2f64 vec2f64_reflect(Vec2f64 incident, Vec2f64 normal);
function Vec2f64 vec2f64_project(Vec2f64 vector, Vec2f64 onto);
function Vec2f64 vec2f64_snap_to_grid(Vec2f64 vector, f32 grid_size);
function f32 vec2f64_dot_product(Vec2f64 a, Vec2f64 b);
function f32 vec2f64_cross_product(Vec2f64 a, Vec2f64 b);
function f32 vec2f64_length(Vec2f64 vector);
function f32 vec2f64_length_squared(Vec2f64 vector);
function f32 vec2f64_distance(Vec2f64 a, Vec2f64 b);
function f32 vec2f64_distance_squared(Vec2f64 a, Vec2f64 b);
function f32 vec2f64_angle_between(Vec2f64 a, Vec2f64 b);
function f32 vec2f64_signed_angle_between(Vec2f64 a, Vec2f64 b);

// Vector3
// -------// Vec3u32
function Vec3u32 vec3u32_add(Vec3u32 a, Vec3u32 b);
function Vec3u32 vec3u32_subtract(Vec3u32 a, Vec3u32 b);
function Vec3u32 vec3u32_multiply(Vec3u32 a, Vec3u32 b);
function Vec3u32 vec3u32_divide(Vec3u32 a, Vec3u32 b);
function Vec3u32 vec3u32_scale(Vec3u32 vector, f32 scalar);
function Vec3u32 vec3u32_negate(Vec3u32 vector);
function Vec3u32 vec3u32_normalize(Vec3u32 vector);
function Vec3u32 vec3u32_linear_interpolate(Vec3u32 a, Vec3u32 b, f32 t);
function Vec3u32 vec3u32_clamp(Vec3u32 vector, Vec3u32 minimum, Vec3u32 maximum);
function Vec3u32 vec3u32_absolute(Vec3u32 vector);
function Vec3u32 vec3u32_reflect(Vec3u32 incident, Vec3u32 normal);
function Vec3u32 vec3u32_project(Vec3u32 vector, Vec3u32 onto);
function Vec3u32 vec3u32_snap_to_grid(Vec3u32 vector, f32 grid_size);
function Vec3u32 vec3u32_cross_product(Vec3u32 a, Vec3u32 b);
function Vec3u32 vec3u32_rotate_axis_angle(Vec3u32 vector, Vec3u32 axis, f32 radians);
function Vec3u32 vec3u32_from_to_rotation(Vec3u32 from, Vec3u32 to);
function Vec3u32 vec3u32_normal_from_triangle(Vec3u32 a, Vec3u32 b, Vec3u32 c);
function f32 vec3u32_dot_product(Vec3u32 a, Vec3u32 b);
function f32 vec3u32_length(Vec3u32 vector);
function f32 vec3u32_length_squared(Vec3u32 vector);
function f32 vec3u32_distance(Vec3u32 a, Vec3u32 b);
function f32 vec3u32_distance_squared(Vec3u32 a, Vec3u32 b);
function f32 vec3u32_angle_between(Vec3u32 a, Vec3u32 b);

// Vec3u64
function Vec3u64 vec3u64_add(Vec3u64 a, Vec3u64 b);
function Vec3u64 vec3u64_subtract(Vec3u64 a, Vec3u64 b);
function Vec3u64 vec3u64_multiply(Vec3u64 a, Vec3u64 b);
function Vec3u64 vec3u64_divide(Vec3u64 a, Vec3u64 b);
function Vec3u64 vec3u64_scale(Vec3u64 vector, f32 scalar);
function Vec3u64 vec3u64_negate(Vec3u64 vector);
function Vec3u64 vec3u64_normalize(Vec3u64 vector);
function Vec3u64 vec3u64_linear_interpolate(Vec3u64 a, Vec3u64 b, f32 t);
function Vec3u64 vec3u64_clamp(Vec3u64 vector, Vec3u64 minimum, Vec3u64 maximum);
function Vec3u64 vec3u64_absolute(Vec3u64 vector);
function Vec3u64 vec3u64_reflect(Vec3u64 incident, Vec3u64 normal);
function Vec3u64 vec3u64_project(Vec3u64 vector, Vec3u64 onto);
function Vec3u64 vec3u64_snap_to_grid(Vec3u64 vector, f32 grid_size);
function Vec3u64 vec3u64_cross_product(Vec3u64 a, Vec3u64 b);
function Vec3u64 vec3u64_rotate_axis_angle(Vec3u64 vector, Vec3u64 axis, f32 radians);
function Vec3u64 vec3u64_from_to_rotation(Vec3u64 from, Vec3u64 to);
function Vec3u64 vec3u64_normal_from_triangle(Vec3u64 a, Vec3u64 b, Vec3u64 c);
function f32 vec3u64_dot_product(Vec3u64 a, Vec3u64 b);
function f32 vec3u64_length(Vec3u64 vector);
function f32 vec3u64_length_squared(Vec3u64 vector);
function f32 vec3u64_distance(Vec3u64 a, Vec3u64 b);
function f32 vec3u64_distance_squared(Vec3u64 a, Vec3u64 b);
function f32 vec3u64_angle_between(Vec3u64 a, Vec3u64 b);

// Vec3s32
function Vec3s32 vec3s32_add(Vec3s32 a, Vec3s32 b);
function Vec3s32 vec3s32_subtract(Vec3s32 a, Vec3s32 b);
function Vec3s32 vec3s32_multiply(Vec3s32 a, Vec3s32 b);
function Vec3s32 vec3s32_divide(Vec3s32 a, Vec3s32 b);
function Vec3s32 vec3s32_scale(Vec3s32 vector, f32 scalar);
function Vec3s32 vec3s32_negate(Vec3s32 vector);
function Vec3s32 vec3s32_normalize(Vec3s32 vector);
function Vec3s32 vec3s32_linear_interpolate(Vec3s32 a, Vec3s32 b, f32 t);
function Vec3s32 vec3s32_clamp(Vec3s32 vector, Vec3s32 minimum, Vec3s32 maximum);
function Vec3s32 vec3s32_absolute(Vec3s32 vector);
function Vec3s32 vec3s32_reflect(Vec3s32 incident, Vec3s32 normal);
function Vec3s32 vec3s32_project(Vec3s32 vector, Vec3s32 onto);
function Vec3s32 vec3s32_snap_to_grid(Vec3s32 vector, f32 grid_size);
function Vec3s32 vec3s32_cross_product(Vec3s32 a, Vec3s32 b);
function Vec3s32 vec3s32_rotate_axis_angle(Vec3s32 vector, Vec3s32 axis, f32 radians);
function Vec3s32 vec3s32_from_to_rotation(Vec3s32 from, Vec3s32 to);
function Vec3s32 vec3s32_normal_from_triangle(Vec3s32 a, Vec3s32 b, Vec3s32 c);
function f32 vec3s32_dot_product(Vec3s32 a, Vec3s32 b);
function f32 vec3s32_length(Vec3s32 vector);
function f32 vec3s32_length_squared(Vec3s32 vector);
function f32 vec3s32_distance(Vec3s32 a, Vec3s32 b);
function f32 vec3s32_distance_squared(Vec3s32 a, Vec3s32 b);
function f32 vec3s32_angle_between(Vec3s32 a, Vec3s32 b);

// Vec3s64
function Vec3s64 vec3s64_add(Vec3s64 a, Vec3s64 b);
function Vec3s64 vec3s64_subtract(Vec3s64 a, Vec3s64 b);
function Vec3s64 vec3s64_multiply(Vec3s64 a, Vec3s64 b);
function Vec3s64 vec3s64_divide(Vec3s64 a, Vec3s64 b);
function Vec3s64 vec3s64_scale(Vec3s64 vector, f32 scalar);
function Vec3s64 vec3s64_negate(Vec3s64 vector);
function Vec3s64 vec3s64_normalize(Vec3s64 vector);
function Vec3s64 vec3s64_linear_interpolate(Vec3s64 a, Vec3s64 b, f32 t);
function Vec3s64 vec3s64_clamp(Vec3s64 vector, Vec3s64 minimum, Vec3s64 maximum);
function Vec3s64 vec3s64_absolute(Vec3s64 vector);
function Vec3s64 vec3s64_reflect(Vec3s64 incident, Vec3s64 normal);
function Vec3s64 vec3s64_project(Vec3s64 vector, Vec3s64 onto);
function Vec3s64 vec3s64_snap_to_grid(Vec3s64 vector, f32 grid_size);
function Vec3s64 vec3s64_cross_product(Vec3s64 a, Vec3s64 b);
function Vec3s64 vec3s64_rotate_axis_angle(Vec3s64 vector, Vec3s64 axis, f32 radians);
function Vec3s64 vec3s64_from_to_rotation(Vec3s64 from, Vec3s64 to);
function Vec3s64 vec3s64_normal_from_triangle(Vec3s64 a, Vec3s64 b, Vec3s64 c);
function f32 vec3s64_dot_product(Vec3s64 a, Vec3s64 b);
function f32 vec3s64_length(Vec3s64 vector);
function f32 vec3s64_length_squared(Vec3s64 vector);
function f32 vec3s64_distance(Vec3s64 a, Vec3s64 b);
function f32 vec3s64_distance_squared(Vec3s64 a, Vec3s64 b);
function f32 vec3s64_angle_between(Vec3s64 a, Vec3s64 b);

// Vec3f32
function Vec3f32 vec3f32_add(Vec3f32 a, Vec3f32 b);
function Vec3f32 vec3f32_subtract(Vec3f32 a, Vec3f32 b);
function Vec3f32 vec3f32_multiply(Vec3f32 a, Vec3f32 b);
function Vec3f32 vec3f32_divide(Vec3f32 a, Vec3f32 b);
function Vec3f32 vec3f32_scale(Vec3f32 vector, f32 scalar);
function Vec3f32 vec3f32_negate(Vec3f32 vector);
function Vec3f32 vec3f32_normalize(Vec3f32 vector);
function Vec3f32 vec3f32_linear_interpolate(Vec3f32 a, Vec3f32 b, f32 t);
function Vec3f32 vec3f32_clamp(Vec3f32 vector, Vec3f32 minimum, Vec3f32 maximum);
function Vec3f32 vec3f32_absolute(Vec3f32 vector);
function Vec3f32 vec3f32_reflect(Vec3f32 incident, Vec3f32 normal);
function Vec3f32 vec3f32_project(Vec3f32 vector, Vec3f32 onto);
function Vec3f32 vec3f32_snap_to_grid(Vec3f32 vector, f32 grid_size);
function Vec3f32 vec3f32_cross_product(Vec3f32 a, Vec3f32 b);
function Vec3f32 vec3f32_rotate_axis_angle(Vec3f32 vector, Vec3f32 axis, f32 radians);
function Vec3f32 vec3f32_from_to_rotation(Vec3f32 from, Vec3f32 to);
function Vec3f32 vec3f32_normal_from_triangle(Vec3f32 a, Vec3f32 b, Vec3f32 c);
function f32 vec3f32_dot_product(Vec3f32 a, Vec3f32 b);
function f32 vec3f32_length(Vec3f32 vector);
function f32 vec3f32_length_squared(Vec3f32 vector);
function f32 vec3f32_distance(Vec3f32 a, Vec3f32 b);
function f32 vec3f32_distance_squared(Vec3f32 a, Vec3f32 b);
function f32 vec3f32_angle_between(Vec3f32 a, Vec3f32 b);

// Vec3f64
function Vec3f64 vec3f64_add(Vec3f64 a, Vec3f64 b);
function Vec3f64 vec3f64_subtract(Vec3f64 a, Vec3f64 b);
function Vec3f64 vec3f64_multiply(Vec3f64 a, Vec3f64 b);
function Vec3f64 vec3f64_divide(Vec3f64 a, Vec3f64 b);
function Vec3f64 vec3f64_scale(Vec3f64 vector, f32 scalar);
function Vec3f64 vec3f64_negate(Vec3f64 vector);
function Vec3f64 vec3f64_normalize(Vec3f64 vector);
function Vec3f64 vec3f64_linear_interpolate(Vec3f64 a, Vec3f64 b, f32 t);
function Vec3f64 vec3f64_clamp(Vec3f64 vector, Vec3f64 minimum, Vec3f64 maximum);
function Vec3f64 vec3f64_absolute(Vec3f64 vector);
function Vec3f64 vec3f64_reflect(Vec3f64 incident, Vec3f64 normal);
function Vec3f64 vec3f64_project(Vec3f64 vector, Vec3f64 onto);
function Vec3f64 vec3f64_snap_to_grid(Vec3f64 vector, f32 grid_size);
function Vec3f64 vec3f64_cross_product(Vec3f64 a, Vec3f64 b);
function Vec3f64 vec3f64_rotate_axis_angle(Vec3f64 vector, Vec3f64 axis, f32 radians);
function Vec3f64 vec3f64_from_to_rotation(Vec3f64 from, Vec3f64 to);
function Vec3f64 vec3f64_normal_from_triangle(Vec3f64 a, Vec3f64 b, Vec3f64 c);
function f32 vec3f64_dot_product(Vec3f64 a, Vec3f64 b);
function f32 vec3f64_length(Vec3f64 vector);
function f32 vec3f64_length_squared(Vec3f64 vector);
function f32 vec3f64_distance(Vec3f64 a, Vec3f64 b);
function f32 vec3f64_distance_squared(Vec3f64 a, Vec3f64 b);
function f32 vec3f64_angle_between(Vec3f64 a, Vec3f64 b);

// Vector4
// -------// Vec4u32
function Vec4u32 vector4_add(Vec4u32 a, Vec4u32 b);
function Vec4u32 vector4_subtract(Vec4u32 a, Vec4u32 b);
function Vec4u32 vector4_multiply(Vec4u32 a, Vec4u32 b);
function Vec4u32 vector4_divide(Vec4u32 a, Vec4u32 b);
function Vec4u32 vector4_scale(Vec4u32 vector, f32 scalar);
function Vec4u32 vector4_negate(Vec4u32 vector);
function Vec4u32 vector4_normalize(Vec4u32 vector);
function Vec4u32 vector4_linear_interpolate(Vec4u32 a, Vec4u32 b, f32 t);
function Vec4u32 vector4_minimum(Vec4u32 a, Vec4u32 b);
function Vec4u32 vector4_maximum(Vec4u32 a, Vec4u32 b);
function Vec4u32 vector4_clamp(Vec4u32 vector, Vec4u32 minimum, Vec4u32 maximum);
function Vec4u32 vector4_absolute(Vec4u32 vector);
function Vec4u32 vector4_reflect(Vec4u32 incident, Vec4u32 normal);
function Vec4u32 vector4_project(Vec4u32 vector, Vec4u32 onto);
function Vec4u32 vector4_snap_to_grid(Vec4u32 vector, f32 grid_size);
function Vec4u32 vector4_homogenize(Vec4u32 vector);
function f32 vector4_dot_product(Vec4u32 a, Vec4u32 b);
function f32 vector4_length(Vec4u32 vector);
function f32 vector4_length_squared(Vec4u32 vector);
function f32 vector4_distance(Vec4u32 a, Vec4u32 b);
function f32 vector4_distance_squared(Vec4u32 a, Vec4u32 b);
function f32 vector4_angle_between(Vec4u32 a, Vec4u32 b);
function f32 vector4_min_component(Vec4u32 vector);
function f32 vector4_max_component(Vec4u32 vector);

// Vec4u64
function Vec4u64 vector4_add(Vec4u64 a, Vec4u64 b);
function Vec4u64 vector4_subtract(Vec4u64 a, Vec4u64 b);
function Vec4u64 vector4_multiply(Vec4u64 a, Vec4u64 b);
function Vec4u64 vector4_divide(Vec4u64 a, Vec4u64 b);
function Vec4u64 vector4_scale(Vec4u64 vector, f32 scalar);
function Vec4u64 vector4_negate(Vec4u64 vector);
function Vec4u64 vector4_normalize(Vec4u64 vector);
function Vec4u64 vector4_linear_interpolate(Vec4u64 a, Vec4u64 b, f32 t);
function Vec4u64 vector4_minimum(Vec4u64 a, Vec4u64 b);
function Vec4u64 vector4_maximum(Vec4u64 a, Vec4u64 b);
function Vec4u64 vector4_clamp(Vec4u64 vector, Vec4u64 minimum, Vec4u64 maximum);
function Vec4u64 vector4_absolute(Vec4u64 vector);
function Vec4u64 vector4_reflect(Vec4u64 incident, Vec4u64 normal);
function Vec4u64 vector4_project(Vec4u64 vector, Vec4u64 onto);
function Vec4u64 vector4_snap_to_grid(Vec4u64 vector, f32 grid_size);
function Vec4u64 vector4_homogenize(Vec4u64 vector);
function f32 vector4_dot_product(Vec4u64 a, Vec4u64 b);
function f32 vector4_length(Vec4u64 vector);
function f32 vector4_length_squared(Vec4u64 vector);
function f32 vector4_distance(Vec4u64 a, Vec4u64 b);
function f32 vector4_distance_squared(Vec4u64 a, Vec4u64 b);
function f32 vector4_angle_between(Vec4u64 a, Vec4u64 b);
function f32 vector4_min_component(Vec4u64 vector);
function f32 vector4_max_component(Vec4u64 vector);

// Vec4s32
function Vec4s32 vector4_add(Vec4s32 a, Vec4s32 b);
function Vec4s32 vector4_subtract(Vec4s32 a, Vec4s32 b);
function Vec4s32 vector4_multiply(Vec4s32 a, Vec4s32 b);
function Vec4s32 vector4_divide(Vec4s32 a, Vec4s32 b);
function Vec4s32 vector4_scale(Vec4s32 vector, f32 scalar);
function Vec4s32 vector4_negate(Vec4s32 vector);
function Vec4s32 vector4_normalize(Vec4s32 vector);
function Vec4s32 vector4_linear_interpolate(Vec4s32 a, Vec4s32 b, f32 t);
function Vec4s32 vector4_minimum(Vec4s32 a, Vec4s32 b);
function Vec4s32 vector4_maximum(Vec4s32 a, Vec4s32 b);
function Vec4s32 vector4_clamp(Vec4s32 vector, Vec4s32 minimum, Vec4s32 maximum);
function Vec4s32 vector4_absolute(Vec4s32 vector);
function Vec4s32 vector4_reflect(Vec4s32 incident, Vec4s32 normal);
function Vec4s32 vector4_project(Vec4s32 vector, Vec4s32 onto);
function Vec4s32 vector4_snap_to_grid(Vec4s32 vector, f32 grid_size);
function Vec4s32 vector4_homogenize(Vec4s32 vector);
function f32 vector4_dot_product(Vec4s32 a, Vec4s32 b);
function f32 vector4_length(Vec4s32 vector);
function f32 vector4_length_squared(Vec4s32 vector);
function f32 vector4_distance(Vec4s32 a, Vec4s32 b);
function f32 vector4_distance_squared(Vec4s32 a, Vec4s32 b);
function f32 vector4_angle_between(Vec4s32 a, Vec4s32 b);
function f32 vector4_min_component(Vec4s32 vector);
function f32 vector4_max_component(Vec4s32 vector);

// Vec4s64
function Vec4s64 vector4_add(Vec4s64 a, Vec4s64 b);
function Vec4s64 vector4_subtract(Vec4s64 a, Vec4s64 b);
function Vec4s64 vector4_multiply(Vec4s64 a, Vec4s64 b);
function Vec4s64 vector4_divide(Vec4s64 a, Vec4s64 b);
function Vec4s64 vector4_scale(Vec4s64 vector, f32 scalar);
function Vec4s64 vector4_negate(Vec4s64 vector);
function Vec4s64 vector4_normalize(Vec4s64 vector);
function Vec4s64 vector4_linear_interpolate(Vec4s64 a, Vec4s64 b, f32 t);
function Vec4s64 vector4_minimum(Vec4s64 a, Vec4s64 b);
function Vec4s64 vector4_maximum(Vec4s64 a, Vec4s64 b);
function Vec4s64 vector4_clamp(Vec4s64 vector, Vec4s64 minimum, Vec4s64 maximum);
function Vec4s64 vector4_absolute(Vec4s64 vector);
function Vec4s64 vector4_reflect(Vec4s64 incident, Vec4s64 normal);
function Vec4s64 vector4_project(Vec4s64 vector, Vec4s64 onto);
function Vec4s64 vector4_snap_to_grid(Vec4s64 vector, f32 grid_size);
function Vec4s64 vector4_homogenize(Vec4s64 vector);
function f32 vector4_dot_product(Vec4s64 a, Vec4s64 b);
function f32 vector4_length(Vec4s64 vector);
function f32 vector4_length_squared(Vec4s64 vector);
function f32 vector4_distance(Vec4s64 a, Vec4s64 b);
function f32 vector4_distance_squared(Vec4s64 a, Vec4s64 b);
function f32 vector4_angle_between(Vec4s64 a, Vec4s64 b);
function f32 vector4_min_component(Vec4s64 vector);
function f32 vector4_max_component(Vec4s64 vector);

// Vec4f32
function Vec4f32 vector4_add(Vec4f32 a, Vec4f32 b);
function Vec4f32 vector4_subtract(Vec4f32 a, Vec4f32 b);
function Vec4f32 vector4_multiply(Vec4f32 a, Vec4f32 b);
function Vec4f32 vector4_divide(Vec4f32 a, Vec4f32 b);
function Vec4f32 vector4_scale(Vec4f32 vector, f32 scalar);
function Vec4f32 vector4_negate(Vec4f32 vector);
function Vec4f32 vector4_normalize(Vec4f32 vector);
function Vec4f32 vector4_linear_interpolate(Vec4f32 a, Vec4f32 b, f32 t);
function Vec4f32 vector4_minimum(Vec4f32 a, Vec4f32 b);
function Vec4f32 vector4_maximum(Vec4f32 a, Vec4f32 b);
function Vec4f32 vector4_clamp(Vec4f32 vector, Vec4f32 minimum, Vec4f32 maximum);
function Vec4f32 vector4_absolute(Vec4f32 vector);
function Vec4f32 vector4_reflect(Vec4f32 incident, Vec4f32 normal);
function Vec4f32 vector4_project(Vec4f32 vector, Vec4f32 onto);
function Vec4f32 vector4_snap_to_grid(Vec4f32 vector, f32 grid_size);
function Vec4f32 vector4_homogenize(Vec4f32 vector);
function f32 vector4_dot_product(Vec4f32 a, Vec4f32 b);
function f32 vector4_length(Vec4f32 vector);
function f32 vector4_length_squared(Vec4f32 vector);
function f32 vector4_distance(Vec4f32 a, Vec4f32 b);
function f32 vector4_distance_squared(Vec4f32 a, Vec4f32 b);
function f32 vector4_angle_between(Vec4f32 a, Vec4f32 b);
function f32 vector4_min_component(Vec4f32 vector);
function f32 vector4_max_component(Vec4f32 vector);

// Vec4f64
function Vec4f64 vector4_add(Vec4f64 a, Vec4f64 b);
function Vec4f64 vector4_subtract(Vec4f64 a, Vec4f64 b);
function Vec4f64 vector4_multiply(Vec4f64 a, Vec4f64 b);
function Vec4f64 vector4_divide(Vec4f64 a, Vec4f64 b);
function Vec4f64 vector4_scale(Vec4f64 vector, f32 scalar);
function Vec4f64 vector4_negate(Vec4f64 vector);
function Vec4f64 vector4_normalize(Vec4f64 vector);
function Vec4f64 vector4_linear_interpolate(Vec4f64 a, Vec4f64 b, f32 t);
function Vec4f64 vector4_minimum(Vec4f64 a, Vec4f64 b);
function Vec4f64 vector4_maximum(Vec4f64 a, Vec4f64 b);
function Vec4f64 vector4_clamp(Vec4f64 vector, Vec4f64 minimum, Vec4f64 maximum);
function Vec4f64 vector4_absolute(Vec4f64 vector);
function Vec4f64 vector4_reflect(Vec4f64 incident, Vec4f64 normal);
function Vec4f64 vector4_project(Vec4f64 vector, Vec4f64 onto);
function Vec4f64 vector4_snap_to_grid(Vec4f64 vector, f32 grid_size);
function Vec4f64 vector4_homogenize(Vec4f64 vector);
function f32 vector4_dot_product(Vec4f64 a, Vec4f64 b);
function f32 vector4_length(Vec4f64 vector);
function f32 vector4_length_squared(Vec4f64 vector);
function f32 vector4_distance(Vec4f64 a, Vec4f64 b);
function f32 vector4_distance_squared(Vec4f64 a, Vec4f64 b);
function f32 vector4_angle_between(Vec4f64 a, Vec4f64 b);
function f32 vector4_min_component(Vec4f64 vector);
function f32 vector4_max_component(Vec4f64 vector);


#endif // UI_HEPHAESTUS_H