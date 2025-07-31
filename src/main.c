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

    glClearColor(0.5, 0.96, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    renderer_draw_quad(vec2f32(-0.85f, 0.70f), vec2f32(0.1f, 0.15f), vec4f32(1.0f, 0.0f, 0.0f, 1.0f));
    renderer_draw_quad(vec2f32(-0.65f, 0.70f), vec2f32(0.1f, 0.15f), vec4f32(0.0f, 1.0f, 0.0f, 1.0f));
    renderer_draw_quad(vec2f32(-0.45f, 0.70f), vec2f32(0.1f, 0.15f), vec4f32(0.0f, 0.0f, 1.0f, 1.0f));
    
    renderer_end_frame();
    os_swap_buffers();
  }

  system("pause");
}

function void
input_update()
{
  if (input_is_key_pressed(Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }
}