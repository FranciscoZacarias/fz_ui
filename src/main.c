#ifndef MAIN_H
#define MAIN_H

#define DEBUG 1

///////////////////////////////////////////////////////
// @Section: fz_std
#include "fz_base.h"
#include "fz_opengl.h"

///////////////////////////////////////////////////////
// @Section: project

#define PROJECT_NAME S("Turtle")

// *.h

// *.c
#include "camera2d.c"
#include "renderer.c"

// global Camera g_camera;
global Camera2D g_camera;
global Input_State g_input;

global OS_Timer g_frame_timer   = {0};
global u64      g_frame_counter = 0;
global f32      g_delta_time    = 0.0f;
global f32      g_fps           = 0.0f;

global Texture_Info g_tex_black;
global Texture_Info g_tex_red;
global Texture_Info g_tex_color_blue;
global Texture_Info g_tex_color_yellow;

function void input_update();
function void simulation();
function b32  is_game_running();
function void camera2d_update(Camera2D* camera, Input_State, f32 delta_time);

#endif // MAIN_H

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
  camera2d_init(arena, &g_camera);
  // camera_init(&g_camera, 8.0f);
  // g_camera.position = vec3f32(-1.0f, 1.0f, 5.0f);
  // camera_look_at(&g_camera, vec3f32(0.0f, 0.0f, 0.0f));

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

  //r_draw_2d_grid(vec2f32(0.0f, 0.0f), vec2f32(g_os_window.dimensions.x, g_os_window.dimensions.y), 32.0f, COLOR_BLACK(0.1));
  r_draw_2d_quad_colored(vec2f32(0.0f, 0.0f), vec2f32(50.0f, 50.0f), COLOR_RED(1.0f));

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
  f32 speed = 1.0;
  f32 delta = speed * delta_time;

  Vec2f32 move = vec2f32(0.0f, 0.0f);
  if (input_is_key_down(&g_input, Keyboard_Key_W))
  {
    move.y = delta;
    camera2d_move(camera, move);
  }
  if (input_is_key_down(&g_input, Keyboard_Key_S))
  {
    move.x = -delta;
    camera2d_move(camera, move);
  }
  if (input_is_key_down(&g_input, Keyboard_Key_D))
  {
    move.y = delta;
    camera2d_move(camera, move);
  }
  if (input_is_key_down(&g_input, Keyboard_Key_A))
  {
    move.y = -delta;
    camera2d_move(camera, move);
  }

  printf("Camera x: %.2f\n", camera->position.x);
  printf("Camera y: %.2f\n", camera->position.y);
}