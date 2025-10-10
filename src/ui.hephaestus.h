#ifndef UI_HEPHAESTUS_H
#define UI_HEPHAESTUS_H

/*

@Hephaestus generated code 2025-October-10 15:40:48

*/

typedef u32 UI_Node_Flags;
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

// Initializes all stack structures
#define UI_Init_Stacks \
  ui_context.node_stack.top_index = 0; ui_context.node_stack.bottom_val = &ui_node_nil_sentinel; \
  ui_context.top_left_stack.top_index = 0; ui_context.top_left_stack.bottom_val = vec2f32(5.0f, 5.0f); \
  ui_context.size_x_stack.top_index = 0; ui_context.size_x_stack.bottom_val = g_os_window.dimensions.x; \
  ui_context.size_y_stack.top_index = 0; ui_context.size_y_stack.bottom_val = g_os_window.dimensions.y; \
  ui_context.padding_x_stack.top_index = 0; ui_context.padding_x_stack.bottom_val = 0.0f; \
  ui_context.padding_y_stack.top_index = 0; ui_context.padding_y_stack.bottom_val = 0.0f; \
  ui_context.spacing_left_stack.top_index = 0; ui_context.spacing_left_stack.bottom_val = 0.0f; \
  ui_context.spacing_right_stack.top_index = 0; ui_context.spacing_right_stack.bottom_val = 0.0f; \
  ui_context.spacing_top_stack.top_index = 0; ui_context.spacing_top_stack.bottom_val = 0.0f; \
  ui_context.spacing_bottom_stack.top_index = 0; ui_context.spacing_bottom_stack.bottom_val = 0.0f; \
  ui_context.alignment_kind_stack.top_index = 0; ui_context.alignment_kind_stack.bottom_val = UI_Alignment_Kind_Y; \
  ui_context.width_kind_stack.top_index = 0; ui_context.width_kind_stack.bottom_val = UI_Width_Kind_Fill; \
  ui_context.height_kind_stack.top_index = 0; ui_context.height_kind_stack.bottom_val = UI_Height_Kind_Fill; \
  ui_context.node_color_scheme_stack.top_index = 0; ui_context.node_color_scheme_stack.bottom_val = ui_context.color_scheme.window; \
  ui_context.border_color_stack.top_index = 0; ui_context.border_color_stack.bottom_val = PURPLE(1); \
  ui_context.background_color_stack.top_index = 0; ui_context.background_color_stack.bottom_val = PURPLE(1); \
  ui_context.background_hover_color_stack.top_index = 0; ui_context.background_hover_color_stack.bottom_val = PURPLE(1); \
  ui_context.background_active_color_stack.top_index = 0; ui_context.background_active_color_stack.bottom_val = PURPLE(1); \
  ui_context.text_color_stack.top_index = 0; ui_context.text_color_stack.bottom_val = PURPLE(1); \
  ui_context.text_hover_color_stack.top_index = 0; ui_context.text_hover_color_stack.bottom_val = PURPLE(1); \
  ui_context.text_active_color_stack.top_index = 0; ui_context.text_active_color_stack.bottom_val = PURPLE(1); \

// Creates struct with all UI stacks
#define UI_Config_Stacks \
  struct \
  { \
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
  }

// Debug: Serves to check if all stacks are at the bottom by the end of the frame
#define UI_Debug_Stacks_At_Bottom \
  ui_stack_assert_top_at((node),(1)) \
  ui_stack_assert_top_at((top_left),(0)) \
  ui_stack_assert_top_at((size_x),(0)) \
  ui_stack_assert_top_at((size_y),(0)) \
  ui_stack_assert_top_at((padding_x),(0)) \
  ui_stack_assert_top_at((padding_y),(0)) \
  ui_stack_assert_top_at((spacing_left),(0)) \
  ui_stack_assert_top_at((spacing_right),(0)) \
  ui_stack_assert_top_at((spacing_top),(0)) \
  ui_stack_assert_top_at((spacing_bottom),(0)) \
  ui_stack_assert_top_at((alignment_kind),(0)) \
  ui_stack_assert_top_at((width_kind),(0)) \
  ui_stack_assert_top_at((height_kind),(0)) \
  ui_stack_assert_top_at((node_color_scheme),(0)) \
  ui_stack_assert_top_at((border_color),(0)) \
  ui_stack_assert_top_at((background_color),(0)) \
  ui_stack_assert_top_at((background_hover_color),(0)) \
  ui_stack_assert_top_at((background_active_color),(0)) \
  ui_stack_assert_top_at((text_color),(0)) \
  ui_stack_assert_top_at((text_hover_color),(0)) \
  ui_stack_assert_top_at((text_active_color),(0)) \


#endif