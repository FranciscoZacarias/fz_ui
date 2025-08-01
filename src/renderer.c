function void
renderer_init()
{
  Scratch scratch = scratch_begin(0,0);
  String8 project_path = os_executable_path(scratch.arena);
  project_path = os_directory_pop(project_path);
  project_path = os_directory_pop(project_path);
  
  g_renderer.arena = arena_alloc();
  g_renderer.vs = renderer_compile_shader(VertexShader_Screenspace, GL_VERTEX_SHADER);
  g_renderer.fs = renderer_compile_shader(FragmentShader, GL_FRAGMENT_SHADER);
  g_renderer.quads2d = push_array(g_renderer.arena, Quad2D, TotalQuads2D);
  
  // Create pipeline
  glCreateProgramPipelines(1, &g_renderer.pipeline);
  glUseProgramStages(g_renderer.pipeline, GL_VERTEX_SHADER_BIT, g_renderer.vs);
  glUseProgramStages(g_renderer.pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.fs);
  
  // Unit quad vertex buffer
  glCreateBuffers(1, &g_renderer.unit_quad_vbo);
  glNamedBufferStorage(g_renderer.unit_quad_vbo, sizeof(unit_quad), unit_quad, 0);
  
  // Instance data buffer
  glCreateBuffers(1, &g_renderer.instance_vbo);
  glNamedBufferStorage(g_renderer.instance_vbo, sizeof(Quad2D) * TotalQuads2D, NULL, GL_DYNAMIC_STORAGE_BIT);
  
  // VAO setup
  glCreateVertexArrays(1, &g_renderer.vao);
  
  // Unit quad positions (per-vertex)
  glVertexArrayVertexBuffer(g_renderer.vao, 0, g_renderer.unit_quad_vbo, 0, sizeof(Vec2f32));
  glEnableVertexArrayAttrib(g_renderer.vao, 0);
  glVertexArrayAttribFormat(g_renderer.vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(g_renderer.vao, 0, 0);
  
  // Instance data (per-instance)
  glVertexArrayVertexBuffer(g_renderer.vao, 1, g_renderer.instance_vbo, 0, sizeof(Quad2D));
  
  glEnableVertexArrayAttrib(g_renderer.vao, 1); // position
  glVertexArrayAttribFormat(g_renderer.vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, position));
  glVertexArrayAttribBinding(g_renderer.vao, 1, 1);
  glVertexArrayBindingDivisor(g_renderer.vao, 1, 1);
  
  glEnableVertexArrayAttrib(g_renderer.vao, 2); // scale
  glVertexArrayAttribFormat(g_renderer.vao, 2, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, scale));
  glVertexArrayAttribBinding(g_renderer.vao, 2, 1);
  glVertexArrayBindingDivisor(g_renderer.vao, 2, 1);
  
  glEnableVertexArrayAttrib(g_renderer.vao, 3); // color
  glVertexArrayAttribFormat(g_renderer.vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, color));
  glVertexArrayAttribBinding(g_renderer.vao, 3, 1);
  glVertexArrayBindingDivisor(g_renderer.vao, 3, 1);
  
  scratch_end(&scratch);
}

function void
renderer_begin_frame()
{
  glClearColor(0.5, 0.96, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glBindProgramPipeline(g_renderer.pipeline);
  glBindVertexArray(g_renderer.vao);
  g_renderer.quads2d_count = 0;

  // TODO(fz): We can just cache the value glGetUniformLocation
  glProgramUniform2f(g_renderer.vs, glGetUniformLocation(g_renderer.vs, "u_screen_size"), (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);
}

function void
renderer_end_frame()
{
  glNamedBufferSubData(g_renderer.instance_vbo, 0, sizeof(Quad2D) * g_renderer.quads2d_count, g_renderer.quads2d);
  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.quads2d_count);
}

function void
renderer_draw_quad(Vec2f32 position, Vec2f32 scale, Vec4f32 color)
{
  if (g_renderer.quads2d_count >= TotalQuads2D)
  {
    emit_fatal(S("Tried to render more quads than TotalQuads2D"));
  }

  g_renderer.quads2d[g_renderer.quads2d_count].position = position;
  g_renderer.quads2d[g_renderer.quads2d_count].scale    = scale;
  g_renderer.quads2d[g_renderer.quads2d_count].color    = color;
  g_renderer.quads2d_count += 1;
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