function void
r_init()
{
  Scratch scratch = scratch_begin(0,0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

#if 0
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
#endif

  MemoryZeroStruct(&g_renderer);
  g_renderer.arena = arena_alloc();
  
  g_renderer.shaders.v_ss_line = r_compile_shader(V_SS_Line_Path,      GL_VERTEX_SHADER);
  g_renderer.shaders.v_ss_quad = r_compile_shader(V_SS_Primitive_Path, GL_VERTEX_SHADER);
  g_renderer.shaders.v_ss_text = r_compile_shader(V_SS_Text_Path,      GL_VERTEX_SHADER);
  g_renderer.shaders.v_ws_quad = r_compile_shader(V_WS_Primitive_Path, GL_VERTEX_SHADER);
  g_renderer.shaders.v_ws_line = r_compile_shader(V_WS_Line_Path,      GL_VERTEX_SHADER);

  g_renderer.shaders.f_line    = r_compile_shader(F_Line_Path,    GL_FRAGMENT_SHADER);
  g_renderer.shaders.f_texture = r_compile_shader(F_Texture_Path, GL_FRAGMENT_SHADER);
  g_renderer.shaders.f_text    = r_compile_shader(F_Text_Path,    GL_FRAGMENT_SHADER);
  
  // Screenspace
  {
    // 2D Lines
    {
      Render_Batch_Kind batch_kind = Render_Batch_SS_Line;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_line, "u_screen_size");

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Line2D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
      // VAO
      glCreateVertexArrays(1, &batch->vao);
    
      // Instance data
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Line2D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ss_line);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_line);

      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 0); // p0
      glVertexArrayAttribFormat(batch->vao, 0, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Line2D, p0));
      glVertexArrayAttribBinding(batch->vao, 0, 1);
      glVertexArrayBindingDivisor(batch->vao, 0, 1);

      glEnableVertexArrayAttrib(batch->vao, 1); // p1
      glVertexArrayAttribFormat(batch->vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Line2D, p1));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // color
      glVertexArrayAttribFormat(batch->vao, 2, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Line2D, color));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);
    }

    // 2D Triangles
    {
      Render_Batch_Kind batch_kind = Render_Batch_SS_triangle;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_quad, "u_screen_size");
    
      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_2d_triangle), unit_2d_triangle, 0);

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry binding (binding 0)
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));

      // Instance data binding (binding 1)
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ss_quad);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_texture);

      // Unit quad positions (per-vertex)
      glEnableVertexArrayAttrib(batch->vao, 0);
      glVertexArrayAttribFormat(batch->vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribBinding(batch->vao, 0, 0);

      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 1); // Position
      glVertexArrayAttribFormat(batch->vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, position));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // Scale
      glVertexArrayAttribFormat(batch->vao, 2, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, scale));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);

      glEnableVertexArrayAttrib(batch->vao, 3); // UV Min
      glVertexArrayAttribFormat(batch->vao, 3, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, uv_min));
      glVertexArrayAttribBinding(batch->vao, 3, 1);
      glVertexArrayBindingDivisor(batch->vao, 3, 1);

      glEnableVertexArrayAttrib(batch->vao, 4); // UV Max
      glVertexArrayAttribFormat(batch->vao, 4, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, uv_max));
      glVertexArrayAttribBinding(batch->vao, 4, 1);
      glVertexArrayBindingDivisor(batch->vao, 4, 1);

      glEnableVertexArrayAttrib(batch->vao, 5); // Color
      glVertexArrayAttribFormat(batch->vao, 5, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, color));
      glVertexArrayAttribBinding(batch->vao, 5, 1);
      glVertexArrayBindingDivisor(batch->vao, 5, 1);

      glEnableVertexArrayAttrib(batch->vao, 6); // Texture ID
      glVertexArrayAttribIFormat(batch->vao, 6, 1, GL_UNSIGNED_INT, OffsetOfMember(Primitive2D, texture_id));
      glVertexArrayAttribBinding(batch->vao, 6, 1);
      glVertexArrayBindingDivisor(batch->vao, 6, 1);
    }


    // 2D Quads
    {
      Render_Batch_Kind batch_kind = Render_Batch_SS_quad;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_quad, "u_screen_size");
    
      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_2d_quad), unit_2d_quad, 0);

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry binding (binding 0)
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));

      // Instance data binding (binding 1)
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ss_quad);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_texture);

      // Unit quad positions (per-vertex)
      glEnableVertexArrayAttrib(batch->vao, 0);
      glVertexArrayAttribFormat(batch->vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribBinding(batch->vao, 0, 0);

      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 1); // Position
      glVertexArrayAttribFormat(batch->vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, position));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // Scale
      glVertexArrayAttribFormat(batch->vao, 2, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, scale));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);

      glEnableVertexArrayAttrib(batch->vao, 3); // UV Min
      glVertexArrayAttribFormat(batch->vao, 3, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, uv_min));
      glVertexArrayAttribBinding(batch->vao, 3, 1);
      glVertexArrayBindingDivisor(batch->vao, 3, 1);

      glEnableVertexArrayAttrib(batch->vao, 4); // UV Max
      glVertexArrayAttribFormat(batch->vao, 4, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, uv_max));
      glVertexArrayAttribBinding(batch->vao, 4, 1);
      glVertexArrayBindingDivisor(batch->vao, 4, 1);

      glEnableVertexArrayAttrib(batch->vao, 5); // Color
      glVertexArrayAttribFormat(batch->vao, 5, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, color));
      glVertexArrayAttribBinding(batch->vao, 5, 1);
      glVertexArrayBindingDivisor(batch->vao, 5, 1);

      glEnableVertexArrayAttrib(batch->vao, 6); // Texture ID
      glVertexArrayAttribIFormat(batch->vao, 6, 1, GL_UNSIGNED_INT, OffsetOfMember(Primitive2D, texture_id));
      glVertexArrayAttribBinding(batch->vao, 6, 1);
      glVertexArrayBindingDivisor(batch->vao, 6, 1);
    }

    // 2D Text
    {
      Render_Batch_Kind batch_kind = Render_Batch_SS_text;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_text, "u_screen_size");
    
      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_2d_quad), unit_2d_quad, 0);

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry binding (binding 0)
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));

      // Instance data binding (binding 1)
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ss_text);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_text);

      // Unit quad positions (per-vertex)
      glEnableVertexArrayAttrib(batch->vao, 0);
      glVertexArrayAttribFormat(batch->vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribBinding(batch->vao, 0, 0);

      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 1); // Position
      glVertexArrayAttribFormat(batch->vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, position));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // Scale
      glVertexArrayAttribFormat(batch->vao, 2, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, scale));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);

      glEnableVertexArrayAttrib(batch->vao, 3); // UV Min
      glVertexArrayAttribFormat(batch->vao, 3, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, uv_min));
      glVertexArrayAttribBinding(batch->vao, 3, 1);
      glVertexArrayBindingDivisor(batch->vao, 3, 1);

      glEnableVertexArrayAttrib(batch->vao, 4); // UV Max
      glVertexArrayAttribFormat(batch->vao, 4, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, uv_max));
      glVertexArrayAttribBinding(batch->vao, 4, 1);
      glVertexArrayBindingDivisor(batch->vao, 4, 1);

      glEnableVertexArrayAttrib(batch->vao, 5); // Color
      glVertexArrayAttribFormat(batch->vao, 5, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive2D, color));
      glVertexArrayAttribBinding(batch->vao, 5, 1);
      glVertexArrayBindingDivisor(batch->vao, 5, 1);

      glEnableVertexArrayAttrib(batch->vao, 6); // Texture ID
      glVertexArrayAttribIFormat(batch->vao, 6, 1, GL_UNSIGNED_INT, OffsetOfMember(Primitive2D, texture_id));
      glVertexArrayAttribBinding(batch->vao, 6, 1);
      glVertexArrayBindingDivisor(batch->vao, 6, 1);
    }
  }

  // Worldspace
  {
    // 3D Triangles
    {
      Render_Batch_Kind batch_kind = Render_Batch_WS_Triangle;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_ws_quad, "u_projection");
      batch->u_view_location = glGetUniformLocation(g_renderer.shaders.v_ws_quad, "u_view");

      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_3d_triangle), unit_3d_triangle, 0);
    
      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
      // VAO
      glCreateVertexArrays(1, &batch->vao);
    
      // Unit geometry binding (binding 0)
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec3f32));
    
      // Instance data binding (binding 1)
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive3D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ws_quad);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_texture);

      // Unit quad positions (per-vertex)
      glEnableVertexArrayAttrib(batch->vao, 0);
      glVertexArrayAttribFormat(batch->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribBinding(batch->vao, 0, 0);
    
      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 1); // Translation
      glVertexArrayAttribFormat(batch->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.translation));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // Rotation
      glVertexArrayAttribFormat(batch->vao, 2, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.rotation));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);

      glEnableVertexArrayAttrib(batch->vao, 3); // Scale
      glVertexArrayAttribFormat(batch->vao, 3, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.scale));
      glVertexArrayAttribBinding(batch->vao, 3, 1);
      glVertexArrayBindingDivisor(batch->vao, 3, 1);

      glEnableVertexArrayAttrib(batch->vao, 4); // UV Min
      glVertexArrayAttribFormat(batch->vao, 4, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, uv_min));
      glVertexArrayAttribBinding(batch->vao, 4, 1);
      glVertexArrayBindingDivisor(batch->vao, 4, 1);

      glEnableVertexArrayAttrib(batch->vao, 5); // UV Max
      glVertexArrayAttribFormat(batch->vao, 5, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, uv_max));
      glVertexArrayAttribBinding(batch->vao, 5, 1);
      glVertexArrayBindingDivisor(batch->vao, 5, 1);

      glEnableVertexArrayAttrib(batch->vao, 6); // Normal
      glVertexArrayAttribFormat(batch->vao, 6, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, normal));
      glVertexArrayAttribBinding(batch->vao, 6, 1);
      glVertexArrayBindingDivisor(batch->vao, 6, 1);

      glEnableVertexArrayAttrib(batch->vao, 7); // Color
      glVertexArrayAttribFormat(batch->vao, 7, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, color));
      glVertexArrayAttribBinding(batch->vao, 7, 1);
      glVertexArrayBindingDivisor(batch->vao, 7, 1);

      glEnableVertexArrayAttrib(batch->vao, 8); // Texture ID
      glVertexArrayAttribIFormat(batch->vao, 8, 1, GL_UNSIGNED_INT, OffsetOfMember(Primitive3D, texture_id));
      glVertexArrayAttribBinding(batch->vao, 8, 1);
      glVertexArrayBindingDivisor(batch->vao, 8, 1);
    }

    // 3D Quads
    {
      Render_Batch_Kind batch_kind = Render_Batch_WS_Quad;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_ws_quad, "u_projection");
      batch->u_view_location = glGetUniformLocation(g_renderer.shaders.v_ws_quad, "u_view");

      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_3d_quad), unit_3d_quad, 0);
    
      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
      // VAO
      glCreateVertexArrays(1, &batch->vao);
    
      // Unit geometry binding (binding 0)
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec3f32));
    
      // Instance data binding (binding 1)
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive3D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ws_quad);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_texture);

      // Unit quad positions (per-vertex)
      glEnableVertexArrayAttrib(batch->vao, 0);
      glVertexArrayAttribFormat(batch->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribBinding(batch->vao, 0, 0);
    
      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 1); // Translation
      glVertexArrayAttribFormat(batch->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.translation));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // Rotation
      glVertexArrayAttribFormat(batch->vao, 2, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.rotation));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);

      glEnableVertexArrayAttrib(batch->vao, 3); // Scale
      glVertexArrayAttribFormat(batch->vao, 3, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.scale));
      glVertexArrayAttribBinding(batch->vao, 3, 1);
      glVertexArrayBindingDivisor(batch->vao, 3, 1);

      glVertexArrayAttribFormat(batch->vao, 4, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, uv_min));
      glVertexArrayAttribBinding(batch->vao, 4, 1);
      glVertexArrayBindingDivisor(batch->vao, 4, 1);

      glEnableVertexArrayAttrib(batch->vao, 5); // UV Max
      glVertexArrayAttribFormat(batch->vao, 5, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, uv_max));
      glVertexArrayAttribBinding(batch->vao, 5, 1);
      glEnableVertexArrayAttrib(batch->vao, 4); // UV Min
      glVertexArrayBindingDivisor(batch->vao, 5, 1);

      glEnableVertexArrayAttrib(batch->vao, 6); // Normal
      glVertexArrayAttribFormat(batch->vao, 6, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, normal));
      glVertexArrayAttribBinding(batch->vao, 6, 1);
      glVertexArrayBindingDivisor(batch->vao, 6, 1);

      glEnableVertexArrayAttrib(batch->vao, 7); // Color
      glVertexArrayAttribFormat(batch->vao, 7, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, color));
      glVertexArrayAttribBinding(batch->vao, 7, 1);
      glVertexArrayBindingDivisor(batch->vao, 7, 1);

      glEnableVertexArrayAttrib(batch->vao, 8); // Texture ID
      glVertexArrayAttribIFormat(batch->vao, 8, 1, GL_UNSIGNED_INT, OffsetOfMember(Primitive3D, texture_id));
      glVertexArrayAttribBinding(batch->vao, 8, 1);
      glVertexArrayBindingDivisor(batch->vao, 8, 1);
    }

    // 3D Text
    {
      Render_Batch_Kind batch_kind = Render_Batch_WS_text;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;
      
      // Uniforms
      batch->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_ws_quad, "u_projection");
      batch->u_view_location = glGetUniformLocation(g_renderer.shaders.v_ws_quad, "u_view");

      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_3d_quad), unit_3d_quad, 0);

      // Instance data buffer  
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);

      // VAO setup
      glCreateVertexArrays(1, &batch->vao);
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec3f32));
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive3D));

      // Pipeline - use f_text fragment shader
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ws_quad);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_text);

      // Unit quad positions (per-vertex)
      glEnableVertexArrayAttrib(batch->vao, 0);
      glVertexArrayAttribFormat(batch->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
      glVertexArrayAttribBinding(batch->vao, 0, 0);
    
      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 1); // Translation
      glVertexArrayAttribFormat(batch->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.translation));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // Rotation
      glVertexArrayAttribFormat(batch->vao, 2, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.rotation));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);

      glEnableVertexArrayAttrib(batch->vao, 3); // Scale
      glVertexArrayAttribFormat(batch->vao, 3, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, transform.scale));
      glVertexArrayAttribBinding(batch->vao, 3, 1);
      glVertexArrayBindingDivisor(batch->vao, 3, 1);

      glEnableVertexArrayAttrib(batch->vao, 4); // UV Min
      glVertexArrayAttribFormat(batch->vao, 4, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, uv_min));
      glVertexArrayAttribBinding(batch->vao, 4, 1);
      glVertexArrayBindingDivisor(batch->vao, 4, 1);

      glEnableVertexArrayAttrib(batch->vao, 5); // UV Max
      glVertexArrayAttribFormat(batch->vao, 5, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, uv_max));
      glVertexArrayAttribBinding(batch->vao, 5, 1);
      glVertexArrayBindingDivisor(batch->vao, 5, 1);

      glEnableVertexArrayAttrib(batch->vao, 6); // Normal
      glVertexArrayAttribFormat(batch->vao, 6, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, normal));
      glVertexArrayAttribBinding(batch->vao, 6, 1);
      glVertexArrayBindingDivisor(batch->vao, 6, 1);

      glEnableVertexArrayAttrib(batch->vao, 7); // Color
      glVertexArrayAttribFormat(batch->vao, 7, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Primitive3D, color));
      glVertexArrayAttribBinding(batch->vao, 7, 1);
      glVertexArrayBindingDivisor(batch->vao, 7, 1);

      glEnableVertexArrayAttrib(batch->vao, 8); // Texture ID
      glVertexArrayAttribIFormat(batch->vao, 8, 1, GL_UNSIGNED_INT, OffsetOfMember(Primitive3D, texture_id));
      glVertexArrayAttribBinding(batch->vao, 8, 1);
      glVertexArrayBindingDivisor(batch->vao, 8, 1);
    }

    // Lines
    {
      Render_Batch_Kind batch_kind = Render_Batch_WS_line;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, Thousand(1));
      g_renderer.batches[batch_kind] = batch;

      batch->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_ws_line, "u_projection");
      batch->u_view_location = glGetUniformLocation(g_renderer.shaders.v_ws_line, "u_view");

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Line3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
      // VAO
      glCreateVertexArrays(1, &batch->vao);
    
      // Instance data
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Line3D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ws_line);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_line);

      // Instance data (per-instance)
      glEnableVertexArrayAttrib(batch->vao, 0); // p0
      glVertexArrayAttribFormat(batch->vao, 0, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, p0));
      glVertexArrayAttribBinding(batch->vao, 0, 1);
      glVertexArrayBindingDivisor(batch->vao, 0, 1);

      glEnableVertexArrayAttrib(batch->vao, 1); // p1
      glVertexArrayAttribFormat(batch->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, p1));
      glVertexArrayAttribBinding(batch->vao, 1, 1);
      glVertexArrayBindingDivisor(batch->vao, 1, 1);

      glEnableVertexArrayAttrib(batch->vao, 2); // color
      glVertexArrayAttribFormat(batch->vao, 2, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, color));
      glVertexArrayAttribBinding(batch->vao, 2, 1);
      glVertexArrayBindingDivisor(batch->vao, 2, 1);
    }
  }

  // Textures
  {
    s32 max_gpu_textures;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_gpu_textures);
    g_renderer.texture_max   = max_gpu_textures;
    g_renderer.textures      = push_array(g_renderer.arena, GLuint, g_renderer.texture_max);
    g_renderer.texture_count = 0;

    // Set texture sampler
    GLint* sampler_locations = push_array(scratch.arena, GLint, g_renderer.texture_max);
    for (u32 idx = 0; idx < g_renderer.texture_max; idx++)
    {
      sampler_locations[idx] = idx;
    }
    glProgramUniform1iv(g_renderer.shaders.f_texture, glGetUniformLocation(g_renderer.shaders.f_texture, "u_textures"), 32, sampler_locations);

    r_create_fallback_texture();
  }

  // Font
  {
    g_renderer.fonts_max   = 2;
    g_renderer.fonts       = push_array(g_renderer.arena, Font, g_renderer.fonts_max);
    g_renderer.fonts_count = 0;
    r_load_font(Font_ProggyClean);
  }

  scratch_end(&scratch);
}

function Render_Batch*
r_new_render_batch(Arena* arena, Render_Batch_Kind kind, u32 max_instances)
{
  Render_Batch* result = push_array(arena, Render_Batch, 1);

  u32 stride = 0;
  switch (kind)
  {
    case Render_Batch_SS_triangle:
    case Render_Batch_SS_quad:
    case Render_Batch_SS_text:
    {
      stride = sizeof(Primitive2D);
    } break;
    case Render_Batch_WS_Triangle:
    case Render_Batch_WS_Quad:
    case Render_Batch_WS_text:
    {
      stride = sizeof(Primitive3D);
    } break;
    case Render_Batch_SS_Line:
    {
      stride = sizeof(Line2D);
    } break;
    case Render_Batch_WS_line:
    {
      stride = sizeof(Line3D);
    } break;
    default:
    {
      emit_error(S("Unhandled Instanced_Target_Kind"));
      return result;
    } break;
  }

  result->kind   = kind;
  result->data   = arena_push(arena, stride * max_instances);
  result->stride = stride;
  result->max    = max_instances;
    
  return result;
}

function void
r_render(Mat4f32 view, Mat4f32 projection)
{
  // Bind textures
  for (u32 idx = 0; idx < g_renderer.texture_count; idx += 1)
  {
    glBindTextureUnit(idx, g_renderer.textures[idx]);
  }

  ///////////////////////////////////////////////////////
  // @Section: Worldspace
  if (g_renderer.batches[Render_Batch_WS_Triangle]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_WS_Triangle]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_WS_Triangle]->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_quad, g_renderer.batches[Render_Batch_WS_Triangle]->u_view_location, 1, GL_TRUE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_quad, g_renderer.batches[Render_Batch_WS_Triangle]->u_projection_location, 1, GL_TRUE, &projection.data[0][0]);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_WS_Triangle]->instance_vbo, 0, sizeof(Primitive3D) * g_renderer.batches[Render_Batch_WS_Triangle]->count, g_renderer.batches[Render_Batch_WS_Triangle]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, g_renderer.batches[Render_Batch_WS_Triangle]->count);
  }

  if (g_renderer.batches[Render_Batch_WS_Quad]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_WS_Quad]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_WS_Quad]->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_quad, g_renderer.batches[Render_Batch_WS_Quad]->u_view_location, 1, GL_TRUE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_quad, g_renderer.batches[Render_Batch_WS_Quad]->u_projection_location, 1, GL_TRUE, &projection.data[0][0]);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_WS_Quad]->instance_vbo, 0, sizeof(Primitive3D) * g_renderer.batches[Render_Batch_WS_Quad]->count, g_renderer.batches[Render_Batch_WS_Quad]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_WS_Quad]->count);
  }

  if (g_renderer.batches[Render_Batch_WS_text]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_WS_text]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_WS_text]->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_quad, g_renderer.batches[Render_Batch_WS_text]->u_view_location, 1, GL_TRUE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_quad, g_renderer.batches[Render_Batch_WS_text]->u_projection_location, 1, GL_TRUE, &projection.data[0][0]);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_WS_text]->instance_vbo, 0, sizeof(Primitive3D) * g_renderer.batches[Render_Batch_WS_text]->count, g_renderer.batches[Render_Batch_WS_text]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_WS_text]->count);
  }

  if (g_renderer.batches[Render_Batch_WS_line]->count > 0)
  {
    // Lines
    glBindProgramPipeline(g_renderer.batches[Render_Batch_WS_line]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_WS_line]->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_line, g_renderer.batches[Render_Batch_WS_line]->u_view_location, 1, GL_TRUE, (f32*)&view);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_line, g_renderer.batches[Render_Batch_WS_line]->u_projection_location, 1, GL_TRUE, (f32*)&projection);
    
    glNamedBufferSubData(g_renderer.batches[Render_Batch_WS_line]->instance_vbo, 0, sizeof(Line3D) * g_renderer.batches[Render_Batch_WS_line]->count, g_renderer.batches[Render_Batch_WS_line]->data);
    glDrawArraysInstanced(GL_LINES, 0, 2, g_renderer.batches[Render_Batch_WS_line]->count);
  }

  ///////////////////////////////////////////////////////
  // @Section: Screenspace
  if (g_renderer.batches[Render_Batch_SS_triangle]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_triangle]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_triangle]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_quad, g_renderer.batches[Render_Batch_SS_triangle]->u_screen_size_location, (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_triangle]->instance_vbo, 0, sizeof(Primitive2D) * g_renderer.batches[Render_Batch_SS_triangle]->count, g_renderer.batches[Render_Batch_SS_triangle]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_SS_triangle]->count);
  }

  if (g_renderer.batches[Render_Batch_SS_quad]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_quad]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_quad]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_quad, g_renderer.batches[Render_Batch_SS_quad]->u_screen_size_location, (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_quad]->instance_vbo, 0, sizeof(Primitive2D) * g_renderer.batches[Render_Batch_SS_quad]->count, g_renderer.batches[Render_Batch_SS_quad]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_SS_quad]->count);
  }

  if (g_renderer.batches[Render_Batch_SS_text]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_text]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_text]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_text, g_renderer.batches[Render_Batch_SS_text]->u_screen_size_location, (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_text]->instance_vbo, 0, sizeof(Primitive2D) * g_renderer.batches[Render_Batch_SS_text]->count, g_renderer.batches[Render_Batch_SS_text]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_SS_text]->count);
  }

  if (g_renderer.batches[Render_Batch_SS_Line]->count > 0)
  {
    // Draw on top of everything
    glDepthFunc(GL_ALWAYS);
    glDepthMask(GL_TRUE);

    // Lines
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_Line]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_Line]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_line, g_renderer.batches[Render_Batch_SS_Line]->u_screen_size_location, (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);
    
    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_Line]->instance_vbo, 0, sizeof(Line2D) * g_renderer.batches[Render_Batch_SS_Line]->count, g_renderer.batches[Render_Batch_SS_Line]->data);
    glDrawArraysInstanced(GL_LINES, 0, 2, g_renderer.batches[Render_Batch_SS_Line]->count);

    glDepthFunc(GL_LESS); 
  }

  os_swap_buffers();

  glClearColor(0.5f, 0.96f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  for (u32 idx = 1; idx < Render_Batch_Count; idx += 1)
  {
    g_renderer.batches[idx]->count = 0;
  }
}

function void
r_draw_2d_line(Vec2f32 p0, Vec2f32 p1, Vec4f32 color)
{
  if (g_renderer.batches[Render_Batch_SS_Line]->count >= g_renderer.batches[Render_Batch_SS_Line]->max)
  {
    emit_fatal(S("Tried to render more lines than g_renderer.batches[Render_Batch_SS_Line]->max"));
    return;
  }
  Line2D* data = (Line2D*)g_renderer.batches[Render_Batch_SS_Line]->data;
  data[g_renderer.batches[Render_Batch_SS_Line]->count].p0    = p0;
  data[g_renderer.batches[Render_Batch_SS_Line]->count].p1    = p1;
  data[g_renderer.batches[Render_Batch_SS_Line]->count].color = color;
  g_renderer.batches[Render_Batch_SS_Line]->count += 1;
}

function void
_r_draw_2d_primitive(Render_Batch* render_batch, Vec2f32 position, Vec2f32 scale, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  if (render_batch->count >= render_batch->max)
  {
    emit_fatal(S("Tried to render more quads than render_batch->max"));
    return;
  }

  Primitive2D* data = (Primitive2D*)render_batch->data;
  data[render_batch->count].position   = position;
  data[render_batch->count].scale      = scale;
  data[render_batch->count].uv_min     = uv_min;
  data[render_batch->count].uv_max     = uv_max;
  data[render_batch->count].color      = color;
  data[render_batch->count].texture_id = texture_id;
  render_batch->count += 1;
}

function void
r_draw_2d_triangle(Vec2f32 position, Vec2f32 scale, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  _r_draw_2d_primitive(g_renderer.batches[Render_Batch_SS_triangle], position, scale, uv_min, uv_max, color, texture_id);
}

function void
r_draw_2d_quad(Vec2f32 position, Vec2f32 scale, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  _r_draw_2d_primitive(g_renderer.batches[Render_Batch_SS_quad], position, scale, uv_min, uv_max, color, texture_id);
}

function void
r_draw_2d_box(Vec2f32 p0, Vec2f32 p1, Vec4f32 color)
{
  r_draw_2d_line(p0, vec2f32(p0.x, p1.y), color);
  r_draw_2d_line(vec2f32(p0.x, p1.y), p1, color);
  r_draw_2d_line(p1, vec2f32(p1.x, p0.y), color);
  r_draw_2d_line(vec2f32(p1.x, p0.y), p0, color);
}

function Vec2f32
r_draw_2d_text(Vec2f32 position, f32 scale, Vec4f32 color, String8 text)
{
  if (g_renderer.batches[Render_Batch_SS_text]->count + text.size >= g_renderer.batches[Render_Batch_SS_text]->max)
  {
    emit_fatal(S("Tried to render more textured quads than g_renderer.batches[Render_Batch_SS_quad]_texture->max"));
    return vec2f32(0, 0);
  }

  Font* font = &g_renderer.fonts[0]; // TODO(fz): Should be arg
  
  for (u64 i = 0; i < text.size; ++i)
  {
    u8 c = text.str[i];

    if (c == '\n' || c < 32 || c > 126)
    {
      continue;
    }

    Glyph* glyph = &font->glyphs[c - 32];
  
    // Around the glyph
    {
      f32 half_advan  = glyph->advance / 2;
      f32 half_width  = glyph->size.x / 2;
      f32 half_height = glyph->size.y / 2;
      Vec2f32 p0 = vec2f32(position.x - half_width, position.y - half_height);
      Vec2f32 p1 = vec2f32(position.x + half_width, position.y + half_height);
      r_draw_2d_box(p0, p1, Color_Yellow(1));
    }

    // Red box: advance area (centered on position)
    {
      f32 half_advance = glyph->advance / 2;
      f32 half_line    = font->line_height / 2;
      Vec2f32 p0 = vec2f32(position.x - half_advance, position.y - half_line);
      Vec2f32 p1 = vec2f32(position.x + half_advance, position.y + half_line);
      r_draw_2d_box(p0, p1, Color_Red(1));
    }

    _r_draw_2d_primitive(g_renderer.batches[Render_Batch_SS_text], position, glyph->size, glyph->uv_min, glyph->uv_max, color, font->texture_index);
    position.x += glyph->advance;
  }

  return vec2f32(0, 0);
}

function void
_r_draw_3d_primitive(Render_Batch* render_batch, Transform3f32 transform, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  if (render_batch->count >= render_batch->max)
  {
    emit_fatal(S("Tried to render more primitives than render_batch->max"));
    return;
  }

  Vec4f32 normal4 = vec4f32_mul_mat4f32(vec4f32(0.0f, 0.0f, 1.0f, 0.0f), mat4f32_from_quatf32(transform.rotation));
  Vec3f32 normal = vec3f32_normalize(vec3f32_from_vec4f32(normal4));

  Vec3f32 end = vec3f32_add(transform.translation, vec3f32_scale(normal, 1.0f));
  r_draw_3d_line(transform.translation, end, Color_Yellow(1.0f));

  Primitive3D *data = (Primitive3D*)render_batch->data;
  data[render_batch->count].transform = transform;
  data[render_batch->count].uv_min    = uv_min;
  data[render_batch->count].uv_max    = uv_max;
  data[render_batch->count].normal    = normal;
  data[render_batch->count].color     = color;
  data[render_batch->count].texture_id= texture_id;
  render_batch->count += 1;
}

function void
r_draw_3d_triangle(Transform3f32 transform, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  _r_draw_3d_primitive(g_renderer.batches[Render_Batch_WS_Triangle], transform, uv_min, uv_max, color, texture_id);
}

function void
r_draw_3d_quad(Transform3f32 transform, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  _r_draw_3d_primitive(g_renderer.batches[Render_Batch_WS_Quad], transform, uv_min, uv_max, color, texture_id);
}

function void
r_draw_3d_box(Vec3f32 translation, Quatf32 rotation, f32 size, Vec4f32 color)
{
  f32 half_size = size * 0.5f;
  
  // 8 corners of the cube in local space (centered at origin)
  Vec3f32 corners[8] = {
    vec3f32(-half_size, -half_size, -half_size), // 0: back-bottom-left
    vec3f32( half_size, -half_size, -half_size), // 1: back-bottom-right
    vec3f32( half_size,  half_size, -half_size), // 2: back-top-right
    vec3f32(-half_size,  half_size, -half_size), // 3: back-top-left
    vec3f32(-half_size, -half_size,  half_size), // 4: front-bottom-left
    vec3f32( half_size, -half_size,  half_size), // 5: front-bottom-right
    vec3f32( half_size,  half_size,  half_size), // 6: front-top-right
    vec3f32(-half_size,  half_size,  half_size), // 7: front-top-left
  };
  
  // Transform all corners: rotate -> translate
  for (s32 i = 0; i < 8; i++) {
    corners[i] = quatf32_rotate_vec3f32(rotation, corners[i]);
    corners[i] = vec3f32_add(corners[i], translation);
  }
  
  // Back face (z = min)
  r_draw_3d_line(corners[0], corners[1], color);
  r_draw_3d_line(corners[1], corners[2], color);
  r_draw_3d_line(corners[2], corners[3], color);
  r_draw_3d_line(corners[3], corners[0], color);
  
  // Front face (z = max)
  r_draw_3d_line(corners[4], corners[5], color);
  r_draw_3d_line(corners[5], corners[6], color);
  r_draw_3d_line(corners[6], corners[7], color);
  r_draw_3d_line(corners[7], corners[4], color);
  
  // Connecting edges (back to front)
  r_draw_3d_line(corners[0], corners[4], color);
  r_draw_3d_line(corners[1], corners[5], color);
  r_draw_3d_line(corners[2], corners[6], color);
  r_draw_3d_line(corners[3], corners[7], color);
}

function void
r_draw_3d_text(Transform3f32 transform, Vec4f32 color, f32 font_scale, String8 text)
{
  font_scale *= 0.002;

  Font* font = &g_renderer.fonts[0];
  f32 cursor_x = 0;
  f32 cursor_y = 0;
  f32 line_height = font->line_height * font_scale;
  
  for (u64 i = 0; i < text.size; ++i)
  {
    u8 c = text.str[i];
    
    if (c == '\n')
    {
      cursor_x = 0;
      cursor_y -= line_height;
      continue;
    }
    
    if (c < 32 || c > 126) continue;
    
    Glyph* glyph = &font->glyphs[c - 32];
    
    Vec3f32 glyph_translation = vec3f32_add(transform.translation, vec3f32(
      cursor_x + glyph->offset.x * font_scale,
      cursor_y - glyph->offset.y * font_scale,
      0.0f
    ));
    
    Vec3f32 glyph_scale = vec3f32(
      glyph->size.x * font_scale,
      glyph->size.y * font_scale,
      1.0f
    );
    
    if (g_renderer.batches[Render_Batch_WS_text]->count >= g_renderer.batches[Render_Batch_WS_text]->max)
    {
      emit_fatal(S("Tried to render more 3D text quads than max"));
      return;
    }

    Transform3f32 text_transform = transform3f32(glyph_translation, transform.rotation, glyph_scale);
    Vec2f32 uv_min = vec2f32(glyph->uv_min.x, glyph->uv_max.y);
    Vec2f32 uv_max = vec2f32(glyph->uv_max.x, glyph->uv_min.y);
    _r_draw_3d_primitive(g_renderer.batches[Render_Batch_WS_text], text_transform, uv_min, uv_max, color, font->texture_index);
    
    cursor_x += glyph->advance * font_scale;
  }
}

function void
r_draw_3d_line(Vec3f32 p0, Vec3f32 p1, Vec4f32 color)
{
  if (g_renderer.batches[Render_Batch_WS_line]->count >= g_renderer.batches[Render_Batch_WS_line]->max)
  {
    emit_fatal(S("Tried to render more lines than g_renderer.batches[Render_Batch_WS_line]->max"));
    return;
  }
  Line3D* data = (Line3D*)g_renderer.batches[Render_Batch_WS_line]->data;
  data[g_renderer.batches[Render_Batch_WS_line]->count].p0    = p0;
  data[g_renderer.batches[Render_Batch_WS_line]->count].p1    = p1;
  data[g_renderer.batches[Render_Batch_WS_line]->count].color = color;
  g_renderer.batches[Render_Batch_WS_line]->count += 1;
}

function void
r_draw_3d_arrow(Vec3f32 start, Vec3f32 end, Vec4f32 color)
{
  r_draw_3d_line(start, end, color);

  Vec3f32 dir = vec3f32_sub(end, start);
  f32 len = vec3f32_length(dir);
  if (len < 0.0001f) return;

  dir = vec3f32_normalize(dir);

  Vec3f32 up = fabsf(dir.y) < 0.99f ? vec3f32(0,1,0) : vec3f32(1,0,0);

  Vec3f32 right   = vec3f32_normalize(vec3f32_cross(up, dir));
  Vec3f32 forward = vec3f32_cross(dir, right);

  f32 head_length = 0.2f;
  right   = vec3f32_scale(right, head_length);
  forward = vec3f32_scale(forward, head_length);
  Vec3f32 tip  = end;
  Vec3f32 base = vec3f32_sub(tip, vec3f32_scale(dir, head_length));

  // Two arrowhead lines
  r_draw_3d_line(tip, vec3f32_add(base, right),   color);
  r_draw_3d_line(tip, vec3f32_sub(base, right),   color);
  r_draw_3d_line(tip, vec3f32_add(base, forward), color);
  r_draw_3d_line(tip, vec3f32_sub(base, forward), color);
}

function void
r_draw_grid(Vec3f32 center, Vec3f32 normal, Vec3f32 forward, u32 square_size, u32 square_per_side, Vec4f32 color)
{
  u32 width = square_per_side * square_size;

  Vec3f32 left  = vec3f32_cross(normal, forward);
  Vec3f32 right = vec3f32_scale(left, -1);
  
  Vec3f32 p0_v = vec3f32_add(center, vec3f32_scale(left, width / 2));
  p0_v = vec3f32_add(p0_v, vec3f32_scale(vec3f32_scale(forward, -1), width / 2));
  Vec3f32 p0_h = p0_v;
  
  Vec3f32 p1_v = vec3f32_add(p0_v, vec3f32_scale(forward, width));
  Vec3f32 p1_h = vec3f32_add(p0_h, vec3f32_scale(right, width));

  for (u32 idx = 0; idx <= square_per_side; idx += 1)
  {
    r_draw_3d_line(p0_v, p1_v, color);
    r_draw_3d_line(p0_h, p1_h, color);

    p0_v = vec3f32_add(p0_v, vec3f32_scale(right, square_size));
    p1_v = vec3f32_add(p1_v, vec3f32_scale(right, square_size));

    p0_h = vec3f32_add(p0_h, vec3f32_scale(forward, square_size));
    p1_h = vec3f32_add(p1_h, vec3f32_scale(forward, square_size));
  }
}

function void
r_load_font(String8 relative_path) 
{
  Scratch scratch = scratch_begin(0, 0);
  f32 font_height = FontSize;

  if (g_renderer.texture_count >= g_renderer.texture_max)
  {
    emit_error(S("Error loading font. More textures than g_renderer.texture_max"));
    return;
  }
 
  String8 project_path = os_executable_path(scratch.arena);
  project_path = os_directory_pop(project_path);
  project_path = os_directory_pop(project_path);
  String8 font_path = string8_concat(scratch.arena, project_path, relative_path);
  File_Data file_data = os_file_load(scratch.arena, font_path);
 
  if (!file_data.data.str || file_data.data.size == 0)
  {
    emit_error(Sf(scratch.arena, "Error loading font. Failed to load file: %.*s", font_path.size, font_path.str));
    return;
  }
 
  stbtt_fontinfo font_info;
  if (!stbtt_InitFont(&font_info, (u8*)file_data.data.str, 0))
  {
    emit_error(S("Error initializing font with stbtt_InitFont"));
    return;
  }
 
  // Get font metrics in font units
  s32 ascent, descent, line_gap;
  stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &line_gap);
 
  // Calculate scale to convert font units to pixels
  f32 scale = stbtt_ScaleForPixelHeight(&font_info, font_height);
 
  s32 atlas_width = 512, atlas_height = 512;
  u8* atlas_bitmap = push_array(scratch.arena, u8, atlas_width * atlas_height);
  stbtt_packedchar char_data[MaxFontGlyphs];
 
  stbtt_pack_context pack;
  stbtt_PackBegin(&pack, atlas_bitmap, atlas_width, atlas_height, atlas_width, 1, NULL);
  stbtt_PackSetOversampling(&pack, 1, 1);
  stbtt_PackFontRange(&pack, (u8*)file_data.data.str, 0, font_height, 32, MaxFontGlyphs, char_data);
  stbtt_PackEnd(&pack);
 
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, atlas_width, atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, atlas_bitmap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
  for (s32 i = 0; i < MaxFontGlyphs; i++)
  {
    Glyph* glyph = &g_renderer.fonts[g_renderer.fonts_count].glyphs[i];
    stbtt_packedchar* ch = &char_data[i];
  
    glyph->uv_min = vec2f32((f32)ch->x0 / atlas_width, (f32)ch->y1 / atlas_height);
    glyph->uv_max = vec2f32((f32)ch->x1 / atlas_width, (f32)ch->y0 / atlas_height);

    glyph->size    = vec2f32(ch->x1 - ch->x0, ch->y1 - ch->y0);
    glyph->offset  = vec2f32(ch->xoff, ch->yoff);
    glyph->advance = ch->xadvance;
  }
 
  scratch_end(&scratch);
 
  // Store font data
  g_renderer.textures[g_renderer.texture_count] = texture;
 
  Font* font = &g_renderer.fonts[g_renderer.fonts_count];
  font->texture_id    = texture;
  font->texture_index = g_renderer.texture_count;
  font->height        = font_height;
  font->ascent        = ascent * scale;   // Pixels above baseline
  font->descent       = descent * scale;  // Pixels below baseline (negative)
  font->line_gap      = line_gap * scale; // Extra spacing between lines
  font->line_height   = (ascent - descent + line_gap) * scale; // Proper line spacing
 
  g_renderer.texture_count += 1;
  g_renderer.fonts_count += 1;
}

function Texture_Info
r_load_texture(String8 path)
{
  Scratch scratch = scratch_begin(0, 0);
  Texture_Info result = {0};

  if (g_renderer.texture_count >= g_renderer.texture_max)
  {
    emit_error(S("Texture limit reached\n"));
    return result;
  }

  stbi_set_flip_vertically_on_load(1);

  s32 width, height, channels;
  u8 *data = stbi_load(path.str, &width, &height, &channels, 4); // force 4 channels
  if (!data || width <= 0 || height <= 0)
  {
    emit_error(Sf(scratch.arena, "Failed to load texture or invalid dimensions: %s\n", path.str));
    if (data)
    {
      stbi_image_free(data);
    }
    return result;
  }

  GLuint texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
  glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  stbi_image_free(data);

  g_renderer.textures[g_renderer.texture_count] = texture;

  result.handle = texture;
  result.index  = g_renderer.texture_count;
  result.width  = width;
  result.height = height;
  g_renderer.texture_count += 1;

  scratch_end(&scratch);
  return result;
}

function void
r_create_fallback_texture()
{
  Scratch scratch = scratch_begin(0,0);

  u32 size = 16;
  u32 square_size = 2;
  u8* data = arena_push(scratch.arena, size * size * 4);
  
  for (u32 y = 0; y < size; y++)
  {
    for (u32 x = 0; x < size; x++)
    {
      u32 square_x = x / square_size;
      u32 square_y = y / square_size;
      b32 is_black = (square_x + square_y) % 2 == 0;
      
      u32 pixel_index = (y * size + x) * 4;
      if (is_black)
      {
        data[pixel_index + 0] = 0;   // R
        data[pixel_index + 1] = 0;   // G
        data[pixel_index + 2] = 0;   // B
        data[pixel_index + 3] = 255; // A
      }
      else
      {
        data[pixel_index + 0] = 255; // R
        data[pixel_index + 1] = 0;   // G
        data[pixel_index + 2] = 255; // B
        data[pixel_index + 3] = 255; // A
      }
    }
  }

  GLuint texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGBA8, size, size);
  glTextureSubImage2D(texture, 0, 0, 0, size, size, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

  for (u32 slot = 0; slot < g_renderer.texture_max; slot++)
  {
    glBindTextureUnit(slot, texture);
  }

  scratch_end(&scratch);
}

function Texture_Info
r_create_color_texture(Vec4f32 color)
{
  Scratch scratch = scratch_begin(0, 0);
  Texture_Info result = {0};

  u32 size = 16;
  u8* data = push_array(scratch.arena, u8, size * size * 4);

  for (u32 y = 0; y < size; y++)
  {
    for (u32 x = 0; x < size; x++)
    {
      u32 pixel_index = (y * size + x) * 4;
      data[pixel_index + 0] = (u8)(color.x * 255.0f + 0.5f);
      data[pixel_index + 1] = (u8)(color.y * 255.0f + 0.5f);
      data[pixel_index + 2] = (u8)(color.z * 255.0f + 0.5f);
      data[pixel_index + 3] = (u8)(color.w * 255.0f + 0.5f);
    }
  }

  GLuint texture;
  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGBA8, size, size);
  glTextureSubImage2D(texture, 0, 0, 0, size, size, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

  g_renderer.textures[g_renderer.texture_count] = texture;

  result.handle = texture;
  result.index  = g_renderer.texture_count;
  result.width  = size;
  result.height = size;
  g_renderer.texture_count += 1;

  scratch_end(&scratch);
  return result;
}

function void
r_toggle_wireframe()
{
  local_persist b32 is_wireframe = false;
  glPolygonMode(GL_FRONT_AND_BACK, is_wireframe ? GL_FILL : GL_LINE);
  is_wireframe = !is_wireframe;
}

function u32
r_compile_shader(String8 relative_path, GLenum shader_type)
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
      emit_error(string8_from_format(scratch.arena, "Failed to create shader: %s", info_log));
    }
  }

  scratch_end(&scratch);
  return result;
}