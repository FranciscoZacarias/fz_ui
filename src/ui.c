
function void
ui_window(Vec2f32 position, Vec2f32 dimensions)
{
  f32 title_bar_height = 18;
  f32 window_height    = dimensions.y - title_bar_height;

  Vec2f32 title_bar_dimensions = vec2f32(dimensions.x, title_bar_height);;
  Vec2f32 title_bar_position   = vec2f32(position.x, position.y + (dimensions.y/2) - (title_bar_height/2));

  Vec2f32 usable_dimensions = vec2f32(dimensions.x, window_height);
  Vec2f32 usable_position   = vec2f32(position.x, position.y + (dimensions.y/2) - title_bar_height - (window_height/2));

  r_draw_2d_quad_colored(title_bar_position, title_bar_dimensions, COLOR_BLUE(0.3));
  r_draw_2d_quad_colored(usable_position, usable_dimensions, COLOR_BLUE(0.1));
}