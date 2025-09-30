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

  // Camera
  g_camera = camera2d_init();

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
    ui_window(S("Test Window"))
    {
      ui_stack_defer(padding_x, 4.0f) ui_stack_defer(padding_y, 4.0f)
      ui_row(S("Horizontal buttons"), 50)
      {
        for (u32 i = 0; i < 2; i += 1)
        {
          ui_button(Sf(frame_arena, "Same Name!##%d", i));
        }
      }
      ui_column(S("Vertical buttons"), 90)
      {
        ui_button(S("Button C"));
        ui_button(S("Button D"));
      }
    }
    ui_end();
    
    r_render(g_camera.view, g_camera.projection);
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

function void
camera2d_update(Camera2D* camera, Input_State input,  f32 delta_time)
{
  f32 speed = 512.0;
  Vec2f32 move = vec2f32(0.0f, 0.0f);
  if (input_is_key_down(&g_input, Keyboard_Key_W))
  {
    move.y = 1;
  }
  if (input_is_key_down(&g_input, Keyboard_Key_S))
  {
    move.y = -1;
  }
  if (input_is_key_down(&g_input, Keyboard_Key_D))
  {
    move.x = 1;
  }
  if (input_is_key_down(&g_input, Keyboard_Key_A))
  {
    move.x = -1;
  }

  if (input_is_key_down(&g_input, Keyboard_Key_Q))
  {
    camera2d_zoom(camera, 0.01);
  }
  if (input_is_key_down(&g_input, Keyboard_Key_E))
  {
    camera2d_zoom(camera, -0.01);
  }

  Vec2f32 delta = vec2f32_normalize(move);
  delta = vec2f32_scale(delta, speed);
  delta = vec2f32_scale(delta, delta_time);
  camera2d_move(camera, delta);
}