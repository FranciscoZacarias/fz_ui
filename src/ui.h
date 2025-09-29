#ifndef UI_H
#define UI_H

#define ui_stack(type, name, size) struct { type data[size]; u32 top_index; type  bottom_val; } name##_stack
#define ui_stack_init(name, bot_val) Statement((ui_context.name##_stack).top_index = 0; (ui_context.name##_stack).bottom_val = (bot_val);)
#define ui_stack_push(name, val) ((ui_context.name##_stack).data[((ui_context.name##_stack).top_index < sizeof((ui_context.name##_stack).data)/sizeof((ui_context.name##_stack).data[0])) ? (ui_context.name##_stack).top_index++ : (ui_context.name##_stack).top_index] = (val))
#define ui_stack_pop(name) (((ui_context.name##_stack).top_index > 0) ? (ui_context.name##_stack).data[--(ui_context.name##_stack).top_index] : (ui_context.name##_stack).bottom_val)
#define ui_stack_top(name) (((ui_context.name##_stack).top_index > 0) ? (ui_context.name##_stack).data[(ui_context.name##_stack).top_index-1] : (ui_context.name##_stack).bottom_val)
#define ui_stack_assert_top_at(name, at) if((ui_context.name##_stack).top_index != (at)) emit_fatal(Sf(ui_context.arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify((ui_context.name##_stack)), (at), (ui_context.name##_stack).top_index))
#define ui_stack_is_at_bottom(name) ((ui_context.name##_stack).top_index == 0)
#define ui_stack_defer(name, val) DeferLoop(ui_stack_push(name, val), ui_stack_pop(name))
#define ui_stack_defer_if_default(name,val) DeferLoop((ui_context.name##_stack.top_index == 0) && (ui_stack_push(name,val),1), (ui_stack_pop(name)))

typedef u32 UI_Widget_Flags;
enum
{
  UI_Widget_Flags_Mouse_Clickable = (1<<0),
  UI_Widget_Flags_Display_String  = (1<<1),
  UI_Widget_Flags_Draggable = (1<<2),
  UI_Widget_Flags_Hoverable = (1<<3),
};

typedef u64 UI_Signal_Flags;
enum
{
  UI_Signal_Flags_Left_Down   = (1<<0),
  UI_Signal_Flags_Middle_Down = (1<<1),
  UI_Signal_Flags_Right_Down  = (1<<2),

  UI_Signal_Flags_Left_Clicked   = (1<<3),
  UI_Signal_Flags_Middle_Clicked = (1<<4),
  UI_Signal_Flags_Right_Clicked  = (1<<5),

  UI_Signal_Flags_Mouse_Hovered  = (1<<6),
};

typedef enum
{
  UI_Alignment_Kind_None = 0,
  UI_Alignment_Kind_X,
  UI_Alignment_Kind_Y,
  UI_Alignment_Kind_Floating,
} UI_Alignment_Kind;

typedef enum
{
  UI_Width_Kind_Fill,
  UI_Width_Kind_Fixed
} UI_Width_Kind;

typedef enum
{
  UI_Height_Kind_Fill,
  UI_Height_Kind_Fixed
} UI_Height_Kind;

typedef struct UI_Color_Scheme UI_Color_Scheme;
struct UI_Color_Scheme
{
  Color background_color;
  Color title_bar_color;
  Color text_color;
  Color border_color;
};

typedef struct UI_Widget UI_Widget;
struct UI_Widget
{
  u64 hash;

  // Widget tree
  UI_Widget* first; /* First child */
  UI_Widget* last;  /* Last child */
  UI_Widget* next;  /* Next child, after current widget */
  UI_Widget* previous; /* Previous child, before current widget */
  UI_Widget* parent;   /* Parent of current widget */

  // Widget Settings
  Rectf32 bounds;  /* Container rectangle drawing bounds - Absolute values */
  Rectf32 clip;    /* Clipping rectangle for children - Absolute values */
  Vec2f32 cursor;  /* Next position to draw - Relative to widget->clip */
  f32 padding_x;
  f32 padding_y;
  f32 spacing_x;
  f32 spacing_y;
  UI_Alignment_Kind alignment_kind;
  f32 depth; /* Keeps track of that's in front. Smaller number means closer to the camera. 1 is root */
  UI_Widget_Flags flags;
  Vec2f32 local_drag_offset; /* How much it was offseted this frame */

  // Style
  Color target_background_color;
  Color target_text_color;

  // String stuff
  String8 string;
  Vec2f32 string_top_left;
  Vec2f32 string_dimensions;
  f32 text_pixel_height;
};

typedef struct UI_Widget_Cache UI_Widget_Cache;
struct UI_Widget_Cache
{
  u64 hash;

  Vec2f32 accumulated_drag_offset; /* How much it has been offseted in total */

  f32 hover_t;
  f32 active_t;
};

#define UI_MAX_CACHED_WIDGETS 16
global UI_Widget_Cache ui_cached_widgets[UI_MAX_CACHED_WIDGETS];
global u32 ui_cached_widgets_count = 0;

typedef struct UI_Signal UI_Signal;
struct UI_Signal
{
  UI_Widget* widget;
  UI_Signal_Flags flags;
};

#define UI_STACKS_MAX 8
typedef struct UI_Context UI_Context;
struct UI_Context
{
  // Per frame
  Arena* frame_arena;
  UI_Widget* root;

  // Cross frame 
  Arena* arena;

  u64 hash_active;
  f32 hash_active_depth;
  u64 hash_hot;
  f32 hash_hot_depth;

  // State
  ui_stack(UI_Widget*,        widget,           UI_STACKS_MAX);
  ui_stack(Vec2f32,           top_left,         UI_STACKS_MAX);
  ui_stack(f32,               size_x,           UI_STACKS_MAX);
  ui_stack(f32,               size_y,           UI_STACKS_MAX);
  ui_stack(f32,               padding_x,        UI_STACKS_MAX);
  ui_stack(f32,               padding_y,        UI_STACKS_MAX);
  ui_stack(f32,               spacing_x,        UI_STACKS_MAX); /* Spacing does not count towards the clip calculation */
  ui_stack(f32,               spacing_y,        UI_STACKS_MAX); /* Spacing does not count towards the clip calculation */
  ui_stack(f32,               text_height,      UI_STACKS_MAX);
  ui_stack(UI_Alignment_Kind, alignment_kind,   UI_STACKS_MAX);
  ui_stack(UI_Width_Kind,     width_kind,       UI_STACKS_MAX);
  ui_stack(UI_Height_Kind,    height_kind,      UI_STACKS_MAX);
  ui_stack(Color,             background_color, UI_STACKS_MAX);
  ui_stack(Color,             text_color,       UI_STACKS_MAX);
  ui_stack(Color,             hover_color,      UI_STACKS_MAX);
  ui_stack(Color,             active_color,     UI_STACKS_MAX);

  f32 animation_speed;

  b32 is_initialized; /* Has ui_init been called */
  b32 is_working;     /* If true, ui_begin() was last called. If false, ui_end() was last called */

  // Debug
  struct
  {
    b32 show_bounds : 1;
    b32 show_clip   : 1;
    b32 show_cursor : 1;
    b32 print_widget: 1;
  } debug;
};

global UI_Context ui_context;

// Core functions
function void ui_init();
function void ui_begin();
function void ui_end();
function void ui_render_widget(UI_Widget* widget);

// UI module api
#define  ui_window(text) DeferLoop(ui_window_begin((text)), ui_window_end())
function void ui_window_begin(String8 text);
function void ui_window_end();

// Builder code
function UI_Widget* ui_widget_from_string(String8 string, UI_Widget_Flags flags);
function UI_Signal  ui_signal_from_widget(UI_Widget* widget);
function void       ui_widget_end(UI_Widget* root);

// Helper
function String8    ui_clean_string(Arena* arena, String8 string);
function void       ui_debug_draw_widget(UI_Widget* widget, f32 depth);
function Rectf32    ui_clamp_rect(Rectf32 parent, Rectf32 child);
function b32        ui_is_mouse_in_widget(UI_Widget* widget);
function UI_Widget_Cache* ui_get_cached_widget(u64 hash);

// Widget tree
function void ui_add_widget_child(UI_Widget *parent, UI_Widget *child);
function b32  ui_find_first_drag_offset(UI_Widget* widget, Vec2f32* out_offset);
function void ui_apply_drag_offset(UI_Widget* widget, Vec2f32 offset);
function void ui_update_tree_widgets(UI_Widget* widget);
function void ui_print_tree(UI_Widget* widget, u32 depth);


#endif // UI_H