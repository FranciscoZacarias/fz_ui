#ifndef RENDERER_H
#define RENDERER_H

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "fz_std\\external\\stb_image.h"

// Fonts
#define Font_ProggyClean S("\\assets\\fonts\\ProggyClean.ttf")
#define Font_Inconsolata S("\\assets\\fonts\\Inconsolata.ttf")
#define Font_Karmina     S("\\assets\\fonts\\Karmina.otf")

///////////////////////////////////////////////////////
// @Section: Screenspace primitives

// Vertex Shaders
#define V_SS_Quad_Path S("\\src\\shaders\\v_ss_quad.glsl")
#define V_SS_Text_Path S("\\src\\shaders\\v_ss_text.glsl")
#define V_WS_Quad_Path S("\\src\\shaders\\v_ws_quad.glsl")
#define V_WS_Line_Path S("\\src\\shaders\\v_ws_line.glsl")

// Fragment Shaders
#define F_Texture_Path S("\\src\\shaders\\f_texture.glsl")
#define F_Text_Path    S("\\src\\shaders\\f_text.glsl")
#define F_Line_Path    S("\\src\\shaders\\f_line.glsl")

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
  Vec2f32 uv_min;
  Vec2f32 uv_max;
  Vec4f32 color;
  u32 texture_id;
};
global Vec2f32 unit_2dquad[6] = {
  { -0.5f, -0.5f }, {  0.5f, -0.5f },
  {  0.5f,  0.5f }, { -0.5f, -0.5f },
  {  0.5f,  0.5f }, { -0.5f,  0.5f }
};

///////////////////////////////////////////////////////
// @Section: Worldspace primitives
typedef struct Primitive3D Primitive3D;
struct Primitive3D
{
  Transformf32 transform;
  Vec2f32 uv_min;
  Vec2f32 uv_max;
  Vec3f32 normal;
  Vec4f32 color;
  u32 texture_id;
};

// Triangles
global Vec3f32 unit_3dtriangle[3] = {
  { -0.5f, -0.5f, 0.0f }, 
  {  0.5f, -0.5f, 0.0f },
  { -0.5f,  0.5f, 0.0f }
};

// Quad
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

///////////////////////////////////////////////////////
// @Section: Fonts
typedef struct Glyph Glyph;
struct Glyph
{
  Vec2f32 uv_min; /* Top left texture coordinate in atlas */
  Vec2f32 uv_max; /* Bottom right texture coordinate in atlas */
  Vec2f32 size; /* Pixel dimensions */
  Vec2f32 offset; /* Pixel offset from the baseline cursor position to where the glyph should be drawn. X is horizontal offset from cursor, Y is vertical offset from baseline (negative Y means above baseline) */
  f32     advance; /* How far - horizontally - to move the cursor after drawing this glyph */
};

typedef struct Font Font;
struct Font
{
  #define MaxFontGlyphs 95
  Glyph glyphs[MaxFontGlyphs];
  u32   texture_id; /* Opengl texture handle for the atlas */
  u32   texture_index; /* Index into renderer's texture array */
  f32   height; /* Pixel size requested when loading the font */
  f32   line_height; /* Total pixels between baselines when stacking text */
  f32   ascent; /* Pixels from baseline to highest any glyph can reach */
  f32   descent; /* Pixels brom baseline to lowest any glyph can reach */
  f32   line_gap; /* Additional spacing between lines */
};

///////////////////////////////////////////////////////
// @Section: Instanced Target
typedef enum
{
  IT_Kind_Screenspace_quad,
  IT_Kind_Screenspace_text,
  IT_Kind_Worldspace_quad,
  IT_Kind_Worldspace_text,
  IT_Kind_Worldspace_line,
} Instanced_Target_Kind;

typedef struct Render_Batch Render_Batch;
struct Render_Batch
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
    u32 v_ss_quad;
    u32 v_ss_text;
    u32 v_ws_quad;
    u32 v_ws_line;
    u32 f_line;
    u32 f_texture;
    u32 f_text;
  } shaders;

  // Screenspace
  Render_Batch* ss_quad;
  Render_Batch* ss_text;

  // Worldspace
  Render_Batch* ws_triangle;
  Render_Batch* ws_quad;
  Render_Batch* ws_text;
  Render_Batch* ws_line;

  // Textures
  u32* textures;
  u32 texture_count;
  u32 texture_max;

  // Fonts
  Font* fonts;
  u32 fonts_count;
  u32 fonts_max;
};

global Renderer g_renderer;

function void r_init();
function void r_render(Mat4f32 view, Mat4f32 projection);

function void    r_draw_2dquad(Vec2f32 position, Vec2f32 scale, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id);
function Vec2f32 r_draw_2dtext(Vec2f32 position, Vec4f32 color, f32 scale, String8 text);

function void    r_draw_3dtriangle(Transformf32 transform, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id);
function void    r_draw_3dquad(Transformf32 transform, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id);
function void    r_draw_3dtext(Transformf32 transform, Vec4f32 color, f32 font_scale, String8 text);
function void    r_draw_3dline(Vec3f32 p0, Vec3f32 p1, Vec4f32 color);
function void    r_draw_3darrow(Vec3f32 start, Vec3f32 end, Vec4f32 color);

function Texture_Info  r_load_texture(String8 path);
function void          r_create_fallback_texture();
function Texture_Info  r_create_color_texture(Vec4f32 color);
function void          r_load_font(String8 relative_path, f32 font_height);
function Render_Batch* r_new_render_batch(Arena* arena, Instanced_Target_Kind kind, u32 max_instances);

function void r_toggle_wireframe();
function void r_toggle_facecull();
function u32  r_compile_shader(String8 relative_path, GLenum shader_type);

#endif // RENDERER_H