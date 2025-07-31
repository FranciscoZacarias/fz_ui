#ifndef RENDERER_H
#define RENDERER_H

#define VertexShader_Screenspace S("\\src\\shaders\\vs_screenspace.glsl")
#define FragmentShader           S("\\src\\shaders\\fs.glsl")

///////////////////////////////////////////////////////
// @Section: Renderer Primitives

typedef enum
{
  Entity_Kind_Quad2D,

  Entity_Kind_Count
} Entity_Kind;

typedef struct Vertex Vertex;
struct Vertex
{
  Vec2f32 position;
  Vec4f32 color;
};

typedef struct Quad2D Quad2D;
struct Quad2D
{
  Vec2f32 scale;
  Vertex  p0;
};

///////////////////////////////////////////////////////
// @Section: Renderer

typedef struct Renderer Renderer;
struct Renderer
{
  Arena* arena;

  u32 vao;
  u32 vbo;

  u32 vs;
  u32 fs;
  u32 pipeline;
};

global Renderer g_renderer;

function void renderer_init();
function void renderer_begin_frame();
function void renderer_end_frame();

function void renderer_draw_quad(Vec2f32 position, Vec2f32 scale, Vec4f32 color);

function u32 renderer_compile_shader(String8 relative_path, GLenum shader_type);


#endif // RENDERER_H