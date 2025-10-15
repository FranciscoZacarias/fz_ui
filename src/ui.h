#ifndef UI_H
#define UI_H

// Stack functions
#define ui_stack(type, name, size) struct { type data[size]; u32 top_index; type  bottom_val; } name##_stack
#define ui_stack_init(name, bot_val) Statement((ui_context.name##_stack).top_index = 0; (ui_context.name##_stack).bottom_val = (bot_val);)
#define ui_stack_push(name, val) ((ui_context.name##_stack).data[((ui_context.name##_stack).top_index < sizeof((ui_context.name##_stack).data)/sizeof((ui_context.name##_stack).data[0])) ? (ui_context.name##_stack).top_index++ : (ui_context.name##_stack).top_index] = (val))
#define ui_stack_pop(name) (((ui_context.name##_stack).top_index > 0) ? (ui_context.name##_stack).data[--(ui_context.name##_stack).top_index] : (ui_context.name##_stack).bottom_val)
#define ui_stack_top(name) (((ui_context.name##_stack).top_index > 0) ? (ui_context.name##_stack).data[(ui_context.name##_stack).top_index-1] : (ui_context.name##_stack).bottom_val)
#define ui_stack_assert_top_at(name, at) if((ui_context.name##_stack).top_index != (at)) emit_fatal(Sf(ui_context.arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify((ui_context.name##_stack)), (at), (ui_context.name##_stack).top_index))
#define ui_stack_is_at_bottom(name) ((ui_context.name##_stack).top_index == 0)
#define ui_stack_defer(name, val) DeferLoop(ui_stack_push(name, val), ui_stack_pop(name))

#include "ui.hephaestus.h"

// Color schemes
typedef struct UI_Node_Color_Scheme UI_Node_Color_Scheme;
struct UI_Node_Color_Scheme
{
  Color border_color;

  Color background_color;
  Color background_hover_color;
  Color background_active_color;

  Color text_color;
  Color text_hover_color;
  Color text_active_color;
};

typedef struct UI_Color_Scheme UI_Color_Scheme;
struct UI_Color_Scheme 
{
  UI_Node_Color_Scheme title_bar;
  UI_Node_Color_Scheme window;
  UI_Node_Color_Scheme button;
};

global UI_Color_Scheme ui_color_scheme_dark;
global UI_Color_Scheme ui_color_scheme_high_contrast;

typedef struct UI_Node UI_Node;
struct UI_Node
{
  // Node tree
  UI_Node* first; /* First child */
  UI_Node* last;  /* Last child */
  UI_Node* next;  /* Next child, after current node */
  UI_Node* previous; /* Previous child, before current node */
  UI_Node* parent;   /* Parent of current node */

  u64 hash;

  // Node Settings
  Rectf32 bounds;  /* Container rectangle drawing bounds - Absolute values */
  Rectf32 clip;    /* Clipping rectangle for children - Absolute values */
  Vec2f32 cursor;  /* Next position to draw - Relative to node->clip */
  UI_Alignment_Kind alignment_kind; /* Where the cursor will shift to */
  f32 depth; /* Keeps track of that's in front. Smaller number means closer to the camera. 1 is root */
  UI_Node_Flags flags; /* Behaviour for this node */
  Vec2f32 local_drag_offset; /* How much it was offseted this frame */

  // Style
  UI_Node_Color_Scheme node_color_scheme;
  Color target_background_color;
  Color target_text_color;

  // String stuff
  String8 string;
  String8 string_clean; /* String with everything after ## stripped */
  Vec2f32 string_top_left; /* Relative to cursor */
  Vec2f32 string_dimensions; 
  f32 text_pixel_height;
};

typedef struct UI_Node_Cache UI_Node_Cache;
struct UI_Node_Cache
{
  u64 hash;

  Vec2f32 accumulated_drag_offset; /* How much it has been offseted in total */

  f32 hover_t;
  f32 active_t;
};

#define UI_MAX_CACHED_NODES 16
global UI_Node_Cache ui_cached_nodes[UI_MAX_CACHED_NODES];
global u32 ui_cached_nodes_count = 0;

typedef struct UI_Signal UI_Signal;
struct UI_Signal
{
  UI_Node* node;
  UI_Signal_Flags flags;
};

#define UI_STACKS_MAX 8
typedef struct UI_Context UI_Context;
struct UI_Context
{
  // Per frame
  Arena* frame_arena;
  UI_Node* root;

  // Cross frame 
  Arena* arena;

  u64 hash_active;
  f32 hash_active_depth;
  u64 hash_hot;
  f32 hash_hot_depth;

  UI_Color_Scheme color_scheme;

  // State
  u32 text_pixel_height;
  f32 animation_speed;
  b32 is_initialized; /* Has ui_init been called */
  b32 is_working;     /* If true, ui_begin() was last called. If false, ui_end() was last called */

  UI_Config_Stacks;

  // Debug
  struct
  {
    b32 show_bounds : 1;
    b32 show_clip   : 1;
    b32 show_cursor : 1;
    b32 print_node_tree: 1;
    b32 show_text_borders: 1;
  } debug;
};

global u32 debug_color_index = 0;

// Used as a bottom value for UI_Node stack, since bottom value is a pointer.
read_only global UI_Node ui_node_nil_sentinel =
{
  .first    = &ui_node_nil_sentinel,
  .last     = &ui_node_nil_sentinel,
  .next     = &ui_node_nil_sentinel,
  .previous = &ui_node_nil_sentinel,
  .parent   = &ui_node_nil_sentinel,
};

global UI_Context ui_context;

// Core functions
function void ui_init();
function void ui_begin();
function void ui_end();

// UI Widgets
// -------------------
#define  ui_window(text) DeferLoop(ui_window_begin((text)), ui_window_end())
function void ui_window_begin(String8 text);
function void ui_window_end();

#define  ui_row(text,height)   DeferLoop(ui_layout_begin(UI_Alignment_Kind_X, (height), (text)), ui_layout_end())
#define  ui_column(text,width) DeferLoop(ui_layout_begin(UI_Alignment_Kind_Y, (width),  (text)), ui_layout_end())
function void ui_layout_begin(UI_Alignment_Kind alignment, f32 size, String8 text);
function void ui_layout_end();

// Builder code
// -------------------
function UI_Node*  ui_node_from_string(String8 string, UI_Node_Flags flags);
function void      ui_fill_signals_from_node(UI_Signal* signal); /* Signal in argument must contain the node already attached to it */
function b32       ui_find_first_drag_offset(UI_Node* widget_root, Vec2f32* out_offset);
function void      ui_apply_drag_offset(UI_Node* widget_root, Vec2f32 offset);

// Helper
function void           ui_render_ui_tree(UI_Node* widget_root);
function void           ui_debug_draw_node(UI_Node* widget, f32 depth);
function String8        ui_clean_string(Arena* arena, String8 string);
function Rectf32        ui_clamp_rect(Rectf32 parent, Rectf32 child);
function b32            ui_is_mouse_in_node(UI_Node* node);
function UI_Node_Cache* ui_get_cached_node(u64 hash);

// Widget tree
function void ui_add_node_child(UI_Node *parent, UI_Node *child);
function void ui_update_tree_nodes(UI_Node* node);
#define  ui_print_tree(root) ui_print_tree_impl(root, 0)
function void ui_print_tree_impl(UI_Node* node, u32 depth);

#endif // UI_H