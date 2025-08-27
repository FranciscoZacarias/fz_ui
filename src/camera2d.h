#ifndef CAMERA2D_H
#define CAMERA2D_H
// @namespace camera2d

typedef struct {
  Vec2f32 position;
  f32 zoom;
  Mat4f32 projection;
  Mat4f32 view;
  f32 near_plane;
  f32 far_plane;
} Camera2D;

function Camera2D camera2d_init();
function void _camera2d_update(Camera2D* camera);
function void camera2d_zoom(Camera2D* camera, f32 delta);
function void camera2d_move(Camera2D* camera, Vec2f32 delta);

#endif // CAMERA2D_H