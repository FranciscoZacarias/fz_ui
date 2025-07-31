global const Vec2f32 unit_quad[6] = {
  {0.0f, 0.0f},
  {1.0f, 0.0f},
  {1.0f, 1.0f},
  {0.0f, 0.0f},
  {1.0f, 1.0f},
  {0.0f, 1.0f}
};

function void
renderer_init()
{
  Scratch scratch = scratch_begin(0,0);

  String8 project_path = os_executable_path(scratch.arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  // Create shaders
  String8 screenspace_vs_path = string8_concat(scratch.arena, project_path, VertexShader_Screenspace);
  File_Data screenspace_vs    = os_file_load(scratch.arena, screenspace_vs_path);
  u8* cscreenspace_vs         = cstring_from_string8(scratch.arena, screenspace_vs.data);
  g_renderer.vs = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &cscreenspace_vs);
  if (!g_renderer.vs)
  {
    emit_error(S("Failed to create vertex shader"));
  }
  else
  {
    GLint status = 0;
    glGetProgramiv(g_renderer.vs, GL_LINK_STATUS, &status);
    if (!status)
    {
      GLchar info_log[1024];
      glGetProgramInfoLog(g_renderer.vs, sizeof(info_log), NULL, info_log);
      emit_error(string8_from_format(scratch.arena, "Vertex shader failed to link: %s", info_log));
    }
  }

  String8 fragmentshader_fs_path = string8_concat(scratch.arena, project_path, FragmentShader);
  File_Data fragmentshader_fs    = os_file_load(scratch.arena, fragmentshader_fs_path);
  u8* cfragmentshader_fs         = cstring_from_string8(scratch.arena, fragmentshader_fs.data);
  g_renderer.fs = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &cfragmentshader_fs);
  if (!g_renderer.fs)
  {
    emit_error(S("Failed to create fragment shader"));
  }
  else
  {
    GLint status = 0;
    glGetProgramiv(g_renderer.fs, GL_LINK_STATUS, &status);
    if (!status)
    {
      GLchar info_log[1024];
      glGetProgramInfoLog(g_renderer.fs, sizeof(info_log), NULL, info_log);
      emit_error(string8_from_format(scratch.arena, "Fragment shader failed to link: %sd", info_log));
    }
  }

  // Create pipeline
  glCreateProgramPipelines(1, &g_renderer.pipeline);
  glUseProgramStages(g_renderer.pipeline, GL_VERTEX_SHADER_BIT, g_renderer.vs);
  glUseProgramStages(g_renderer.pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.fs);

  // Get uniform location
  g_renderer.color_uniform = glGetUniformLocation(g_renderer.fs, "u_color");

  // Create buffer and upload unit quad
  glCreateBuffers(1, &g_renderer.vbo);
  glNamedBufferStorage(g_renderer.vbo, sizeof(unit_quad), unit_quad, GL_DYNAMIC_STORAGE_BIT);

  // Create VAO and configure
  glCreateVertexArrays(1, &g_renderer.vao);
  glVertexArrayVertexBuffer(g_renderer.vao, 0, g_renderer.vbo, 0, sizeof(Vec2f32));
  glEnableVertexArrayAttrib(g_renderer.vao, 0);
  glVertexArrayAttribFormat(g_renderer.vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(g_renderer.vao, 0, 0);

  scratch_end(&scratch);
}

function void
renderer_begin_frame()
{
  glBindProgramPipeline(g_renderer.pipeline);
  glBindVertexArray(g_renderer.vao);
}

function void
renderer_end_frame()
{

}

function void
renderer_draw_quad(Vec2f32 position, Vec2f32 scale, Vec4f32 color)
{
  Vec2f32 offset = position;

  Vec2f32 verts[6];
  for (int i = 0; i < 6; i++)
  {
    verts[i].x = offset.x + unit_quad[i].x * scale.x;
    verts[i].y = offset.y + unit_quad[i].y * scale.y;
  }

  glNamedBufferSubData(g_renderer.vbo, 0, sizeof(verts), verts);
  glProgramUniform4f(g_renderer.fs, g_renderer.color_uniform, color.x, color.y, color.z, color.w);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

