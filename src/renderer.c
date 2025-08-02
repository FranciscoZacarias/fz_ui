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
  g_renderer.shaders.v_screenspace_quad = renderer_compile_shader(V_Quad_Screenspace, GL_VERTEX_SHADER);
  g_renderer.shaders.v_worldspace_quad  = renderer_compile_shader(V_Quad_Worldspace, GL_VERTEX_SHADER);
  g_renderer.shaders.v_worldspace_line  = renderer_compile_shader(V_Line_Worldspace, GL_VERTEX_SHADER);
  g_renderer.shaders.f_default          = renderer_compile_shader(F_Default, GL_FRAGMENT_SHADER);
  
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
    //
    // Quads
    //
    g_renderer.worldspace.quads3d = push_array(g_renderer.arena, Quad3D, Max3DQuads);

    // Create pipeline
    glCreateProgramPipelines(1, &g_renderer.worldspace.quads3d_pipeline);
    glUseProgramStages(g_renderer.worldspace.quads3d_pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_worldspace_quad);
    glUseProgramStages(g_renderer.worldspace.quads3d_pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);
  
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

    g_renderer.worldspace.u_quad_projection_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad, "u_projection");
    g_renderer.worldspace.u_quad_view_location       = glGetUniformLocation(g_renderer.shaders.v_worldspace_quad, "u_view");

    //
    // Lines
    //
    g_renderer.worldspace.lines3d = push_array(g_renderer.arena, Line3D, Max3DLines);

    // Create pipeline
    glCreateProgramPipelines(1, &g_renderer.worldspace.lines3d_pipeline);
    glUseProgramStages(g_renderer.worldspace.lines3d_pipeline, GL_VERTEX_SHADER_BIT, g_renderer.shaders.v_worldspace_line);
    glUseProgramStages(g_renderer.worldspace.lines3d_pipeline, GL_FRAGMENT_SHADER_BIT, g_renderer.shaders.f_default);
  
    // Unit quad vertex buffer
    glCreateBuffers(1, &g_renderer.worldspace.unit_line_vbo);
    glNamedBufferStorage(g_renderer.worldspace.unit_line_vbo, sizeof(unit_3dquad), unit_3dquad, 0);

    // Instance buffer for Line3D
    glCreateBuffers(1, &g_renderer.worldspace.lines_instance_vbo);
    glNamedBufferStorage(g_renderer.worldspace.lines_instance_vbo, sizeof(Line3D) * Max3DLines, NULL, GL_DYNAMIC_STORAGE_BIT);

    // VAO
    glCreateVertexArrays(1, &g_renderer.worldspace.lines_vao);

    // Binding 0: unit line vertex positions
    glVertexArrayVertexBuffer(g_renderer.worldspace.lines_vao, 0, g_renderer.worldspace.unit_line_vbo, 0, sizeof(Vec3f32));
    glEnableVertexArrayAttrib(g_renderer.worldspace.lines_vao, 0);
    glVertexArrayAttribFormat(g_renderer.worldspace.lines_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(g_renderer.worldspace.lines_vao, 0, 0);

    // Binding 1: instance buffer (Line3D)
    glVertexArrayVertexBuffer(g_renderer.worldspace.lines_vao, 1, g_renderer.worldspace.lines_instance_vbo, 0, sizeof(Line3D));

    glEnableVertexArrayAttrib(g_renderer.worldspace.lines_vao, 1); // p0
    glVertexArrayAttribFormat(g_renderer.worldspace.lines_vao, 1, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, p0));
    glVertexArrayAttribBinding(g_renderer.worldspace.lines_vao, 1, 1);
    glVertexArrayBindingDivisor(g_renderer.worldspace.lines_vao, 1, 1);

    glEnableVertexArrayAttrib(g_renderer.worldspace.lines_vao, 2); // p1
    glVertexArrayAttribFormat(g_renderer.worldspace.lines_vao, 2, 3, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, p1));
    glVertexArrayAttribBinding(g_renderer.worldspace.lines_vao, 2, 1);
    glVertexArrayBindingDivisor(g_renderer.worldspace.lines_vao, 2, 1);

    glEnableVertexArrayAttrib(g_renderer.worldspace.lines_vao, 3); // color
    glVertexArrayAttribFormat(g_renderer.worldspace.lines_vao, 3, 4, GL_FLOAT, GL_FALSE, OffsetOfMember(Line3D, color));
    glVertexArrayAttribBinding(g_renderer.worldspace.lines_vao, 3, 1);
    glVertexArrayBindingDivisor(g_renderer.worldspace.lines_vao, 3, 1);

    g_renderer.worldspace.u_line_projection_location = glGetUniformLocation(g_renderer.shaders.v_worldspace_line, "u_projection");
    g_renderer.worldspace.u_line_view_location       = glGetUniformLocation(g_renderer.shaders.v_worldspace_line, "u_view");
  }
  
  // Textures
  {
    s32 max_gpu_textures;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_gpu_textures);
    g_renderer.texture_max   = max_gpu_textures;
    g_renderer.textures      = push_array(g_renderer.arena, GLuint, g_renderer.texture_max);
    g_renderer.texture_count = 0;
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
    // Quads
    glBindProgramPipeline(g_renderer.worldspace.quads3d_pipeline);
    glBindVertexArray(g_renderer.worldspace.vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad, g_renderer.worldspace.u_quad_view_location, 1, GL_TRUE, &view.data[0][0]);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_quad, g_renderer.worldspace.u_quad_projection_location, 1, GL_TRUE, &projection.data[0][0]);

    glNamedBufferSubData(g_renderer.worldspace.instance_vbo, 0, sizeof(Quad3D) * g_renderer.worldspace.quads3d_count, g_renderer.worldspace.quads3d);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, g_renderer.worldspace.quads3d_count);

    // Lines
    glBindProgramPipeline(g_renderer.worldspace.lines3d_pipeline);
    glBindVertexArray(g_renderer.worldspace.lines_vao);

    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_line, g_renderer.worldspace.u_line_view_location, 1, GL_TRUE, (f32*)&view);
    glProgramUniformMatrix4fv(g_renderer.shaders.v_worldspace_line, g_renderer.worldspace.u_line_projection_location, 1, GL_TRUE, (f32*)&projection);

    glNamedBufferSubData(g_renderer.worldspace.lines_instance_vbo, 0, sizeof(Quad3D) * g_renderer.worldspace.lines3d_count, g_renderer.worldspace.lines3d);
    glDrawArraysInstanced(GL_LINES, 0, 2, g_renderer.worldspace.lines3d_count);
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
renderer_load_texture(String8 path)
{
  Scratch scratch = scratch_begin(0, 0);
  u32 result = 0;

  if (g_renderer.texture_count >= g_renderer.texture_max)
  {
    emit_error(S("Texture limit reached\n"));
    return result;
  }

  s32 width, height, channels;
  u8 *data = stbi_load(path.str, &width, &height, &channels, 4); // force 4 channels
  if (!data)
  {
    emit_error(Sf(scratch.arena, "Failed to load texture: %s\n", path.str));
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
  result = texture;
  g_renderer.texture_count += 1;
  
  scratch_end(&scratch);

  return result;
}

#if 0
function u32
renderer_load_font(String8 path, f32 font_height) 
{
  Scratch scratch = scratch_begin(0, 0);
  u32 result = 0;

  if (g_renderer.texture_count >= g_renderer.texture_max) return 0;

  File_Data file_data = file_load(scratch.arena, path);
  if (!file_data.data.str || file_data.data.size == 0) return 0;

  stbtt_fontinfo font_info;
  if (!stbtt_InitFont(&font_info, (u8*)file_data.data.str, 0)) return 0;

  s32 atlas_width = 512, atlas_height = 512;
  u8* atlas_bitmap = push_array(scratch.arena, u8, atlas_width * atlas_height);

  stbtt_packedchar char_data[95];
  stbtt_pack_context pack;
  stbtt_PackBegin(&pack, atlas_bitmap, atlas_width, atlas_height, atlas_width, 1, NULL);
  stbtt_PackSetOversampling(&pack, 1, 1);
  stbtt_PackFontRange(&pack, (u8*)file_data.data.str, 0, font_height, 32, 95, char_data);
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

  for (s32 i = 0; i < 95; i++) {
    Glyph* glyph = &g_renderer.font.glyphs[i];
    stbtt_packedchar* ch = &char_data[i];

    glyph->uv_min  = vec2f32((f32)ch->x0 / atlas_width, (f32)ch->y0 / atlas_height);
    glyph->uv_max  = vec2f32((f32)ch->x1 / atlas_width, (f32)ch->y1 / atlas_height);
    glyph->size    = vec2f32(ch->x1 - ch->x0, ch->y1 - ch->y0);
    glyph->offset  = vec2f32(ch->xoff, ch->yoff);
    glyph->advance = ch->xadvance;

    f32 y_top    = ch->yoff;
    f32 y_bottom = ch->yoff + (ch->y1 - ch->y0);

    if (y_top < min_y) min_y = y_top;
    if (y_bottom > max_height) max_height = y_bottom;
  }

  scratch_end(&scratch);

  g_renderer.font.line_height = max_height - min_y;
  g_renderer.font.height      = font_height;
  g_renderer.font.texture_id  = result;

  return result;
}
#endif

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