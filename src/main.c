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
  renderer_init();
  Texture_Info tex_black = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\black.png")));
  Texture_Info tex_red   = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\red.png")));
  Texture_Info tex_pink  = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\pink.png")));
  Texture_Info tex_yelow = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\yelow.png")));
  Texture_Info tex_blue  = renderer_load_texture(string8_concat(arena, project_path, S("\\assets\\textures\\prototype\\blue 1.png")));

	Texture_Info yellow = renderer_create_color_texture(Color_Yellow);
	Texture_Info green  = renderer_create_color_texture(Color_Green);

  // Camera
  camera_init(&g_camera);
  g_camera.position = vec3f32(-1.0f, 1.0f, 5.0f);
  camera_look_at(&g_camera, vec3f32(0.0f, 0.0f, 0.0f));

  // Time
  g_frame_timer = os_timer_start();
  g_delta_time  = 0.0f;
  g_fps         = 0.0f;
  
  while(os_is_application_running())
  {
    f32 g_fps = 1.0f / g_delta_time;
    input_update();
    camera_update(&g_camera, g_delta_time);

    renderer_begin_frame();

    renderer_draw_3darrow(vec3f32(-4.0f,   0.0f,   0.0f), vec3f32(4.0f, 0.0f,  0.0), Color_Red);
    renderer_draw_3darrow(vec3f32(  0.0f, -4.0f,   0.0f), vec3f32(0.0f, 4.0f,  0.0), Color_Green);
    renderer_draw_3darrow(vec3f32(  0.0f,   0.0f, -4.0f), vec3f32(0.0f,  0.0f, 4.0), Color_Blue);

    renderer_draw_3dquad(transformf32(vec3f32(0.0f, 0.0f, 2.0f), quatf32_from_euler(Radians(90.0f), Radians(0.0f), Radians(0.0f)), vec3f32(1.0f, 1.0f, 1.0f)), Color_White, green.index);
    
    renderer_draw_3dquad(transformf32(vec3f32( 2.0f,  2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), Color_White, tex_black.index);
    renderer_draw_3dquad(transformf32(vec3f32(-2.0f,  2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), Color_White, tex_red.index);
    renderer_draw_3dquad(transformf32(vec3f32( 2.0f, -2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), Color_White, tex_pink.index);
    renderer_draw_3dquad(transformf32(vec3f32(-2.0f, -2.0f, -2.0f), quatf32_identity(), vec3f32(2.0f, 2.0f, 1.0f)), Color_White, tex_yelow.index);

    renderer_draw_2dquad(vec2f32(30.f,  100.f), vec2f32(50.f, 50.f), Color_Red,   tex_black.index);
    renderer_draw_2dquad(vec2f32(90.f,  100.f), vec2f32(50.f, 50.f), Color_Green, tex_red.index);
    renderer_draw_2dquad(vec2f32(150.f, 100.f), vec2f32(50.f, 50.f), Color_Blue,  tex_pink.index);
    renderer_draw_2dquad(vec2f32(210.f, 100.f), vec2f32(50.f, 50.f), Color_White, yellow.index);
    renderer_draw_2dquad(vec2f32(270.f, 100.f), vec2f32(50.f, 50.f), Color_White, green.index);

    renderer_draw_2dquad(vec2f32(30.f, 30.f), vec2f32(50.f, 50.f), Color_White, tex_black.index);
    renderer_draw_2dquad(vec2f32(90.f, 30.f), vec2f32(50.f, 50.f), Color_White, tex_red.index);
    renderer_draw_2dquad(vec2f32(150.f, 30.f), vec2f32(50.f, 50.f), Color_White, tex_pink.index);
    renderer_draw_2dquad(vec2f32(210.f, 30.f), vec2f32(50.f, 50.f), Color_White, tex_yelow.index);
    renderer_draw_2dquad(vec2f32(270.f, 30.f), vec2f32(50.f, 50.f), Color_White, tex_blue.index);

		renderer_draw_2dtext(vec2f32(10.0f, 140.0f), Color_Black, 8.0f, S("We are not your kind."));

    renderer_draw_2dtext(vec2f32(5.0f, g_os_window->dimensions.y - 15.0f), Color_Black, 4.0f, Sf(arena, "FPS: %.2f", g_fps));

    Mat4f32 view       = camera_get_view_matrix(&g_camera);
    Mat4f32 projection = mat4f32_perspective(g_camera.fov, g_os_window->dimensions.x, g_os_window->dimensions.y, 0.1f, 100.0f);
      
    renderer_end_frame(view, projection);

    g_delta_time = (f32)os_timer_seconds(&g_frame_timer);
    os_timer_reset(&g_frame_timer);
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
    renderer_toggle_wireframe();
  }

  if (input_is_key_pressed(Keyboard_Key_F12))
  {
    local_persist b32 is_vsync_on = true;
    os_window_enable_vsync(is_vsync_on ? false : true);
    is_vsync_on = !is_vsync_on;
  }


}