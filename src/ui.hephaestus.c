/*

@Hephaestus generated code 2025-October-11 00:30:44

*/

/* Pointer to the current UI node */
function void ui_parent_stack_init(UI_Node* bot_val) { ui_stack_init(parent, bot_val); }
function void ui_parent_stack_push(UI_Node* val) { ui_stack_push(parent, val); }
function UI_Node* ui_parent_stack_pop() { return ui_stack_pop(parent); }
function UI_Node* ui_parent_stack_top() { return ui_stack_top(parent); }
function b32  ui_parent_stack_is_at_bottom() { return ui_stack_is_at_bottom(parent); }
function void ui_parent_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(parent, at); }
#define ui_parent(val) DeferLoop(ui_parent_stack_push(val), ui_parent_stack_pop())

/* Top-left corner position */
function void ui_top_left_stack_init(Vec2f32 bot_val) { ui_stack_init(top_left, bot_val); }
function void ui_top_left_stack_push(Vec2f32 val) { ui_stack_push(top_left, val); }
function Vec2f32 ui_top_left_stack_pop() { return ui_stack_pop(top_left); }
function Vec2f32 ui_top_left_stack_top() { return ui_stack_top(top_left); }
function b32  ui_top_left_stack_is_at_bottom() { return ui_stack_is_at_bottom(top_left); }
function void ui_top_left_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(top_left, at); }
#define ui_top_left(val) DeferLoop(ui_top_left_stack_push(val), ui_top_left_stack_pop())

/* Default X size equals window width */
function void ui_size_x_stack_init(f32 bot_val) { ui_stack_init(size_x, bot_val); }
function void ui_size_x_stack_push(f32 val) { ui_stack_push(size_x, val); }
function f32 ui_size_x_stack_pop() { return ui_stack_pop(size_x); }
function f32 ui_size_x_stack_top() { return ui_stack_top(size_x); }
function b32  ui_size_x_stack_is_at_bottom() { return ui_stack_is_at_bottom(size_x); }
function void ui_size_x_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(size_x, at); }
#define ui_size_x(val) DeferLoop(ui_size_x_stack_push(val), ui_size_x_stack_pop())

/* Default Y size equals window height */
function void ui_size_y_stack_init(f32 bot_val) { ui_stack_init(size_y, bot_val); }
function void ui_size_y_stack_push(f32 val) { ui_stack_push(size_y, val); }
function f32 ui_size_y_stack_pop() { return ui_stack_pop(size_y); }
function f32 ui_size_y_stack_top() { return ui_stack_top(size_y); }
function b32  ui_size_y_stack_is_at_bottom() { return ui_stack_is_at_bottom(size_y); }
function void ui_size_y_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(size_y, at); }
#define ui_size_y(val) DeferLoop(ui_size_y_stack_push(val), ui_size_y_stack_pop())

/* Horizontal padding */
function void ui_padding_x_stack_init(f32 bot_val) { ui_stack_init(padding_x, bot_val); }
function void ui_padding_x_stack_push(f32 val) { ui_stack_push(padding_x, val); }
function f32 ui_padding_x_stack_pop() { return ui_stack_pop(padding_x); }
function f32 ui_padding_x_stack_top() { return ui_stack_top(padding_x); }
function b32  ui_padding_x_stack_is_at_bottom() { return ui_stack_is_at_bottom(padding_x); }
function void ui_padding_x_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_x, at); }
#define ui_padding_x(val) DeferLoop(ui_padding_x_stack_push(val), ui_padding_x_stack_pop())

/* Vertical padding */
function void ui_padding_y_stack_init(f32 bot_val) { ui_stack_init(padding_y, bot_val); }
function void ui_padding_y_stack_push(f32 val) { ui_stack_push(padding_y, val); }
function f32 ui_padding_y_stack_pop() { return ui_stack_pop(padding_y); }
function f32 ui_padding_y_stack_top() { return ui_stack_top(padding_y); }
function b32  ui_padding_y_stack_is_at_bottom() { return ui_stack_is_at_bottom(padding_y); }
function void ui_padding_y_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_y, at); }
#define ui_padding_y(val) DeferLoop(ui_padding_y_stack_push(val), ui_padding_y_stack_pop())

/* Left spacing (not clipped) */
function void ui_spacing_left_stack_init(f32 bot_val) { ui_stack_init(spacing_left, bot_val); }
function void ui_spacing_left_stack_push(f32 val) { ui_stack_push(spacing_left, val); }
function f32 ui_spacing_left_stack_pop() { return ui_stack_pop(spacing_left); }
function f32 ui_spacing_left_stack_top() { return ui_stack_top(spacing_left); }
function b32  ui_spacing_left_stack_is_at_bottom() { return ui_stack_is_at_bottom(spacing_left); }
function void ui_spacing_left_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(spacing_left, at); }
#define ui_spacing_left(val) DeferLoop(ui_spacing_left_stack_push(val), ui_spacing_left_stack_pop())

/* Right spacing (not clipped) */
function void ui_spacing_right_stack_init(f32 bot_val) { ui_stack_init(spacing_right, bot_val); }
function void ui_spacing_right_stack_push(f32 val) { ui_stack_push(spacing_right, val); }
function f32 ui_spacing_right_stack_pop() { return ui_stack_pop(spacing_right); }
function f32 ui_spacing_right_stack_top() { return ui_stack_top(spacing_right); }
function b32  ui_spacing_right_stack_is_at_bottom() { return ui_stack_is_at_bottom(spacing_right); }
function void ui_spacing_right_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(spacing_right, at); }
#define ui_spacing_right(val) DeferLoop(ui_spacing_right_stack_push(val), ui_spacing_right_stack_pop())

/* Top spacing (not clipped) */
function void ui_spacing_top_stack_init(f32 bot_val) { ui_stack_init(spacing_top, bot_val); }
function void ui_spacing_top_stack_push(f32 val) { ui_stack_push(spacing_top, val); }
function f32 ui_spacing_top_stack_pop() { return ui_stack_pop(spacing_top); }
function f32 ui_spacing_top_stack_top() { return ui_stack_top(spacing_top); }
function b32  ui_spacing_top_stack_is_at_bottom() { return ui_stack_is_at_bottom(spacing_top); }
function void ui_spacing_top_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(spacing_top, at); }
#define ui_spacing_top(val) DeferLoop(ui_spacing_top_stack_push(val), ui_spacing_top_stack_pop())

/* Bottom spacing (not clipped) */
function void ui_spacing_bottom_stack_init(f32 bot_val) { ui_stack_init(spacing_bottom, bot_val); }
function void ui_spacing_bottom_stack_push(f32 val) { ui_stack_push(spacing_bottom, val); }
function f32 ui_spacing_bottom_stack_pop() { return ui_stack_pop(spacing_bottom); }
function f32 ui_spacing_bottom_stack_top() { return ui_stack_top(spacing_bottom); }
function b32  ui_spacing_bottom_stack_is_at_bottom() { return ui_stack_is_at_bottom(spacing_bottom); }
function void ui_spacing_bottom_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(spacing_bottom, at); }
#define ui_spacing_bottom(val) DeferLoop(ui_spacing_bottom_stack_push(val), ui_spacing_bottom_stack_pop())

/* Default alignment along Y */
function void ui_alignment_kind_stack_init(UI_Alignment_Kind bot_val) { ui_stack_init(alignment_kind, bot_val); }
function void ui_alignment_kind_stack_push(UI_Alignment_Kind val) { ui_stack_push(alignment_kind, val); }
function UI_Alignment_Kind ui_alignment_kind_stack_pop() { return ui_stack_pop(alignment_kind); }
function UI_Alignment_Kind ui_alignment_kind_stack_top() { return ui_stack_top(alignment_kind); }
function b32  ui_alignment_kind_stack_is_at_bottom() { return ui_stack_is_at_bottom(alignment_kind); }
function void ui_alignment_kind_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(alignment_kind, at); }
#define ui_alignment_kind(val) DeferLoop(ui_alignment_kind_stack_push(val), ui_alignment_kind_stack_pop())

/* Width filling strategy */
function void ui_width_kind_stack_init(UI_Width_Kind bot_val) { ui_stack_init(width_kind, bot_val); }
function void ui_width_kind_stack_push(UI_Width_Kind val) { ui_stack_push(width_kind, val); }
function UI_Width_Kind ui_width_kind_stack_pop() { return ui_stack_pop(width_kind); }
function UI_Width_Kind ui_width_kind_stack_top() { return ui_stack_top(width_kind); }
function b32  ui_width_kind_stack_is_at_bottom() { return ui_stack_is_at_bottom(width_kind); }
function void ui_width_kind_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(width_kind, at); }
#define ui_width_kind(val) DeferLoop(ui_width_kind_stack_push(val), ui_width_kind_stack_pop())

/* Height filling strategy */
function void ui_height_kind_stack_init(UI_Height_Kind bot_val) { ui_stack_init(height_kind, bot_val); }
function void ui_height_kind_stack_push(UI_Height_Kind val) { ui_stack_push(height_kind, val); }
function UI_Height_Kind ui_height_kind_stack_pop() { return ui_stack_pop(height_kind); }
function UI_Height_Kind ui_height_kind_stack_top() { return ui_stack_top(height_kind); }
function b32  ui_height_kind_stack_is_at_bottom() { return ui_stack_is_at_bottom(height_kind); }
function void ui_height_kind_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(height_kind, at); }
#define ui_height_kind(val) DeferLoop(ui_height_kind_stack_push(val), ui_height_kind_stack_pop())

/* Node color scheme override */
function void ui_node_color_scheme_stack_init(UI_Node_Color_Scheme bot_val) { ui_stack_init(node_color_scheme, bot_val); }
function void ui_node_color_scheme_stack_push(UI_Node_Color_Scheme val) { ui_stack_push(node_color_scheme, val); }
function UI_Node_Color_Scheme ui_node_color_scheme_stack_pop() { return ui_stack_pop(node_color_scheme); }
function UI_Node_Color_Scheme ui_node_color_scheme_stack_top() { return ui_stack_top(node_color_scheme); }
function b32  ui_node_color_scheme_stack_is_at_bottom() { return ui_stack_is_at_bottom(node_color_scheme); }
function void ui_node_color_scheme_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(node_color_scheme, at); }
#define ui_node_color_scheme(val) DeferLoop(ui_node_color_scheme_stack_push(val), ui_node_color_scheme_stack_pop())

/* Default border color */
function void ui_border_color_stack_init(Color bot_val) { ui_stack_init(border_color, bot_val); }
function void ui_border_color_stack_push(Color val) { ui_stack_push(border_color, val); }
function Color ui_border_color_stack_pop() { return ui_stack_pop(border_color); }
function Color ui_border_color_stack_top() { return ui_stack_top(border_color); }
function b32  ui_border_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(border_color); }
function void ui_border_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(border_color, at); }
#define ui_border_color(val) DeferLoop(ui_border_color_stack_push(val), ui_border_color_stack_pop())

/* Default background color */
function void ui_background_color_stack_init(Color bot_val) { ui_stack_init(background_color, bot_val); }
function void ui_background_color_stack_push(Color val) { ui_stack_push(background_color, val); }
function Color ui_background_color_stack_pop() { return ui_stack_pop(background_color); }
function Color ui_background_color_stack_top() { return ui_stack_top(background_color); }
function b32  ui_background_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(background_color); }
function void ui_background_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(background_color, at); }
#define ui_background_color(val) DeferLoop(ui_background_color_stack_push(val), ui_background_color_stack_pop())

/* Background color on hover */
function void ui_background_hover_color_stack_init(Color bot_val) { ui_stack_init(background_hover_color, bot_val); }
function void ui_background_hover_color_stack_push(Color val) { ui_stack_push(background_hover_color, val); }
function Color ui_background_hover_color_stack_pop() { return ui_stack_pop(background_hover_color); }
function Color ui_background_hover_color_stack_top() { return ui_stack_top(background_hover_color); }
function b32  ui_background_hover_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(background_hover_color); }
function void ui_background_hover_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(background_hover_color, at); }
#define ui_background_hover_color(val) DeferLoop(ui_background_hover_color_stack_push(val), ui_background_hover_color_stack_pop())

/* Background color when active */
function void ui_background_active_color_stack_init(Color bot_val) { ui_stack_init(background_active_color, bot_val); }
function void ui_background_active_color_stack_push(Color val) { ui_stack_push(background_active_color, val); }
function Color ui_background_active_color_stack_pop() { return ui_stack_pop(background_active_color); }
function Color ui_background_active_color_stack_top() { return ui_stack_top(background_active_color); }
function b32  ui_background_active_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(background_active_color); }
function void ui_background_active_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(background_active_color, at); }
#define ui_background_active_color(val) DeferLoop(ui_background_active_color_stack_push(val), ui_background_active_color_stack_pop())

/* Default text color */
function void ui_text_color_stack_init(Color bot_val) { ui_stack_init(text_color, bot_val); }
function void ui_text_color_stack_push(Color val) { ui_stack_push(text_color, val); }
function Color ui_text_color_stack_pop() { return ui_stack_pop(text_color); }
function Color ui_text_color_stack_top() { return ui_stack_top(text_color); }
function b32  ui_text_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(text_color); }
function void ui_text_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(text_color, at); }
#define ui_text_color(val) DeferLoop(ui_text_color_stack_push(val), ui_text_color_stack_pop())

/* Text color on hover */
function void ui_text_hover_color_stack_init(Color bot_val) { ui_stack_init(text_hover_color, bot_val); }
function void ui_text_hover_color_stack_push(Color val) { ui_stack_push(text_hover_color, val); }
function Color ui_text_hover_color_stack_pop() { return ui_stack_pop(text_hover_color); }
function Color ui_text_hover_color_stack_top() { return ui_stack_top(text_hover_color); }
function b32  ui_text_hover_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(text_hover_color); }
function void ui_text_hover_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(text_hover_color, at); }
#define ui_text_hover_color(val) DeferLoop(ui_text_hover_color_stack_push(val), ui_text_hover_color_stack_pop())

/* Text color when active */
function void ui_text_active_color_stack_init(Color bot_val) { ui_stack_init(text_active_color, bot_val); }
function void ui_text_active_color_stack_push(Color val) { ui_stack_push(text_active_color, val); }
function Color ui_text_active_color_stack_pop() { return ui_stack_pop(text_active_color); }
function Color ui_text_active_color_stack_top() { return ui_stack_top(text_active_color); }
function b32  ui_text_active_color_stack_is_at_bottom() { return ui_stack_is_at_bottom(text_active_color); }
function void ui_text_active_color_stack_assert_top_at(u32 at) { ui_stack_assert_top_at(text_active_color, at); }
#define ui_text_active_color(val) DeferLoop(ui_text_active_color_stack_push(val), ui_text_active_color_stack_pop())

