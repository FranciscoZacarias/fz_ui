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
  
  g_renderer.shaders.v_ss_line = r_compile_shader(V_SS_LINE_PATH,      GL_VERTEX_SHADER);
  g_renderer.shaders.v_ss_quad = r_compile_shader(V_SS_PRIMITIVE_PATH, GL_VERTEX_SHADER);
  g_renderer.shaders.v_ss_text = r_compile_shader(V_SS_TEXT_PATH,      GL_VERTEX_SHADER);

  g_renderer.shaders.v_ws_line = r_compile_shader(V_WS_LINE_PATH,      GL_VERTEX_SHADER);

  g_renderer.shaders.f_line    = r_compile_shader(F_COLOR_PATH,    GL_FRAGMENT_SHADER);
  g_renderer.shaders.f_texture = r_compile_shader(F_TEXTURE_PATH, GL_FRAGMENT_SHADER);
  g_renderer.shaders.f_text    = r_compile_shader(F_TEXT_PATH,    GL_FRAGMENT_SHADER);
  
  // Screenspace
  {
    // 2D Lines
    {
      Render_Batch_Kind batch_kind = Render_Batch_SS_Line;
      u32 max_instances = Thousand(2);

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_line, "u_screen_size");

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Line2D) * max_instances, NULL, GL_DYNAMIC_STORAGE_BIT);
    
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
      u32 max_instances = Thousand(1);

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_quad, "u_screen_size");
    
      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_2d_triangle), unit_2d_triangle, 0);

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * max_instances, NULL, GL_DYNAMIC_STORAGE_BIT);

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
      u32 max_instances = Thousand(1);

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_quad, "u_screen_size");
    
      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_2d_quad), unit_2d_quad, 0);

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * max_instances, NULL, GL_DYNAMIC_STORAGE_BIT);

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
      u32 max_instances = Thousand(1);

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_ss_text, "u_screen_size");
    
      // Unit geometry buffer
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_2d_quad), unit_2d_quad, 0);

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * max_instances, NULL, GL_DYNAMIC_STORAGE_BIT);

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
    
    // Lines
    {
      Render_Batch_Kind batch_kind = Render_Batch_WS_Line;
      u32 max_instances = Thousand(2);

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_ws_line, "u_projection");
      batch->u_view_location = glGetUniformLocation(g_renderer.shaders.v_ws_line, "u_view");

      // Instance data buffer
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Line2D) * max_instances, NULL, GL_DYNAMIC_STORAGE_BIT);
    
      // VAO
      glCreateVertexArrays(1, &batch->vao);
    
      // Instance data
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Line2D));

      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_ws_line);
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
    r_load_font(FONT_INCONSOLATA_PATH);
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
    case Render_Batch_SS_Line:
    case Render_Batch_WS_Line:
    {
      stride = sizeof(Line2D);
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
  if (g_renderer.batches[Render_Batch_WS_Line]->count > 0)
  {
    // Lines
    glBindProgramPipeline(g_renderer.batches[Render_Batch_WS_Line]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_WS_Line]->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_line, g_renderer.batches[Render_Batch_WS_Line]->u_view_location, 1, GL_TRUE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_ws_line, g_renderer.batches[Render_Batch_WS_Line]->u_projection_location, 1, GL_TRUE, &projection.data[0][0]);
    
    glNamedBufferSubData(g_renderer.batches[Render_Batch_WS_Line]->instance_vbo, 0, sizeof(Line2D) * g_renderer.batches[Render_Batch_WS_Line]->count, g_renderer.batches[Render_Batch_WS_Line]->data);
    glDrawArraysInstanced(GL_LINES, 0, 2, g_renderer.batches[Render_Batch_WS_Line]->count);

    glDepthFunc(GL_LESS); 
  }

  ///////////////////////////////////////////////////////
  // @Section: Screenspace
  if (g_renderer.batches[Render_Batch_SS_triangle]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_triangle]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_triangle]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_quad, g_renderer.batches[Render_Batch_SS_triangle]->u_screen_size_location, (f32)g_os_window.dimensions.x, (f32)g_os_window.dimensions.y);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_triangle]->instance_vbo, 0, sizeof(Primitive2D) * g_renderer.batches[Render_Batch_SS_triangle]->count, g_renderer.batches[Render_Batch_SS_triangle]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_SS_triangle]->count);
  }

  if (g_renderer.batches[Render_Batch_SS_quad]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_quad]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_quad]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_quad, g_renderer.batches[Render_Batch_SS_quad]->u_screen_size_location, (f32)g_os_window.dimensions.x, (f32)g_os_window.dimensions.y);

    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_quad]->instance_vbo, 0, sizeof(Primitive2D) * g_renderer.batches[Render_Batch_SS_quad]->count, g_renderer.batches[Render_Batch_SS_quad]->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.batches[Render_Batch_SS_quad]->count);
  }

  if (g_renderer.batches[Render_Batch_SS_text]->count > 0)
  {
    glBindProgramPipeline(g_renderer.batches[Render_Batch_SS_text]->pipeline);
    glBindVertexArray(g_renderer.batches[Render_Batch_SS_text]->vao);

    glProgramUniform2f(g_renderer.shaders.v_ss_text, g_renderer.batches[Render_Batch_SS_text]->u_screen_size_location, (f32)g_os_window.dimensions.x, (f32)g_os_window.dimensions.y);

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

    glProgramUniform2f(g_renderer.shaders.v_ss_line, g_renderer.batches[Render_Batch_SS_Line]->u_screen_size_location, (f32)g_os_window.dimensions.x, (f32)g_os_window.dimensions.y);
    
    glNamedBufferSubData(g_renderer.batches[Render_Batch_SS_Line]->instance_vbo, 0, sizeof(Line2D) * g_renderer.batches[Render_Batch_SS_Line]->count, g_renderer.batches[Render_Batch_SS_Line]->data);
    glDrawArraysInstanced(GL_LINES, 0, 2, g_renderer.batches[Render_Batch_SS_Line]->count);

    glDepthFunc(GL_LESS); 
  }

  os_swap_buffers();

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
    emit_fatal(S("Tried to render more lines than g_renderer.batches[Render_Batch_SS_Line]->Max"));
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
    emit_fatal(S("Tried to render more quads than render_batch->Max"));
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
r_draw_2d_quad_colored(Vec2f32 position, Vec2f32 scale, Vec4f32 color)
{
	_r_draw_2d_primitive(g_renderer.batches[Render_Batch_SS_quad], position, scale, vec2f32(0.0f, 0.0), vec2f32(1.0f, 1.0f), color, 0xFFFFFFFFu);
}

function void
r_draw_2d_point(Vec2f32 position, Vec4f32 color)
{
  f32 len = 10.0f;
  f32 diag = sqrtf(len);
  r_draw_2d_line(vec2f32(position.x - diag, position.y - diag), vec2f32(position.x + diag, position.y + diag), color);
  r_draw_2d_line(vec2f32(position.x - diag, position.y + diag), vec2f32(position.x + diag, position.y - diag), color);
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
r_draw_2d_text(Vec2f32 position, f32 pixel_height, Vec4f32 color, String8 text)
{
  if (g_renderer.batches[Render_Batch_SS_text]->count + text.size >= g_renderer.batches[Render_Batch_SS_text]->max)
  {
    emit_fatal(S("Tried to render more textured quads than g_renderer.batches[Render_Batch_SS_quad]_texture->Max"));
    return vec2f32(0, 0);
  }
  Font* font = &g_renderer.fonts[0]; // TODO(fz): Font should be arg
  f32 pixel_scale = pixel_height / font->height;
  f32 line_height = font->line_height * pixel_scale;
 
  // Get first character to calculate offset
  u8 first_char = text.str[0];
  Glyph* first_glyph = &font->glyphs[first_char - 32];
 
  // Adjust starting position so first glyph centers on 'position'
  Vec2f32 start_pos = vec2f32(
    position.x - (first_glyph->offset.x + first_glyph->size.x * 0.5f) * pixel_scale,
    position.y + (first_glyph->offset.y + first_glyph->size.y * 0.5f) * pixel_scale
  );
 
  Vec2f32 cursor = start_pos;
  f32 max_width = 0.0f;
  f32 current_line_width = 0.0f;
  s32 line_count = 1;
 
  for (u64 idx = 0; idx < text.size; ++idx)
  {
    u8 c = text.str[idx];
   
    if (c == '\n')
    {
      max_width = Max(max_width, current_line_width);
      current_line_width = 0.0f;
      cursor.x = start_pos.x;
      cursor.y -= line_height;
      line_count++;
      continue;
    }
   
    if (c < 32 || c > 126)
    {
      continue;
    }
   
    Glyph* glyph = &font->glyphs[c - 32];
   
    Vec2f32 glyph_pos = vec2f32(
      cursor.x + (glyph->offset.x + glyph->size.x * 0.5f) * pixel_scale,
      cursor.y - (glyph->offset.y + glyph->size.y * 0.5f) * pixel_scale
    );
    Vec2f32 glyph_size = vec2f32(glyph->size.x * pixel_scale, glyph->size.y * pixel_scale);
    _r_draw_2d_primitive(g_renderer.batches[Render_Batch_SS_text], glyph_pos, glyph_size, glyph->uv_min, glyph->uv_max, color, font->texture_index);
   
    f32 advance = glyph->advance * pixel_scale;
    cursor.x += advance;
    current_line_width += advance;
  }
 
  max_width = Max(max_width, current_line_width);
  f32 total_height = line_count * line_height;
 
  return vec2f32(max_width, total_height);
}

function Vec2f32
r_draw_2d_text_centered(Vec2f32 position, f32 pixel_height, Vec4f32 color, String8 text)
{
  if (g_renderer.batches[Render_Batch_SS_text]->count + text.size >= g_renderer.batches[Render_Batch_SS_text]->max)
  {
    emit_fatal(S("Tried to render more textured quads than g_renderer.batches[Render_Batch_SS_quad]_texture->Max"));
    return vec2f32(0, 0);
  }
  
  Font* font = &g_renderer.fonts[0]; // TODO(fz): Font should be arg
  u8 first_char = text.str[0];
  Glyph* first_glyph = &font->glyphs[first_char - 32];
 
  Vec2f32 size = r_get_2d_text_dimensions(text, pixel_height);

  position.x = position.x - (size.x / 2) + (first_glyph->size.x / 2);
  position.y = position.y + (size.y / 2);

  r_draw_2d_text(position, pixel_height, color, text);

  return vec2f32(0, 0);
}

function void
r_draw_2d_grid(Vec2f32 p0, Vec2f32 p1, u32 square_size_pixel, Vec4f32 color)
{
  f32 width = p1.x - p0.x;
  f32 height = p1.y - p0.y;
 
  u32 vertical_lines = (u32)(width / square_size_pixel) + 1;
  u32 horizontal_lines = (u32)(height / square_size_pixel) + 1;
 
  for (u32 i = 0; i < vertical_lines; ++i)
  {
    f32 x = p0.x + i * square_size_pixel;
    if (x <= p1.x)
    {
      r_draw_2d_line(vec2f32(x, p0.y), vec2f32(x, p1.y), color);
    }
  }
 
  for (u32 i = 0; i < horizontal_lines; ++i)
  {
    f32 y = p0.y + i * square_size_pixel;
    if (y <= p1.y)
    {
      r_draw_2d_line(vec2f32(p0.x, y), vec2f32(p1.x, y), color);
    }
  }
}

function void
_r_draw_ws_primitive(Render_Batch* render_batch, Vec2f32 position, Vec2f32 scale, Vec2f32 uv_min, Vec2f32 uv_max, Vec4f32 color, u32 texture_id)
{
  if (render_batch->count >= render_batch->max)
  {
    emit_fatal(S("Tried to render more quads than render_batch->Max"));
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
r_draw_ws_line(Vec2f32 p0, Vec2f32 p1, Vec4f32 color)
{
  if (g_renderer.batches[Render_Batch_WS_Line]->count >= g_renderer.batches[Render_Batch_WS_Line]->max)
  {
    emit_fatal(S("Tried to render more lines than g_renderer.batches[Render_Batch_WS_Line]->Max"));
    return;
  }
  Line2D* data = (Line2D*)g_renderer.batches[Render_Batch_WS_Line]->data;
  data[g_renderer.batches[Render_Batch_WS_Line]->count].p0    = p0;
  data[g_renderer.batches[Render_Batch_WS_Line]->count].p1    = p1;
  data[g_renderer.batches[Render_Batch_WS_Line]->count].color = color;
  g_renderer.batches[Render_Batch_WS_Line]->count += 1;
}

function void
r_draw_ws_grid(Vec2f32 p0, Vec2f32 p1, u32 square_size_pixel, Vec4f32 color)
{
  f32 width = p1.x - p0.x;
  f32 height = p1.y - p0.y;
 
  u32 vertical_lines = (u32)(width / square_size_pixel) + 1;
  u32 horizontal_lines = (u32)(height / square_size_pixel) + 1;
 
  for (u32 i = 0; i < vertical_lines; ++i)
  {
    f32 x = p0.x + i * square_size_pixel;
    if (x <= p1.x)
    {
      r_draw_ws_line(vec2f32(x, p0.y), vec2f32(x, p1.y), color);
    }
  }
 
  for (u32 i = 0; i < horizontal_lines; ++i)
  {
    f32 y = p0.y + i * square_size_pixel;
    if (y <= p1.y)
    {
      r_draw_ws_line(vec2f32(p0.x, y), vec2f32(p1.x, y), color);
    }
  }
}

function void
r_clear_color(Vec4f32 color)
{
  glClearColor(color.x, color.y, color.z, color.w);
}

function void
r_load_font(String8 relative_path) 
{
  Scratch scratch = scratch_begin(0, 0);
  f32 font_height = FONT_LOAD_SIZE;

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
  stbtt_packedchar char_data[MAX_FONT_GLYPHS];
 
  stbtt_pack_context pack;
  stbtt_PackBegin(&pack, atlas_bitmap, atlas_width, atlas_height, atlas_width, 1, NULL);
  stbtt_PackSetOversampling(&pack, 1, 1);
  stbtt_PackFontRange(&pack, (u8*)file_data.data.str, 0, font_height, 32, MAX_FONT_GLYPHS, char_data);
  stbtt_PackEnd(&pack);
 
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, atlas_width, atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, atlas_bitmap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
  for (s32 i = 0; i < MAX_FONT_GLYPHS; i++)
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

function Vec2f32
r_get_2d_text_dimensions(String8 text, f32 pixel_height)
{
  Font* font = &g_renderer.fonts[0];
  f32 pixel_scale = pixel_height / font->height;
  f32 line_height = font->line_height * pixel_scale;

  f32 max_width = 0.0f;
  f32 current_line_width = 0.0f;
  s32 line_count = 1;

  for (u64 idx = 0; idx < text.size; ++idx)
  {
    u8 c = text.str[idx];
  
    if (c == '\n')
    {
      max_width = Max(max_width, current_line_width);
      current_line_width = 0.0f;
      line_count++;
      continue;
    }
  
    if (c < 32 || c > 126)
    {
      continue;
    }
  
    Glyph* glyph = &font->glyphs[c - 32];
    f32 advance = glyph->advance * pixel_scale;
    current_line_width += advance;
  }

  max_width = Max(max_width, current_line_width);
  f32 total_height = line_count * line_height;

  return vec2f32(max_width, total_height);
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