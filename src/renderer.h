#ifndef RENDERER_H
#define RENDERER_H

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "fz_std\\external\\stb_image.h"

#define V_Quad_Screenspace         S("\\src\\shaders\\vs_quad_screenspace.glsl")
#define V_Quad_Worldspace          S("\\src\\shaders\\vs_quad_worldspace.glsl")
#define V_Quad_Texture_Worldspace  S("\\src\\shaders\\vs_quad_texture_worldspace.glsl")
#define V_Line_Worldspace          S("\\src\\shaders\\vs_line_worldspace.glsl")
#define F_Default                  S("\\src\\shaders\\fs.glsl")
#define F_Texture                  S("\\src\\shaders\\fs_texture.glsl")

///////////////////////////////////////////////////////
// @Section: Texture
typedef struct Texture_Info Texture_Info;
struct Texture_Info
{
  u32 handle;
  u32 index;
  u32 width;
  u32 height;
};

///////////////////////////////////////////////////////
// @Section: Screenspace primitives
typedef struct Quad2D Quad2D;
struct Quad2D
{
  Vec2f32 position;
  Vec2f32 scale;
  Vec4f32 color;
};
global Vec2f32 unit_2dquad[6] = {
  {0.0f, 0.0f}, {1.0f, 0.0f},
  {1.0f, 1.0f}, {0.0f, 0.0f},
  {1.0f, 1.0f}, {0.0f, 1.0f}
};
global Vec2f32 unit_2dquad_uv[6] = {
  {0.0f, 0.0f}, {1.0f, 0.0f},
  {1.0f, 1.0f}, {0.0f, 0.0f},
  {1.0f, 1.0f}, {0.0f, 1.0f}
};

///////////////////////////////////////////////////////
// @Section: Worldspace primitives
typedef struct TexturedQuad3D TexturedQuad3D;
struct TexturedQuad3D
{
  Vec3f32 position;
  Vec3f32 scale;
  Vec4f32 color;
  u32 texture_id;
};
typedef struct Quad3D Quad3D;
struct Quad3D
{
  Vec3f32 position;
  Vec3f32 scale;
  Vec4f32 color;
};
global Vec3f32 unit_3dquad[6] = {
  {  0.5f,  0.5f, 0.0f }, { -0.5f,  0.5f, 0.0f },
  { -0.5f, -0.5f, 0.0f }, {  0.5f, -0.5f, 0.0f },
  {  0.5f,  0.5f, 0.0f }, { -0.5f, -0.5f, 0.0f }
};

typedef struct Line3D Line3D;
struct Line3D
{
  Vec3f32 p0;
  Vec3f32 p1;
  Vec4f32 color;
};
global Vec3f32 unit_line[] = {
  {0.0f, 0.0f, 0.0f},
  {1.0f, 0.0f, 0.0f},
};
 
///////////////////////////////////////////////////////
// @Section: Fonts
typedef struct Glyph Glyph;
struct Glyph
{
  Vec2f32 uv_min;
  Vec2f32 uv_max;
  Vec2f32 size;
  Vec2f32 offset;
  f32     advance;
};

typedef struct Font Font;
struct Font
{
  Glyph glyphs[95];
  u32   texture_id;
  f32   height;
  f32   line_height;
};

///////////////////////////////////////////////////////
// @Section: Instanced Target
typedef enum
{
  IT_Kind_Screenspace_quad,
  IT_Kind_Worldspace_quad,
  IT_Kind_Worldspace_quad_texture,
  IT_Kind_Worldspace_line,
} Instanced_Target_Kind;

typedef struct Instanced_Target Instanced_Target;
struct Instanced_Target
{
  Instanced_Target_Kind kind;

  u32 pipeline;

  // Buffers
  u32 vao;
  u32 unit_vbo;
  u32 instance_vbo;

  // Uniforms
  u32 u_screen_size_location;
  u32 u_view_location;
  u32 u_projection_location;

  // Instanced data
  void* data;   
  u32   stride; /* Size of data type used in data */
  u32   max;    /* Max allocated instances */
  u32   count;  /* Current instances count */
};

///////////////////////////////////////////////////////
// @Section: Renderer
typedef struct Renderer Renderer;
struct Renderer
{
  Arena* arena;

  struct
  {
    u32 v_screenspace_quad;
    u32 v_worldspace_quad;
    u32 v_worldspace_quad_texture;
    u32 v_worldspace_line;
    u32 f_default;
    u32 f_texture;
  } shaders;

  // Screenspace
  Instanced_Target* ss_quad;

  // Worldspace
  Instanced_Target* ws_quad;
  Instanced_Target* ws_quad_texture;
  Instanced_Target* ws_line;

  // Textures
  u32* textures;
  u32 texture_count;
  u32 texture_max;

  // Fonts
  Font font;
};

global Renderer g_renderer;

function void renderer_init();
function void renderer_begin_frame();
function void renderer_end_frame(Mat4f32 view, Mat4f32 projection);

function Instanced_Target* renderer_allocate_instanced_target(Arena* arena, Instanced_Target_Kind kind, u32 max_instances, void* unit_geometry_data, u32 unit_geometry_size, u32 unit_vertex_stride);

function void renderer_draw_2dquad(Vec2f32 position, Vec2f32 scale, Vec4f32 color);
function void renderer_draw_3dquad(Vec3f32 position, Vec3f32 scale, Vec4f32 color);
function void renderer_draw_3dquad_textured(Vec3f32 position, Vec3f32 scale, Vec4f32 color, u32 texture_id);
function void renderer_draw_3dline(Vec3f32 p0, Vec3f32 p1, Vec4f32 color);
function void renderer_draw_3darrow(Vec3f32 start, Vec3f32 end, Vec4f32 color);

function Texture_Info renderer_load_texture(String8 path);
function u32 renderer_load_font(String8 path, f32 font_height);

function u32 renderer_compile_shader(String8 relative_path, GLenum shader_type);

#endif // RENDERER_H