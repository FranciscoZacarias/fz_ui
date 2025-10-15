function void ui_stack_parent_init(UI_Node* bot_val) { ui_stack_init(parent, bot_val); }
function void ui_stack_parent_push(UI_Node* val) { ui_stack_push(parent, val); }
function UI_Node* ui_stack_parent_pop() { return ui_stack_pop(parent); }
function UI_Node* ui_stack_parent_top() { return ui_stack_top(parent); }
function b32  ui_stack_parent_is_at_bottom() { return ui_stack_is_at_bottom(parent); }
function void ui_stack_parent_assert_top_at(u32 at) { ui_stack_assert_top_at(parent, at); }
#define ui_parent(val) DeferLoop(ui_stack_parent_push(val), ui_stack_parent_pop())

function void ui_stack_top_left_init(Vec2f32 bot_val) { ui_stack_init(top_left, bot_val); }
function void ui_stack_top_left_push(Vec2f32 val) { ui_stack_push(top_left, val); }
function Vec2f32 ui_stack_top_left_pop() { return ui_stack_pop(top_left); }
function Vec2f32 ui_stack_top_left_top() { return ui_stack_top(top_left); }
function b32  ui_stack_top_left_is_at_bottom() { return ui_stack_is_at_bottom(top_left); }
function void ui_stack_top_left_assert_top_at(u32 at) { ui_stack_assert_top_at(top_left, at); }
#define ui_top_left(val) DeferLoop(ui_stack_top_left_push(val), ui_stack_top_left_pop())

function void ui_stack_size_fixed_x_init(f32 bot_val) { ui_stack_init(size_fixed_x, bot_val); }
function void ui_stack_size_fixed_x_push(f32 val) { ui_stack_push(size_fixed_x, val); }
function f32 ui_stack_size_fixed_x_pop() { return ui_stack_pop(size_fixed_x); }
function f32 ui_stack_size_fixed_x_top() { return ui_stack_top(size_fixed_x); }
function b32  ui_stack_size_fixed_x_is_at_bottom() { return ui_stack_is_at_bottom(size_fixed_x); }
function void ui_stack_size_fixed_x_assert_top_at(u32 at) { ui_stack_assert_top_at(size_fixed_x, at); }
#define ui_size_fixed_x(val) DeferLoop(ui_stack_size_fixed_x_push(val), ui_stack_size_fixed_x_pop())

function void ui_stack_size_fixed_y_init(f32 bot_val) { ui_stack_init(size_fixed_y, bot_val); }
function void ui_stack_size_fixed_y_push(f32 val) { ui_stack_push(size_fixed_y, val); }
function f32 ui_stack_size_fixed_y_pop() { return ui_stack_pop(size_fixed_y); }
function f32 ui_stack_size_fixed_y_top() { return ui_stack_top(size_fixed_y); }
function b32  ui_stack_size_fixed_y_is_at_bottom() { return ui_stack_is_at_bottom(size_fixed_y); }
function void ui_stack_size_fixed_y_assert_top_at(u32 at) { ui_stack_assert_top_at(size_fixed_y, at); }
#define ui_size_fixed_y(val) DeferLoop(ui_stack_size_fixed_y_push(val), ui_stack_size_fixed_y_pop())

function void ui_stack_alignment_kind_init(UI_Alignment_Kind bot_val) { ui_stack_init(alignment_kind, bot_val); }
function void ui_stack_alignment_kind_push(UI_Alignment_Kind val) { ui_stack_push(alignment_kind, val); }
function UI_Alignment_Kind ui_stack_alignment_kind_pop() { return ui_stack_pop(alignment_kind); }
function UI_Alignment_Kind ui_stack_alignment_kind_top() { return ui_stack_top(alignment_kind); }
function b32  ui_stack_alignment_kind_is_at_bottom() { return ui_stack_is_at_bottom(alignment_kind); }
function void ui_stack_alignment_kind_assert_top_at(u32 at) { ui_stack_assert_top_at(alignment_kind, at); }
#define ui_alignment_kind(val) DeferLoop(ui_stack_alignment_kind_push(val), ui_stack_alignment_kind_pop())

function void ui_stack_width_kind_init(UI_Width_Kind bot_val) { ui_stack_init(width_kind, bot_val); }
function void ui_stack_width_kind_push(UI_Width_Kind val) { ui_stack_push(width_kind, val); }
function UI_Width_Kind ui_stack_width_kind_pop() { return ui_stack_pop(width_kind); }
function UI_Width_Kind ui_stack_width_kind_top() { return ui_stack_top(width_kind); }
function b32  ui_stack_width_kind_is_at_bottom() { return ui_stack_is_at_bottom(width_kind); }
function void ui_stack_width_kind_assert_top_at(u32 at) { ui_stack_assert_top_at(width_kind, at); }
#define ui_width_kind(val) DeferLoop(ui_stack_width_kind_push(val), ui_stack_width_kind_pop())

function void ui_stack_height_kind_init(UI_Height_Kind bot_val) { ui_stack_init(height_kind, bot_val); }
function void ui_stack_height_kind_push(UI_Height_Kind val) { ui_stack_push(height_kind, val); }
function UI_Height_Kind ui_stack_height_kind_pop() { return ui_stack_pop(height_kind); }
function UI_Height_Kind ui_stack_height_kind_top() { return ui_stack_top(height_kind); }
function b32  ui_stack_height_kind_is_at_bottom() { return ui_stack_is_at_bottom(height_kind); }
function void ui_stack_height_kind_assert_top_at(u32 at) { ui_stack_assert_top_at(height_kind, at); }
#define ui_height_kind(val) DeferLoop(ui_stack_height_kind_push(val), ui_stack_height_kind_pop())

function void ui_stack_node_color_scheme_init(UI_Node_Color_Scheme bot_val) { ui_stack_init(node_color_scheme, bot_val); }
function void ui_stack_node_color_scheme_push(UI_Node_Color_Scheme val) { ui_stack_push(node_color_scheme, val); }
function UI_Node_Color_Scheme ui_stack_node_color_scheme_pop() { return ui_stack_pop(node_color_scheme); }
function UI_Node_Color_Scheme ui_stack_node_color_scheme_top() { return ui_stack_top(node_color_scheme); }
function b32  ui_stack_node_color_scheme_is_at_bottom() { return ui_stack_is_at_bottom(node_color_scheme); }
function void ui_stack_node_color_scheme_assert_top_at(u32 at) { ui_stack_assert_top_at(node_color_scheme, at); }
#define ui_node_color_scheme(val) DeferLoop(ui_stack_node_color_scheme_push(val), ui_stack_node_color_scheme_pop())

