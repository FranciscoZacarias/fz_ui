#include "main.h"

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(1280, 720, PROJECT_NAME, &g_input);
  os_opengl_init();
  os_window_open();

  String8 project_path = os_executable_path(arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  // Renderer
  r_init();

  // Time
  g_frame_timer = os_timer_start();

  // Frame arena
  Arena* frame_arena = arena_alloc();

  ui_init();

  while(os_is_application_running(&g_input))
  {
    // Begin frame
    {
      g_delta_time = (f32)os_timer_seconds(&g_frame_timer);
      g_fps = 1.0f / g_delta_time;
      g_frame_counter += 1;
      os_timer_reset(&g_frame_timer);
    }
    r_clear_color(vec4f32(0.25f, 0.75f, 1.0f, 1.0f));
    input_update();

    ui_begin();

    local_persist f32 x = 200;
    local_persist f32 y = 200;
    if (input_is_key_clicked(&g_input, Keyboard_Key_I)) {x+=10;}
    if (input_is_key_clicked(&g_input, Keyboard_Key_O)) {x-=10;}

    if (input_is_key_clicked(&g_input, Keyboard_Key_K)) {y+=10;}
    if (input_is_key_clicked(&g_input, Keyboard_Key_L)) {y-=10;}


    local_persist b32 a = false;

    ui_top_left(vec2f32(200,200))
    ui_size_fixed_x(x) ui_size_fixed_y(y)
    ui_window(S("Test Window"))
    {
      ui_padding_fixed(5)
      ui_row(S("Test Row"), 100)
      {
        ui_label(S("Label"));
        ui_button(S("Button 1"));
        ui_button(S("Button 2"));
        ui_checkbox(S("CB2"), &a);
      }
      ui_padding_fixed(5)
      ui_row(S("Test Row 2"), 100)
      {
        ui_checkbox(S("Checkbox"), &a);
      }
    }
    ui_end();
    
    r_render(mat4f32_identity(), mat4f32_identity());
    arena_clear(frame_arena);
  }

  ui_end();
}

function void
input_update()
{
  if (input_is_key_down(&g_input, Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }
}