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
  g_renderer.vs = renderer_compile_shader(VertexShader_Screenspace, GL_VERTEX_SHADER);
  g_renderer.fs = renderer_compile_shader(FragmentShader, GL_FRAGMENT_SHADER);

  // Create Screenspace pipeline
  glCreateProgramPipelines(1, &g_renderer.pipeline);
  glUseProgramStages(g_renderer.pipeline, GL_VERTEX_SHADER_BIT, g_renderer.vs);
  glUseProgramStages(g_renderer.pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.fs);

  // Create buffer and upload unit quad
  glCreateBuffers(1, &g_renderer.vbo);
  glNamedBufferStorage(g_renderer.vbo, sizeof(Vertex) * 6, NULL, GL_DYNAMIC_STORAGE_BIT);

  // Create VAO and configure
  glCreateVertexArrays(1, &g_renderer.vao);
  glVertexArrayVertexBuffer(g_renderer.vao, 0, g_renderer.vbo, 0, sizeof(Vertex));

  glEnableVertexArrayAttrib(g_renderer.vao, 0); // Vec2f32 Position
  glVertexArrayAttribFormat(g_renderer.vao, 0, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Vertex, position));
  glVertexArrayAttribBinding(g_renderer.vao, 0, 0);
  glEnableVertexArrayAttrib(g_renderer.vao, 1); // Vec4f32 Color
  glVertexArrayAttribFormat(g_renderer.vao, 1, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Vertex, color));
  glVertexArrayAttribBinding(g_renderer.vao, 1, 0);

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
  Vertex verts[6];
  for (s32 i = 0; i < 6; i += 1)
  {
    verts[i].position.x = position.x + unit_quad[i].x * scale.x;
    verts[i].position.y = position.y + unit_quad[i].y * scale.y;
    verts[i].color      = color;
  }

  glNamedBufferSubData(g_renderer.vbo, 0, sizeof(verts), verts);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

function u32
renderer_compile_shader(String8 relative_path, GLenum shader_type)
{
  if (!shader_type)
  {
    emit_error(S("Invalid shader type"));
    return 0;
  }

  u32 result = 0;
  Scratch scratch = scratch_begin(0,0);

  String8 project_path = os_executable_path(scratch.arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  String8 shader_path   = string8_concat(scratch.arena, project_path, relative_path);
  File_Data shader_file = os_file_load(scratch.arena, shader_path);
  u8* cstr_shader_code  = cstring_from_string8(scratch.arena, shader_file.data);
  result = glCreateShaderProgramv(shader_type, 1, &cstr_shader_code);
  if (!result)
  {
    emit_error(string8_from_format(scratch.arena, "Failed to create shader at: %.*s", relative_path.size, relative_path.str));
  }
  else
  {
    GLint status = 0;
    glGetProgramiv(result, GL_LINK_STATUS, &status);
    if (!status)
    {
      GLchar info_log[1024];
      glGetProgramInfoLog(result, sizeof(info_log), NULL, info_log);
      emit_error(string8_from_format(scratch.arena, "Failed to create shader: ", info_log));
    }
  }

  scratch_end(&scratch);
  return result;
}