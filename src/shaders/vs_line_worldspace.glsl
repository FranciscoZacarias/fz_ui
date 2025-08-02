#version 450 core

layout(location = 0) in vec3 a_unit_line_pos; // (0,0,0) or (1,0,0)
layout(location = 1) in vec3 a_p0;
layout(location = 2) in vec3 a_p1;
layout(location = 3) in vec4 a_color;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 v_color;

out gl_PerVertex
{
  vec4 gl_Position;
};

void main()
{
  vec3 world_pos = mix(a_p0, a_p1, a_unit_line_pos.x); // interpolate based on unit_line
  gl_Position = u_projection * u_view * vec4(world_pos, 1.0);
  v_color = a_color;
}