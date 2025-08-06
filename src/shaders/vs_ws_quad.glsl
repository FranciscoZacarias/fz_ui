#version 450 core

layout(location = 0) in vec3 a_unit_pos;
layout(location = 1) in vec3 a_instance_translation;
layout(location = 2) in vec4 a_instance_rotation;
layout(location = 3) in vec3 a_instance_scale;
layout(location = 4) in vec4 a_instance_color;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 v_color;

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
  vec3 scaled_pos  = a_unit_pos * a_instance_scale;
  vec3 rotated_pos = rotate_vec3_by_quat(scaled_pos, a_instance_rotation);
  vec3 world_pos   = a_instance_translation + rotated_pos;

  gl_Position      = u_projection * u_view * vec4(world_pos, 1.0);
  v_color          = a_instance_color;
}
