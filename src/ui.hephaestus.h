#ifndef UI_HEPHAESTUS_H
#define UI_HEPHAESTUS_H

/*
@Hephaestus generated code
*/

typedef u32 UI_Node_Flags;
enum
{
  UI_Node_Flags_Mouse_Clickable = (1 << 0), /* Makes this node emit a signal when clicked */
  UI_Node_Flags_Draggable = (1 << 1), /* Makes this node emit a signal when dragged */
  UI_Node_Flags_Hoverable = (1 << 2), /* Makes this node emit a signal when hovered */
  UI_Node_Flags_Text_Display = (1 << 3), /* The UI_Node will display the text on the cursor's position and skip the cursor relative to UI_Alignment_Kind */
  UI_Node_Flags_Text_Center_X = (1 << 4), /* If text is displayed, centers the text horizontally in the node */
  UI_Node_Flags_Text_Center_Y = (1 << 5), /* If text is displayed, centers the text vertically in the node */
  UI_Node_Flags_Size_Wrap_Around_Text = (1 << 6), /* Wraps the size of the node around the text with. If fixed size is provided, it is used as padding. */
};

typedef u32 UI_Signal_Flags;
enum
{
  UI_Signal_Flags_Left_Down = (1 << 0), /* Emits signal if LMB is down */
  UI_Signal_Flags_Middle_Down = (1 << 1), /* Emits build signal if MMB is down */
  UI_Signal_Flags_Right_Down = (1 << 2), /* Emits signal if RMB is down */
  UI_Signal_Flags_Left_Clicked = (1 << 3), /* Emits signal if LMB is clicked */
  UI_Signal_Flags_Middle_Clicked = (1 << 4), /* Emits signal if MMB is clicked */
  UI_Signal_Flags_Right_Clicked = (1 << 5), /* Emits signal if RMB is clicked */
  UI_Signal_Flags_Mouse_Hovered = (1 << 6), /* Emits signal if cursor is hovering */
};

typedef enum
{
  UI_Size_Kind_None = 0,
  UI_Size_Kind_Relative, /* Sets the side of the node to be done relative to parent (0.0 to 1.0) */ 
  UI_Size_Kind_Fixed, /* Sets the side of the node to be fixed (within parent's clip space) */ 
  UI_Size_Kind_Copy_X, /* Will set X value as the absolute value calculated in Y. Don't set size X. */ 
  UI_Size_Kind_Copy_Y, /* Will set Y value as the absolute value calculated in X. Don't set size Y. */ 
} UI_Size_Kind;
const char* ui_size_kind_table_string[] = { "UI_Size_Kind_None", "UI_Size_Kind_Relative", "UI_Size_Kind_Fixed", "UI_Size_Kind_Copy_X", "UI_Size_Kind_Copy_Y", };
#define ui_size_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Size_Kind kind: %s", ui_size_kind_table_string[kind]));

typedef enum
{
  UI_Alignment_Kind_None = 0,
  UI_Alignment_Kind_X, /* After a node is placed, the cursor is moved horizontally by the width of the node */ 
  UI_Alignment_Kind_Y, /* After a node is placed, the cursor is moved vertically by the height of the node */ 
} UI_Alignment_Kind;
const char* ui_alignment_kind_table_string[] = { "UI_Alignment_Kind_None", "UI_Alignment_Kind_X", "UI_Alignment_Kind_Y", };
#define ui_alignment_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Alignment_Kind kind: %s", ui_alignment_kind_table_string[kind]));

typedef enum
{
  UI_Layout_Kind_None = 0,
  UI_Layout_Kind_Row, /* Layout with fixed height and 100% relative width */ 
  UI_Layout_Kind_Row_Fixed, /* Row layout with fixed width */ 
  UI_Layout_Kind_Column, /* Layout with fixed width and 100% relative height */ 
  UI_Layout_Kind_Column_Fixed, /* Column layout with fixed height */ 
} UI_Layout_Kind;
const char* ui_layout_kind_table_string[] = { "UI_Layout_Kind_None", "UI_Layout_Kind_Row", "UI_Layout_Kind_Row_Fixed", "UI_Layout_Kind_Column", "UI_Layout_Kind_Column_Fixed", };
#define ui_layout_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Layout_Kind kind: %s", ui_layout_kind_table_string[kind]));


#endif // UI_HEPHAESTUS_H// Initializes all stack structures
#define UI_Init_Stacks(ctx) \
  ctx.parent_stack.top_index = 0; ctx.parent_stack.bottom_val = &ui_node_nil_sentinel; \
  ctx.top_left_stack.top_index = 0; ctx.top_left_stack.bottom_val = vec2f32(0.0f, 0.0f); \
  ctx.size_kind_x_stack.top_index = 0; ctx.size_kind_x_stack.bottom_val = UI_Size_Kind_Fixed; \
  ctx.size_kind_y_stack.top_index = 0; ctx.size_kind_y_stack.bottom_val = UI_Size_Kind_Fixed; \
  ctx.size_fixed_x_stack.top_index = 0; ctx.size_fixed_x_stack.bottom_val = g_os_window.dimensions.x; \
  ctx.size_fixed_y_stack.top_index = 0; ctx.size_fixed_y_stack.bottom_val = g_os_window.dimensions.y; \
  ctx.size_relative_x_stack.top_index = 0; ctx.size_relative_x_stack.bottom_val = 1; \
  ctx.size_relative_y_stack.top_index = 0; ctx.size_relative_y_stack.bottom_val = 1; \
  ctx.padding_fixed_stack.top_index = 0; ctx.padding_fixed_stack.bottom_val = 0; \
  ctx.padding_fixed_top_stack.top_index = 0; ctx.padding_fixed_top_stack.bottom_val = 0; \
  ctx.padding_fixed_bot_stack.top_index = 0; ctx.padding_fixed_bot_stack.bottom_val = 0; \
  ctx.padding_fixed_left_stack.top_index = 0; ctx.padding_fixed_left_stack.bottom_val = 0; \
  ctx.padding_fixed_right_stack.top_index = 0; ctx.padding_fixed_right_stack.bottom_val = 0; \
  ctx.layout_kind_stack.top_index = 0; ctx.layout_kind_stack.bottom_val = UI_Layout_Kind_Row; \
  ctx.child_layout_kind_stack.top_index = 0; ctx.child_layout_kind_stack.bottom_val = UI_Alignment_Kind_Y; \
  ctx.resizable_stack.top_index = 0; ctx.resizable_stack.bottom_val = false; \
  ctx.node_color_scheme_stack.top_index = 0; ctx.node_color_scheme_stack.bottom_val = ui_context.color_scheme.window; \

// Creates struct with all UI stacks
#define UI_Config_Stacks \
  struct \
  { \
    struct UI_Parent_stack { UI_Node* data[32]; u32 top_index; UI_Node* bottom_val; } parent_stack; \
    struct UI_Top_Left_stack { Vec2f32 data[32]; u32 top_index; Vec2f32 bottom_val; } top_left_stack; \
    struct UI_Size_Kind_X_stack { UI_Size_Kind data[32]; u32 top_index; UI_Size_Kind bottom_val; } size_kind_x_stack; \
    struct UI_Size_Kind_Y_stack { UI_Size_Kind data[32]; u32 top_index; UI_Size_Kind bottom_val; } size_kind_y_stack; \
    struct UI_Size_Fixed_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; } size_fixed_x_stack; \
    struct UI_Size_Fixed_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; } size_fixed_y_stack; \
    struct UI_Size_Relative_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; } size_relative_x_stack; \
    struct UI_Size_Relative_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; } size_relative_y_stack; \
    struct UI_Padding_Fixed_stack { f32 data[32]; u32 top_index; f32 bottom_val; } padding_fixed_stack; \
    struct UI_Padding_Fixed_Top_stack { f32 data[32]; u32 top_index; f32 bottom_val; } padding_fixed_top_stack; \
    struct UI_Padding_Fixed_Bot_stack { f32 data[32]; u32 top_index; f32 bottom_val; } padding_fixed_bot_stack; \
    struct UI_Padding_Fixed_Left_stack { f32 data[32]; u32 top_index; f32 bottom_val; } padding_fixed_left_stack; \
    struct UI_Padding_Fixed_Right_stack { f32 data[32]; u32 top_index; f32 bottom_val; } padding_fixed_right_stack; \
    struct UI_Layout_Kind_stack { f32 data[32]; u32 top_index; f32 bottom_val; } layout_kind_stack; \
    struct UI_Child_Layout_Kind_stack { UI_Alignment_Kind data[32]; u32 top_index; UI_Alignment_Kind bottom_val; } child_layout_kind_stack; \
    struct UI_Resizable_stack { b32 data[32]; u32 top_index; b32 bottom_val; } resizable_stack; \
    struct UI_Node_Color_Scheme_stack { UI_Node_Color_Scheme data[32]; u32 top_index; UI_Node_Color_Scheme bottom_val; } node_color_scheme_stack; \
  }

// Debug: Serves to check if all stacks are at the bottom by the end of the frame
#define UI_Debug_Stacks_At_Bottom \
  ui_stack_assert_top_at(parent,1); \
  ui_stack_assert_top_at(top_left,0); \
  ui_stack_assert_top_at(size_kind_x,0); \
  ui_stack_assert_top_at(size_kind_y,0); \
  ui_stack_assert_top_at(size_fixed_x,0); \
  ui_stack_assert_top_at(size_fixed_y,0); \
  ui_stack_assert_top_at(size_relative_x,0); \
  ui_stack_assert_top_at(size_relative_y,0); \
  ui_stack_assert_top_at(padding_fixed,0); \
  ui_stack_assert_top_at(padding_fixed_top,0); \
  ui_stack_assert_top_at(padding_fixed_bot,0); \
  ui_stack_assert_top_at(padding_fixed_left,0); \
  ui_stack_assert_top_at(padding_fixed_right,0); \
  ui_stack_assert_top_at(layout_kind,0); \
  ui_stack_assert_top_at(child_layout_kind,0); \
  ui_stack_assert_top_at(resizable,0); \
  ui_stack_assert_top_at(node_color_scheme,0); \

