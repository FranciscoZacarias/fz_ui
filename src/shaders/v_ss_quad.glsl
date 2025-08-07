#version 450 core

layout(location = 0) in vec2 a_unit_quad_pos;
layout(location = 1) in vec2 a_pos;
layout(location = 2) in vec2 a_scale;
layout(location = 3) in vec2 a_uv_min;
layout(location = 4) in vec2 a_uv_max;
layout(location = 5) in vec4 a_color;
layout(location = 6) in uint a_texture_id;

uniform vec2 u_screen_size;

out vec4 v_color;
out vec2 v_uv;

flat out uint v_texture_id;

out gl_PerVertex
{
  vec4 gl_Position;
};

void main()
{
  vec2 pixel_pos = a_pos + a_unit_quad_pos * a_scale;
  vec2 ndc = (pixel_pos / u_screen_size) * 2.0 - 1.0;
  gl_Position = vec4(ndc, 0.0, 1.0);
 
  vec2 unit_uv = a_unit_quad_pos + 0.5;
  v_uv = mix(a_uv_min, a_uv_max, unit_uv);
  v_color = a_color;
  v_texture_id = a_texture_id;
}