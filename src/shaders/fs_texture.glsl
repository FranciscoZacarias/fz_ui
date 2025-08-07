#version 450 core

in vec4 v_color;
in vec2 v_uv;

in flat uint v_texture_id;

uniform sampler2D u_textures[32];

out vec4 FragColor;

void main()
{
  vec4 tex_color = texture(u_textures[v_texture_id], v_uv);
  FragColor = tex_color * v_color;
}