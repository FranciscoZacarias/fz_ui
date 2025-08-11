#include "main.h"

Texture_Info g_tex_black;
Texture_Info g_tex_red;
Texture_Info g_blue;

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(1280, 720, PROJECT_NAME);
  os_opengl_init();
  os_window_open();

  String8 project_path = os_executable_path(arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  // Renderer
  r_init();

  // Camera
  camera_init(&g_camera, 8.0f);
  g_camera.position = vec3f32(-1.0f, 1.0f, 5.0f);
  camera_look_at(&g_camera, vec3f32(0.0f, 0.0f, 0.0f));

  // Time
  g_frame_timer = os_timer_start();

  // Frame arena
  Arena* frame_arena = arena_alloc();
  u64 frame_arena_initial_position = frame_arena->position;

  g_tex_black = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\black.png")));
  g_tex_red   = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\red.png")));
  g_blue      = r_create_color_texture(COLOR_BLUE(1.0f));
  
  while(os_is_application_running())
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
    r_render(camera_get_view_matrix(&g_camera), mat4f32_perspective(g_camera.fov, g_os_window->dimensions.x, g_os_window->dimensions.y, 0.1f, 100.0f));

    // Close frame
    {
      arena_pop_to(frame_arena, frame_arena_initial_position);
    }
  }
}

function void
simulation(Arena* frame_arena)
{
  camera_update(&g_camera, g_delta_time);

  r_draw_3d_arrow(vec3f32(-16.0f,  0.0f,  0.0f), vec3f32(16.0f, 0.0f, 0.0), COLOR_RED(1.0f));
  r_draw_3d_arrow(vec3f32( 0.0f, -16.0f,  0.0f), vec3f32(0.0f, 16.0f, 0.0), COLOR_GREEN(1.0f));
  r_draw_3d_arrow(vec3f32( 0.0f,  0.0f, -16.0f), vec3f32(0.0f, 0.0f, 16.0), COLOR_BLUE(1.0f));

  r_draw_3d_grid(vec3f32(0.0f, 0.0f, 0.0f), WORLD_UP, WORLD_FORWARD, 1, 16, COLOR_GRAY(0.4));

  u8* time_now = cstring_from_string8(frame_arena, os_datetime_to_string8(frame_arena, os_datetime_now(), false));
  r_draw_2d_text(vec2f32(10.0f, g_os_window->dimensions.y - 15.0f), 24.0f, COLOR_BLACK(1.0f), 
    Sf(frame_arena, "%s\nFPS: %.2f\nFrame Counter: %d", time_now, g_fps, g_frame_counter));
}

function void
input_update()
{
  if (input_is_key_pressed(Keyboard_Key_ESCAPE))
  {
    os_exit_process(0);
  }

  if (input_is_key_pressed(Keyboard_Key_F11))
  {
    r_toggle_wireframe();
  }

  if (input_is_key_pressed(Keyboard_Key_F12))
  {
    local_persist b32 is_vsync_on = true;
    os_window_enable_vsync(is_vsync_on ? false : true);
    is_vsync_on = !is_vsync_on;
  }
}
