function void
renderer_init()
{
  Scratch scratch = scratch_begin(0,0);
  String8 project_path = os_executable_path(scratch.arena);
  project_path = os_directory_pop(project_path);
  project_path = os_directory_pop(project_path);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  MemoryZeroStruct(&g_renderer);
  g_renderer.arena = arena_alloc();
  g_renderer.shaders.v_screenspace_quad = renderer_compile_shader(VertexShader_Screenspace, GL_VERTEX_SHADER);
  g_renderer.shaders.v_worldspace_quad = renderer_compile_shader(VertexShader_Worldspace, GL_VERTEX_SHADER);
  g_renderer.shaders.f_default = renderer_compile_shader(FragmentShader, GL_FRAGMENT_SHADER);
  
  // Screenspace
  {
    g_renderer.screenspace.quads2d = push_array(g_renderer.arena, Quad2D, Max2DQuads);

    // Create pipeline
    glCreateProgramPipelines(1, &g_renderer.screenspace.pipeline);
    glUseProgramStages(g_renderer.screenspace.pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_screenspace_quad);
    glUseProgramStages(g_renderer.screenspace.pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);
  
    // Unit quad vertex buffer
    glCreateBuffers(1, &g_renderer.screenspace.unit_quad_vbo);
    glNamedBufferStorage(g_renderer.screenspace.unit_quad_vbo, sizeof(unit_2dquad), unit_2dquad, 0);
  
    // Instance data buffer
    glCreateBuffers(1, &g_renderer.screenspace.instance_vbo);
    glNamedBufferStorage(g_renderer.screenspace.instance_vbo, sizeof(Quad2D) * Max2DQuads, NULL, GL_DYNAMIC_STORAGE_BIT);
  
    // VAO setup
    glCreateVertexArrays(1, &g_renderer.screenspace.vao);
  
    // Unit quad positions (per-vertex)
    glVertexArrayVertexBuffer(g_renderer.screenspace.vao, 0, g_renderer.screenspace.unit_quad_vbo, 0, sizeof(Vec2f32));
    glEnableVertexArrayAttrib(g_renderer.screenspace.vao, 0);
    glVertexArrayAttribFormat(g_renderer.screenspace.vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_renderer.screenspace.vao, 0, 0);
  
    // Instance data (per-instance)
    glVertexArrayVertexBuffer(g_renderer.screenspace.vao, 1, g_renderer.screenspace.instance_vbo, 0, sizeof(Quad2D));
  
    glEnableVertexArrayAttrib(g_renderer.screenspace.vao, 1); // position
    glVertexArrayAttribFormat(g_renderer.screenspace.vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, position));
    glVertexArrayAttribBinding(g_renderer.screenspace.vao, 1, 1);
    glVertexArrayBindingDivisor(g_renderer.screenspace.vao, 1, 1);
  
    glEnableVertexArrayAttrib(g_renderer.screenspace.vao, 2); // scale
    glVertexArrayAttribFormat(g_renderer.screenspace.vao, 2, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, scale));
    glVertexArrayAttribBinding(g_renderer.screenspace.vao, 2, 1);
    glVertexArrayBindingDivisor(g_renderer.screenspace.vao, 2, 1);
  
    glEnableVertexArrayAttrib(g_renderer.screenspace.vao, 3); // color
    glVertexArrayAttribFormat(g_renderer.screenspace.vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, color));
    glVertexArrayAttribBinding(g_renderer.screenspace.vao, 3, 1);
    glVertexArrayBindingDivisor(g_renderer.screenspace.vao, 3, 1);

    g_renderer.screenspace.u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_screenspace_quad, "u_screen_size");
  }

  // Worldspace
  {
    g_renderer.worldspace.quads3d = push_array(g_renderer.arena, Quad3D, Max3DQuads);

    // Create pipeline
    glCreateProgramPipelines(1, &g_renderer.worldspace.pipeline);
    glUseProgramStages(g_renderer.worldspace.pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_worldspace_quad);
    glUseProgramStages(g_renderer.worldspace.pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);
  
    // Unit quad vertex buffer
    glCreateBuffers(1, &g_renderer.worldspace.unit_quad_vbo);
    glNamedBufferStorage(g_renderer.worldspace.unit_quad_vbo, sizeof(unit_3dquad), unit_3dquad, 0);

    // Instance data buffer
    glCreateBuffers(1, &g_renderer.worldspace.instance_vbo);
    glNamedBufferStorage(g_renderer.worldspace.instance_vbo, sizeof(Quad3D) * Max3DQuads, NULL, GL_DYNAMIC_STORAGE_BIT);

    // VAO setup
    glCreateVertexArrays(1, &g_renderer.worldspace.vao);
    
    // Unit quad positions (per-vertex)
    glVertexArrayVertexBuffer(g_renderer.worldspace.vao, 0, g_renderer.worldspace.unit_quad_vbo, 0, sizeof(Vec3f32));
    glEnableVertexArrayAttrib(g_renderer.worldspace.vao, 0);
    glVertexArrayAttribFormat(g_renderer.worldspace.vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_renderer.worldspace.vao, 0, 0);

    // Instance data (per-instance)
    glVertexArrayVertexBuffer(g_renderer.worldspace.vao, 1, g_renderer.worldspace.instance_vbo, 0, sizeof(Quad3D));
  
    glEnableVertexArrayAttrib(g_renderer.worldspace.vao, 1); // position
    glVertexArrayAttribFormat(g_renderer.worldspace.vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad3D, position));
    glVertexArrayAttribBinding(g_renderer.worldspace.vao, 1, 1);
    glVertexArrayBindingDivisor(g_renderer.worldspace.vao, 1, 1);
  
    glEnableVertexArrayAttrib(g_renderer.worldspace.vao, 2); // scale
    glVertexArrayAttribFormat(g_renderer.worldspace.vao, 2, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad3D, scale));
    glVertexArrayAttribBinding(g_renderer.worldspace.vao, 2, 1);
    glVertexArrayBindingDivisor(g_renderer.worldspace.vao, 2, 1);
  
    glEnableVertexArrayAttrib(g_renderer.worldspace.vao, 3); // color
    glVertexArrayAttribFormat(g_renderer.worldspace.vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad3D, color));
    glVertexArrayAttribBinding(g_renderer.worldspace.vao, 3, 1);
    glVertexArrayBindingDivisor(g_renderer.worldspace.vao, 3, 1);

    g_renderer.worldspace.u_projection_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad, "u_projection");
    g_renderer.worldspace.u_view_location       = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad, "u_view");
  }

  scratch_end(&scratch);
}

function void
renderer_begin_frame()
{
  glClearColor(0.5f, 0.96f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  g_renderer.screenspace.quads2d_count = 0;
  g_renderer.worldspace.quads3d_count  = 0;
}

function void
renderer_end_frame(Mat4f32 view, Mat4f32 projection)
{
  // Worldspace
  if (g_renderer.worldspace.quads3d_count > 0)
  {
    glBindProgramPipeline(g_renderer.worldspace.pipeline);
    glBindVertexArray(g_renderer.worldspace.vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad, g_renderer.worldspace.u_view_location, 1, GL_FALSE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad, g_renderer.worldspace.u_projection_location, 1, GL_FALSE, &projection.data[0][0]);

    glNamedBufferSubData(g_renderer.worldspace.instance_vbo, 0, sizeof(Quad3D) * g_renderer.worldspace.quads3d_count, g_renderer.worldspace.quads3d);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.worldspace.quads3d_count);
  }

  // Screenspace
  if (g_renderer.screenspace.quads2d_count > 0)
  {
    glBindProgramPipeline(g_renderer.screenspace.pipeline);
    glBindVertexArray(g_renderer.screenspace.vao);

    glProgramUniform2f(g_renderer.shaders.v_screenspace_quad, g_renderer.screenspace.u_screen_size_location, (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);

    glNamedBufferSubData(g_renderer.screenspace.instance_vbo, 0, sizeof(Quad2D) * g_renderer.screenspace.quads2d_count, g_renderer.screenspace.quads2d);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.screenspace.quads2d_count);
  }

  os_swap_buffers();
}

function void
renderer_draw_2dquad(Vec2f32 position, Vec2f32 scale, Vec4f32 color)
{
  if (g_renderer.screenspace.quads2d_count >= Max2DQuads)
  {
    emit_fatal(S("Tried to render more quads than Max2DQuads"));
  }

  g_renderer.screenspace.quads2d[g_renderer.screenspace.quads2d_count].position = position;
  g_renderer.screenspace.quads2d[g_renderer.screenspace.quads2d_count].scale    = scale;
  g_renderer.screenspace.quads2d[g_renderer.screenspace.quads2d_count].color    = color;
  g_renderer.screenspace.quads2d_count += 1;
}

function void
renderer_draw_3dquad(Vec3f32 position, Vec3f32 scale, Vec4f32 color)
{
  if (g_renderer.worldspace.quads3d_count >= Max3DQuads)
  {
    emit_fatal(S("Tried to render more quads than Max23Quads"));
  }

  g_renderer.worldspace.quads3d[g_renderer.worldspace.quads3d_count].position = position;
  g_renderer.worldspace.quads3d[g_renderer.worldspace.quads3d_count].scale    = scale;
  g_renderer.worldspace.quads3d[g_renderer.worldspace.quads3d_count].color    = color;
  g_renderer.worldspace.quads3d_count += 1;
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