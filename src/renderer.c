function void
renderer_init()
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

  g_renderer.shaders.v_screenspace_quad         = renderer_compile_shader(V_SS_Quad_Path,         GL_VERTEX_SHADER);
  g_renderer.shaders.v_worldspace_quad          = renderer_compile_shader(V_WS_Quad_Path,          GL_VERTEX_SHADER);
  g_renderer.shaders.v_worldspace_quad_texture  = renderer_compile_shader(V_WS_Quad_Texture_Path,  GL_VERTEX_SHADER);
  g_renderer.shaders.v_worldspace_line          = renderer_compile_shader(V_WS_Line_Path,          GL_VERTEX_SHADER);

  g_renderer.shaders.f_default                  = renderer_compile_shader(F_Default_Path, GL_FRAGMENT_SHADER);
  g_renderer.shaders.f_texture                  = renderer_compile_shader(F_Texture_Path, GL_FRAGMENT_SHADER);
  
  // Set texture sampler
  GLint sampler_locations[32];
  for (u32 idx = 0; idx < 32; idx++)
  {
    sampler_locations[idx] = idx;
  }
  glProgramUniform1iv(g_renderer.shaders.f_texture, glGetUniformLocation(g_renderer.shaders.f_texture, "u_textures"), 32, sampler_locations);

  // Screenspace
  {
    //
    // Quads
    //
    g_renderer.ss_quad = renderer_new_instanced_target(g_renderer.arena, IT_Kind_Screenspace_quad, Thousand(1));

    // Unit geometry buffer
    glCreateBuffers(1, &g_renderer.ss_quad->unit_vbo);
    glNamedBufferStorage(g_renderer.ss_quad->unit_vbo, sizeof(unit_2dquad), unit_2dquad, 0);
    
    // Instance data buffer
    glCreateBuffers(1, &g_renderer.ss_quad->instance_vbo);
    glNamedBufferStorage(g_renderer.ss_quad->instance_vbo, sizeof(Quad2D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
    // VAO
    glCreateVertexArrays(1, &g_renderer.ss_quad->vao);
    
    // Unit geometry binding (binding 0)
    glVertexArrayVertexBuffer(g_renderer.ss_quad->vao, 0, g_renderer.ss_quad->unit_vbo, 0, sizeof(Vec2f32));
    
    // Instance data binding (binding 1)
    glVertexArrayVertexBuffer(g_renderer.ss_quad->vao, 1, g_renderer.ss_quad->instance_vbo, 0, sizeof(Quad2D));

    // Pipeline
    glCreateProgramPipelines(1, &g_renderer.ss_quad->pipeline);
    glUseProgramStages(g_renderer.ss_quad->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_screenspace_quad);
    glUseProgramStages(g_renderer.ss_quad->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);

    // Unit quad positions (per-vertex)
    glEnableVertexArrayAttrib(g_renderer.ss_quad->vao, 0); // Unit
    glVertexArrayAttribFormat(g_renderer.ss_quad->vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_renderer.ss_quad->vao, 0, 0);

    // Instance data (per-instance)
    glEnableVertexArrayAttrib(g_renderer.ss_quad->vao, 1); // Position
    glVertexArrayAttribFormat(g_renderer.ss_quad->vao, 1, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, position));
    glVertexArrayAttribBinding(g_renderer.ss_quad->vao, 1, 1);
    glVertexArrayBindingDivisor(g_renderer.ss_quad->vao, 1, 1);

    glEnableVertexArrayAttrib(g_renderer.ss_quad->vao, 2); // Scale
    glVertexArrayAttribFormat(g_renderer.ss_quad->vao, 2, 2, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, scale));
    glVertexArrayAttribBinding(g_renderer.ss_quad->vao, 2, 1);
    glVertexArrayBindingDivisor(g_renderer.ss_quad->vao, 2, 1);

    glEnableVertexArrayAttrib(g_renderer.ss_quad->vao, 3); // Color
    glVertexArrayAttribFormat(g_renderer.ss_quad->vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad2D, color));
    glVertexArrayAttribBinding(g_renderer.ss_quad->vao, 3, 1);
    glVertexArrayBindingDivisor(g_renderer.ss_quad->vao, 3, 1);

    g_renderer.ss_quad->u_screen_size_location = glGetUniformLocation(g_renderer.shaders.v_screenspace_quad, "u_screen_size");

  }

  // Worldspace
  {
    //
    // Quads
    //
    g_renderer.ws_quad = renderer_new_instanced_target(g_renderer.arena, IT_Kind_Worldspace_quad, Thousand(1));

    // Unit geometry buffer
    glCreateBuffers(1, &g_renderer.ws_quad->unit_vbo);
    glNamedBufferStorage(g_renderer.ws_quad->unit_vbo, sizeof(unit_3dquad), unit_3dquad, 0);
    
    // Instance data buffer
    glCreateBuffers(1, &g_renderer.ws_quad->instance_vbo);
    glNamedBufferStorage(g_renderer.ws_quad->instance_vbo, sizeof(Quad3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
    // VAO
    glCreateVertexArrays(1, &g_renderer.ws_quad->vao);
    
    // Unit geometry binding (binding 0)
    glVertexArrayVertexBuffer(g_renderer.ws_quad->vao, 0, g_renderer.ws_quad->unit_vbo, 0, sizeof(Vec3f32));
    
    // Instance data binding (binding 1)
    glVertexArrayVertexBuffer(g_renderer.ws_quad->vao, 1, g_renderer.ws_quad->instance_vbo, 0, sizeof(Quad3D));

    // Pipeline
    glCreateProgramPipelines(1, &g_renderer.ws_quad->pipeline);
    glUseProgramStages(g_renderer.ws_quad->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_worldspace_quad);
    glUseProgramStages(g_renderer.ws_quad->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);

    // Unit quad positions (per-vertex)
    glEnableVertexArrayAttrib(g_renderer.ws_quad->vao, 0); // Unit
    glVertexArrayAttribFormat(g_renderer.ws_quad->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_renderer.ws_quad->vao, 0, 0);

    // Instance data (per-instance)
    glEnableVertexArrayAttrib(g_renderer.ws_quad->vao, 1); // Position
    glVertexArrayAttribFormat(g_renderer.ws_quad->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad3D, position));
    glVertexArrayAttribBinding(g_renderer.ws_quad->vao, 1, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad->vao, 1, 1);

    glEnableVertexArrayAttrib(g_renderer.ws_quad->vao, 2); // Scale
    glVertexArrayAttribFormat(g_renderer.ws_quad->vao, 2, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad3D, scale));
    glVertexArrayAttribBinding(g_renderer.ws_quad->vao, 2, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad->vao, 2, 1);

    glEnableVertexArrayAttrib(g_renderer.ws_quad->vao, 3); // Color
    glVertexArrayAttribFormat(g_renderer.ws_quad->vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Quad3D, color));
    glVertexArrayAttribBinding(g_renderer.ws_quad->vao, 3, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad->vao, 3, 1);

    g_renderer.ws_quad->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad, "u_projection");
    g_renderer.ws_quad->u_view_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad, "u_view");

    //
    // Textured Quads
    //
    g_renderer.ws_quad_texture = renderer_new_instanced_target(g_renderer.arena, IT_Kind_Worldspace_quad_texture, Thousand(1));

    // Unit geometry buffer
    glCreateBuffers(1, &g_renderer.ws_quad_texture->unit_vbo);
    glNamedBufferStorage(g_renderer.ws_quad_texture->unit_vbo, sizeof(unit_3dquad), unit_3dquad, 0);
    
    // Instance data buffer
    glCreateBuffers(1, &g_renderer.ws_quad_texture->instance_vbo);
    glNamedBufferStorage(g_renderer.ws_quad_texture->instance_vbo, sizeof(TexturedQuad3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
    // VAO
    glCreateVertexArrays(1, &g_renderer.ws_quad_texture->vao);
    
    // Unit geometry binding (binding 0)
    glVertexArrayVertexBuffer(g_renderer.ws_quad_texture->vao, 0, g_renderer.ws_quad_texture->unit_vbo, 0, sizeof(Vec3f32));
    
    // Instance data binding (binding 1)
    glVertexArrayVertexBuffer(g_renderer.ws_quad_texture->vao, 1, g_renderer.ws_quad_texture->instance_vbo, 0, sizeof(TexturedQuad3D));

    // Pipeline
    glCreateProgramPipelines(1, &g_renderer.ws_quad_texture->pipeline);
    glUseProgramStages(g_renderer.ws_quad_texture->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_worldspace_quad_texture);
    glUseProgramStages(g_renderer.ws_quad_texture->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_texture);

    // Vertex attributes
    glEnableVertexArrayAttrib(g_renderer.ws_quad_texture->vao, 0);
    glVertexArrayAttribFormat(g_renderer.ws_quad_texture->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_renderer.ws_quad_texture->vao, 0, 0);

    glEnableVertexArrayAttrib(g_renderer.ws_quad_texture->vao, 1);
    glVertexArrayAttribFormat(g_renderer.ws_quad_texture->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(TexturedQuad3D, position));
    glVertexArrayAttribBinding(g_renderer.ws_quad_texture->vao, 1, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad_texture->vao, 1, 1);

    glEnableVertexArrayAttrib(g_renderer.ws_quad_texture->vao, 2);
    glVertexArrayAttribFormat(g_renderer.ws_quad_texture->vao, 2, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(TexturedQuad3D, scale));
    glVertexArrayAttribBinding(g_renderer.ws_quad_texture->vao, 2, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad_texture->vao, 2, 1);

    glEnableVertexArrayAttrib(g_renderer.ws_quad_texture->vao, 3);
    glVertexArrayAttribFormat(g_renderer.ws_quad_texture->vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(TexturedQuad3D, color));
    glVertexArrayAttribBinding(g_renderer.ws_quad_texture->vao, 3, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad_texture->vao, 3, 1);

    glEnableVertexArrayAttrib(g_renderer.ws_quad_texture->vao, 4);
    glVertexArrayAttribIFormat(g_renderer.ws_quad_texture->vao, 4, 1, GL_UNSIGNED_INT, OffsetOfMember(TexturedQuad3D, texture_id));
    glVertexArrayAttribBinding(g_renderer.ws_quad_texture->vao, 4, 1);
    glVertexArrayBindingDivisor(g_renderer.ws_quad_texture->vao, 4, 1);

    g_renderer.ws_quad_texture->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad_texture, "u_projection");
    g_renderer.ws_quad_texture->u_view_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad_texture, "u_view");

    //
    // Lines
    //
    g_renderer.ws_line = renderer_new_instanced_target(g_renderer.arena, IT_Kind_Worldspace_line, Thousand(1));

    // Instance data buffer
    glCreateBuffers(1, &g_renderer.ws_line->instance_vbo);
    glNamedBufferStorage(g_renderer.ws_line->instance_vbo, sizeof(Line3D) * Thousand(1), NULL, GL_DYNAMIC_STORAGE_BIT);
    
    // VAO
    glCreateVertexArrays(1, &g_renderer.ws_line->vao);
    
    // Instance data (per-instance)
    glVertexArrayVertexBuffer(g_renderer.ws_line->vao, 1, g_renderer.ws_line->instance_vbo, 0, sizeof(Line3D));

    // Pipeline
    glCreateProgramPipelines(1, &g_renderer.ws_line->pipeline);
    glUseProgramStages(g_renderer.ws_line->pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_worldspace_line);
    glUseProgramStages(g_renderer.ws_line->pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);


    // Instance data (per-instance) - use binding 1 and divisor 1
    glEnableVertexArrayAttrib(g_renderer.ws_line->vao, 0); // p0
    glVertexArrayAttribFormat(g_renderer.ws_line->vao, 0, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, p0));
    glVertexArrayAttribBinding(g_renderer.ws_line->vao, 0, 1);  // binding 1
    glVertexArrayBindingDivisor(g_renderer.ws_line->vao, 0, 1); // divisor 1

    glEnableVertexArrayAttrib(g_renderer.ws_line->vao, 1); // p1
    glVertexArrayAttribFormat(g_renderer.ws_line->vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, p1));
    glVertexArrayAttribBinding(g_renderer.ws_line->vao, 1, 1);  // binding 1
    glVertexArrayBindingDivisor(g_renderer.ws_line->vao, 1, 1); // divisor 1

    glEnableVertexArrayAttrib(g_renderer.ws_line->vao, 2); // color
    glVertexArrayAttribFormat(g_renderer.ws_line->vao, 2, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, color));
    glVertexArrayAttribBinding(g_renderer.ws_line->vao, 2, 1);  // binding 1
    glVertexArrayBindingDivisor(g_renderer.ws_line->vao, 2, 1); // divisor 1


    g_renderer.ws_line->u_projection_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_line, "u_projection");
    g_renderer.ws_line->u_view_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_line, "u_view");
  }

  // Textures
  {
    s32 max_gpu_textures;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_gpu_textures);
    g_renderer.texture_max   = max_gpu_textures;
    g_renderer.textures      = push_array(g_renderer.arena, GLuint, g_renderer.texture_max);
    g_renderer.texture_count = 0;
  }

  // Font
  {
    g_renderer.fonts_max   = 4;
    g_renderer.fonts       = push_array(g_renderer.arena, Font, g_renderer.fonts_max);
    g_renderer.fonts_count = 0;
    renderer_load_font(Font_ProggyClean, 32.0f);
  }

  scratch_end(&scratch);
}
function Instanced_Target*
renderer_new_instanced_target(Arena* arena, Instanced_Target_Kind kind, u32 max_instances)
{
  Instanced_Target* result = push_array(arena, Instanced_Target, 1);

  u32 stride = 0;
  switch (kind)
  {
    case IT_Kind_Screenspace_quad:
    {
      stride = sizeof(Quad2D);
    } break;
    case IT_Kind_Worldspace_quad:
    {
      stride = sizeof(Quad3D);
    } break;
    case IT_Kind_Worldspace_quad_texture:
    {
      stride = sizeof(TexturedQuad3D);
    } break;
    case IT_Kind_Worldspace_line:
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
renderer_begin_frame()
{
  glClearColor(0.5f, 0.96f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  g_renderer.ss_quad->count         = 0;
  g_renderer.ws_quad->count         = 0;
  g_renderer.ws_quad_texture->count = 0;
  g_renderer.ws_line->count         = 0;
}

function void
renderer_end_frame(Mat4f32 view, Mat4f32 projection)
{
  ///////////////////////////////////////////////////////
  // @Section: Worldspace
  if (g_renderer.ws_quad->count > 0)
  {
    // Quads
    glBindProgramPipeline(g_renderer.ws_quad->pipeline);
    glBindVertexArray(g_renderer.ws_quad->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad, g_renderer.ws_quad->u_view_location, 1, GL_TRUE, &view.m0);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad, g_renderer.ws_quad->u_projection_location, 1, GL_TRUE, &projection.m0);

    glNamedBufferSubData(g_renderer.ws_quad->instance_vbo, 0, sizeof(Quad3D) * g_renderer.ws_quad->count, g_renderer.ws_quad->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.ws_quad->count);

  }

  if (g_renderer.ws_quad_texture->count > 0)
  {
    glBindProgramPipeline(g_renderer.ws_quad_texture->pipeline);
    glBindVertexArray(g_renderer.ws_quad_texture->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad_texture, g_renderer.ws_quad_texture->u_view_location, 1, GL_TRUE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad_texture, g_renderer.ws_quad_texture->u_projection_location, 1, GL_TRUE, &projection.data[0][0]);

    // Bind textures
    for (u32 idx = 0; idx < g_renderer.texture_count; idx += 1)
    {
      glBindTextureUnit(idx, g_renderer.textures[idx]);
    }

    glNamedBufferSubData(g_renderer.ws_quad_texture->instance_vbo, 0, sizeof(TexturedQuad3D) * g_renderer.ws_quad_texture->count, g_renderer.ws_quad_texture->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.ws_quad_texture->count);
  }

  if (g_renderer.ws_line->count > 0)
  {
    // Lines
    glBindProgramPipeline(g_renderer.ws_line->pipeline);
    glBindVertexArray(g_renderer.ws_line->vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_line, g_renderer.ws_line->u_view_location, 1, GL_TRUE, (f32*)&view);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_line, g_renderer.ws_line->u_projection_location, 1, GL_TRUE, (f32*)&projection);
    
    glNamedBufferSubData(g_renderer.ws_line->instance_vbo, 0, sizeof(Line3D) * g_renderer.ws_line->count, g_renderer.ws_line->data);
    glDrawArraysInstanced(GL_LINES, 0, 2, g_renderer.ws_line->count);
  }

  ///////////////////////////////////////////////////////
  // @Section: Screenspace
  if (g_renderer.ss_quad->count > 0)
  {
    glBindProgramPipeline(g_renderer.ss_quad->pipeline);
    glBindVertexArray(g_renderer.ss_quad->vao);

    glProgramUniform2f(g_renderer.shaders.v_screenspace_quad, g_renderer.ss_quad->u_screen_size_location, (f32)g_os_window->dimensions.x, (f32)g_os_window->dimensions.y);

    glNamedBufferSubData(g_renderer.ss_quad->instance_vbo, 0, sizeof(Quad2D) * g_renderer.ss_quad->count, g_renderer.ss_quad->data);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.ss_quad->count);
  }

  os_swap_buffers();
}

function void
renderer_draw_2dquad(Vec2f32 position, Vec2f32 scale, Vec4f32 color)
{
  if (g_renderer.ss_quad->count >= g_renderer.ss_quad->max)
  {
    emit_fatal(S("Tried to render more quads than g_renderer.ss_quad->max"));
    return;
  }
  Quad2D* data = (Quad2D*)g_renderer.ss_quad->data;
  data[g_renderer.ss_quad->count].position = position;
  data[g_renderer.ss_quad->count].scale    = scale;
  data[g_renderer.ss_quad->count].color    = color;
  g_renderer.ss_quad->count += 1;
}

function void
renderer_draw_3dquad(Vec3f32 position, Vec3f32 scale, Vec4f32 color)
{
  if (g_renderer.ws_quad->count >= g_renderer.ws_quad->max)
  {
    emit_fatal(S("Tried to render more quads than g_renderer.ws_quad->max"));
    return;
  }
  Quad3D* data = (Quad3D*)g_renderer.ws_quad->data;
  data[g_renderer.ws_quad->count].position = position;
  data[g_renderer.ws_quad->count].scale    = scale;
  data[g_renderer.ws_quad->count].color    = color;
  g_renderer.ws_quad->count += 1;
}

function void
renderer_draw_3dquad_textured(Vec3f32 position, Vec3f32 scale, Vec4f32 color, u32 texture_id)
{
  if (g_renderer.ws_quad_texture->count >= g_renderer.ws_quad_texture->max)
  {
    emit_fatal(S("Tried to render more textured quads than g_renderer.ws_quad_texture->max"));
    return;
  }
  TexturedQuad3D* quad = &((TexturedQuad3D*)g_renderer.ws_quad_texture->data)[g_renderer.ws_quad_texture->count];
  quad->position = position;
  quad->scale = scale;
  quad->color = color;
  quad->texture_id = texture_id;
  g_renderer.ws_quad_texture->count += 1;
}

function void
renderer_draw_3dline(Vec3f32 p0, Vec3f32 p1, Vec4f32 color)
{
  if (g_renderer.ws_line->count >= g_renderer.ws_line->max)
  {
    emit_fatal(S("Tried to render more lines than g_renderer.ws_line->max"));
    return;
  }
  Line3D* data = (Line3D*)g_renderer.ws_line->data;
  data[g_renderer.ws_line->count].p0    = p0;
  data[g_renderer.ws_line->count].p1    = p1;
  data[g_renderer.ws_line->count].color = color;
  g_renderer.ws_line->count += 1;
}

function void
renderer_draw_3darrow(Vec3f32 start, Vec3f32 end, Vec4f32 color)
{
  renderer_draw_3dline(start, end, color);

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
  renderer_draw_3dline(tip, vec3f32_add(base, right),   color);
  renderer_draw_3dline(tip, vec3f32_sub(base, right),   color);
  renderer_draw_3dline(tip, vec3f32_add(base, forward), color);
  renderer_draw_3dline(tip, vec3f32_sub(base, forward), color);
}

function u32
renderer_load_font(String8 relative_path, f32 font_height) 
{
  Scratch scratch = scratch_begin(0, 0);
  u32 result = 0;

  if (g_renderer.texture_count >= g_renderer.texture_max)
  {
    emit_error(S("Error loading font. More textures than g_renderer.texture_max"));
    return 0;
  }

  String8 project_path = os_executable_path(scratch.arena);
  project_path = os_directory_pop(project_path); // Pop *.exe
  project_path = os_directory_pop(project_path); // Pop from build/

  String8 font_path = string8_concat(scratch.arena, project_path, relative_path);
  File_Data file_data = os_file_load(scratch.arena, font_path);
  if (!file_data.data.str || file_data.data.size == 0)
  {
    emit_error(Sf(scratch.arena, "Error loading font. Failed toload file: %.*s", font_path.size, font_path.str));
    return 0;
  }

  stbtt_fontinfo font_info;
  if (!stbtt_InitFont(&font_info, (u8*)file_data.data.str, 0))
  {
    emit_error(S("Error initializing font with stbtt_InitFont. "));
    return 0;
  }

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

  u32 texture_index = g_renderer.texture_count++;
  g_renderer.textures[texture_index] = texture;
  result = texture_index + 1;

  f32 max_height = 0.0f;
  f32 min_y = 0.0f;

  for (s32 i = 0; i < MaxFontGlyphs; i++)
  {
    Glyph* glyph = &g_renderer.fonts[g_renderer.fonts_count].glyphs[i];
    stbtt_packedchar* ch = &char_data[i];

    glyph->uv_min  = vec2f32((f32)ch->x0 / atlas_width, (f32)ch->y0 / atlas_height);
    glyph->uv_max  = vec2f32((f32)ch->x1 / atlas_width, (f32)ch->y1 / atlas_height);
    glyph->size    = vec2f32(ch->x1 - ch->x0, ch->y1 - ch->y0);
    glyph->offset  = vec2f32(ch->xoff, ch->yoff);
    glyph->advance = ch->xadvance;

    f32 y_top    = ch->yoff;
    f32 y_bottom = ch->yoff + (ch->y1 - ch->y0);

    if (y_top < min_y)
    {
      min_y = y_top;
    }
    if (y_bottom > max_height)
    {
      max_height = y_bottom;
    }
  }

  scratch_end(&scratch);

  g_renderer.fonts[g_renderer.fonts_count].line_height = max_height - min_y;
  g_renderer.fonts[g_renderer.fonts_count].height      = font_height;
  g_renderer.fonts[g_renderer.fonts_count].texture_id  = result;
  g_renderer.fonts_count += 1;

  return result;
}

function Texture_Info
renderer_load_texture(String8 path)
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
      emit_error(string8_from_format(scratch.arena, "Failed to create shader: %s", info_log));
    }
  }

  scratch_end(&scratch);
  return result;
}