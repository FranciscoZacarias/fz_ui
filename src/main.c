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

#if 0
    ui_stack_defer(top_left, vec2f32(2,2))
    ui_window(S("fz_ui config"))
    {
      ui_row(S("font size"), 20)
      {
        ui_stack_defer(size_y, 20)
        ui_stack_defer(size_x, 20)
        ui_stack_defer(spacing_right, 5)
        if (ui_clicked(ui_button(S("-"))))
        {
          ui_context.text_pixel_height -= 1;
        }
        ui_stack_defer(size_y, 20)
        ui_stack_defer(size_x, 20)
        if (ui_clicked(ui_button(S("+"))))
        {
          ui_context.text_pixel_height += 1;
        }
        ui_label(S("UI Font size"));
      }
      if (ui_clicked(ui_button(S("ui debug"))))
      {
        ui_context.debug.show_bounds = !ui_context.debug.show_bounds;
        ui_context.debug.show_clip   = !ui_context.debug.show_clip;
        ui_context.debug.show_cursor = !ui_context.debug.show_cursor;
      }
    }
#endif

    ui_top_left(vec2f32(250,200))
    ui_size_x(300) ui_size_y(300)
    ui_window(S("Test Window"))
    {
#if 0
      //ui_stack_defer(padding_x, 4.0f) ui_stack_defer(padding_y, 4.0f)
      ui_row(S("Horizontal buttons"), 30)
      {
        for (u32 i = 0; i < 2; i += 1)
        {
          ui_stack_defer(spacing_right, 10)
          ui_button(Sf(frame_arena, "Same Name!##%d", i));
        }
      }
      //ui_stack_defer(padding_x, 4.0f) ui_stack_defer(padding_y, 4.0f)
      ui_column(S("Vertical buttons"), 90)
      {
        ui_button(S("Button C"));
        ui_button(S("Button D"));
      }
#endif
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