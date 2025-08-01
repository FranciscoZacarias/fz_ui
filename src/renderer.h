#ifndef RENDERER_H
#define RENDERER_H

#define VertexShader_Screenspace S("\\src\\shaders\\vs_quad_screenspace.glsl")
#define VertexShader_Worldspace  S("\\src\\shaders\\vs_quad_worldspace.glsl")
#define FragmentShader           S("\\src\\shaders\\fs.glsl")


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
  {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
  {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
  {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 
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
    u32 pipeline;

    u32 vao;
    u32 instance_vbo;
    u32 unit_quad_vbo;

    u32 u_view_location;
    u32 u_projection_location;

    #define Max3DQuads Thousand(1)
    Quad3D* quads3d;
    u32 quads3d_count;
  } worldspace;
};

global Renderer g_renderer;

function void renderer_init();
function void renderer_begin_frame();
function void renderer_end_frame(Mat4f32 view, Mat4f32 projection);

function void renderer_draw_2dquad(Vec2f32 position, Vec2f32 scale, Vec4f32 color);
function void renderer_draw_3dquad(Vec3f32 position, Vec3f32 scale, Vec4f32 color);

function u32 renderer_compile_shader(String8 relative_path, GLenum shader_type);

#endif // RENDERER_H