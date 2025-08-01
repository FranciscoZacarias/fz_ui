function void
camera_init(Camera* camera)
{
  AssertNoReentry();
  MemoryZeroStruct(camera);
  camera->position    = vec3f32(0.0f, 0.0f, 5.0f);
  camera->orientation = quatf32_identity();
  camera->fov         = 90.0f;
  camera->mode        = CameraMode_Select;
}

function void
camera_update(Camera* camera, f32 delta_time)
{
  local_persist b32 was_right_mouse_button_down = 0;

  if (input_is_button_down(MouseButton_Right))
  {
    if (!was_right_mouse_button_down)
    {
      g_input_state.mouse_previous.screen_space.x = g_input_state.mouse_current.screen_space.x;
      g_input_state.mouse_previous.screen_space.y = g_input_state.mouse_current.screen_space.y;
      was_right_mouse_button_down = 1;
      os_cursor_lock(true);
      os_cursor_hide(true);
    }

    camera->mode = CameraMode_Fly;

#ifdef FZ_CAMERA_SPEED
    f32 camera_speed = (f32)(FZ_CAMERA_SPEED * delta_time);
#else
    f32 camera_speed = (f32)(8.0f * delta_time);
#endif

    Vec3f32 forward = camera_get_forward(camera);
    Vec3f32 right   = camera_get_right(camera);
    Vec3f32 up      = camera_get_up(camera);

    if (input_is_key_down(Keyboard_Key_W)) camera->position = vec3f32_add(camera->position, vec3f32_scale(forward, camera_speed));
    if (input_is_key_down(Keyboard_Key_S)) camera->position = vec3f32_sub(camera->position, vec3f32_scale(forward, camera_speed));
    if (input_is_key_down(Keyboard_Key_D)) camera->position = vec3f32_add(camera->position, vec3f32_scale(right, camera_speed));
    if (input_is_key_down(Keyboard_Key_A)) camera->position = vec3f32_sub(camera->position, vec3f32_scale(right, camera_speed));
    if (input_is_key_down(Keyboard_Key_E)) camera->position = vec3f32_add(camera->position, vec3f32_scale(up, camera_speed));
    if (input_is_key_down(Keyboard_Key_Q)) camera->position = vec3f32_sub(camera->position, vec3f32_scale(up, camera_speed));

    // Mouse look
    f32 sensitivity = 0.0015f;
#ifdef FZ_CAMERA_SENSITIVITY
    sensitivity *= FZ_CAMERA_SENSITIVITY;
#endif

    f32 dx = g_input_state.mouse_current.delta.x;
    f32 dy = g_input_state.mouse_current.delta.y;

    f32 yaw   = -dx * sensitivity;
    f32 pitch = -dy * sensitivity;

    Quatf32 yaw_rotation   = quatf32_from_axis_angle((Vec3f32){0.0f, 1.0f, 0.0f}, yaw);
    Vec3f32 camera_right   = camera_get_right(camera);
    Quatf32 pitch_rotation = quatf32_from_axis_angle(camera_right, pitch);

    camera->orientation = quatf32_multiply(yaw_rotation, quatf32_multiply(pitch_rotation, camera->orientation));
    camera->orientation = quatf32_normalize(camera->orientation);

    Vec2s32 dimensions = os_window_get_client_dimensions(); // SPEED(fz): Can be cached and updates on resize
    Vec2s32 relative_client_center = vec2s32(dimensions.x/2, dimensions.y/2);
    Vec2s32 absolute_client_center = os_window_client_to_screen(relative_client_center);
    os_cursor_set_position(absolute_client_center.x, absolute_client_center.y);

    // Manually set current mouse position to center (so next frame delta is correct)
    g_input_state.mouse_current.screen_space.x = (f32)((dimensions.x) / 2);
    g_input_state.mouse_current.screen_space.y = (f32)((dimensions.y) / 2);
  }
  else
  {
    camera->mode = CameraMode_Select;
    was_right_mouse_button_down = 0;
    os_cursor_lock(false);
    os_cursor_hide(false);
  }
}

function Vec3f32
camera_get_forward(Camera* camera)
{
  Mat4f32 rot     = mat4f32_from_quatf32(camera->orientation);
  Vec3f32 forward = {0.0f, 0.0f, -1.0f};
  return vec3f32_normalize(mat4f32_transform_vec3f32(rot, forward));
}

function Vec3f32
camera_get_right(Camera* camera)
{
  Mat4f32 rot   = mat4f32_from_quatf32(camera->orientation);
  Vec3f32 right = {1.0f, 0.0f, 0.0f};
  return vec3f32_normalize(mat4f32_transform_vec3f32(rot, right));
}

function Vec3f32
camera_get_up(Camera* camera)
{
  Mat4f32 rot = mat4f32_from_quatf32(camera->orientation);
  Vec3f32 up  = {0.0f, 1.0f, 0.0f};
  return vec3f32_normalize(mat4f32_transform_vec3f32(rot, up));
}

function Mat4f32
camera_get_view_matrix(Camera* camera)
{
  Vec3f32 forward = camera_get_forward(camera);
  Vec3f32 up      = camera_get_up(camera);
  Vec3f32 target  = vec3f32_add(camera->position, forward);
  Mat4f32 result  = mat4f32_look_at(camera->position, target, up);
  return result;
}

function void
camera_look_at(Camera* camera, Vec3f32 target)
{
  Vec3f32 direction   = vec3f32_normalize(vec3f32_sub(target, camera->position));
  Vec3f32 forward     = {0.0f, 0.0f, -1.0f};
  camera->orientation = quatf32_from_vec3f32_to_vec3f32(forward, direction);
}

function void
camera_set_euler(Camera* camera, f32 pitch, f32 yaw, f32 roll)
{
  camera->orientation = quatf32_from_euler(pitch, yaw, roll);
}

function void
camera_print(Camera* cam)
{
  printf("Camera:\n");
  printf("  Position: (%.3f, %.3f, %.3f)\n",
         cam->position.x, cam->position.y, cam->position.z);
  printf("  Orientation (quat): (%.3f, %.3f, %.3f, %.3f)\n",
         cam->orientation.x, cam->orientation.y,
         cam->orientation.z, cam->orientation.w);
  printf("  FOV: %.3f\n", cam->fov);

  const char* mode_str = "Unknown";
  switch (cam->mode)
  {
    case CameraMode_Select:   mode_str = "Select";   break;
    case CameraMode_Fly:      mode_str = "Fly";      break;
    case CameraMode_Disabled: mode_str = "Disabled"; break;
  }
  printf("  Mode: %s\n", mode_str);
}