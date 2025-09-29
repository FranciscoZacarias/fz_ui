#ifndef RENDERER_H
#define RENDERER_H
// @namespace r

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "fz_std\\external\\stb_image.h"

// Fonts
#define FONT_PROGGY_CLEAN_PATH S("\\assets\\fonts\\ProggyClean.ttf")
#define FONT_INCONSOLATA_PATH  S("\\assets\\fonts\\Inconsolata.ttf")

// Vertex Shaders
#define V_PRIMITIVE_PATH S("\\src\\shaders\\v_primitive.glsl")
#define V_TEXT_PATH      S("\\src\\shaders\\v_text.glsl")
#define V_LINE_PATH      S("\\src\\shaders\\v_line.glsl")

// Fragment Shaders
#define F_TEXTURE_PATH S("\\src\\shaders\\f_texture.glsl")
#define F_TEXT_PATH    S("\\src\\shaders\\f_text.glsl")
#define F_COLOR_PATH   S("\\src\\shaders\\f_color.glsl")

typedef struct
{
  u32 handle;
  u32 index;
  u32 width;
  u32 height;
} Texture_Info;

#define NO_TEXTURE 0xFFFFFFFFu

typedef struct
{
  Vec2f32 p0;
  Vec2f32 p1;
  Color color;
  f32 depth;
} Line2D;

typedef struct
{
  Vec2f32 center;
  Vec2f32 scale;
  f32 rotation;
  Vec2f32 uv_min;
  Vec2f32 uv_max;
  Color color;
  u32 texture_id;
  f32 depth; /* With GL_LESS, the fragments with less depth are in front */
} Primitive2D;

global Vec2f32 unit_triangle[6] = {{-0.5f,-0.5f},{0.5f,-0.5f},{-0.5f,0.5f}};
global Vec2f32 unit_quad[6] = {{-0.5f,-0.5f},{0.5f,-0.5f},{0.5f,0.5f},{-0.5f,-0.5f},{0.5f,0.5f},{-0.5f,0.5f}};

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
  #define FONT_LOAD_SIZE 96
  #define MAX_FONT_GLYPHS 95
  Glyph glyphs[MAX_FONT_GLYPHS];
  u32   texture_id; /* Opengl texture handle for the atlas */
  u32   texture_index; /* Index into renderer's texture array */
  f32   height; /* Pixel size requested when loading the font */
  f32   line_height; /* Total pixels between baselines when stacking text. line_height = ascent + |descent| + line_gap */
  f32   ascent; /* Pixels from baseline to highest any glyph can reach */
  f32   descent; /* Pixels from baseline to lowest any glyph can reach */
  f32   line_gap; /* Additional spacing between lines */
};

typedef enum
{
  Render_Batch_Line,

  Render_Batch_Triangle,
  Render_Batch_Triangle_Texture,

  Render_Batch_Quad,
  Render_Batch_Quad_Texture,

  Render_Batch_Text,

  Render_Batch_Count,
} Render_Batch_Kind;

typedef struct Render_Batch Render_Batch;
struct Render_Batch
{
  Render_Batch_Kind kind;

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
  void* data; /* Data buffer */
  u32   stride; /* Size of data type used in data */
  u32   max; /* Max allocated instances */
  u32   count; /* Current instances count */
  u32   v_shader; /* Vertex shader used for this batch */
  u32   mode; /* Opengl render mode E.g. GL_TRIANGLES, GL_LINES... */
  u32   vertex_count; /* Vertices per instance */
};

typedef struct Renderer_Context Renderer_Context;
struct Renderer_Context
{
  Arena* arena;

  struct
  {
    u32 v_primitive;
    u32 v_text;
    u32 v_line;

    u32 f_color;
    u32 f_texture;
    u32 f_text;
  } shaders;

  Render_Batch* batches[Render_Batch_Count];

  // Textures
  u32* textures;
  u32 texture_count;
  u32 texture_max;

  // Fonts
  Font* fonts;
  u32 fonts_count;
  u32 fonts_max;

  // Config
  Font* selected_font;
  
};

global Renderer_Context g_renderer;

// Core
function void r_init();
function void r_render(Mat4f32 view, Mat4f32 projection);
function void r_render_batch(Render_Batch* batch, Mat4f32 view, Mat4f32 projection);

// Draw functions
function void r_draw_primitive(Render_Batch* render_batch, Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Vec2f32 uv_min, Vec2f32 uv_max, Color color, u32 texture_id, f32 depth); /* Used both for screenspace and worldspace, since they both share the same primitive type */
function void r_draw_line(Vec2f32 p0, Vec2f32 p1, Color color, f32 depth);

function void r_draw_triangle(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Color color, f32 depth);
function void r_draw_triangle_texture(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Vec2f32 uv_min, Vec2f32 uv_max, Color gradient, u32 texture_index, f32 depth);
function void r_draw_quad(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Color color, f32 depth);
function void r_draw_quad_texture(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Vec2f32 uv_min, Vec2f32 uv_max, Color gradient, u32 texture_index, f32 depth);
function void r_draw_text(Vec2f32 top_left, f32 pixel_height, Vec4f32 color, String8 text, f32 depth);
function void r_draw_text_ext(Vec2f32 top_left, f32 pixel_height, Color color, String8 text, f32 depth, f32 max_width, f32 max_height);

function void r_draw_point(Vec2f32 position, Color color, f32 depth);
function void r_draw_box(Vec2f32 top_left, Vec2f32 scale, Color color, f32 depth);

// Renderer Helpers
function Render_Batch* r_new_render_batch(Arena* arena, Render_Batch_Kind kind, u32 max_instances, u32 v_shader, u32 vertex_count, u32 mode);
function void          r_clear_color(Color color);
function void          r_create_fallback_texture();
function Texture_Info  r_load_texture(String8 path);
function Font*         r_load_font(String8 relative_path);
function Vec2f32       r_text_dimensions(String8 text, f32 pixel_height);
function Vec2f32       r_vec2f32_flip_y(Vec2f32 v);

// Opengl helpers
function u32           r_compile_shader(String8 relative_path, GLenum shader_type);
function void          r_set_wireframe(b32 set);
function void          r_set_vertex_attribute_f32(u32 vao, u32 index, u32 size, u32 divisor, u32 offset);
function void          r_set_vertex_attribute_u32(u32 vao, u32 index, u32 size, u32 divisor, u32 offset);

#endif // RENDERER_H
