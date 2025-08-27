function Camera2D
camera2d_init()
{
  Camera2D camera = {0};
  camera.position = vec2f32(0.0f, 0.0f);
  camera.zoom     = 1.0f;
  camera.near_plane = -1.0f;
  camera.far_plane  = 1.0f;
  _camera2d_update(&camera);
  return camera;
}

function void
_camera2d_update(Camera2D* camera)
{
  f32 half_width  = (g_os_window.dimensions.x / 2.0f) / camera->zoom;
  f32 half_height = (g_os_window.dimensions.y / 2.0f) / camera->zoom;

  camera->projection = mat4f32_orthographic(-half_width, half_width, -half_height, half_height, camera->near_plane, camera->far_plane);
  camera->view       = mat4f32_translate(-camera->position.x, -camera->position.y, 0.0f);
}

function void 
camera2d_move(Camera2D* camera, Vec2f32 delta)
{
  camera->position = vec2f32_add(camera->position, delta);
  _camera2d_update(camera);
}

function void
camera2d_zoom(Camera2D* camera, f32 delta)
{
  f32 new_zoom = camera->zoom + delta;
  if (!(new_zoom < 0.1 || new_zoom > camera->far_plane))
  {
    camera->zoom = new_zoom;
  }
  _camera2d_update(camera);
}

#if 0
function Vec2f32
camera2d_screen_to_world(Camera2D* camera);
{
  // Convert screen to NDC
  f32 ndc_x = (2.0f * g_os_window.dimensions.x / camera->screen_width) - 1.0f;
  f32 ndc_y = 1.0f - (2.0f * g_os_window.dimensions.y / camera->screen_height); // flip Y

  // Build clip space vector
  Vec4f32 clip = { ndc_x, ndc_y, 0.0f, 1.0f };

  // Invert VP
  Mat4f32 inv_vp = mat4f32_inverse(camera->vp); // You'll need to implement this if not present

  Vec4f32 world = mat4f32_mul_vec4(inv_vp, clip);
  return (Vec2f32){ world.x, world.y };
}
#endif