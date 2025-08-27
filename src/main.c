#include "main.h"

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(400, 400, PROJECT_NAME, &g_input);
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
  u64 frame_arena_initial_position = frame_arena->position;

  g_tex_black = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\black.png")));
  g_tex_red   = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\red.png")));
  g_tex_color_blue = r_create_color_texture(COLOR_BLUE(1.0f));
  g_tex_color_yellow = r_create_color_texture(COLOR_YELLOW(1.0f));

  while(os_is_application_running(&g_input))
  {
    // Begin frame
    {
      g_delta_time = (f32)os_timer_seconds(&g_frame_timer);
      g_fps = 1.0f / g_delta_time;
      g_frame_counter += 1;
      os_timer_reset(&g_frame_timer);
    }

    input_update();
    simulation(frame_arena);
    r_render(g_camera.view, g_camera.projection);

    // Close frame
    {
      arena_pop_to(frame_arena, frame_arena_initial_position);
    }
  }
}

function void
simulation(Arena* frame_arena)
{
  camera2d_update(&g_camera, g_input, g_delta_time);

  r_draw_ws_grid(vec2f32(-512.0f, -512.0f), vec2f32(512.0f, 512.0f), 64.0f, COLOR_BLACK(0.1));

  u8* time_now = cstring_from_string8(frame_arena, os_datetime_to_string8(frame_arena, os_datetime_now(), false));
  r_draw_2d_text(vec2f32(10.0f, g_os_window.dimensions.y - 15.0f), 24.0f, COLOR_BLACK(1.0f), Sf(frame_arena, "%s\nFPS: %.2f\nFrame Counter: %d", time_now, g_fps, g_frame_counter));
}

function void
input_update()
{
  if (input_is_key_pressed(&g_input, Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }

  if (input_is_key_pressed(&g_input, Keyboard_Key_F11))
  {
    r_toggle_wireframe();
  }

  if (input_is_key_pressed(&g_input, Keyboard_Key_F12))
  {
    local_persist b32 is_vsync_on = true;
    os_window_enable_vsync(is_vsync_on ? false : true);
    is_vsync_on = !is_vsync_on;
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