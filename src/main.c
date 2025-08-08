#include "main.h"

#define FZ_CAMERA_SPEED 8.0f

function void
entry_point(Command_Line* command_line)
{
  Arena* arena = arena_alloc();

  os_console_init();
  os_window_init(600, 600, Project_Name);
  os_opengl_init();
  os_window_open();

  String8 project_path = os_executable_path(arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  // Renderer
  r_init();
  Texture_Info tex_black = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\black.png")));
  Texture_Info tex_red   = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\red.png")));
  Texture_Info tex_pink  = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\pink.png")));
  Texture_Info tex_yelow = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\yelow.png")));
  Texture_Info tex_blue  = r_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\blue 1.png")));

  Texture_Info yellow = r_create_color_texture(Color_Yellow(1.0f));
  Texture_Info green  = r_create_color_texture(Color_Green(1.0f));

  // Camera
  camera_init(&g_camera);
  g_camera.position = vec3f32(-1.0f, 1.0f, 5.0f);
  camera_look_at(&g_camera, vec3f32(0.0f, 0.0f, 0.0f));

  // Time
  g_frame_timer   = os_timer_start();
  g_delta_time    = 0.0f;
  g_fps           = 0.0f;
  g_frame_counter = 1.0f;

  Arena* frame_arena = arena_alloc();
  while(os_is_application_running())
  {
    f32 g_fps = 1.0f / g_delta_time;
    input_update();
    camera_update(&g_camera, g_delta_time);

    r_draw_grid(vec3f32(0.0f, 0.0f, 0.0f), WORLD_UP, WORLD_FORWARD, 1, 16, Color_Black(0.2));

    r_draw_3d_arrow(vec3f32(-16.0f,  0.0f,  0.0f), vec3f32(16.0f, 0.0f, 0.0), Color_Red(1.0f));
    r_draw_3d_arrow(vec3f32( 0.0f, -16.0f,  0.0f), vec3f32(0.0f, 16.0f, 0.0), Color_Green(1.0f));
    r_draw_3d_arrow(vec3f32( 0.0f,  0.0f, -16.0f), vec3f32(0.0f, 0.0f, 16.0), Color_Blue(1.0f));

    r_draw_3d_quad(transform3f32(vec3f32(0.0f, 0.0f, 2.0f), quatf32_from_euler(Radians(g_frame_counter), Radians(g_frame_counter), Radians(0.0f)), vec3f32(1.0f, 1.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), green.index);

    r_draw_3d_triangle(transform3f32(vec3f32(0.0f, 0.0f, -2.0f), quatf32_from_euler(Radians(g_frame_counter), Radians(g_frame_counter), Radians(0.0f)), vec3f32(1.0f, 1.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_blue.index);
    r_draw_3d_triangle(transform3f32(vec3f32(-2.0f, 0.0f, -2.0f), quatf32_identity(), vec3f32(1.0f, 1.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_pink.index);
    
    r_draw_3d_quad(transform3f32(vec3f32( 2.0f,  2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_black.index);
    r_draw_3d_quad(transform3f32(vec3f32(-2.0f,  2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_red.index);
    r_draw_3d_quad(transform3f32(vec3f32( 2.0f, -2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_pink.index);
    r_draw_3d_quad(transform3f32(vec3f32(-2.0f, -2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_yelow.index);

    r_draw_3d_text(transform3f32(vec3f32(0.0f, 0.0f, 0.0f),  quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), Color_Black(1.0f), 4.0f, S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    r_draw_3d_text(transform3f32(vec3f32(0.0f, -0.4f, 0.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), Color_Black(1.0f), 4.0f, S("abcdefghijklmnopqrstuvwxyz"));

    r_draw_2d_quad(vec2f32(30.f,  100.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_Red(1.0f),   tex_black.index);
    r_draw_2d_quad(vec2f32(90.f,  100.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_Green(1.0f), tex_red.index);
    r_draw_2d_quad(vec2f32(150.f, 100.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_Blue(1.0f),  tex_pink.index);
    r_draw_2d_quad(vec2f32(210.f, 100.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), yellow.index);
    r_draw_2d_quad(vec2f32(270.f, 100.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), green.index);

    r_draw_2d_quad(vec2f32(30.f, 30.f), vec2f32(50.f, 50.f),  vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_black.index);
    r_draw_2d_quad(vec2f32(90.f, 30.f), vec2f32(50.f, 50.f),  vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_red.index);
    r_draw_2d_quad(vec2f32(150.f, 30.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_pink.index);
    r_draw_2d_quad(vec2f32(210.f, 30.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_yelow.index);
    r_draw_2d_quad(vec2f32(270.f, 30.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_White(1.0f), tex_blue.index);

    r_draw_2d_triangle(vec2f32(40.f, 300.f), vec2f32(50.f, 50.f), vec2f32(0.0f, 0.0f), vec2f32(1.0f, 1.0f), Color_Red(1.0f),   tex_black.index);

    r_draw_2d_text(vec2f32(10.0f, 200.0f), Color_Black(1.0f), 8.0f, S("We are not your kind.\nWe are not your kind!"));
    r_draw_2d_text(vec2f32(5.0f, g_os_window->dimensions.y - 15.0f), Color_Black(1.0f), 4.0f, Sf(frame_arena, "FPS: %.2f", g_fps));

    Mat4f32 view       = camera_get_view_matrix(&g_camera);
    Mat4f32 projection = mat4f32_perspective(g_camera.fov, g_os_window->dimensions.x, g_os_window->dimensions.y, 0.1f, 100.0f);

    r_render(view, projection);

    // Close frame
    { 
      g_delta_time = (f32)os_timer_seconds(&g_frame_timer);
      os_timer_reset(&g_frame_timer);
      g_frame_counter += 1;
      arena_pop_to(frame_arena, 0);
    }
  }
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