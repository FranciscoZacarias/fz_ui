
// Core functions
function void ui_init()
{
  AssertNoReentry();

  MemoryZeroStruct(&ui_context);
  {
    ui_context.arena          = arena_alloc();
    ui_context.frame_arena    = arena_alloc();
    ui_context.is_initialized = true;

    ui_context.debug.show_bounds = true;
    ui_context.debug.show_clip = true;
    ui_context.debug.show_cursor = false;

    ui_stack_init(top_left, vec2f32(10.0f, 10.0f));
    ui_stack_init(size_x, 200.0f);
    ui_stack_init(size_y, 300.0f);
    ui_stack_init(padding_x, 0.0f);
    ui_stack_init(padding_y, 0.0f);
    ui_stack_init(spacing_x, 0);
    ui_stack_init(spacing_y, 0);
    ui_stack_init(background_color, BLACK(1));
    ui_stack_init(text_color, WHITE(1));
    ui_stack_init(text_height, 16);
    ui_stack_init(alignment, UI_Alignment_Y);
  }
}

function void ui_begin()
{
  ui_context.is_working = true;
  
  // Window widget
  {
    String8 root_name = S("##Root Window Widget");
    Vec2s32 window_size = g_os_window.dimensions;
    ui_context.root = push_array(ui_context.frame_arena, UI_Widget, 1);
    ui_context.root->hash      = string8_hash(root_name);
    ui_context.root->bounds    = rectf32(vec2f32(0,0), vec2f32(window_size.x, window_size.y));
    ui_context.root->clip      = rectf32(vec2f32(0,0), vec2f32(window_size.x, window_size.y));
    ui_context.root->cursor    = vec2f32(0.0f, 0.0f);
    ui_context.root->depth     = 1;

    ui_stack_push(widget, ui_context.root);
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
}

function void ui_end()
{
#if DEBUG
  ui_stack_assert_top_at(widget, 1);
  ui_stack_assert_top_at(top_left, 0);
  ui_stack_assert_top_at(size_x, 0);
  ui_stack_assert_top_at(size_y, 0);
  ui_stack_assert_top_at(padding_x, 0);
  ui_stack_assert_top_at(padding_y, 0);
  ui_stack_assert_top_at(background_color, 0);
  ui_stack_assert_top_at(text_color, 0);
  ui_stack_assert_top_at(text_height, 0);
  Assert(ui_context.root->depth == 1);
#endif

  ui_render_widget(ui_context.root);

  // Reset tree
  ui_context.root->first    = NULL;
  ui_context.root->last     = NULL;
  ui_context.root->next     = NULL;
  ui_context.root->previous = NULL;
  ui_context.root->parent   = NULL;

  ui_stack_pop(widget); // Pop root (os window) because it's regenerated every frame
  ui_context.is_working = false;
  arena_clear(ui_context.frame_arena);
}

function void
ui_render_widget(UI_Widget* widget)
{
  if (ui_context.root != widget)
  {
    r_draw_quad(widget->bounds.top_left, widget->bounds.size, 0, widget->background_color, widget->depth);
    if (HasFlags(widget->flags, UI_Widget_Flags_Display_String))
    {
      r_draw_text(widget->string_top_left, widget->text_pixel_height, widget->text_color, widget->string, widget->depth - F32_EPSILON);
    }
    ui_debug_draw_widget(widget);
  }

  for (UI_Widget *child = widget->first; child; child = child->next)
  {
    ui_render_widget(child);
  }
}

// UI module api
function void
ui_window_begin(String8 text)
{
  Scratch scratch = scratch_begin(0,0);

  String8 window_string = Sf(scratch.arena, "##window_text_"S_FMT"", S_ARG(text));

  ui_stack_defer(padding_x, 4.0f)
  ui_stack_defer(padding_y, 4.0f)
  {
    UI_Widget_Flags window_flags = 0;    
    UI_Widget* window_widget = ui_widget_from_string(window_string, window_flags);
    UI_Signal  window_signal = ui_signal_from_widget(window_widget);
    ui_stack_push(widget, window_widget);
  }

  ui_stack_defer(spacing_x, 2.0f)
  ui_stack_defer(background_color, GRAY(1))
  ui_stack_defer(size_y, 20.0f)
  {
    UI_Widget_Flags title_bar_flags = UI_Widget_Flags_Mouse_Clickable|UI_Widget_Flags_Display_String;
    UI_Widget* title_bar_widget = ui_widget_from_string(text, title_bar_flags);
    UI_Signal  title_bar_signal = ui_signal_from_widget(title_bar_widget);
  }

  scratch_end(&scratch);
}

function void
ui_window_end()
{
  ui_stack_pop(widget);
}

// Builder code
function UI_Widget*
ui_widget_from_string(String8 string, UI_Widget_Flags flags)
{
  if (!ui_context.is_initialized)
  {
    emit_fatal(S("Did not unit UI"));
  }
  if (!ui_context.is_working)
  {
    emit_fatal(S("Not within ui_begin and ui_end"));
  }

  UI_Widget* parent = ui_stack_top(widget);
  UI_Widget* widget = push_array(ui_context.frame_arena, UI_Widget, 1);
  ui_add_widget_child(parent, widget);

  Vec2f32 top_left  = ui_stack_top(top_left);
  f32 size_x        = ui_stack_top(size_x);
  f32 size_y        = ui_stack_top(size_y);
  f32 padding_x     = ui_stack_top(padding_x);
  f32 padding_y     = ui_stack_top(padding_y);
  f32 spacing_x     = ui_stack_top(spacing_x);
  f32 spacing_y     = ui_stack_top(spacing_y);

  widget->hash    = string8_hash(string);
  widget->bounds  = ui_clip_rect(parent->clip, rectf32(top_left, vec2f32(size_x, size_y)));
  
  Rectf32 clip;
  clip.top_left = vec2f32(widget->bounds.top_left.x + padding_x, widget->bounds.top_left.y + padding_y);
  clip.size     = vec2f32(widget->bounds.size.x - (padding_x * 2), widget->bounds.size.y - (padding_y * 2));
  widget->clip  = ui_clip_rect(widget->bounds, clip);

  widget->padding_x = padding_x;
  widget->padding_y = padding_y;

  widget->cursor.x = widget->cursor.x + spacing_x;
  widget->cursor.y = widget->cursor.y + spacing_y;

  widget->depth  = (parent) ? parent->depth - F32_EPSILON : 1.0f;
  widget->flags  = flags;

  // Update parent 
  if (parent != ui_context.root)
  {
    UI_Alignment alignment = ui_stack_top(alignment);
    switch (alignment)
    {
      case UI_Alignment_Y:
      {
        parent->clip.top_left.y = parent->clip.top_left.y + size_y;
        parent->clip.size.y     = parent->clip.size.y - size_y;
      } break;
      default:
      {
        emit_fatal(S("Unhandled UI_Alignment"));
      };
    }
  }

  // Style
  widget->background_color = ui_stack_top(background_color);
  if (HasFlags(flags, UI_Widget_Flags_Display_String))
  {
    widget->string            = string;
    widget->string_top_left   = vec2f32_add(widget->clip.top_left, widget->cursor);
    widget->text_pixel_height = ui_stack_top(text_height);
    widget->text_color        = ui_stack_top(text_color);

    // TODO(fz): Dimensions could be cached
    widget->string_dimensions = r_text_dimensions(widget->string, widget->text_pixel_height);
    widget->cursor.x = widget->cursor.x + widget->string_dimensions.x + widget->padding_x;
  }

  if (HasFlags(flags, UI_Widget_Flags_Mouse_Clickable))
  {
    if (ui_mouse_in_rect(widget->bounds))
    {
      widget->background_color = BLUE(1);
    }
  }

  return widget;
}

function UI_Signal
ui_signal_from_widget(UI_Widget* widget)
{
  UI_Signal signal = (UI_Signal){0};

  if (ui_mouse_in_rect(widget->bounds))
  {
    SetFlags(signal.flags, UI_Signal_Flags_Mouse_Hovered);

    if (input_is_button_down(&g_input, Mouse_Button_Left))      SetFlags(signal.flags, UI_Signal_Flags_Left_Clicked);
    if (input_is_button_down(&g_input, Mouse_Button_Middle))    SetFlags(signal.flags, UI_Signal_Flags_Middle_Clicked);
    if (input_is_button_down(&g_input, Mouse_Button_Right))     SetFlags(signal.flags, UI_Signal_Flags_Right_Clicked);
    
    if (input_is_button_clicked(&g_input, Mouse_Button_Left))   SetFlags(signal.flags, UI_Signal_Flags_Left_Clicked);
    if (input_is_button_clicked(&g_input, Mouse_Button_Middle)) SetFlags(signal.flags, UI_Signal_Flags_Middle_Clicked);
    if (input_is_button_clicked(&g_input, Mouse_Button_Right))  SetFlags(signal.flags, UI_Signal_Flags_Right_Clicked);
  }

  return signal;
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
ui_debug_draw_widget(UI_Widget* widget)
{
  if (ui_context.debug.show_cursor) r_draw_point(vec2f32_add(widget->clip.top_left, widget->cursor), GREEN(1), widget->depth - (F32_EPSILON*3));
  if (ui_context.debug.show_bounds) r_draw_box(widget->bounds.top_left, widget->bounds.size, RED(1), widget->depth - F32_EPSILON);
  if (ui_context.debug.show_clip)   r_draw_box(widget->clip.top_left, widget->clip.size, YELLOW(1), widget->depth - (F32_EPSILON*2));
}

function Rectf32
ui_clip_rect(Rectf32 parent, Rectf32 child)
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
ui_mouse_in_rect(Rectf32 rect)
{
  Vec2f32 mouse = g_input.mouse_current.screen_space;
  b32 result = (mouse.x >= rect.top_left.x && mouse.x <= rect.top_left.x + rect.size.x &&
                mouse.y >= rect.top_left.y && mouse.y <= rect.top_left.y + rect.size.y);
  return result;
}

function UI_Cache*
ui_get_cached_widget(UI_Widget* widget)
{
  UI_Cache* cached_widget = NULL;

  for (u32 i = 0; i < ui_cached_widgets_count; i += 1)
  {
    if (ui_cached_widgets[i].hash == widget->hash)
    {
      cached_widget = &ui_cached_widgets[i];
      break;
    }
  }

  if (cached_widget == NULL)
  {
    if (ui_cached_widgets_count >= UI_MAX_CACHED_WIDGETS)
    {
      emit_fatal(S("Too many widgets"));
    }

    cached_widget->hash   = widget->hash;
    cached_widget->bounds = widget->bounds;
    cached_widget->clip   = widget->clip;
    cached_widget->cursor = widget->cursor;

    ui_cached_widgets_count += 1;
  }

  return cached_widget;
}

// Widget tree
function void
ui_add_widget_child(UI_Widget *parent, UI_Widget *child)
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
