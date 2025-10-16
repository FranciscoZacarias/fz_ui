#include "ui.hephaestus.c"

// Core functions
function void ui_init()
{
  AssertNoReentry();

  ui_color_scheme_dark = (UI_Color_Scheme)
  {
    .title_bar = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.20f, 0.20f, 0.20f, 1.0f),
      .background_color        = color(0.07f, 0.07f, 0.07f, 1.0f),
      .background_hover_color  = color(0.10f, 0.10f, 0.10f, 1.0f),
      .background_active_color = color(0.12f, 0.12f, 0.12f, 1.0f),
      .text_color        = color(0.76f, 0.71f, 0.62f, 1.0f),
      .text_hover_color  = color(1.0f, 1.0f, 1.0f, 1.0f),
      .text_active_color = color(0.95f, 0.95f, 0.95f, 1.0f),
    },
    .window = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.18f, 0.18f, 0.18f, 1.0f),
      .background_color        = color(0.14f, 0.14f, 0.14f, 1.0f),
      .background_hover_color  = color(0.17f, 0.17f, 0.17f, 1.0f),
      .background_active_color = color(0.20f, 0.20f, 0.20f, 1.0f),
      .text_color        = color(0.76f, 0.71f, 0.62f, 1.0f),
      .text_hover_color  = color(0.95f, 0.95f, 0.95f, 1.0f),
      .text_active_color = color(1.0f, 1.0f, 1.0f, 1.0f),
    },
    .button = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.25f, 0.25f, 0.25f, 1.0f),
      .background_color        = color(0.20f, 0.20f, 0.20f, 1.0f),
      .background_hover_color  = color(0.25f, 0.25f, 0.25f, 1.0f),
      .background_active_color = color(0.30f, 0.30f, 0.30f, 1.0f),
      .text_color        = color(0.76f, 0.71f, 0.62f, 1.0f),
      .text_hover_color  = color(1.0f, 1.0f, 1.0f, 1.0f),
      .text_active_color = color(0.90f, 0.90f, 0.90f, 1.0f),
    },
  };

  ui_color_scheme_high_contrast = (UI_Color_Scheme)
  {
    .title_bar = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.85f, 0.85f, 0.85f, 1.0f),
      .background_color        = color(0.10f, 0.10f, 0.10f, 1.0f),
      .background_hover_color  = color(0.18f, 0.18f, 0.18f, 1.0f),
      .background_active_color = color(0.25f, 0.25f, 0.25f, 1.0f),
      .text_color        = color(0.90f, 0.90f, 0.90f, 1.0f),
      .text_hover_color  = color(1.00f, 0.90f, 0.20f, 1.0f),
      .text_active_color = color(1.00f, 0.80f, 0.00f, 1.0f),
    },
    .window = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.20f, 0.20f, 0.20f, 1.0f),
      .background_color        = color(0.30f, 0.30f, 0.30f, 1.0f),
      .background_hover_color  = color(0.35f, 0.35f, 0.35f, 1.0f),
      .background_active_color = color(0.40f, 0.40f, 0.40f, 1.0f),
      .text_color        = color(0.95f, 0.95f, 0.85f, 1.0f),
      .text_hover_color  = color(1.00f, 0.90f, 0.20f, 1.0f),
      .text_active_color = color(1.00f, 0.80f, 0.00f, 1.0f),
    },
    .button = (UI_Node_Color_Scheme)
    {
      .border_color            = color(0.15f, 0.15f, 0.15f, 1.0f),
      .background_color        = color(0.85f, 0.65f, 0.00f, 1.0f),
      .background_hover_color  = color(1.00f, 0.75f, 0.00f, 1.0f),
      .background_active_color = color(0.90f, 0.50f, 0.00f, 1.0f),
      .text_color        = color(0.05f, 0.05f, 0.05f, 1.0f),
      .text_hover_color  = color(0.00f, 0.00f, 0.00f, 1.0f),
      .text_active_color = color(0.00f, 0.00f, 0.00f, 1.0f),
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
    ui_context.color_scheme      = ui_color_scheme_high_contrast;

    ui_context.debug.show_bounds  = true;
    ui_context.debug.show_clip    = true;
    ui_context.debug.show_cursor  = true;
    ui_context.debug.show_text_borders = true;

    Vec2s32 window_size = g_os_window.dimensions;

    UI_Init_Stacks(ui_context);
  }
}

function void ui_begin()
{
  ui_context.is_working = true;

  // Window Node
  {
    ui_context.root = push_array(ui_context.frame_arena, UI_Node, 1);

    String8 root_name = S("##__root__");
    UI_Node* root_node = NULL;
    {
      UI_Node_Flags root_flags = 0;
      root_node = ui_node_from_string(root_name, root_flags);
      ui_context.root = root_node;
      ui_context.root->depth = 1.0f;
      ui_stack_parent_push(ui_context.root);
    }
  }

  // Input handling
  if (input_is_key_clicked(&g_input, Keyboard_Key_NUMPAD1))
  {
    ui_context.debug.show_bounds = !ui_context.debug.show_bounds;
    ui_context.debug.show_text_borders = !ui_context.debug.show_text_borders;
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
  UI_Debug_Stacks_At_Bottom;
  if (ui_context.root->depth != 1)
  {
    emit_fatal(Sf(ui_context.arena, "UI: ui_context.root->depth is expected to be 1. It was: %.10f\n", ui_context.root->depth));
  }
#endif

  ui_render_ui_tree(ui_context.root);

  r_draw_text(vec2f32(600, 50),  32, BLACK(1), Sf(ui_context.frame_arena, "hash_active: %llu", ui_context.hash_active), 0);
  r_draw_text(vec2f32(600, 80),  32, BLACK(1), Sf(ui_context.frame_arena, "hash_active_depth: %.10f", ui_context.hash_active_depth), 0);
  r_draw_text(vec2f32(600, 110), 32, BLACK(1), Sf(ui_context.frame_arena, "hash_hot: %llu", ui_context.hash_hot), 0);
  r_draw_text(vec2f32(600, 140), 32, BLACK(1), Sf(ui_context.frame_arena, "hash_hot_depth: %.10f", ui_context.hash_hot_depth), 0);
  r_draw_text(vec2f32(600, 170), 32, BLACK(1), Sf(ui_context.frame_arena, "mouse delta: %.2f,%.2f", g_input.mouse_current.delta.x, g_input.mouse_current.delta.y), 0);
  r_draw_text(vec2f32(600, 200), 32, BLACK(1), Sf(ui_context.frame_arena, "mouse: %.2f,%.2f", g_input.mouse_current.screen_space.x, g_input.mouse_current.screen_space.y), 0);
  r_draw_text(vec2f32(600, 230), 32, BLACK(1), Sf(ui_context.frame_arena, "Frame: %d", g_frame_counter), 0);

  if (input_is_key_clicked(&g_input, Keyboard_Key_K)) ui_print_tree(ui_context.root);

  // Reset
  ui_context.hash_hot = 0;
  ui_context.hash_hot_depth = 1.0f;

  ui_context.root->first    = NULL;
  ui_context.root->last     = NULL;
  ui_context.root->next     = NULL;
  ui_context.root->previous = NULL;
  ui_context.root->parent   = NULL;

  ui_stack_parent_pop(); // Pop root (os window) because it's regenerated every frame
  ui_context.is_working = false;
  arena_clear(ui_context.frame_arena);

  debug_color_index = 0;
}

function void
ui_render_ui_tree(UI_Node* node)
{
  if (ui_context.root != node)
  {
    r_draw_quad(node->bounds.top_left, node->bounds.size, 0, node->target_background_color, node->depth);
    if (HasFlags(node->flags, UI_Node_Flags_Text_Display))
    {
      node->string_bounds.top_left = vec2f32_add(node->clip.top_left, node->string_bounds.top_left);
      node->string_bounds = ui_clamp_rect(node->clip, node->string_bounds);
      f32 clamp_width  = (node->clip.top_left.x + node->clip.size.x) - node->string_bounds.top_left.x;
      f32 clamp_height = (node->clip.top_left.y + node->clip.size.y) - node->string_bounds.top_left.y;
      r_draw_text_clamped(node->string_bounds.top_left, ui_context.text_pixel_height, node->target_text_color, node->string_clean, node->depth - F32_EPSILON, clamp_width, clamp_height);
    }
    ui_debug_draw_node(node, node->depth);
  }

  for (UI_Node *child = node->first; child; child = child->next)
  {
    ui_render_ui_tree(child);
  }
}


function void
ui_update_tree_nodes(UI_Node* node)
{
  if (!node)
  {
    return;
  }

  if (node != ui_context.root)
  {
    UI_Node_Cache* cached_node = ui_get_cached_node(node->hash);
    cached_node->accumulated_drag_offset = vec2f32_add(node->local_drag_offset, cached_node->accumulated_drag_offset);

    // Bounds
    node->bounds.top_left = vec2f32_add(node->bounds.top_left, cached_node->accumulated_drag_offset);
    node->clip.top_left   = vec2f32_add(node->clip.top_left,   cached_node->accumulated_drag_offset);

    // Interaction
    // -----------
    {
      // Hover
      if (HasFlags(node->flags, UI_Node_Flags_Hoverable))
      {
        if (ui_context.hash_hot == node->hash)
        {
          cached_node->hover_t = Clamp(cached_node->hover_t + g_delta_time * ui_context.animation_speed, 0, 1);
        }
        else
        {
          cached_node->hover_t = Clamp(cached_node->hover_t - g_delta_time * ui_context.animation_speed, 0, 1);
        }
      }

      // Active
      if (HasFlags(node->flags, UI_Node_Flags_Mouse_Clickable))
      {
        if (ui_context.hash_active == node->hash)
        {
          cached_node->active_t = Clamp(cached_node->active_t + g_delta_time * ui_context.animation_speed, 0, 1);
        }
        else
        {
          cached_node->active_t = Clamp(cached_node->active_t - g_delta_time * ui_context.animation_speed, 0, 1);
        }
      }
    }

    // Style
    // -----
    {
      Color border_color            = node->node_color_scheme.border_color;
      Color background_color        = node->node_color_scheme.background_color;
      Color background_hover_color  = node->node_color_scheme.background_hover_color;
      Color background_active_color = node->node_color_scheme.background_active_color;
      Color text_color              = node->node_color_scheme.text_color;
      Color text_hover_color        = node->node_color_scheme.text_hover_color;
      Color text_active_color       = node->node_color_scheme.text_active_color;

      node->target_background_color = color_lerp(background_color, background_hover_color, cached_node->hover_t);
      node->target_background_color = color_lerp(node->target_background_color, background_active_color, cached_node->active_t);
      node->target_text_color = color_lerp(text_color, text_hover_color, cached_node->hover_t);
      node->target_text_color = color_lerp(node->target_text_color, text_active_color, cached_node->active_t);
    }
  }

  for (UI_Node* child = node->first; child; child = child->next)
  {
    ui_update_tree_nodes(child);
  }
}

function void
ui_window_begin(String8 text)
{
  UI_Signal window_signal = (UI_Signal){0};
  {
    ui_node_color_scheme(ui_context.color_scheme.window)
    ui_child_layout_kind(UI_Alignment_Kind_Y)
    {
      UI_Node_Flags window_flags = 0;
      String8 window_text = Sf(ui_context.frame_arena, ""S_FMT"##_window_", S_ARG(text));
      window_signal.node = ui_node_from_string(window_text, window_flags);
      ui_stack_parent_push(window_signal.node);
    }
  }

  UI_Signal title_bar_signal = (UI_Signal){0};
  {
    ui_node_color_scheme(ui_context.color_scheme.title_bar)
    ui_child_layout_kind(UI_Alignment_Kind_X)
    ui_padding_fixed(4)
    ui_size_kind(UI_Size_Kind_Relative)
    ui_size_relative_x(1) ui_size_relative_y(0.1)
    {
      UI_Node_Flags title_bar_flags = UI_Node_Flags_Mouse_Clickable |
                                      UI_Node_Flags_Hoverable       |
                                      UI_Node_Flags_Draggable       |
                                      UI_Node_Flags_Text_Display    |
                                      UI_Node_Flags_Text_Center_Y;
      String8 window_title_bar_text = Sf(ui_context.frame_arena, ""S_FMT"##_title_bar_", S_ARG(text));
      title_bar_signal.node = ui_node_from_string(window_title_bar_text, title_bar_flags);
    }
  }
}

function void
ui_window_end()
{
  UI_Node* node = ui_stack_parent_pop();
  Vec2f32 offset = {0};
  if (ui_find_first_drag_offset(node, &offset))
  {
    ui_apply_drag_offset(node, offset);
  }
  ui_update_tree_nodes(node);
}

function void
ui_layout_begin(UI_Alignment_Kind alignment, f32 size, String8 text)
{
  ui_stack_child_layout_kind_push(alignment);
  if (alignment == UI_Alignment_Kind_X)
  {
    ui_stack_size_fixed_y_push(size);
  }
  else if (alignment == UI_Alignment_Kind_Y)
  {
    ui_stack_size_fixed_x_push(size);
  }

  UI_Signal layout_box = (UI_Signal){0};
  ui_node_color_scheme(ui_context.color_scheme.window)
  {
    UI_Node_Flags layout_box_flags = 0;
    layout_box.node = ui_node_from_string(text, layout_box_flags);
    ui_stack_parent_push(layout_box.node);
  }
}

function void
ui_layout_end()
{
  UI_Alignment_Kind alignment = ui_stack_child_layout_kind_pop();
  if (alignment == UI_Alignment_Kind_X)
  {
    ui_stack_size_fixed_y_pop();
  }
  else if (alignment == UI_Alignment_Kind_Y)
  {
    ui_stack_size_fixed_x_pop();
  }
  ui_stack_parent_pop();
}

function UI_Signal
ui_button(String8 text)
{
  UI_Signal button_signal = (UI_Signal){0};
  {
    ui_node_color_scheme(ui_context.color_scheme.button)
    ui_child_layout_kind(UI_Alignment_Kind_X)
    ui_padding_fixed(0)
    ui_size_fixed(20,10)
    {
      UI_Node_Flags button_flags = UI_Node_Flags_Mouse_Clickable |
                                   UI_Node_Flags_Hoverable       |
                                   UI_Node_Flags_Text_Display    |
                                   UI_Node_Flags_Text_Center_Y   |
                                   UI_Node_Flags_Text_Center_X   |
                                   UI_Node_Flags_Size_Wrap_Around_Text;
      button_signal.node  = ui_node_from_string(text, button_flags);
      ui_fill_signals_from_node(&button_signal);
    }
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

  UI_Node* parent = ui_stack_parent_top();
  UI_Node* node = push_array(ui_context.frame_arena, UI_Node, 1);

  if (parent == &ui_node_nil_sentinel)
  {
    // If we're the ui_context.root (screen)
    // We simulate a parent with the same values as screen just so it goes through this iteration
    parent = push_array(ui_context.frame_arena, UI_Node, 1);
    parent->bounds.top_left = vec2f32(0,0);
    parent->bounds.size     = vec2f32(g_os_window.dimensions.x, g_os_window.dimensions.y);
    parent->clip            = parent->bounds;
    parent->depth           = 1.0f;
    ui_context.root         = node;
  }

  UI_Node_Cache* cached_node = ui_get_cached_node(node->hash);
  ui_add_node_child(parent, node);

  node->hash              = parent->hash ^ string8_hash(string);
  node->local_drag_offset = vec2f32(0,0);
  node->flags             = flags;
  node->depth             = (node != ui_context.root) ? (parent->depth - F32_EPSILON) : 1.0f;
  node->node_color_scheme = ui_stack_node_color_scheme_top();
  node->alignment_kind    = ui_stack_child_layout_kind_top();
  node->resizable         = ui_stack_resizable_top();
  node->string            = string8_copy(ui_context.frame_arena, string);
  node->string_clean      = ui_clean_string(ui_context.frame_arena, string);
  node->string_bounds.size = r_text_dimensions(node->string_clean, ui_context.text_pixel_height);
  node->string_bounds.top_left   = vec2f32(0,0);

  // Bounds & Clip
  // -------------
  f32 size_x = 0;
  f32 size_y = 0;

  UI_Size_Kind size_kind = ui_stack_size_kind_top();
  switch (size_kind)
  {
    case UI_Size_Kind_Fixed:
    {
      size_x = ui_stack_size_fixed_x_top(); 
      size_y = ui_stack_size_fixed_y_top(); 
    } break;

    case UI_Size_Kind_Relative:
    {
      size_x = (parent->bounds.size.x * ui_stack_size_relative_x_top());
      size_y = (parent->bounds.size.y * ui_stack_size_relative_y_top());
      if (HasFlags(node->flags, UI_Node_Flags_Text_Display))
      {
        f32 text_dimension_factor = (0.08f * Clamp(ui_context.text_pixel_height, 14, 100));
        text_dimension_factor = Clamp(text_dimension_factor, 1, 10);
        size_y *= text_dimension_factor;
      }
    } break;

    default:
    {
      ui_size_kind_not_handled(ui_context.arena, size_kind);
    } break;
  }

  if (HasFlags(node->flags, UI_Node_Flags_Size_Wrap_Around_Text|UI_Node_Flags_Text_Display))
  {
    size_x = node->string_bounds.size.x + size_x;
    size_y = node->string_bounds.size.y + size_y;
  }

  node->bounds.size = vec2f32(size_x, size_y);
  
  // If this is a node that we are placing on top of the root, we receive the stack top_left value.
  // If not, we just inherit the parent's top_left
  Vec2f32 top_left = (parent != ui_context.root) ? parent->bounds.top_left : vec2f32_add(parent->cursor, ui_stack_top_left_top());
  if (node != ui_context.root)
  {
    switch (parent->alignment_kind)
    {
      case UI_Alignment_Kind_X: { top_left.x += parent->padding_left; } break;
      case UI_Alignment_Kind_Y: { top_left.y += parent->padding_top;  } break;
      default: { ui_alignment_kind_not_handled(ui_context.arena, parent->alignment_kind); }
    }
  }
  node->bounds.top_left = vec2f32_add(parent->cursor, top_left);
  node->bounds = ui_clamp_rect(parent->clip, node->bounds);

  Rectf32 clip;
  clip.top_left = vec2f32(node->bounds.top_left.x, node->bounds.top_left.y);
  clip.size     = vec2f32(node->bounds.size.x, node->bounds.size.y);
  {
    f32 padding_global = ui_stack_padding_fixed_top();
    f32 padding_left   = ui_stack_padding_fixed_left_top();
    f32 padding_right  = ui_stack_padding_fixed_right_top();
    f32 padding_top    = ui_stack_padding_fixed_top_top();
    f32 padding_bottom = ui_stack_padding_fixed_bot_top();

    node->padding_left   = padding_global + padding_left;
    node->padding_right  = padding_global + padding_right;
    node->padding_top    = padding_global + padding_top;
    node->padding_bottom = padding_global + padding_bottom;

    clip.top_left.x += node->padding_left;
    clip.size.x     -= (node->padding_left + node->padding_right);

    clip.top_left.y += node->padding_top;
    clip.size.y     -= (node->padding_top + node->padding_bottom);
  }
  node->clip = ui_clamp_rect(node->bounds, clip);

  // Update Parent
  // -------------
  if (node != ui_context.root)
  {
    switch (parent->alignment_kind)
    {
      case UI_Alignment_Kind_X:
      {
        parent->cursor.x += node->bounds.size.x;
        parent->cursor.x += parent->padding_left;
      } break;
      case UI_Alignment_Kind_Y:
      {
        parent->cursor.y += node->bounds.size.y;
        parent->cursor.y += parent->padding_top;
      } break;
      default:
      {
        ui_alignment_kind_not_handled(ui_context.arena, parent->alignment_kind);
      }
    }
  }

  // String
  // ------
  if (HasFlags(node->flags, UI_Node_Flags_Text_Center_Y))
  {
    f32 center_y = node->clip.size.y * 0.5f;
    f32 string_half_h = node->string_bounds.size.y * 0.5f;
    node->string_bounds.top_left.y = center_y - string_half_h;
  }
  if (HasFlags(node->flags, UI_Node_Flags_Text_Center_X))
  {
    f32 center_x = node->clip.size.x * 0.5f;
    f32 string_half_w = node->string_bounds.size.x * 0.5f;
    node->string_bounds.top_left.x = center_x - string_half_w;
  }

  if (HasFlags(node->flags, UI_Node_Flags_Text_Display))
  {
    node->cursor = vec2f32_add(node->cursor, node->string_bounds.top_left);
    switch (node->alignment_kind)
    {
      case UI_Alignment_Kind_X:
      {
        node->cursor.x = Clamp(node->cursor.x + node->string_bounds.size.x, 0, node->clip.size.x);
        node->cursor.y = Clamp(node->cursor.y, 0, node->clip.size.y);
      }
      break;
      case UI_Alignment_Kind_Y:
      {
        node->cursor.y = Clamp(node->cursor.y + node->string_bounds.size.y, 0, node->clip.size.y);
        node->cursor.x = Clamp(node->cursor.x, 0, node->clip.size.x);
      }
      break;
      default: { ui_alignment_kind_not_handled(ui_context.arena, node->alignment_kind); } break;
    }
  }

  // Interaction
  // -----------
  {
    // Input
    if (ui_is_mouse_in_node(node))
    {
      if (node->depth < ui_context.hash_hot_depth)
      {
        ui_context.hash_hot       = node->hash;
        ui_context.hash_hot_depth = node->depth;
        if (input_is_button_clicked(&g_input, Mouse_Button_Left))
        {
          ui_context.hash_active       = node->hash;
          ui_context.hash_active_depth = node->depth;
        }
      }
    }
    if (input_is_button_up(&g_input, Mouse_Button_Left) && input_was_button_down(&g_input, Mouse_Button_Left))
    {
      ui_context.hash_active = 0;
      ui_context.hash_active_depth = 1.0f;
    }

    // Dragging
    if (ui_context.hash_active == node->hash)
    {
      if (HasFlags(node->flags, UI_Node_Flags_Draggable))
      {
        node->local_drag_offset = g_input.mouse_current.delta;
      }
    }
  }

  return node;
}

function void
ui_fill_signals_from_node(UI_Signal* signal)
{
  if (ui_is_mouse_in_node(signal->node))
  {
    if (input_is_button_down(&g_input, Mouse_Button_Left))      SetFlags(signal->flags, UI_Signal_Flags_Left_Down);
    if (input_is_button_down(&g_input, Mouse_Button_Middle))    SetFlags(signal->flags, UI_Signal_Flags_Middle_Down);
    if (input_is_button_down(&g_input, Mouse_Button_Right))     SetFlags(signal->flags, UI_Signal_Flags_Right_Down);
    
    if (input_is_button_clicked(&g_input, Mouse_Button_Left))   SetFlags(signal->flags, UI_Signal_Flags_Left_Clicked);
    if (input_is_button_clicked(&g_input, Mouse_Button_Middle)) SetFlags(signal->flags, UI_Signal_Flags_Middle_Clicked);
    if (input_is_button_clicked(&g_input, Mouse_Button_Right))  SetFlags(signal->flags, UI_Signal_Flags_Right_Clicked);

    SetFlags(signal->flags, UI_Signal_Flags_Mouse_Hovered);
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
  local_persist Color colors[] =
  {
    {1.0f, 0.0f, 0.0f, 1.0f}, // RED
    {0.0f, 1.0f, 0.0f, 1.0f}, // GREEN
    {0.0f, 0.0f, 1.0f, 1.0f}, // BLUE
    {1.0f, 1.0f, 0.0f, 1.0f}, // YELLOW
    {0.0f, 1.0f, 1.0f, 1.0f}, // CYAN
    {1.0f, 0.0f, 1.0f, 1.0f}, // MAGENTA
    {1.0f, 1.0f, 1.0f, 1.0f}, // WHITE
    {0.0f, 0.0f, 0.0f, 1.0f}, // BLACK
    {0.5f, 0.5f, 0.5f, 1.0f}, // GRAY
    {1.0f, 0.5f, 0.0f, 1.0f}, // ORANGE
    {0.5f, 0.0f, 0.5f, 1.0f}, // PURPLE
    {0.6f, 0.4f, 0.2f, 1.0f}, // BROWN
    {1.0f, 0.75f, 0.8f, 1.0f} // PINK
  };
  Color color = colors[(debug_color_index++)%ArrayCount(colors)];

  if (ui_context.debug.show_cursor)
  {
    r_draw_point(vec2f32_add(node->clip.top_left, node->cursor), color, depth - (F32_EPSILON*2));
  }

  if (ui_context.debug.show_bounds)
  {
    r_draw_box(node->bounds.top_left, node->bounds.size, color, depth - (F32_EPSILON*2));
  }

  if (ui_context.debug.show_clip)
  {
    r_draw_box(node->clip.top_left, node->clip.size, color, depth - (F32_EPSILON*2));
  }

  if (ui_context.debug.show_text_borders)
  {
    if (HasFlags(node->flags, UI_Node_Flags_Text_Display))
    {
      r_draw_box(node->string_bounds.top_left, node->string_bounds.size, color, 0);
    }
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
  UI_Node_Cache* cached_node = ui_get_cached_node(node->hash);

  Rectf32 bounds = node->bounds;
  bounds.top_left = vec2f32_add(node->bounds.top_left, cached_node->accumulated_drag_offset);

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
    emit_fatal(S("UI: Too many UI_Nodes"));
  }

  UI_Node_Cache* cached_node = &ui_cached_nodes[ui_cached_nodes_count];

  cached_node->hash = hash;
  cached_node->hash = hash;
  cached_node->accumulated_drag_offset = vec2f32(0,0);
  cached_node->hover_t = 0;
  cached_node->active_t = 0;

  ui_cached_nodes_count += 1;

  return cached_node;
}

// Node tree
function void
ui_add_node_child(UI_Node *parent, UI_Node *child)
{
  if (parent == &ui_node_nil_sentinel)
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

function b32
ui_find_first_drag_offset(UI_Node* node, Vec2f32* out_offset)
{
  b32 result = false;
  if (HasFlags(node->flags, UI_Node_Flags_Draggable) && ui_context.hash_active == node->hash)
  {
    *out_offset = node->local_drag_offset;
    result = true;
  }
  else
  {
    for (UI_Node* child = node->first; child; child = child->next)
    {
      if (HasFlags(child->flags, UI_Node_Flags_Draggable) && ui_context.hash_active == child->hash)
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

function void
ui_apply_drag_offset(UI_Node* node, Vec2f32 offset)
{
  node->local_drag_offset = offset;
  for (UI_Node* child = node->first; child; child = child->next)
  {
    ui_apply_drag_offset(child, offset);
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
  printf("NODE("S_FMT"), Bounds: {TL: %.2f, %.2f - S: %.2f, %.2f} Clip: {TL: %.2f, %.2f - S: %.2f, %.2f} Text: {TL: %.2f, %.2f - S: %.2f, %.2f}\n",
    S_ARG(node->string_clean),
    node->bounds.top_left.x, node->bounds.top_left.y,
    node->bounds.size.x,     node->bounds.size.y,
    node->clip.top_left.x,   node->clip.top_left.y,
    node->clip.size.x,       node->clip.size.y,
    node->string_bounds.top_left.x,   node->string_bounds.top_left.y,
    node->string_bounds.size.x, node->string_bounds.size.y);

  // Children
  for (UI_Node *child = node->first; child; child = child->next)
  {
    ui_print_tree_impl(child, depth + 1);
  }
}