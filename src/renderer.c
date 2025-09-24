function void
r_init()
{
  Scratch scratch = scratch_begin(0,0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
  // Renderer Context
  MemoryZeroStruct(&g_renderer);
  {
    g_renderer.arena = arena_alloc();
  
    g_renderer.shaders.v_primitive = r_compile_shader(V_PRIMITIVE_PATH, GL_VERTEX_SHADER);
    g_renderer.shaders.v_text      = r_compile_shader(V_TEXT_PATH,      GL_VERTEX_SHADER);
    g_renderer.shaders.v_line      = r_compile_shader(V_LINE_PATH,      GL_VERTEX_SHADER);

    g_renderer.shaders.f_color   = r_compile_shader(F_COLOR_PATH,   GL_FRAGMENT_SHADER);
    g_renderer.shaders.f_texture = r_compile_shader(F_TEXTURE_PATH, GL_FRAGMENT_SHADER);
    g_renderer.shaders.f_text    = r_compile_shader(F_TEXT_PATH,    GL_FRAGMENT_SHADER);
  }

  // Screenspace
  {
    // 2D Line
    {
      Render_Batch_Kind batch_kind = Render_Batch_Line;
      u32 max_instances     = 256;
      u32 vertex_shader     = g_renderer.shaders.v_line;
      u32 fragment_shader   = g_renderer.shaders.f_color;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances, vertex_shader, 2, GL_LINES);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(vertex_shader, "u_screen_size");
    
      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, vertex_shader);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, fragment_shader);

      // VAO
      glCreateVertexArrays(1, &batch->vao);
    
      // Instance data
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Line2D) * max_instances, NULL, GL_DYNAMIC_STORAGE_BIT);
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Line2D));

      // Instance data (per-instance)
      r_set_vertex_attribute_f32(batch->vao, 0, 2, 1, OffsetOfMember(Line2D, p0));
      r_set_vertex_attribute_f32(batch->vao, 1, 2, 1, OffsetOfMember(Line2D, p1));
      r_set_vertex_attribute_f32(batch->vao, 2, 4, 1, OffsetOfMember(Line2D, color));
    }

    // 2D Triangle
    {
      Render_Batch_Kind batch_kind = Render_Batch_Triangle;
      u32 max_instances     = Thousand(1);
      u32 vertex_shader     = g_renderer.shaders.v_primitive;
      u32 fragment_shader   = g_renderer.shaders.f_texture;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances, vertex_shader, 3, GL_TRIANGLES);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(vertex_shader, "u_screen_size");
    
      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, vertex_shader);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, fragment_shader);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry buffer
      // (binding 0) Unit quad positions (per-vertex)
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_triangle), unit_triangle, 0);
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));
      r_set_vertex_attribute_f32(batch->vao, 0, 2, 0, 0);

      // Instance data buffer
      // (binding 1) Instance data (per-instance)
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * batch->max, NULL, GL_DYNAMIC_STORAGE_BIT);
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));
      r_set_vertex_attribute_f32(batch->vao, 1, 2, 1, OffsetOfMember(Primitive2D, center));
      r_set_vertex_attribute_f32(batch->vao, 2, 2, 1, OffsetOfMember(Primitive2D, scale));
      r_set_vertex_attribute_f32(batch->vao, 3, 1, 1, OffsetOfMember(Primitive2D, rotation));
      r_set_vertex_attribute_f32(batch->vao, 4, 2, 1, OffsetOfMember(Primitive2D, uv_min));
      r_set_vertex_attribute_f32(batch->vao, 5, 2, 1, OffsetOfMember(Primitive2D, uv_max));
      r_set_vertex_attribute_f32(batch->vao, 6, 4, 1, OffsetOfMember(Primitive2D, color));
      r_set_vertex_attribute_u32(batch->vao, 7, 1, 1, OffsetOfMember(Primitive2D, texture_id));
      r_set_vertex_attribute_f32(batch->vao, 8, 1, 1, OffsetOfMember(Primitive2D, depth));
    }

    // 2D Triangle Texture
    {
      Render_Batch_Kind batch_kind = Render_Batch_Triangle_Texture;
      u32 max_instances     = Thousand(1);
      u32 vertex_shader     = g_renderer.shaders.v_primitive;
      u32 fragment_shader   = g_renderer.shaders.f_texture;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances, vertex_shader, 3, GL_TRIANGLES);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(vertex_shader, "u_screen_size");
    
      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, vertex_shader);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, fragment_shader);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry buffer
      // (binding 0) Unit quad positions (per-vertex)
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_triangle), unit_triangle, 0);
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));
      r_set_vertex_attribute_f32(batch->vao, 0, 2, 0, 0);

      // Instance data buffer
      // (binding 1) Instance data (per-instance)
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * batch->max, NULL, GL_DYNAMIC_STORAGE_BIT);
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));
      r_set_vertex_attribute_f32(batch->vao, 1, 2, 1, OffsetOfMember(Primitive2D, center));
      r_set_vertex_attribute_f32(batch->vao, 2, 2, 1, OffsetOfMember(Primitive2D, scale));
      r_set_vertex_attribute_f32(batch->vao, 3, 1, 1, OffsetOfMember(Primitive2D, rotation));
      r_set_vertex_attribute_f32(batch->vao, 4, 2, 1, OffsetOfMember(Primitive2D, uv_min));
      r_set_vertex_attribute_f32(batch->vao, 5, 2, 1, OffsetOfMember(Primitive2D, uv_max));
      r_set_vertex_attribute_f32(batch->vao, 6, 4, 1, OffsetOfMember(Primitive2D, color));
      r_set_vertex_attribute_u32(batch->vao, 7, 1, 1, OffsetOfMember(Primitive2D, texture_id));
      r_set_vertex_attribute_f32(batch->vao, 8, 1, 1, OffsetOfMember(Primitive2D, depth));
    }

    // 2D Quad
    {
      Render_Batch_Kind batch_kind = Render_Batch_Quad;
      u32 max_instances     = Thousand(1);
      u32 vertex_shader     = g_renderer.shaders.v_primitive;
      u32 fragment_shader   = g_renderer.shaders.f_texture;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances, vertex_shader, 6, GL_TRIANGLES);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(vertex_shader, "u_screen_size");
    
      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, vertex_shader);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, fragment_shader);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry buffer
      // (binding 0) Unit quad positions (per-vertex)
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_quad), unit_quad, 0);
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));
      r_set_vertex_attribute_f32(batch->vao, 0, 2, 0, 0);

      // Instance data buffer
      // (binding 1) Instance data (per-instance)
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * batch->max, NULL, GL_DYNAMIC_STORAGE_BIT);
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));
      r_set_vertex_attribute_f32(batch->vao, 1, 2, 1, OffsetOfMember(Primitive2D, center));
      r_set_vertex_attribute_f32(batch->vao, 2, 2, 1, OffsetOfMember(Primitive2D, scale));
      r_set_vertex_attribute_f32(batch->vao, 3, 1, 1, OffsetOfMember(Primitive2D, rotation));
      r_set_vertex_attribute_f32(batch->vao, 4, 2, 1, OffsetOfMember(Primitive2D, uv_min));
      r_set_vertex_attribute_f32(batch->vao, 5, 2, 1, OffsetOfMember(Primitive2D, uv_max));
      r_set_vertex_attribute_f32(batch->vao, 6, 4, 1, OffsetOfMember(Primitive2D, color));
      r_set_vertex_attribute_u32(batch->vao, 7, 1, 1, OffsetOfMember(Primitive2D, texture_id));
      r_set_vertex_attribute_f32(batch->vao, 8, 1, 1, OffsetOfMember(Primitive2D, depth));
    }

    // 2D Quad Texture
    {
      Render_Batch_Kind batch_kind = Render_Batch_Quad_Texture;
      u32 max_instances     = Thousand(1);
      u32 vertex_shader     = g_renderer.shaders.v_primitive;
      u32 fragment_shader   = g_renderer.shaders.f_texture;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances, vertex_shader, 6, GL_TRIANGLES);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(vertex_shader, "u_screen_size");
    
      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, vertex_shader);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, fragment_shader);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry buffer
      // (binding 0) Unit quad positions (per-vertex)
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_quad), unit_quad, 0);
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));
      r_set_vertex_attribute_f32(batch->vao, 0, 2, 0, 0);

      // Instance data buffer
      // (binding 1) Instance data (per-instance)
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * batch->max, NULL, GL_DYNAMIC_STORAGE_BIT);
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));
      r_set_vertex_attribute_f32(batch->vao, 1, 2, 1, OffsetOfMember(Primitive2D, center));
      r_set_vertex_attribute_f32(batch->vao, 2, 2, 1, OffsetOfMember(Primitive2D, scale));
      r_set_vertex_attribute_f32(batch->vao, 3, 1, 1, OffsetOfMember(Primitive2D, rotation));
      r_set_vertex_attribute_f32(batch->vao, 4, 2, 1, OffsetOfMember(Primitive2D, uv_min));
      r_set_vertex_attribute_f32(batch->vao, 5, 2, 1, OffsetOfMember(Primitive2D, uv_max));
      r_set_vertex_attribute_f32(batch->vao, 6, 4, 1, OffsetOfMember(Primitive2D, color));
      r_set_vertex_attribute_u32(batch->vao, 7, 1, 1, OffsetOfMember(Primitive2D, texture_id));
      r_set_vertex_attribute_f32(batch->vao, 8, 1, 1, OffsetOfMember(Primitive2D, depth));
    }

    // 2D Text
    {
      Render_Batch_Kind batch_kind = Render_Batch_Text;
      u32 max_instances     = Thousand(1);
      u32 vertex_shader     = g_renderer.shaders.v_text;
      u32 fragment_shader   = g_renderer.shaders.f_text;

      Render_Batch* batch = r_new_render_batch(g_renderer.arena, batch_kind, max_instances, vertex_shader, 6, GL_TRIANGLES);
      g_renderer.batches[batch_kind] = batch;

      // Uniforms
      batch->u_screen_size_location = glGetUniformLocation(vertex_shader, "u_screen_size");
    
      // Pipeline
      glCreateProgramPipelines(1, &batch->pipeline);
      glUseProgramStages(batch->pipeline, GL_VERTEX_SHADER_BIT, vertex_shader);
      glUseProgramStages(batch->pipeline, GL_FRAGMENT_SHADER_BIT, fragment_shader);

      // VAO
      glCreateVertexArrays(1, &batch->vao);

      // Unit geometry buffer
      // (binding 0) Unit quad positions (per-vertex)
      glCreateBuffers(1, &batch->unit_vbo);
      glNamedBufferStorage(batch->unit_vbo, sizeof(unit_quad), unit_quad, 0);
      glVertexArrayVertexBuffer(batch->vao, 0, batch->unit_vbo, 0, sizeof(Vec2f32));
      r_set_vertex_attribute_f32(batch->vao, 0, 2, 0, 0);

      // Instance data buffer
      // (binding 1) Instance data (per-instance)
      glCreateBuffers(1, &batch->instance_vbo);
      glNamedBufferStorage(batch->instance_vbo, sizeof(Primitive2D) * batch->max, NULL, GL_DYNAMIC_STORAGE_BIT);
      glVertexArrayVertexBuffer(batch->vao, 1, batch->instance_vbo, 0, sizeof(Primitive2D));
      r_set_vertex_attribute_f32(batch->vao, 1, 2, 1, OffsetOfMember(Primitive2D, center));
      r_set_vertex_attribute_f32(batch->vao, 2, 2, 1, OffsetOfMember(Primitive2D, scale));
      r_set_vertex_attribute_f32(batch->vao, 3, 1, 1, OffsetOfMember(Primitive2D, rotation));
      r_set_vertex_attribute_f32(batch->vao, 4, 2, 1, OffsetOfMember(Primitive2D, uv_min));
      r_set_vertex_attribute_f32(batch->vao, 5, 2, 1, OffsetOfMember(Primitive2D, uv_max));
      r_set_vertex_attribute_f32(batch->vao, 6, 4, 1, OffsetOfMember(Primitive2D, color));
      r_set_vertex_attribute_u32(batch->vao, 7, 1, 1, OffsetOfMember(Primitive2D, texture_id));
      r_set_vertex_attribute_f32(batch->vao, 8, 1, 1, OffsetOfMember(Primitive2D, depth));
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
    for (u32 idx = 0; idx < g_renderer.texture_max; idx += 1)
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
r_new_render_batch(Arena* arena, Render_Batch_Kind kind, u32 max_instances, u32 v_shader, u32 vertex_count, u32 mode)
{
  Render_Batch* result = push_array(arena, Render_Batch, 1);

  u32 stride = 0;
  switch (kind)
  {
    case Render_Batch_Triangle:
    case Render_Batch_Triangle_Texture:
    case Render_Batch_Quad:
    case Render_Batch_Quad_Texture:
    case Render_Batch_Text:
    {
      stride = sizeof(Primitive2D);
    } break;
    case Render_Batch_Line:
    {
      stride = sizeof(Line2D);
    } break;
    default:
    {
      emit_fatal(S("Unhandled Render_Batch_Kind"));
      return result;
    } break;
  }

  result->kind   = kind;
  result->data   = arena_push(arena, stride * max_instances);
  result->stride = stride;
  result->max    = max_instances;
  result->v_shader = v_shader;
  result->mode     = mode;
  result->vertex_count = vertex_count;
  result->depth        = result->kind * 0.1;
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

  // Opaque batches
  /* Sort front to back so that the fragment shader only runs once per pixel */
  glDepthMask(GL_TRUE);
  for (s32 i = 0; i < Render_Batch_Count; i++)
  {
    Render_Batch* batch = g_renderer.batches[i];
    r_render_batch(batch, view, projection);
  }

  os_swap_buffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  for (u32 idx = 0; idx < Render_Batch_Count; idx += 1)
  {
    g_renderer.batches[idx]->count = 0;
  }
}

function void
r_render_batch(Render_Batch* batch, Mat4f32 view, Mat4f32 projection)
{
  if (batch->count <= 0)
  {
    return;
  }

  glBindProgramPipeline(batch->pipeline);
  glBindVertexArray(batch->vao);
  
  switch(batch->kind)
  {
    case Render_Batch_Triangle:
    case Render_Batch_Triangle_Texture:
    case Render_Batch_Quad:
    case Render_Batch_Quad_Texture:
    case Render_Batch_Line:
    case Render_Batch_Text:
    {
      glProgramUniform2f(batch->v_shader, batch->u_screen_size_location, (f32)g_os_window.dimensions.x, (f32)g_os_window.dimensions.y);
    } break;
    default:
    {
      emit_fatal(S("Unhandled Render_Batch_Kind"));
    } break;
  }

  glNamedBufferSubData(batch->instance_vbo, 0, batch->stride * batch->count, batch->data);
  glDrawArraysInstanced(batch->mode, 0, batch->vertex_count, batch->count);
}


function void
r_draw_primitive(Render_Batch* render_batch, Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Vec2f32 uv_min, Vec2f32 uv_max, Color color, u32 texture_id)
{
  if (render_batch->count >= render_batch->max)
  {
    Scratch scratch = scratch_begin(0,0);
    emit_fatal(Sf(scratch.arena, "Tried to render more instances than render_batch->Max (%d)", render_batch->max));
    scratch_end(&scratch);
    return;
  }
  
  Vec2f32 center = vec2f32(top_left.x+(scale.x/2), top_left.y+(scale.y/2));
  Primitive2D* data = (Primitive2D*)render_batch->data;
  data[render_batch->count].center     = r_vec2f32_flip_y(center);
  data[render_batch->count].scale      = scale;
  data[render_batch->count].rotation   = rotation_rads;
  data[render_batch->count].uv_min     = uv_min;
  data[render_batch->count].uv_max     = uv_max;
  data[render_batch->count].color      = color;
  data[render_batch->count].texture_id = texture_id;
  data[render_batch->count].depth      = render_batch->depth;
  render_batch->count += 1;
}

function void
r_draw_line(Vec2f32 p0, Vec2f32 p1, Color color)
{
  if (g_renderer.batches[Render_Batch_Line]->count >= g_renderer.batches[Render_Batch_Line]->max)
  {
    emit_fatal(S("Tried to render more lines than g_renderer.batches[Render_Batch_Line]->Max"));
    return;
  }
  Line2D* data = (Line2D*)g_renderer.batches[Render_Batch_Line]->data;
  data[g_renderer.batches[Render_Batch_Line]->count].p0    = r_vec2f32_flip_y(p0);
  data[g_renderer.batches[Render_Batch_Line]->count].p1    = r_vec2f32_flip_y(p1);
  data[g_renderer.batches[Render_Batch_Line]->count].color = color;
  g_renderer.batches[Render_Batch_Line]->count += 1;
}

function void
r_draw_triangle(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Color color)
{
  r_draw_primitive(g_renderer.batches[Render_Batch_Triangle], top_left, scale, rotation_rads, vec2f32(0.0f, 0.0), vec2f32(1.0f, 1.0f), color, NO_TEXTURE);
}

function void
r_draw_triangle_texture(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Vec2f32 uv_min, Vec2f32 uv_max, Color gradient, u32 texture_index)
{
  r_draw_primitive(g_renderer.batches[Render_Batch_Triangle_Texture], top_left, scale, rotation_rads, uv_min, uv_max, gradient, texture_index);
}

function void
r_draw_quad(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Color color)
{
  r_draw_primitive(g_renderer.batches[Render_Batch_Quad], top_left, scale, rotation_rads, vec2f32(0.0f, 0.0), vec2f32(1.0f, 1.0f), color, NO_TEXTURE);
}

function void
r_draw_quad_texture(Vec2f32 top_left, Vec2f32 scale, f32 rotation_rads, Vec2f32 uv_min, Vec2f32 uv_max, Color gradient, u32 texture_index)
{
  r_draw_box(top_left, scale, BLUE(1));
  r_draw_primitive(g_renderer.batches[Render_Batch_Quad_Texture], top_left, scale, rotation_rads, uv_min, uv_max, gradient, texture_index);
}

function void
r_draw_text(Vec2f32 top_left, f32 pixel_height, Color color, String8 text)
{
  if (g_renderer.batches[Render_Batch_Text]->count + text.size >= g_renderer.batches[Render_Batch_Text]->max)
  {
    emit_fatal(S("Tried to render more textured quads than g_renderer.batches[Render_Batch_SS_quad]_texture->Max"));
    return;
  }
  
  if (text.size == 0)
  {
    return;
  }

  Font* font = &g_renderer.fonts[0]; // TODO(fz): Font should be arg
  f32 pixel_scale = pixel_height / font->height;
  f32 line_height = font->line_height * pixel_scale;
 
  // Get first character to calculate offset
  u8 first_char = text.str[0];
  Glyph* first_glyph = &font->glyphs[first_char - 32];
 
  // Adjust starting position so first glyph centers on 'position'
  Vec2f32 center = vec2f32(top_left.x + (first_glyph->advance * pixel_scale/2), top_left.y + pixel_height);
  Vec2f32 start_pos = vec2f32(
    center.x - (first_glyph->offset.x + first_glyph->size.x * 0.5f) * pixel_scale,
    center.y + (first_glyph->offset.y + first_glyph->size.y * 0.5f) * pixel_scale
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
      cursor.y += line_height;
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
      cursor.y + (glyph->offset.y + glyph->size.y * 0.5f) * pixel_scale
    );
    Vec2f32 glyph_size = vec2f32(glyph->size.x * pixel_scale, glyph->size.y * pixel_scale);
    r_draw_primitive(g_renderer.batches[Render_Batch_Text], glyph_pos, glyph_size, 0, glyph->uv_min, glyph->uv_max, color, font->texture_index);

#if 0 // Debug glyphs
    r_draw_box(glyph_pos, glyph_size, YELLOW(1));
    r_draw_point(glyph_pos, RED(1));
#endif

    f32 advance = glyph->advance * pixel_scale;
    cursor.x += advance;
    current_line_width += advance;
  }
 
  max_width = Max(max_width, current_line_width);
  f32 total_height = line_count * line_height;
}

function void
r_draw_point(Vec2f32 position, Color color)
{
  f32 len = 16.0f;
  f32 diagonal = sqrtf(len);
  r_draw_line(vec2f32(position.x-diagonal,position.y-diagonal), vec2f32(position.x+diagonal,position.y+diagonal), color);
  r_draw_line(vec2f32(position.x-diagonal,position.y+diagonal), vec2f32(position.x+diagonal,position.y-diagonal), color);
}

function void
r_draw_box(Vec2f32 top_left, Vec2f32 scale, Color color)
{
  Vec2f32 bot_right = vec2f32(top_left.x + scale.x, top_left.y + scale.y);
  r_draw_line(top_left, vec2f32(bot_right.x, top_left.y), color);
  r_draw_line(vec2f32(bot_right.x, top_left.y), bot_right, color);
  r_draw_line(bot_right, vec2f32(top_left.x, bot_right.y), color);
  r_draw_line(top_left, vec2f32(top_left.x, bot_right.y), color);
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
    emit_error(Sf(scratch.arena, "Error loading font. Failed to load file:" S_FMT, font_path.size, font_path.str));
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
r_clear_color(Color color)
{
  glClearColor(color.x, color.y, color.z, color.w);
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

// TODO(fz): We can pre compute max text height and then just compute width and height based on line breaks
function Vec2f32
r_text_dimensions(String8 text, f32 pixel_height)
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
r_set_wireframe(b32 set)
{
  glPolygonMode(GL_FRONT_AND_BACK, set ? GL_LINE : GL_FILL);
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
    emit_error(string8_from_format(scratch.arena, "Failed to create shader at:" S_FMT, relative_path.size, relative_path.str));
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

function Vec2f32
r_vec2f32_flip_y(Vec2f32 v)
{
  Vec2f32 flipped = v;
  flipped.y = g_os_window.dimensions.y - v.y;
  return flipped;
}

function void
r_set_vertex_attribute_f32(u32 vao, u32 index, u32 size, u32 divisor, u32 offset)
{
  glEnableVertexArrayAttrib(vao, index);
  glVertexArrayAttribFormat(vao, index, size, GL_FLOAT, GL_FALSE, offset);
  glVertexArrayAttribBinding(vao, index, divisor);
  glVertexArrayBindingDivisor(vao, index, divisor);
}

function void
r_set_vertex_attribute_u32(u32 vao, u32 index, u32 size, u32 divisor, u32 offset)
{
  glEnableVertexArrayAttrib(vao, index);
  glVertexArrayAttribIFormat(vao, index, size, GL_UNSIGNED_INT, offset);
  glVertexArrayAttribBinding(vao, index, divisor);
  glVertexArrayBindingDivisor(vao, index, divisor);
}