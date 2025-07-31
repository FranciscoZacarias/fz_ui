#ifndef RENDERER_H
#define RENDERER_H

#define VertexShader_Screenspace S("/src/shaders/vertex_shader_screenspace.glsl")
#define FragmentShader           S("/src/shaders/fragment_shader.glsl")

///////////////////////////////////////////////////////
// @Section: Renderer Primitives
typedef struct Quad2D Quad2D;
struct Quad2D
{
  Vec2f32 position; /* Bottom left */
  Vec2f32 scale;
  Vec4f32 color;
};

///////////////////////////////////////////////////////
// @Section: Renderer

typedef struct Renderer Renderer;
struct Renderer
{
  Arena* arena;

  GLuint vao;
  GLuint vbo;

  GLuint vs;
  GLuint fs;
  GLuint pipeline;

  GLuint color_uniform;
};

global Renderer g_renderer;

function void renderer_init();
function void renderer_begin_frame();
function void renderer_end_frame();

function void renderer_draw_quad(Vec2f32 position, Vec2f32 scale, Vec4f32 color);


#endif // RENDERER_H