#include "main.h"

#define FZ_CAMERA_SPEED 8.0f

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(600, 600, Project_Name);
  os_opengl_init();
  os_window_open();

  String8 project_path = os_executable_path(arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  // Renderer
  renderer_init();
  Texture_Info black = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\black.png")));
  Texture_Info red   = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\red.png")));
  Texture_Info pink   = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\pink.png")));
  Texture_Info yelow   = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\yelow.png")));

  // Camera
  camera_init(&g_camera);
  g_camera.position = vec3f32(-1.0f, 1.0f, 5.0f);
  camera_look_at(&g_camera, vec3f32(0.0f, 0.0f, 0.0f));

  // Time
  g_frame_timer = os_timer_start();
  g_delta_time  = 0.0f;
  g_fps         = 0.0f;
  
  os_window_enable_vsync(true); // Enabled by default.
  while(os_is_application_running())
  {
    f32 g_fps = 1.0f / g_delta_time;
    input_update();
    camera_update(&g_camera, g_delta_time);

    renderer_begin_frame();

    renderer_draw_3darrow(vec3f32(-4.0f,   0.0f,   0.0f), vec3f32(4.0f, 0.0f,  0.0), Color_Red);
    renderer_draw_3darrow(vec3f32(  0.0f, -4.0f,   0.0f), vec3f32(0.0f, 4.0f,  0.0), Color_Green);
    renderer_draw_3darrow(vec3f32(  0.0f,   0.0f, -4.0f), vec3f32(0.0f,  0.0f, 4.0), Color_Blue);

    renderer_draw_3dquad(vec3f32(0.0f, 0.0f, 0.0f), vec3f32(2.0f, 2.0f, 1.0f), Color_Brown);
    renderer_draw_3dquad_texture(vec3f32( 2.0f,  2.0f, -2.0f), vec3f32(2.0f, 2.0f, 1.0f), Color_White, black.index);
    renderer_draw_3dquad_texture(vec3f32(-2.0f,  2.0f, -2.0f), vec3f32(2.0f, 2.0f, 1.0f), Color_White, red.index);
    renderer_draw_3dquad_texture(vec3f32( 2.0f, -2.0f, -2.0f), vec3f32(2.0f, 2.0f, 1.0f), Color_White, pink.index);
    renderer_draw_3dquad_texture(vec3f32(-2.0f, -2.0f, -2.0f), vec3f32(2.0f, 2.0f, 1.0f), Color_White, yelow.index);

    renderer_draw_2dquad(vec2f32(50.f, 100.f), vec2f32(15.f, 20.f), vec4f32(1.0f, 0.0f, 0.0f, 1.0f));
    renderer_draw_2dquad(vec2f32(70.f, 100.f), vec2f32(15.f, 20.f), vec4f32(0.0f, 1.0f, 0.0f, 1.0f));
    renderer_draw_2dquad(vec2f32(90.f, 100.f), vec2f32(15.f, 20.f), vec4f32(0.0f, 0.0f, 1.0f, 1.0f));
    
    renderer_draw_2dquad_texture(vec2f32(90.f, 300.f), vec2f32(50.f, 50.f), Color_White, red.index);

    renderer_draw_text_screenspace(vec2f32(50.f, 500.f), Color_Black, 0.8f, Sf(arena, "We are not your kind. FPS: %.2f", g_fps));

    Mat4f32 view       = camera_get_view_matrix(&g_camera);
    Mat4f32 projection = mat4f32_perspective(g_camera.fov, g_os_window->dimensions.x, g_os_window->dimensions.y, 0.1f, 100.0f);
      
    renderer_end_frame(view, projection);

    g_delta_time = (f32)os_timer_seconds(&g_frame_timer);
    os_timer_reset(&g_frame_timer);
  }
}

function void
input_update()
{
  if (input_is_key_pressed(Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }

  if (input_is_key_pressed(Keyboard_Key_F2))
  {
    renderer_toggle_wireframe();
  }
}