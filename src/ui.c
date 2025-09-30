
// Core functions
function void ui_init()
{
  AssertNoReentry();

  ui_color_scheme_dark = (UI_Color_Scheme)
  {
    .title_bar = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.25f, 0.25f, 0.25f, 1.0f),
      .background_color        = color(0.1f, 0.1f, 0.1f, 1.0f),
      .background_hover_color  = color(0.1f, 0.1f, 0.1f, 1.0f),
      .background_active_color = color(0.10f, 0.10f, 0.10f, 1.0f),
      .text_color        = color(0.95f, 0.95f, 0.95f, 1.0f),
      .text_hover_color  = color(1.0f, 1.0f, 1.0f, 1.0f),
      .text_active_color = color(0.90f, 0.90f, 0.90f, 1.0)
    },
    .window = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.25f, 0.25f, 0.25f, 1.0f),
      .background_color        = color(0.2f, 0.2f, 0.2f, 1.0f),
      .background_hover_color  = color(0.12f, 0.12f, 0.12f, 1.0f),
      .background_active_color = color(0.12f, 0.12f, 0.12f, 1.0f),
      .text_color        = color(0.95f, 0.95f, 0.95f, 1.0f),
      .text_hover_color  = color(0.95f, 0.95f, 0.95f, 1.0f),
      .text_active_color = color(0.95f, 0.95f, 0.95f, 1.0)
    },
    .button = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.3f, 0.3f, 0.3f, 1.0f),
      .background_color        = color(0.29f, 0.29f, 0.29f, 1.0f),
      .background_hover_color  = color(0.25f, 0.25f, 0.25f, 1.0f),
      .background_active_color = color(0.15f, 0.15f, 0.15f, 1.0f),
      .text_color        = color(0.95f, 0.95f, 0.95f, 1.0f),
      .text_hover_color  = color(1.0f, 1.0f, 1.0f, 1.0f),
      .text_active_color = color(0.85f, 0.85f, 0.85f, 1.0)
    },
  };

  MemoryZeroStruct(&ui_context);
  {
    ui_context.arena           = arena_alloc();
    ui_context.frame_arena     = arena_alloc();
    ui_context.is_initialized  = true;
    ui_context.animation_speed = 10.0f;

    ui_context.hash_active_depth = 1.0f;
    ui_context.hash_hot_depth    = 1.0f;

    ui_context.text_pixel_height = 16;
    ui_context.color_scheme      = ui_color_scheme_dark;

    ui_context.debug.show_bounds  = true;
    ui_context.debug.show_clip    = true;
    ui_context.debug.show_cursor  = true;
    ui_context.debug.print_widget_tree = false;

    Vec2s32 window_size = g_os_window.dimensions;

    // Default values
    ui_stack_init(top_left,         vec2f32(0.0f, 0.0f));
    ui_stack_init(size_x,           window_size.x);
    ui_stack_init(size_y,           window_size.y);
    ui_stack_init(padding_x,        0.0f);
    ui_stack_init(padding_y,        0.0f);
    ui_stack_init(spacing_x,        0);
    ui_stack_init(spacing_y,        0);
    ui_stack_init(alignment_kind,   UI_Alignment_Kind_Y);
    ui_stack_init(width_kind,       UI_Width_Kind_Fill);
    ui_stack_init(height_kind,      UI_Height_Kind_Fill);

    ui_stack_init(node_color_scheme,       ui_context.color_scheme.window);
    ui_stack_init(border_color,            PURPLE(1));
    ui_stack_init(background_color,        PURPLE(1));
    ui_stack_init(background_hover_color,  PURPLE(1));
    ui_stack_init(background_active_color, PURPLE(1));
    ui_stack_init(text_color,              PURPLE(1));
    ui_stack_init(text_hover_color,        PURPLE(1));
    ui_stack_init(text_active_color,       PURPLE(1));
  }
}

function void ui_begin()
{
  ui_context.is_working = true;

  // Window widget
  {
    ui_context.root = push_array(ui_context.frame_arena, UI_Node, 1);

    String8 root_name = S("##__root__");
    UI_Node* root_widget = NULL;
    {
      UI_Node_Flags root_flags = 0;
      root_widget = ui_node_from_string(root_name, root_flags);
      ui_context.root = root_widget;
      ui_context.root->depth = 1.0f;
      ui_stack_push(node, ui_context.root);
    }
  }

  // Input handling
  if (input_is_key_clicked(&g_input, Keyboard_Key_NUMPAD1))
  {
    ui_context.debug.show_bounds = !ui_context.debug.show_bounds;
  }
  if (input_is_key_clicked(&g_input, Keyboard_Key_NUMPAD2))
  {
    ui_context.debug.show_clip = !ui_context.debug.show_clip;
  }
  if (input_is_key_clicked(&g_input, Keyboard_Key_NUMPAD3))
  {
    ui_context.debug.show_cursor = !ui_context.debug.show_cursor;
  }
  if (input_is_key_clicked(&g_input, Keyboard_Key_NUMPAD4))
  {
    ui_context.text_pixel_height -= 1;
  }
  if (input_is_key_clicked(&g_input, Keyboard_Key_NUMPAD5))
  {
    ui_context.text_pixel_height += 1;
  }
}

function void ui_end()
{
#if DEBUG
  // Ensure all the stacks are properly cleaned
  ui_stack_assert_top_at(node, 1); // Root should be in the stack
  ui_stack_assert_top_at(top_left, 0);
  ui_stack_assert_top_at(size_x, 0);
  ui_stack_assert_top_at(size_y, 0);
  ui_stack_assert_top_at(padding_x, 0);
  ui_stack_assert_top_at(padding_y, 0);
  ui_stack_assert_top_at(spacing_x, 0);
  ui_stack_assert_top_at(spacing_y, 0);
  ui_stack_assert_top_at(alignment_kind, 0);
  ui_stack_assert_top_at(width_kind, 0);
  ui_stack_assert_top_at(height_kind, 0);
  ui_stack_assert_top_at(node_color_scheme, 0);
  ui_stack_assert_top_at(border_color, 0);
  ui_stack_assert_top_at(background_color, 0);
  ui_stack_assert_top_at(background_hover_color, 0);
  ui_stack_assert_top_at(background_active_color, 0);
  ui_stack_assert_top_at(text_color, 0);
  ui_stack_assert_top_at(text_hover_color, 0);
  ui_stack_assert_top_at(text_active_color, 0);
  if (ui_context.root->depth != 1)
  {
    emit_fatal(Sf(ui_context.arena, "UI: ui_context.root->depth is expected to be 1. It was: %.10f\n", ui_context.root->depth));
  }
#endif

  ui_render_widget(ui_context.root);

  r_draw_text(vec2f32(600, 50),  32, BLACK(1), Sf(ui_context.frame_arena, "hash_active: %llu", ui_context.hash_active), 0);
  r_draw_text(vec2f32(600, 80),  32, BLACK(1), Sf(ui_context.frame_arena, "hash_active_depth: %.10f", ui_context.hash_active_depth), 0);
  r_draw_text(vec2f32(600, 110), 32, BLACK(1), Sf(ui_context.frame_arena, "hash_hot: %llu", ui_context.hash_hot), 0);
  r_draw_text(vec2f32(600, 140), 32, BLACK(1), Sf(ui_context.frame_arena, "hash_hot_depth: %.10f", ui_context.hash_hot_depth), 0);
  r_draw_text(vec2f32(600, 170), 32, BLACK(1), Sf(ui_context.frame_arena, "mouse delta: %.2f,%.2f", g_input.mouse_current.delta.x, g_input.mouse_current.delta.y), 0);
  r_draw_text(vec2f32(600, 200), 32, BLACK(1), Sf(ui_context.frame_arena, "Frame: %d", g_frame_counter), 0);

  if (input_is_key_clicked(&g_input, Keyboard_Key_K))
  {
    ui_print_tree(ui_context.root);
  }

  // Reset
  ui_context.hash_hot = 0;
  ui_context.hash_hot_depth = 1.0f;

  ui_context.root->first    = NULL;
  ui_context.root->last     = NULL;
  ui_context.root->next     = NULL;
  ui_context.root->previous = NULL;
  ui_context.root->parent   = NULL;

  ui_stack_pop(node); // Pop root (os window) because it's regenerated every frame
  ui_context.is_working = false;
  arena_clear(ui_context.frame_arena);
}

function void
ui_render_widget(UI_Node* widget_root)
{
  if (ui_context.root != widget_root)
  {
    r_draw_quad(widget_root->bounds.top_left, widget_root->bounds.size, 0, widget_root->target_background_color, widget_root->depth);
    if (HasFlags(widget_root->flags, UI_Widget_Flags_Display_Text))
    {
      f32 clamp_width  = (widget_root->clip.top_left.x + widget_root->clip.size.x) - widget_root->string_top_left.x;
      f32 clamp_height = (widget_root->clip.top_left.y + widget_root->clip.size.y) - widget_root->string_top_left.y;
      r_draw_text_clamped(widget_root->string_top_left, ui_context.text_pixel_height, widget_root->target_text_color, widget_root->string_clean, widget_root->depth - F32_EPSILON, clamp_width, clamp_height);
    }
    ui_debug_draw_node(widget_root, widget_root->depth);
  }

  for (UI_Node *child = widget_root->first; child; child = child->next)
  {
    ui_render_widget(child);
  }
}

// UI module api
function void
ui_window_begin(String8 text)
{
  Scratch scratch = scratch_begin(0,0);

  UI_Signal window_signal = (UI_Signal){0};
  ui_stack_defer_if_default(node_color_scheme, ui_context.color_scheme.window)
  ui_stack_defer_if_default(top_left, vec2f32(200,200))
  ui_stack_defer_if_default(size_x, 200) ui_stack_defer_if_default(size_y, 200)
  ui_stack_defer_if_default(padding_x, 4.0f) ui_stack_defer_if_default(padding_y, 4.0f)
  ui_stack_defer(width_kind,  UI_Width_Kind_Fixed)
  ui_stack_defer(height_kind, UI_Height_Kind_Fixed)
  {
    UI_Node_Flags window_flags = 0;
    String8 window_text = Sf(scratch.arena, ""S_FMT"##_window_`"S_FMT"`", S_ARG(text));
    window_signal.node = ui_node_from_string(window_text, window_flags);
    ui_stack_push(node, window_signal.node);
  }

  UI_Signal title_bar_signal = (UI_Signal){0};
  ui_stack_defer_if_default(node_color_scheme, ui_context.color_scheme.title_bar)
  ui_stack_defer_if_default(spacing_x, 2.0f)
  ui_stack_defer_if_default(size_y, 20.0f)
  ui_stack_defer_if_default(alignment_kind, UI_Alignment_Kind_X)
  ui_stack_defer_if_default(padding_x, 4.0f) ui_stack_defer_if_default(padding_y, 4.0f)
  ui_stack_defer(height_kind, UI_Height_Kind_Fixed)
  {
    UI_Node_Flags title_bar_flags = UI_Widget_Flags_Mouse_Clickable|
                                    UI_Widget_Flags_Hoverable|
                                    UI_Widget_Flags_Draggable|
                                    UI_Widget_Flags_Display_Text|
                                    UI_Widget_Flags_Center_Text_Vertically;
    String8 window_title_bar_text = Sf(scratch.arena, ""S_FMT"##_title_bar_", S_ARG(text));
    title_bar_signal.node = ui_node_from_string(window_title_bar_text, title_bar_flags);
  }

  scratch_end(&scratch);
}

function void
ui_window_end()
{
  UI_Node* node = ui_stack_pop(node);
  Vec2f32 offset = {0};
  if (ui_find_first_drag_offset(node, &offset))
  {
    ui_apply_drag_offset(node, offset);
  }
  ui_update_tree_nodes(node);
  if (ui_context.debug.print_widget_tree)
  {
    ui_print_tree_impl(node, 0);
  }
}

function void
ui_layout_box_begin(UI_Alignment_Kind alignment, String8 text, f32 size)
{
  ui_stack_push(alignment_kind, alignment);
  if (alignment == UI_Alignment_Kind_X)
  {
    ui_stack_push(height_kind, UI_Height_Kind_Fixed);
    ui_stack_push(width_kind, UI_Width_Kind_Fill);
    ui_stack_push(size_y, size);
  }
  else if (alignment == UI_Alignment_Kind_Y)
  {
    ui_stack_push(height_kind, UI_Height_Kind_Fill);
    ui_stack_push(width_kind, UI_Width_Kind_Fixed);
    ui_stack_push(size_x, size);
  }

  UI_Signal layout_box = (UI_Signal){0};
  ui_stack_defer_if_default(node_color_scheme, ui_context.color_scheme.window)
  {
    UI_Node_Flags layout_box_flags = 0;
    layout_box.node = ui_node_from_string(text, layout_box_flags);
    ui_stack_push(node, layout_box.node);
  }
}

function void
ui_layout_box_end()
{
  ui_stack_pop(width_kind);
  ui_stack_pop(height_kind);

  UI_Alignment_Kind alignment = ui_stack_pop(alignment_kind);
  if (alignment == UI_Alignment_Kind_X)
  {
    ui_stack_pop(size_y);
  }
  else if (alignment == UI_Alignment_Kind_Y)
  {
    ui_stack_pop(size_x);
  }
  ui_stack_pop(node);
}

function UI_Signal
ui_button(String8 text)
{
  UI_Signal button_signal = (UI_Signal){0};
  ui_stack_defer_if_default(node_color_scheme, ui_context.color_scheme.button)
  ui_stack_defer(padding_x, 1.0f) ui_stack_defer(padding_y, 1.0f)
  ui_stack_defer(size_y, 20.0f)
  ui_stack_defer(size_x, 80.0f)
  ui_stack_defer(alignment_kind, UI_Alignment_Kind_X)
  ui_stack_defer(height_kind,    UI_Height_Kind_Fixed)
  ui_stack_defer(width_kind,     UI_Width_Kind_Fixed)
  {
    UI_Node_Flags button_flags = UI_Widget_Flags_Mouse_Clickable|
                                 UI_Widget_Flags_Hoverable|
                                 UI_Widget_Flags_Display_Text|
                                 UI_Widget_Flags_Center_Text_Horizontally|
                                 UI_Widget_Flags_Center_Text_Vertically;
    button_signal.node = ui_node_from_string(text, button_flags);
    ui_fill_signals_from_node(&button_signal);
  }
  
  return button_signal;
}

// Builder code
function UI_Node*
ui_node_from_string(String8 string, UI_Node_Flags flags)
{
  if (!ui_context.is_initialized)
  {
    emit_fatal(S("UI: Did not unit UI"));
  }
  if (!ui_context.is_working)
  {
    emit_fatal(S("UI: Not within ui_begin and ui_end"));
  }

  UI_Node* parent = ui_stack_top(node);
  if (parent == NULL)
  {
    // If we're the ui_context.root (screen)
    // We simulate a parent with the same values as screen just so it goes through this iteration
    parent = push_array(ui_context.frame_arena, UI_Node, 1);
    parent->bounds.top_left = ui_stack_top(top_left);
    parent->bounds.size     = vec2f32(ui_stack_top(size_x), ui_stack_top(size_y));
    parent->clip            = parent->bounds;
    parent->depth           = 1.0f + F32_EPSILON;
  }
  UI_Node* widget = push_array(ui_context.frame_arena, UI_Node, 1);
  ui_add_widget_child(parent, widget);

  widget->hash      = parent->hash ^ string8_hash(string);
  widget->spacing_x = ui_stack_top(spacing_x);
  widget->spacing_y = ui_stack_top(spacing_y);
  widget->padding_x = ui_stack_top(padding_x);
  widget->padding_y = ui_stack_top(padding_y);
  widget->alignment_kind    = ui_stack_top(alignment_kind);
  widget->string            = string8_copy(ui_context.frame_arena, string);
  widget->string_clean      = ui_clean_string(ui_context.frame_arena, string);
  widget->string_top_left   = vec2f32(0,0);
  widget->local_drag_offset = vec2f32(0,0);
  widget->flags             = flags;

  f32 size_x = 0;
  switch (ui_stack_top(width_kind))
  {
    case UI_Width_Kind_Fill:
    {
      size_x = parent->bounds.size.x;
    } break;
    case UI_Width_Kind_Fixed:
    {
      size_x = ui_stack_top(size_x); 
    } break;
    default: emit_fatal(S("UI: Unhandled width_kind")); break;
  }
  f32 size_y = 0;
  switch (ui_stack_top(height_kind))
  {
    case UI_Height_Kind_Fill:
    {
      size_y = parent->bounds.size.y;
    } break;      
    case UI_Height_Kind_Fixed:
    {
      size_y = ui_stack_top(size_y); 
    } break;
    default: emit_fatal(S("UI: Unhandled width_kind")); break;
  }

  if (ui_stack_is_at_bottom(top_left))
  {
    widget->bounds.top_left = vec2f32_add(parent->clip.top_left, parent->cursor);
  }
  else
  {
    widget->bounds.top_left = ui_stack_top(top_left);  
  }
  widget->bounds.size = vec2f32(size_x, size_y);
  widget->bounds      = ui_clamp_rect(parent->clip, widget->bounds);

  // Update parent clip based on this widget
  if (parent != ui_context.root)
  {
    switch (parent->alignment_kind)
    {
      case UI_Alignment_Kind_X:
      {
        parent->cursor.x += widget->bounds.size.x + parent->padding_x;
      } break;

      case UI_Alignment_Kind_Y:
      {
        parent->cursor.y += widget->bounds.size.y + parent->padding_y;
      } break;
    }
  }

  Rectf32 clip;
  clip.top_left = vec2f32(widget->bounds.top_left.x + widget->padding_x, widget->bounds.top_left.y + widget->padding_y);
  clip.size     = vec2f32(widget->bounds.size.x - (widget->padding_x * 2), widget->bounds.size.y - (widget->padding_y * 2));
  widget->clip  = ui_clamp_rect(widget->bounds, clip);
  
  widget->cursor.x  = widget->cursor.x + widget->spacing_x;
  widget->cursor.y  = widget->cursor.y + widget->spacing_y;
  widget->depth     = (parent) ? parent->depth - F32_EPSILON : 1.0f;

  UI_Node_Cache* cached_widget = ui_get_cached_node(widget->hash);

  // Input
  if (ui_is_mouse_in_node(widget))
  {
    if (widget->depth < ui_context.hash_hot_depth)
    {
      ui_context.hash_hot = widget->hash;
      ui_context.hash_hot_depth = widget->depth;
      if (input_is_button_clicked(&g_input, Mouse_Button_Left))
      {
        ui_context.hash_active = widget->hash;
      }
    }
  }
  if (input_is_button_up(&g_input, Mouse_Button_Left) && input_was_button_down(&g_input, Mouse_Button_Left))
  {
    ui_context.hash_active = 0;
  }

  // Style
  // NOTE(fz): We use colors from the stack if they were explicitly added by the user. Otherwise we just take them from the color scheme
  widget->node_color_scheme     = ui_stack_top(node_color_scheme);
  Color border_color            = ui_stack_is_at_bottom(border_color)            ? widget->node_color_scheme.border_color            : ui_stack_top(border_color);
  Color background_color        = ui_stack_is_at_bottom(background_color)        ? widget->node_color_scheme.background_color        : ui_stack_top(background_color);
  Color background_hover_color  = ui_stack_is_at_bottom(background_hover_color)  ? widget->node_color_scheme.background_hover_color  : ui_stack_top(background_hover_color);
  Color background_active_color = ui_stack_is_at_bottom(background_active_color) ? widget->node_color_scheme.background_active_color : ui_stack_top(background_active_color);
  Color text_color              = ui_stack_is_at_bottom(text_color)              ? widget->node_color_scheme.text_color              : ui_stack_top(text_color);
  Color text_hover_color        = ui_stack_is_at_bottom(text_hover_color)        ? widget->node_color_scheme.text_hover_color        : ui_stack_top(text_hover_color);
  Color text_active_color       = ui_stack_is_at_bottom(text_active_color)       ? widget->node_color_scheme.text_active_color       : ui_stack_top(text_active_color);

  widget->target_background_color = color_lerp(background_color, background_hover_color, cached_widget->hover_t);
  widget->target_background_color = color_lerp(widget->target_background_color, background_active_color, cached_widget->active_t);

  widget->target_text_color = color_lerp(text_color, text_hover_color, cached_widget->hover_t);
  widget->target_text_color = color_lerp(widget->target_text_color, text_active_color, cached_widget->active_t);

  // Hover
  if (HasFlags(widget->flags, UI_Widget_Flags_Hoverable))
  {
    if (ui_is_mouse_in_node(widget))
    {
      cached_widget->hover_t = Clamp(cached_widget->hover_t + g_delta_time * ui_context.animation_speed, 0, 1);
    }
    else
    {
      cached_widget->hover_t = Clamp(cached_widget->hover_t - g_delta_time * ui_context.animation_speed, 0, 1);
    }
  }

  // Active
  if (HasFlags(widget->flags, UI_Widget_Flags_Mouse_Clickable))
  {
    if (ui_context.hash_active == widget->hash)
    {
      cached_widget->active_t = Clamp(cached_widget->active_t + g_delta_time * ui_context.animation_speed, 0, 1);
    }
    else
    {
      cached_widget->active_t = Clamp(cached_widget->active_t - g_delta_time * ui_context.animation_speed, 0, 1);
    }
  }
  
  // Dragging
  if (ui_context.hash_active == widget->hash)
  {
    if (HasFlags(widget->flags, UI_Widget_Flags_Draggable))
    {
      widget->local_drag_offset = g_input.mouse_current.delta;
    }
  }

  return widget;
}

function void
ui_fill_signals_from_node(UI_Signal* signal)
{
  if (ui_is_mouse_in_node(signal->node))
  {
    if (input_is_button_down(&g_input, Mouse_Button_Left))      SetFlags(signal->flags, UI_Signal_Flags_Left_Clicked);
    if (input_is_button_down(&g_input, Mouse_Button_Middle))    SetFlags(signal->flags, UI_Signal_Flags_Middle_Clicked);
    if (input_is_button_down(&g_input, Mouse_Button_Right))     SetFlags(signal->flags, UI_Signal_Flags_Right_Clicked);
    
    if (input_is_button_clicked(&g_input, Mouse_Button_Left))   SetFlags(signal->flags, UI_Signal_Flags_Left_Clicked);
    if (input_is_button_clicked(&g_input, Mouse_Button_Middle)) SetFlags(signal->flags, UI_Signal_Flags_Middle_Clicked);
    if (input_is_button_clicked(&g_input, Mouse_Button_Right))  SetFlags(signal->flags, UI_Signal_Flags_Right_Clicked);

    SetFlags(signal->flags, UI_Signal_Flags_Mouse_Hovered);
  }
}

function b32  ui_find_first_drag_offset(UI_Node* widget_root, Vec2f32* out_offset)
{
  b32 result = false;
  if (HasFlags(widget_root->flags, UI_Widget_Flags_Draggable) && ui_context.hash_active == widget_root->hash)
  {
    *out_offset = widget_root->local_drag_offset;
    result = true;
  }
  else
  {
    for (UI_Node* child = widget_root->first; child; child = child->next)
    {
      if (HasFlags(child->flags, UI_Widget_Flags_Draggable) && ui_context.hash_active == child->hash)
      {
        *out_offset = child->local_drag_offset;
        result = true;
        break;
      }
      if (ui_find_first_drag_offset(child, out_offset))
      {
        result = true;
        break;
      }
    }
  }

  return result;
}

function void ui_apply_drag_offset(UI_Node* widget_root, Vec2f32 offset)
{
  widget_root->local_drag_offset = offset;
  for (UI_Node* child = widget_root->first; child; child = child->next)
  {
    ui_apply_drag_offset(child, offset);
  }
}

// Helper
function String8
ui_clean_string(Arena* arena, String8 string)
{
  String8 result;
  String8_List strings = string8_split(arena, string, S("##"));
  result = strings.first->value;
  return result;
}

function void
ui_debug_draw_node(UI_Node* node, f32 depth)
{
  if (ui_context.debug.show_cursor) r_draw_point(vec2f32_add(node->clip.top_left, node->cursor), GREEN(1), depth - (F32_EPSILON*3));
  if (ui_context.debug.show_bounds) r_draw_box(node->bounds.top_left, node->bounds.size, YELLOW(1), depth - F32_EPSILON);
  if (ui_context.debug.show_clip)
  {
    Color color = PURPLE(1);
    if (node->alignment_kind == UI_Alignment_Kind_X)
    {
      color = BLUE(1);
    }
    else if (node->alignment_kind == UI_Alignment_Kind_Y)
    {
      color = RED(1);
    }
    r_draw_box(node->clip.top_left, node->clip.size, color, depth - (F32_EPSILON*2));
  }
}

function Rectf32
ui_clamp_rect(Rectf32 parent, Rectf32 child)
{
  f32 parent_x0 = parent.top_left.x;
  f32 parent_y0 = parent.top_left.y;
  f32 parent_x1 = parent_x0 + parent.size.x;
  f32 parent_y1 = parent_y0 + parent.size.y;

  f32 child_x0 = child.top_left.x;
  f32 child_y0 = child.top_left.y;
  f32 child_x1 = child_x0 + child.size.x;
  f32 child_y1 = child_y0 + child.size.y;

  f32 x0 = ClampBot(child_x0, parent_x0);
  f32 y0 = ClampBot(child_y0, parent_y0);
  f32 x1 = ClampTop(child_x1, parent_x1);
  f32 y1 = ClampTop(child_y1, parent_y1);

  Rectf32 result;
  result.top_left.x = x0;
  result.top_left.y = y0;
  result.size.x = (x1 > x0) ? (x1 - x0) : 0.0f;
  result.size.y = (y1 > y0) ? (y1 - y0) : 0.0f;

  return result;
}

function b32
ui_is_mouse_in_node(UI_Node* node)
{
  UI_Node_Cache* cached_widget = ui_get_cached_node(node->hash);

  Rectf32 bounds = node->bounds;
  bounds.top_left = vec2f32_add(node->bounds.top_left, cached_widget->accumulated_drag_offset);

  Vec2f32 mouse = g_input.mouse_current.screen_space;
  b32 result = (mouse.x >= bounds.top_left.x && mouse.x <= bounds.top_left.x + bounds.size.x &&
                mouse.y >= bounds.top_left.y && mouse.y <= bounds.top_left.y + bounds.size.y);
  return result;
}

function UI_Node_Cache*
ui_get_cached_node(u64 hash)
{
  for (u32 i = 0; i < ui_cached_nodes_count; i += 1)
  {
    if (ui_cached_nodes[i].hash == hash)
    {
      return &ui_cached_nodes[i];
    }
  }

  if (ui_cached_nodes_count >= UI_MAX_CACHED_NODES)
  {
    emit_fatal(S("UI: Too many widgets"));
  }

  UI_Node_Cache* cached_widget = NULL;

  cached_widget = &ui_cached_nodes[ui_cached_nodes_count];

  cached_widget->hash = hash;
  cached_widget->hash = hash;
  cached_widget->accumulated_drag_offset = vec2f32(0,0);
  cached_widget->hover_t = 0;
  cached_widget->active_t = 0;

  ui_cached_nodes_count += 1;

  return cached_widget;
}

// Widget tree
function void
ui_add_widget_child(UI_Node *parent, UI_Node *child)
{
  if (parent == NULL)
  {
    // If we're the ui_context.root (screen)
    child->first    = NULL;
    child->last     = NULL;
    child->next     = NULL;
    child->previous = NULL;
    child->parent   = NULL;
  }
  else
  {
    child->parent   = parent;
    child->next     = NULL;
    child->previous = parent->last;

    if (parent->last)
    {
      parent->last->next = child;
    }
    else
    {
      parent->first = child;
    }

    parent->last = child;
  }
}

function void
ui_update_tree_nodes(UI_Node* widget_root)
{
  if (!widget_root)
  {
    return;
  }

  UI_Node_Cache* cached_widget = ui_get_cached_node(widget_root->hash);
  cached_widget->accumulated_drag_offset = vec2f32_add(widget_root->local_drag_offset, cached_widget->accumulated_drag_offset);

  // Bounds
  widget_root->bounds.top_left = vec2f32_add(widget_root->bounds.top_left, cached_widget->accumulated_drag_offset);
  widget_root->clip.top_left   = vec2f32_add(widget_root->clip.top_left, cached_widget->accumulated_drag_offset);

  // String
  if (HasFlags(widget_root->flags, UI_Widget_Flags_Display_Text))
  {
    widget_root->string_dimensions = r_text_dimensions(widget_root->string_clean, ui_context.text_pixel_height);
    widget_root->string_top_left = vec2f32_add(widget_root->clip.top_left, widget_root->cursor);

    if (HasFlags(widget_root->flags, UI_Widget_Flags_Center_Text_Horizontally))
    {
      f32 offset_x = (widget_root->clip.size.x - widget_root->string_dimensions.x) * 0.5f;
      widget_root->string_top_left.x = widget_root->clip.top_left.x + offset_x;
    }

    if (HasFlags(widget_root->flags, UI_Widget_Flags_Center_Text_Vertically))
    {
      f32 offset_y = (widget_root->clip.size.y - widget_root->string_dimensions.y) * 0.5f;
      widget_root->string_top_left.y = widget_root->clip.top_left.y + offset_y;
    }
  }

  // Advance cursor
  // TODO(fz): After we cache string dimensions, we can move this up to node_from_string
  switch (widget_root->alignment_kind)
  {
    case UI_Alignment_Kind_X:
    {
      f32 advance_x = HasFlags(widget_root->flags, UI_Widget_Flags_Center_Text_Horizontally)
                    ? widget_root->clip.size.x
                    : widget_root->string_dimensions.x;

      widget_root->cursor.x += advance_x + widget_root->padding_x;
      widget_root->cursor.y += widget_root->padding_y;
    } break;

    case UI_Alignment_Kind_Y:
    {
      f32 advance_y = HasFlags(widget_root->flags, UI_Widget_Flags_Center_Text_Vertically)
                    ? widget_root->clip.size.y
                    : widget_root->string_dimensions.y;

      widget_root->cursor.x += widget_root->padding_x;
      widget_root->cursor.y += advance_y + widget_root->padding_y;
    } break;

    default:
    {
      emit_fatal(S("UI: Unhandled UI_Alignment"));
    } break;
  }

  for (UI_Node* child = widget_root->first; child; child = child->next)
  {
    ui_update_tree_nodes(child);
  }
}

function void
ui_print_tree_impl(UI_Node *node, u32 depth)
{
  // Print prefix
  for (u32 i = 0; i < depth; i += 1)
  {
    printf("    ");
  }

  // Branch symbol
  if (node->next == NULL)
  {
    printf("`-- ");
  }
  else
  {
    printf("|-- ");
  }

  UI_Node_Cache *cache = ui_get_cached_node(node->hash);
  printf("Widget hash: %llu, Text: " S_FMT "\n", node->hash, S_ARG(node->string));

  // Children
  for (UI_Node *child = node->first; child; child = child->next)
  {
    ui_print_tree_impl(child, depth + 1);
  }
}