#include "main.h"

#define FZ_CAMERA_SPEED 8.0f

function void
entry_point(Command_Line* command_line)
{
  os_console_init();
  os_window_init(400, 400, Project_Name);
  os_opengl_init();
  os_window_open();

  renderer_init();

  camera_init(&g_camera);
  g_camera.position = vec3f32(0.0f, 0.0f, 10.0f);
  camera_look_at(&g_camera, vec3f32(0.0f, 0.0f, 0.0f));

  g_frame_timer = os_timer_start();
  g_delta_time  = 0.0f;
  
  while(os_is_application_running())
  {
    input_update();
    camera_update(&g_camera, g_delta_time);
    camera_print(&g_camera);

    renderer_begin_frame();

    renderer_draw_2dquad(vec2f32(50.f, 100.f), vec2f32(15.f, 20.f), vec4f32(1.0f, 0.0f, 0.0f, 1.0f));
    renderer_draw_2dquad(vec2f32(70.f, 100.f), vec2f32(15.f, 20.f), vec4f32(0.0f, 1.0f, 0.0f, 1.0f));
    renderer_draw_2dquad(vec2f32(90.f, 100.f), vec2f32(15.f, 20.f), vec4f32(0.0f, 0.0f, 1.0f, 1.0f));

    Vec3f32 quad_position = vec3f32(1.0f, 1.0f, 0.9f);
    Vec3f32 quad_scale    = vec3f32(2.0f, 2.0f, 1.0f);
    Vec4f32 quad_color    = vec4f32(1.0f, 0.0f, 0.0f, 1.0f);
    renderer_draw_3dquad(quad_position, quad_scale, quad_color);

    Mat4f32 view       = camera_get_view_matrix(&g_camera);
    Mat4f32 projection = mat4f32_perspective(g_camera.fov, g_os_window->dimensions.x, g_os_window->dimensions.y, 0.1f, 100.0f);

    mat4f32_print(view, "View");
    mat4f32_print(projection, "Projection");

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
}