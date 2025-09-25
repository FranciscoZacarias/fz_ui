#ifndef UI_H
#define UI_H

#define ui_stack(type, name, size) struct { type data[size]; u32 top_index; type  bottom_val; } name##_stack
#define ui_stack_init(name, bot_val) Statement((ui_context.name##_stack).top_index = 0; (ui_context.name##_stack).bottom_val = (bot_val);)
#define ui_stack_push(name, val) Statement(if ((ui_context.name##_stack).top_index < (sizeof((ui_context.name##_stack).data)/sizeof((ui_context.name##_stack).data[0]))) (ui_context.name##_stack).data[(ui_context.name##_stack).top_index++] = (val);)
#define ui_stack_pop(name) (((ui_context.name##_stack).top_index > 0) ? (ui_context.name##_stack).data[--(ui_context.name##_stack).top_index] : (ui_context.name##_stack).bottom_val)
#define ui_stack_top(name) (((ui_context.name##_stack).top_index > 0) ? (ui_context.name##_stack).data[(ui_context.name##_stack).top_index-1] : (ui_context.name##_stack).bottom_val)
#define ui_stack_assert_top_at(name, at) if(!(ui_context.name##_stack).top_index == (at)) emit_fatal(S("Stack not at expected top"))

typedef u32 UI_Widget_Flags;
enum
{
  UI_Widget_Flags_Mouse_Clickable = (1<<0),
  UI_Widget_Flags_Title_Bar       = (1<<1),
  UI_Widget_Flags_Display_String  = (1<<2),
};

typedef u32 UI_Signal_Flags;
enum
{
  UI_Signal_Flags_Left_Down   = (1<<0),
  UI_Signal_Flags_Middle_Down = (1<<1),
  UI_Signal_Flags_Right_Down  = (1<<2),

  UI_Signal_Flags_Left_Clicked   = (1<<3),
  UI_Signal_Flags_Middle_Clicked = (1<<4),
  UI_Signal_Flags_Right_Clicked  = (1<<5),
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
  Rectf32 bounds;  /* Container rectangle drawing bounds */
  Rectf32 clip;    /* Clipping rectangle for children */
  Vec2f32 cursor;  /* Next position to draw - Relative to widget->clip */
  Vec2f32 padding; /* Padding in each direction */

  u64 depth; /* Keeps track of that's in front. Higher number means closer to the camera. 0 is root */
};

typedef struct UI_Signal UI_Signal;
struct UI_Signal
{
  UI_Widget* widget;
  UI_Signal_Flags flags;
};

#define UI_STACKS_MAX 32
typedef struct UI_Context UI_Context;
struct UI_Context
{
  // Cross frame 
  Arena* arena;

  // Per frame
  Arena* frame_arena;
  UI_Widget* root;

  // State
  ui_stack(UI_Widget*, parent,    UI_STACKS_MAX);
  ui_stack(Vec2f32,    top_left,  UI_STACKS_MAX);
  ui_stack(Vec2f32,    size,      UI_STACKS_MAX);
  ui_stack(Vec2f32,    padding,   UI_STACKS_MAX);
  u32 depth;

  b32 is_initialized; /* Has ui_init been called */
  b32 is_working;     /* If true, ui_begin() was last called. If false, ui_end() was last called */
};

global UI_Context ui_context;

// Core functions
function void ui_init();
function void ui_begin();
function void ui_end();

// UI module api
#define  ui_window(text) DeferLoop(ui_window_begin((text)), ui_window_end())
function UI_Widget* ui_window_begin(String8 text);
function void       ui_window_end();

// Builder code
function UI_Widget* ui_widget_from_string(String8 string, UI_Widget_Flags flags);
function UI_Signal  ui_signal_from_widget(UI_Widget* widget);

// Helper
function String8 ui_clean_string(Arena* arena, String8 string);
function void    ui_debug_draw_widget_cursor(UI_Widget* widget, Color color);
function void    ui_debug_draw_widget(UI_Widget* widget);

// Widget tree
function void ui_add_widget_child(UI_Widget *parent, UI_Widget *child);

#endif // UI_H