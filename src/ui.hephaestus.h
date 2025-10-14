#ifndef UI_HEPHAESTUS_H
#define UI_HEPHAESTUS_H

/*

@Hephaestus generated code 2025-October-14 16:26:51

*/

typedef enum
{
  UI_Alignment_Kind_None = 0,
  UI_Alignment_Kind_X, /* TODO(fz): Add documentation */ 
  UI_Alignment_Kind_Y, /* TODO(fz): Add documentation */ 
  UI_Alignment_Kind_Floating, /* TODO(fz): Add documentation */ 
} UI_Alignment_Kind;
const char* ui_alignment_kind_table_string[] = { "UI_Alignment_Kind_None", "UI_Alignment_Kind_X", "UI_Alignment_Kind_Y", "UI_Alignment_Kind_Floating", };
#define ui_alignment_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Alignment_Kind kind: %s", ui_alignment_kind_table_string[kind]));

typedef enum
{
  UI_Width_Kind_None = 0,
  UI_Width_Kind_Fill, /* TODO(fz): Add documentation */ 
  UI_Width_Kind_Fixed, /* TODO(fz): Add documentation */ 
} UI_Width_Kind;
const char* ui_width_kind_table_string[] = { "UI_Width_Kind_None", "UI_Width_Kind_Fill", "UI_Width_Kind_Fixed", };
#define ui_width_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Width_Kind kind: %s", ui_width_kind_table_string[kind]));

typedef enum
{
  UI_Height_Kind_None = 0,
  UI_Height_Kind_Fill, /* TODO(fz): Add documentation */ 
  UI_Height_Kind_Fixed, /* TODO(fz): Add documentation */ 
} UI_Height_Kind;
const char* ui_height_kind_table_string[] = { "UI_Height_Kind_None", "UI_Height_Kind_Fill", "UI_Height_Kind_Fixed", };
#define ui_height_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Height_Kind kind: %s", ui_height_kind_table_string[kind]));

typedef enum
{
  UI_Clip_Policy_Kind_None = 0,
  UI_Clip_Policy_Kind_Free, /* TODO(Fz): Debug HPH. */ 
  UI_Clip_Policy_Kind_Strict, /* TODO(Fz): Debug HPH. */ 
} UI_Clip_Policy_Kind;
const char* ui_clip_policy_kind_table_string[] = { "UI_Clip_Policy_Kind_None", "UI_Clip_Policy_Kind_Free",  "UI_Clip_Policy_Kind_Strict",  };
#define ui_clip_policy_kind_not_handled(arena, kind) emit_fatal(Sf(arena, "Unhandled UI_Clip_Policy_Kind kind: %s", ui_clip_policy_kind_table_string[kind]));

// Initializes all stack structures
#define UI_Init_Stacks(ctx) \
  ctx.parent_stack.top_index = 0; ctx.parent_stack.bottom_val = &ui_node_nil_sentinel; \
  ctx.top_left_stack.top_index = 0; ctx.top_left_stack.bottom_val = vec2f32(0.0f, 0.0f); \
  ctx.size_x_stack.top_index = 0; ctx.size_x_stack.bottom_val = g_os_window.dimensions.x; \
  ctx.size_y_stack.top_index = 0; ctx.size_y_stack.bottom_val = g_os_window.dimensions.y; \
  ctx.alignment_kind_stack.top_index = 0; ctx.alignment_kind_stack.bottom_val = UI_Alignment_Kind_Y; \
  ctx.width_kind_stack.top_index = 0; ctx.width_kind_stack.bottom_val = UI_Width_Kind_Fill; \
  ctx.height_kind_stack.top_index = 0; ctx.height_kind_stack.bottom_val = UI_Height_Kind_Fill; \
  ctx.clip_policy_stack.top_index = 0; ctx.clip_policy_stack.bottom_val = UI_Clip_Policy_Kind_Strict; \
  ctx.node_color_scheme_stack.top_index = 0; ctx.node_color_scheme_stack.bottom_val = ui_context.color_scheme.window; \

// Creates struct with all UI stacks
#define UI_Config_Stacks \
  struct \
  { \
    struct UI_Parent_stack { UI_Node* data[32]; u32 top_index; UI_Node* bottom_val; } parent_stack; \
    struct UI_Top_Left_stack { Vec2f32 data[32]; u32 top_index; Vec2f32 bottom_val; } top_left_stack; \
    struct UI_Size_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; } size_x_stack; \
    struct UI_Size_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; } size_y_stack; \
    struct UI_Alignment_Kind_stack { UI_Alignment_Kind data[32]; u32 top_index; UI_Alignment_Kind bottom_val; } alignment_kind_stack; \
    struct UI_Width_Kind_stack { UI_Width_Kind data[32]; u32 top_index; UI_Width_Kind bottom_val; } width_kind_stack; \
    struct UI_Height_Kind_stack { UI_Height_Kind data[32]; u32 top_index; UI_Height_Kind bottom_val; } height_kind_stack; \
    struct UI_Clip_Policy_stack { UI_Clip_Policy_Kind data[32]; u32 top_index; UI_Clip_Policy_Kind bottom_val; } clip_policy_stack; \
    struct UI_Node_Color_Scheme_stack { UI_Node_Color_Scheme data[32]; u32 top_index; UI_Node_Color_Scheme bottom_val; } node_color_scheme_stack; \
  }

// Debug: Serves to check if all stacks are at the bottom by the end of the frame
#define UI_Debug_Stacks_At_Bottom \
  ui_stack_assert_top_at(parent,1); \
  ui_stack_assert_top_at(top_left,0); \
  ui_stack_assert_top_at(size_x,0); \
  ui_stack_assert_top_at(size_y,0); \
  ui_stack_assert_top_at(alignment_kind,0); \
  ui_stack_assert_top_at(width_kind,0); \
  ui_stack_assert_top_at(height_kind,0); \
  ui_stack_assert_top_at(clip_policy,0); \
  ui_stack_assert_top_at(node_color_scheme,0); \

typedef u32 UI_Node_Flags;
enum
{
  UI_Node_Flags_Mouse_Clickable = (1 << 0), /* TODO(fz): Add documentation */
  UI_Node_Flags_Draggable = (1 << 1), /* TODO(fz): Add documentation */
  UI_Node_Flags_Hoverable = (1 << 2), /* TODO(fz): Add documentation */
  UI_Node_Flags_Display_Text = (1 << 3), /* TODO(fz): Add documentation */
};

typedef u32 UI_Signal_Flags;
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


#endif // UI_HEPHAESTUS_H