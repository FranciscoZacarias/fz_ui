#ifndef UI_GENERATED_H
#define UI_GENERATED_H

/*

@Hephaestus generated code 2025-October-10 12:08:04

*/

// Forward declare UI structures
typedef struct UI_Node_Color_Scheme UI_Node_Color_Scheme;
typedef struct UI_Color_Scheme UI_Color_Scheme;
typedef struct UI_Node UI_Node;
typedef struct UI_Node_Cache UI_Node_Cache;
typedef struct UI_Signal UI_Signal;
typedef struct UI_Context UI_Context;

// Forward declare UI enums
typedef enum UI_Alignment_Kind UI_Alignment_Kind;
typedef enum UI_Width_Kind UI_Width_Kind;
typedef enum UI_Height_Kind UI_Height_Kind;

typedef u64 UI_Node_Flags;
enum
{
  UI_Node_Flags_Mouse_Clickable = (1 << 0), /* TODO(fz): Add documentation */ 
  UI_Node_Flags_Display_Text = (1 << 1), /* TODO(fz): Add documentation */ 
  UI_Node_Flags_Draggable = (1 << 2), /* TODO(fz): Add documentation */ 
  UI_Node_Flags_Hoverable = (1 << 3), /* TODO(fz): Add documentation */ 
  UI_Node_Flags_Center_Text_Horizontally = (1 << 4), /* TODO(fz): Add documentation */ 
  UI_Node_Flags_Center_Text_Vertically = (1 << 5), /* TODO(fz): Add documentation */ 
  UI_Node_Flags_Dimensions_Wrap_Text = (1 << 6), /* TODO(fz): Add documentation */ 
};

typedef u64 UI_Node_Flags;
enum
{
  UI_Signal_Flags_Left_Down = (1 << 0), /* TODO(fz): Add documentation */
  UI_Signal_Flags_Middle_Down = (1 << 1), /* TODO(fz): Add documentation */
  UI_Signal_Flags_Right_Down = (1 << 2), /* TODO(fz): Add documentation */
  UI_Signal_Flags_Left_Clicked = (1 << 3), /* TODO(fz): Add documentation */
  UI_Signal_Flags_Middle_Clicked = (1 << 4), /* TODO(fz): Add documentation */
  UI_Signal_Flags_Right_Clicked = (1 << 5), /* TODO(fz): Add documentation */
  UI_Signal_Flags_Mouse_Hovered = (1 << 6), /* TODO(fz): Add documentation */
};

#define ui_stack_init(ctx, name, bot_val) Statement((ctx)->name##_stack.top_index = 0; (ctx)->name##_stack.bottom_val = (bot_val);)
#define ui_stack_push(ctx, name, val) ((ctx)->name##_stack.data[((ctx)->name##_stack.top_index < sizeof((ctx)->name##_stack.data)/sizeof((ctx)->name##_stack.data[0])) ? (ctx)->name##_stack.top_index++ : (ctx)->name##_stack.top_index] = (val))
#define ui_stack_pop(ctx, name) (((ctx)->name##_stack.top_index > 0) ? (ctx)->name##_stack.data[--(ctx)->name##_stack.top_index] : (ctx)->name##_stack.bottom_val)
#define ui_stack_top(ctx, name) (((ctx)->name##_stack.top_index > 0) ? (ctx)->name##_stack.data[(ctx)->name##_stack.top_index-1] : (ctx)->name##_stack.bottom_val)
#define ui_stack_assert_top_at(ctx, name, at) if((ctx)->name##_stack.top_index != (at)) emit_fatal(Sf((ctx)->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify((ctx)->name##_stack), (at), (ctx)->name##_stack.top_index))
#define ui_stack_is_at_bottom(ctx, name) ((ctx)->name##_stack.top_index == 0)
#define ui_stack_defer(ctx, name, val) DeferLoop(ui_stack_push(ctx, name, val), ui_stack_pop(ctx, name))

/* Pointer to the current UI node */
typedef struct UI_Node_stack UI_Node_stack;
struct UI_Node_stack { UI_Node* data[32]; u32 top_index; UI_Node* bottom_val; };
#define ui_node_stack_init(bot_val) ui_stack_init(&ui_context, node, bot_val)
#define ui_node_stack_push(val) ui_stack_push(&ui_context, node, val)
#define ui_node_stack_pop() ui_stack_pop(&ui_context, node)
#define ui_node_stack_top() ui_stack_top(&ui_context, node)
#define ui_node_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, node)
#define ui_node_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, node, at)
#define ui_set_node(val) DeferLoop(node_stack_push(val), node_stack_pop())

/* Top-left corner position */
typedef struct UI_Top_Left_stack UI_Top_Left_stack;
struct UI_Top_Left_stack { Vec2f32 data[32]; u32 top_index; Vec2f32 bottom_val; };
#define ui_top_left_stack_init(bot_val) ui_stack_init(&ui_context, top_left, bot_val)
#define ui_top_left_stack_push(val) ui_stack_push(&ui_context, top_left, val)
#define ui_top_left_stack_pop() ui_stack_pop(&ui_context, top_left)
#define ui_top_left_stack_top() ui_stack_top(&ui_context, top_left)
#define ui_top_left_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, top_left)
#define ui_top_left_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, top_left, at)
#define ui_set_top_left(val) DeferLoop(top_left_stack_push(val), top_left_stack_pop())

/* Default X size equals window width */
typedef struct UI_Size_X_stack UI_Size_X_stack;
struct UI_Size_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_size_x_stack_init(bot_val) ui_stack_init(&ui_context, size_x, bot_val)
#define ui_size_x_stack_push(val) ui_stack_push(&ui_context, size_x, val)
#define ui_size_x_stack_pop() ui_stack_pop(&ui_context, size_x)
#define ui_size_x_stack_top() ui_stack_top(&ui_context, size_x)
#define ui_size_x_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, size_x)
#define ui_size_x_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, size_x, at)
#define ui_set_size_x(val) DeferLoop(size_x_stack_push(val), size_x_stack_pop())

/* Default Y size equals window height */
typedef struct UI_Size_Y_stack UI_Size_Y_stack;
struct UI_Size_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_size_y_stack_init(bot_val) ui_stack_init(&ui_context, size_y, bot_val)
#define ui_size_y_stack_push(val) ui_stack_push(&ui_context, size_y, val)
#define ui_size_y_stack_pop() ui_stack_pop(&ui_context, size_y)
#define ui_size_y_stack_top() ui_stack_top(&ui_context, size_y)
#define ui_size_y_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, size_y)
#define ui_size_y_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, size_y, at)
#define ui_set_size_y(val) DeferLoop(size_y_stack_push(val), size_y_stack_pop())

/* Horizontal padding */
typedef struct UI_Padding_X_stack UI_Padding_X_stack;
struct UI_Padding_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_padding_x_stack_init(bot_val) ui_stack_init(&ui_context, padding_x, bot_val)
#define ui_padding_x_stack_push(val) ui_stack_push(&ui_context, padding_x, val)
#define ui_padding_x_stack_pop() ui_stack_pop(&ui_context, padding_x)
#define ui_padding_x_stack_top() ui_stack_top(&ui_context, padding_x)
#define ui_padding_x_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, padding_x)
#define ui_padding_x_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, padding_x, at)
#define ui_set_padding_x(val) DeferLoop(padding_x_stack_push(val), padding_x_stack_pop())

/* Vertical padding */
typedef struct UI_Padding_Y_stack UI_Padding_Y_stack;
struct UI_Padding_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_padding_y_stack_init(bot_val) ui_stack_init(&ui_context, padding_y, bot_val)
#define ui_padding_y_stack_push(val) ui_stack_push(&ui_context, padding_y, val)
#define ui_padding_y_stack_pop() ui_stack_pop(&ui_context, padding_y)
#define ui_padding_y_stack_top() ui_stack_top(&ui_context, padding_y)
#define ui_padding_y_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, padding_y)
#define ui_padding_y_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, padding_y, at)
#define ui_set_padding_y(val) DeferLoop(padding_y_stack_push(val), padding_y_stack_pop())

/* Left spacing (not clipped) */
typedef struct UI_Spacing_Left_stack UI_Spacing_Left_stack;
struct UI_Spacing_Left_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_spacing_left_stack_init(bot_val) ui_stack_init(&ui_context, spacing_left, bot_val)
#define ui_spacing_left_stack_push(val) ui_stack_push(&ui_context, spacing_left, val)
#define ui_spacing_left_stack_pop() ui_stack_pop(&ui_context, spacing_left)
#define ui_spacing_left_stack_top() ui_stack_top(&ui_context, spacing_left)
#define ui_spacing_left_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, spacing_left)
#define ui_spacing_left_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, spacing_left, at)
#define ui_set_spacing_left(val) DeferLoop(spacing_left_stack_push(val), spacing_left_stack_pop())

/* Right spacing (not clipped) */
typedef struct UI_Spacing_Right_stack UI_Spacing_Right_stack;
struct UI_Spacing_Right_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_spacing_right_stack_init(bot_val) ui_stack_init(&ui_context, spacing_right, bot_val)
#define ui_spacing_right_stack_push(val) ui_stack_push(&ui_context, spacing_right, val)
#define ui_spacing_right_stack_pop() ui_stack_pop(&ui_context, spacing_right)
#define ui_spacing_right_stack_top() ui_stack_top(&ui_context, spacing_right)
#define ui_spacing_right_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, spacing_right)
#define ui_spacing_right_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, spacing_right, at)
#define ui_set_spacing_right(val) DeferLoop(spacing_right_stack_push(val), spacing_right_stack_pop())

/* Top spacing (not clipped) */
typedef struct UI_Spacing_Top_stack UI_Spacing_Top_stack;
struct UI_Spacing_Top_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_spacing_top_stack_init(bot_val) ui_stack_init(&ui_context, spacing_top, bot_val)
#define ui_spacing_top_stack_push(val) ui_stack_push(&ui_context, spacing_top, val)
#define ui_spacing_top_stack_pop() ui_stack_pop(&ui_context, spacing_top)
#define ui_spacing_top_stack_top() ui_stack_top(&ui_context, spacing_top)
#define ui_spacing_top_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, spacing_top)
#define ui_spacing_top_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, spacing_top, at)
#define ui_set_spacing_top(val) DeferLoop(spacing_top_stack_push(val), spacing_top_stack_pop())

/* Bottom spacing (not clipped) */
typedef struct UI_Spacing_Bottom_stack UI_Spacing_Bottom_stack;
struct UI_Spacing_Bottom_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
#define ui_spacing_bottom_stack_init(bot_val) ui_stack_init(&ui_context, spacing_bottom, bot_val)
#define ui_spacing_bottom_stack_push(val) ui_stack_push(&ui_context, spacing_bottom, val)
#define ui_spacing_bottom_stack_pop() ui_stack_pop(&ui_context, spacing_bottom)
#define ui_spacing_bottom_stack_top() ui_stack_top(&ui_context, spacing_bottom)
#define ui_spacing_bottom_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, spacing_bottom)
#define ui_spacing_bottom_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, spacing_bottom, at)
#define ui_set_spacing_bottom(val) DeferLoop(spacing_bottom_stack_push(val), spacing_bottom_stack_pop())

/* Default alignment along Y */
typedef struct UI_Alignment_Kind_stack UI_Alignment_Kind_stack;
struct UI_Alignment_Kind_stack { UI_Alignment_Kind data[32]; u32 top_index; UI_Alignment_Kind bottom_val; };
#define ui_alignment_kind_stack_init(bot_val) ui_stack_init(&ui_context, alignment_kind, bot_val)
#define ui_alignment_kind_stack_push(val) ui_stack_push(&ui_context, alignment_kind, val)
#define ui_alignment_kind_stack_pop() ui_stack_pop(&ui_context, alignment_kind)
#define ui_alignment_kind_stack_top() ui_stack_top(&ui_context, alignment_kind)
#define ui_alignment_kind_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, alignment_kind)
#define ui_alignment_kind_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, alignment_kind, at)
#define ui_set_alignment_kind(val) DeferLoop(alignment_kind_stack_push(val), alignment_kind_stack_pop())

/* Width filling strategy */
typedef struct UI_Width_Kind_stack UI_Width_Kind_stack;
struct UI_Width_Kind_stack { UI_Width_Kind data[32]; u32 top_index; UI_Width_Kind bottom_val; };
#define ui_width_kind_stack_init(bot_val) ui_stack_init(&ui_context, width_kind, bot_val)
#define ui_width_kind_stack_push(val) ui_stack_push(&ui_context, width_kind, val)
#define ui_width_kind_stack_pop() ui_stack_pop(&ui_context, width_kind)
#define ui_width_kind_stack_top() ui_stack_top(&ui_context, width_kind)
#define ui_width_kind_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, width_kind)
#define ui_width_kind_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, width_kind, at)
#define ui_set_width_kind(val) DeferLoop(width_kind_stack_push(val), width_kind_stack_pop())

/* Height filling strategy */
typedef struct UI_Height_Kind_stack UI_Height_Kind_stack;
struct UI_Height_Kind_stack { UI_Height_Kind data[32]; u32 top_index; UI_Height_Kind bottom_val; };
#define ui_height_kind_stack_init(bot_val) ui_stack_init(&ui_context, height_kind, bot_val)
#define ui_height_kind_stack_push(val) ui_stack_push(&ui_context, height_kind, val)
#define ui_height_kind_stack_pop() ui_stack_pop(&ui_context, height_kind)
#define ui_height_kind_stack_top() ui_stack_top(&ui_context, height_kind)
#define ui_height_kind_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, height_kind)
#define ui_height_kind_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, height_kind, at)
#define ui_set_height_kind(val) DeferLoop(height_kind_stack_push(val), height_kind_stack_pop())

/* Node color scheme override */
typedef struct UI_Node_Color_Scheme_stack UI_Node_Color_Scheme_stack;
struct UI_Node_Color_Scheme_stack { UI_Node_Color_Scheme data[32]; u32 top_index; UI_Node_Color_Scheme bottom_val; };
#define ui_node_color_scheme_stack_init(bot_val) ui_stack_init(&ui_context, node_color_scheme, bot_val)
#define ui_node_color_scheme_stack_push(val) ui_stack_push(&ui_context, node_color_scheme, val)
#define ui_node_color_scheme_stack_pop() ui_stack_pop(&ui_context, node_color_scheme)
#define ui_node_color_scheme_stack_top() ui_stack_top(&ui_context, node_color_scheme)
#define ui_node_color_scheme_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, node_color_scheme)
#define ui_node_color_scheme_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, node_color_scheme, at)
#define ui_set_node_color_scheme(val) DeferLoop(node_color_scheme_stack_push(val), node_color_scheme_stack_pop())

/* Default border color */
typedef struct UI_Border_Color_stack UI_Border_Color_stack;
struct UI_Border_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_border_color_stack_init(bot_val) ui_stack_init(&ui_context, border_color, bot_val)
#define ui_border_color_stack_push(val) ui_stack_push(&ui_context, border_color, val)
#define ui_border_color_stack_pop() ui_stack_pop(&ui_context, border_color)
#define ui_border_color_stack_top() ui_stack_top(&ui_context, border_color)
#define ui_border_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, border_color)
#define ui_border_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, border_color, at)
#define ui_set_border_color(val) DeferLoop(border_color_stack_push(val), border_color_stack_pop())

/* Default background color */
typedef struct UI_Background_Color_stack UI_Background_Color_stack;
struct UI_Background_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_background_color_stack_init(bot_val) ui_stack_init(&ui_context, background_color, bot_val)
#define ui_background_color_stack_push(val) ui_stack_push(&ui_context, background_color, val)
#define ui_background_color_stack_pop() ui_stack_pop(&ui_context, background_color)
#define ui_background_color_stack_top() ui_stack_top(&ui_context, background_color)
#define ui_background_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, background_color)
#define ui_background_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, background_color, at)
#define ui_set_background_color(val) DeferLoop(background_color_stack_push(val), background_color_stack_pop())

/* Background color on hover */
typedef struct UI_Background_Hover_Color_stack UI_Background_Hover_Color_stack;
struct UI_Background_Hover_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_background_hover_color_stack_init(bot_val) ui_stack_init(&ui_context, background_hover_color, bot_val)
#define ui_background_hover_color_stack_push(val) ui_stack_push(&ui_context, background_hover_color, val)
#define ui_background_hover_color_stack_pop() ui_stack_pop(&ui_context, background_hover_color)
#define ui_background_hover_color_stack_top() ui_stack_top(&ui_context, background_hover_color)
#define ui_background_hover_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, background_hover_color)
#define ui_background_hover_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, background_hover_color, at)
#define ui_set_background_hover_color(val) DeferLoop(background_hover_color_stack_push(val), background_hover_color_stack_pop())

/* Background color when active */
typedef struct UI_Background_Active_Color_stack UI_Background_Active_Color_stack;
struct UI_Background_Active_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_background_active_color_stack_init(bot_val) ui_stack_init(&ui_context, background_active_color, bot_val)
#define ui_background_active_color_stack_push(val) ui_stack_push(&ui_context, background_active_color, val)
#define ui_background_active_color_stack_pop() ui_stack_pop(&ui_context, background_active_color)
#define ui_background_active_color_stack_top() ui_stack_top(&ui_context, background_active_color)
#define ui_background_active_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, background_active_color)
#define ui_background_active_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, background_active_color, at)
#define ui_set_background_active_color(val) DeferLoop(background_active_color_stack_push(val), background_active_color_stack_pop())

/* Default text color */
typedef struct UI_Text_Color_stack UI_Text_Color_stack;
struct UI_Text_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_text_color_stack_init(bot_val) ui_stack_init(&ui_context, text_color, bot_val)
#define ui_text_color_stack_push(val) ui_stack_push(&ui_context, text_color, val)
#define ui_text_color_stack_pop() ui_stack_pop(&ui_context, text_color)
#define ui_text_color_stack_top() ui_stack_top(&ui_context, text_color)
#define ui_text_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, text_color)
#define ui_text_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, text_color, at)
#define ui_set_text_color(val) DeferLoop(text_color_stack_push(val), text_color_stack_pop())

/* Text color on hover */
typedef struct UI_Text_Hover_Color_stack UI_Text_Hover_Color_stack;
struct UI_Text_Hover_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_text_hover_color_stack_init(bot_val) ui_stack_init(&ui_context, text_hover_color, bot_val)
#define ui_text_hover_color_stack_push(val) ui_stack_push(&ui_context, text_hover_color, val)
#define ui_text_hover_color_stack_pop() ui_stack_pop(&ui_context, text_hover_color)
#define ui_text_hover_color_stack_top() ui_stack_top(&ui_context, text_hover_color)
#define ui_text_hover_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, text_hover_color)
#define ui_text_hover_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, text_hover_color, at)
#define ui_set_text_hover_color(val) DeferLoop(text_hover_color_stack_push(val), text_hover_color_stack_pop())

/* Text color when active */
typedef struct UI_Text_Active_Color_stack UI_Text_Active_Color_stack;
struct UI_Text_Active_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
#define ui_text_active_color_stack_init(bot_val) ui_stack_init(&ui_context, text_active_color, bot_val)
#define ui_text_active_color_stack_push(val) ui_stack_push(&ui_context, text_active_color, val)
#define ui_text_active_color_stack_pop() ui_stack_pop(&ui_context, text_active_color)
#define ui_text_active_color_stack_top() ui_stack_top(&ui_context, text_active_color)
#define ui_text_active_color_stack_is_at_bottom() ui_stack_is_at_bottom(&ui_context, text_active_color)
#define ui_text_active_color_stack_assert_top_at(at) ui_stack_assert_top_at(&ui_context, text_active_color, at)
#define ui_set_text_active_color(val) DeferLoop(text_active_color_stack_push(val), text_active_color_stack_pop())

// Put this macro on UI_Context
#define UI_Config_Stacks() \
  UI_Node_stack node_stack; \
  UI_Top_Left_stack top_left_stack; \
  UI_Size_X_stack size_x_stack; \
  UI_Size_Y_stack size_y_stack; \
  UI_Padding_X_stack padding_x_stack; \
  UI_Padding_Y_stack padding_y_stack; \
  UI_Spacing_Left_stack spacing_left_stack; \
  UI_Spacing_Right_stack spacing_right_stack; \
  UI_Spacing_Top_stack spacing_top_stack; \
  UI_Spacing_Bottom_stack spacing_bottom_stack; \
  UI_Alignment_Kind_stack alignment_kind_stack; \
  UI_Width_Kind_stack width_kind_stack; \
  UI_Height_Kind_stack height_kind_stack; \
  UI_Node_Color_Scheme_stack node_color_scheme_stack; \
  UI_Border_Color_stack border_color_stack; \
  UI_Background_Color_stack background_color_stack; \
  UI_Background_Hover_Color_stack background_hover_color_stack; \
  UI_Background_Active_Color_stack background_active_color_stack; \
  UI_Text_Color_stack text_color_stack; \
  UI_Text_Hover_Color_stack text_hover_color_stack; \
  UI_Text_Active_Color_stack text_active_color_stack; \
/* Macro end */

#endif