#version 450 core

layout(location = 0) in vec3 a_unit_pos;
layout(location = 1) in vec3 a_translation;
layout(location = 2) in vec4 a_rotation;
layout(location = 3) in vec3 a_scale;
layout(location = 4) in vec2 a_uv_min;
layout(location = 5) in vec2 a_uv_max;
layout(location = 6) in vec3 a_normal;
layout(location = 7) in vec4 a_color;
layout(location = 8) in uint a_texture_id;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 v_color;
out vec2 v_uv;
out flat uint v_texture_id;

out gl_PerVertex
{
  vec4 gl_Position;
};

vec3 rotate_vec3_by_quat(vec3 vec, vec4 quat)
{
  vec3 t = 2.0 * cross(quat.xyz, vec);
  return vec + quat.w * t + cross(quat.xyz, t);
}

void main()
{
  vec3 scaled_pos  = a_unit_pos * a_scale;
  vec3 rotated_pos = rotate_vec3_by_quat(scaled_pos, a_rotation);
  vec3 world_pos   = a_translation + rotated_pos;
  gl_Position      = u_projection * u_view * vec4(world_pos, 1.0);

	vec2 unit_uv   = a_unit_pos.xy + 0.5;
	v_uv           = mix(a_uv_min.xy, a_uv_max.xy, unit_uv);
  v_color        = a_color;
	v_texture_id   = a_texture_id;
}