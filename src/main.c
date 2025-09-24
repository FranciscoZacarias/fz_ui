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

  Texture_Info t = r_load_texture(S("C:/Personal/fz_render_2d/assets/textures/prototype/Grey 2.png"));
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

    simulation(frame_arena);

  //  r_draw_triangle(vec2f32(100,100), vec2f32(100,100), Radians(90), RED(1.0f));
  //  r_draw_triangle_texture(vec2f32(210,100), vec2f32(100,100), 0, vec2f32(0,0), vec2f32(1,1), WHITE(1), t.index);
  //  r_draw_quad(vec2f32(320,100), vec2f32(100,100), 0, PURPLE(1));
  //  r_draw_quad_texture(vec2f32(430,100), vec2f32(100,100), 0, vec2f32(0,0), vec2f32(1,1), WHITE(1), t.index);
  //  r_draw_quad(vec2f32(550,100), vec2f32(100,100), Radians(30), BLUE(1));

    r_draw_line(vec2f32(0, 16), vec2f32(16,16), BLACK(1));
    r_draw_line(vec2f32(16, 0), vec2f32(16,16), BLACK(1));
    r_draw_text(vec2f32(16,16), 128, BLACK(1), S("We are not your kind\nWe are not your kind"));

    r_render(g_camera.view, g_camera.projection);
    arena_clear(frame_arena);
  }
}

function void
simulation(Arena* frame_arena)
{
  camera2d_update(&g_camera, g_input, g_delta_time);

  // Grid
  if (0)
  {
    Vec2f32 p0 = vec2f32(-512.0f, -512.0f);
    Vec2f32 p1 = vec2f32(512.0f, 512.0f);
    f32 square_size_pixel = 64.0f;
    Color color = BLACK(0.1);

    f32 width = p1.x - p0.x;
    f32 height = p1.y - p0.y;
 
    u32 vertical_lines = (u32)(width / square_size_pixel) + 1;
    u32 horizontal_lines = (u32)(height / square_size_pixel) + 1;
 
    for (u32 i = 0; i < vertical_lines; ++i)
    {
      f32 x = p0.x + i * square_size_pixel;
      if (x <= p1.x)
      {
        //r_draw_ws_line(vec2f32(x, p0.y), vec2f32(x, p1.y), color);
      }
    }
 
    for (u32 i = 0; i < horizontal_lines; ++i)
    {
      f32 y = p0.y + i * square_size_pixel;
      if (y <= p1.y)
      {
        //r_draw_ws_line(vec2f32(p0.x, y), vec2f32(p1.x, y), color);
      }
    }
  }

  u8* time_now = cstring_from_string8(frame_arena, os_datetime_to_string8(frame_arena, os_datetime_now(), false));
  //r_draw_2d_text(vec2f32(10.0f, g_os_window.dimensions.y - 15.0f), 24.0f, BLACK(1.0f), Sf(frame_arena, "%s\nFPS: %.2f\nFrame Counter: %d", time_now, g_fps, g_frame_counter));
}

function void
input_update()
{
  if (input_is_key_down(&g_input, Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }

  if (input_is_key_down(&g_input, Keyboard_Key_F11))
  {
    local_persist b32 set_wireframe = true;
    r_set_wireframe(set_wireframe);
    set_wireframe = !set_wireframe;
  }

  if (input_is_key_down(&g_input, Keyboard_Key_F12))
  {
    local_persist b32 is_vsync_on = false;
    os_window_set_vsync(is_vsync_on);
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