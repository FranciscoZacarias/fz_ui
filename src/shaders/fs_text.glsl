#version 450 core

in vec4 v_color;
in vec2 v_uv;

flat in uint v_texture_id;

uniform sampler2D u_textures[32];

out vec4 FragColor;

void main()
{
  float alpha = texture(u_textures[v_texture_id], v_uv).r;
  FragColor = vec4(v_color.rgb, v_color.a * alpha);
}