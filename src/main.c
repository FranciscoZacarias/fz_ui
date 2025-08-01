#include "main.h"

function void
entry_point(Command_Line* command_line)
{
  os_console_init();
  os_window_init(400, 400, Project_Name);
  os_opengl_init();
  os_window_open();

  renderer_init();

  f32 i = 0;
  while(os_is_application_running())
  {
    input_update();
    renderer_begin_frame();

    renderer_draw_quad(vec2f32(50.f, 100.f), vec2f32(15.f, 20.f), vec4f32(1.0f, 0.0f, 0.0f, 1.0f));
    renderer_draw_quad(vec2f32(70.f, 100.f), vec2f32(15.f, 20.f), vec4f32(0.0f, 1.0f, 0.0f, 1.0f));
    renderer_draw_quad(vec2f32(90.f, 100.f), vec2f32(15.f, 20.f), vec4f32(0.0f, 0.0f, 1.0f, 1.0f));
    
    renderer_end_frame();
    os_swap_buffers();
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