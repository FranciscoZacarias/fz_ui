#ifndef RENDERER_H
#define RENDERER_H

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "fz_std\\external\\stb_image.h"

#define V_Quad_Screenspace S("\\src\\shaders\\vs_quad_screenspace.glsl")
#define V_Quad_Worldspace  S("\\src\\shaders\\vs_quad_worldspace.glsl")
#define V_Line_Worldspace  S("\\src\\shaders\\vs_line_worldspace.glsl")
#define F_Default          S("\\src\\shaders\\fs.glsl")

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
typedef struct Quad3D Quad3D;
struct Quad3D
{
  Vec3f32 position;
  Vec3f32 scale;
  Vec4f32 color;
};
global Vec3f32 unit_3dquad[6] = {
  { -0.5f, -0.5f, 0.0f }, {  0.5f, -0.5f, 0.0f },
  {  0.5f,  0.5f, 0.0f }, { -0.5f, -0.5f, 0.0f },
  {  0.5f,  0.5f, 0.0f }, { -0.5f,  0.5f, 0.0f },
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
// @Section: Renderer
typedef struct Renderer Renderer;
struct Renderer
{
  Arena* arena;
  
  struct
  {
    u32 v_screenspace_quad;
    u32 v_worldspace_quad;
    u32 v_worldspace_line;
    u32 f_default;
  } shaders;

  struct
  {
    u32 pipeline;

    u32 vao;
    u32 instance_vbo;
    u32 unit_quad_vbo;

    u32 u_screen_size_location;

    #define Max2DQuads Thousand(10)
    Quad2D* quads2d;
    u32 quads2d_count;
  } screenspace;

  struct
  {
    // Quads
    u32 quads3d_pipeline;

    u32 vao;
    u32 instance_vbo;
    u32 unit_quad_vbo;

    u32 u_quad_view_location;
    u32 u_quad_projection_location;

    #define Max3DQuads Thousand(1)
    Quad3D* quads3d;
    u32 quads3d_count;

    // Lines
    u32 lines3d_pipeline;

    u32 lines_vao;
    u32 lines_instance_vbo;
    u32 unit_line_vbo;

    u32 u_line_view_location;
    u32 u_line_projection_location;

    #define Max3DLines Thousand(1)
    Line3D* lines3d;
    u32 lines3d_count;
  } worldspace;

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

function void renderer_draw_2dquad(Vec2f32 position, Vec2f32 scale, Vec4f32 color);
function void renderer_draw_3dquad(Vec3f32 position, Vec3f32 scale, Vec4f32 color);

function u32 renderer_load_texture(String8 path);
function u32 renderer_load_font(String8 path, f32 font_height);

function u32 renderer_compile_shader(String8 relative_path, GLenum shader_type);

#endif // RENDERER_H