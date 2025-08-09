#version 450 core
layout(location = 0) in vec2 a_p0;
layout(location = 1) in vec2 a_p1;
layout(location = 2) in vec4 a_color;
uniform vec2 u_screen_size;
out vec4 v_color;
out gl_PerVertex
{
  vec4 gl_Position;
};
void main()
{
  vec2 pixel_pos = (gl_VertexID == 0) ? a_p0 : a_p1;
  vec2 ndc = (pixel_pos / u_screen_size) * 2.0 - 1.0;
  //ndc.y = -ndc.y; // For top left.
  gl_Position = vec4(ndc, 0.0, 1.0);
  v_color = a_color;
}