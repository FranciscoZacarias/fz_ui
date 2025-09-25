
// Core functions
function void ui_init()
{
  AssertNoReentry();

  MemoryZeroStruct(&ui_context);
  {
    ui_context.arena          = arena_alloc();
    ui_context.frame_arena    = arena_alloc();
    ui_context.is_initialized = true;

    ui_stack_init(top_left, vec2f32(10.0f, 10.0f));
    ui_stack_init(size, vec2f32(200.0f, 300.0f));
    ui_stack_init(padding, vec2f32(4.0f,4.0f));
  }
}

function void ui_begin()
{
  ui_context.is_working  = true;
  
  // Window widget
  {
    String8 root_name = S("##Root Window Widget");
    Vec2s32 window_size = g_os_window.dimensions;
    ui_context.root = push_array(ui_context.frame_arena, UI_Widget, 1);
    ui_context.root->hash    = string8_hash(root_name);
    ui_context.root->bounds  = rectf32(vec2f32(0,0), vec2f32(window_size.x, window_size.y));
    ui_context.root->clip    = rectf32(vec2f32(0,0), vec2f32(window_size.x, window_size.y));
    ui_context.root->cursor  = vec2f32(0.0f, 0.0f);
    ui_context.root->padding = vec2f32(0.0f, 0.0f);

    // Window widget is considered 0 depth
    ui_context.root->depth   = 0;
    ui_context.depth         = 0;

    ui_stack_push(parent, ui_context.root);
  }

  // Input handling
}

function void ui_end()
{
#if DEBUG
  ui_stack_assert_top_at(parent, 1);
  ui_stack_assert_top_at(top_left, 0);
  ui_stack_assert_top_at(size, 0);
  ui_stack_assert_top_at(padding, 0);

  Assert(ui_context.depth == 0);
  Assert(ui_context.root->depth == 0);
#endif

  ui_stack_pop(parent); // Pop root (os window) because it's regenerated every frame
  ui_context.is_working = false;
  arena_clear(ui_context.frame_arena);
}

// UI module api
function UI_Widget*
ui_window_begin(String8 text)
{
  UI_Widget_Flags flags = 0;

  UI_Widget* widget = ui_widget_from_string(text, flags);
  

  r_draw_quad(widget->bounds.top_left, widget->bounds.size, 0, BLACK(1));
  ui_debug_draw_widget(widget);

  return widget;
}

function void
ui_window_end()
{
  ui_context.depth -= 1;
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
  
  Vec2f32 top_left  = ui_stack_top(top_left);
  Vec2f32 size      = ui_stack_top(size);
  Vec2f32 padding   = ui_stack_top(padding);

  UI_Widget* widget = push_array(ui_context.frame_arena, UI_Widget, 1);

  widget->hash    = string8_hash(string);
  widget->bounds  = rectf32(top_left, size);
  widget->clip.top_left = vec2f32(widget->bounds.top_left.x + padding.x, widget->bounds.top_left.y + padding.y);
  widget->clip.size     = vec2f32(size.x - (padding.x * 2), size.y - (padding.y * 2));
  widget->cursor  = vec2f32(0.0f, 0.0f);
  widget->padding = padding;
  widget->depth   = ++ui_context.depth;

  UI_Widget* parent = ui_stack_top(parent);
  ui_add_widget_child(parent, widget);

  return widget;
}

function UI_Signal
ui_signal_from_widget(UI_Widget* widget)
{
  UI_Signal signal = (UI_Signal){0};

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
ui_debug_draw_widget_cursor(UI_Widget* widget, Color color)
{
  r_draw_point(vec2f32_add(widget->clip.top_left, widget->cursor), color);
}

function void
ui_debug_draw_widget(UI_Widget* widget)
{
  ui_debug_draw_widget_cursor(widget, YELLOW(1));
  r_draw_box(widget->bounds.top_left, widget->bounds.size, RED(1));
  r_draw_box(widget->clip.top_left, widget->clip.size, YELLOW(1));
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
