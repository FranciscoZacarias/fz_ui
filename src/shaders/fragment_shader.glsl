#version 450 core

layout(location = 0) out vec4 out_color;

uniform vec4 u_color;

void main()
{
  out_color = u_color;
}