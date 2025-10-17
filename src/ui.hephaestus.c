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

function void ui_stack_size_kind_x_init(UI_Size_Kind bot_val) { ui_stack_init(size_kind_x, bot_val); }
function void ui_stack_size_kind_x_push(UI_Size_Kind val) { ui_stack_push(size_kind_x, val); }
function UI_Size_Kind ui_stack_size_kind_x_pop() { return ui_stack_pop(size_kind_x); }
function UI_Size_Kind ui_stack_size_kind_x_top() { return ui_stack_top(size_kind_x); }
function b32  ui_stack_size_kind_x_is_at_bottom() { return ui_stack_is_at_bottom(size_kind_x); }
function void ui_stack_size_kind_x_assert_top_at(u32 at) { ui_stack_assert_top_at(size_kind_x, at); }
#define ui_size_kind_x(val) DeferLoop(ui_stack_size_kind_x_push(val), ui_stack_size_kind_x_pop())

function void ui_stack_size_kind_y_init(UI_Size_Kind bot_val) { ui_stack_init(size_kind_y, bot_val); }
function void ui_stack_size_kind_y_push(UI_Size_Kind val) { ui_stack_push(size_kind_y, val); }
function UI_Size_Kind ui_stack_size_kind_y_pop() { return ui_stack_pop(size_kind_y); }
function UI_Size_Kind ui_stack_size_kind_y_top() { return ui_stack_top(size_kind_y); }
function b32  ui_stack_size_kind_y_is_at_bottom() { return ui_stack_is_at_bottom(size_kind_y); }
function void ui_stack_size_kind_y_assert_top_at(u32 at) { ui_stack_assert_top_at(size_kind_y, at); }
#define ui_size_kind_y(val) DeferLoop(ui_stack_size_kind_y_push(val), ui_stack_size_kind_y_pop())

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

function void ui_stack_size_relative_x_init(f32 bot_val) { ui_stack_init(size_relative_x, bot_val); }
function void ui_stack_size_relative_x_push(f32 val) { ui_stack_push(size_relative_x, val); }
function f32 ui_stack_size_relative_x_pop() { return ui_stack_pop(size_relative_x); }
function f32 ui_stack_size_relative_x_top() { return ui_stack_top(size_relative_x); }
function b32  ui_stack_size_relative_x_is_at_bottom() { return ui_stack_is_at_bottom(size_relative_x); }
function void ui_stack_size_relative_x_assert_top_at(u32 at) { ui_stack_assert_top_at(size_relative_x, at); }
#define ui_size_relative_x(val) DeferLoop(ui_stack_size_relative_x_push(val), ui_stack_size_relative_x_pop())

function void ui_stack_size_relative_y_init(f32 bot_val) { ui_stack_init(size_relative_y, bot_val); }
function void ui_stack_size_relative_y_push(f32 val) { ui_stack_push(size_relative_y, val); }
function f32 ui_stack_size_relative_y_pop() { return ui_stack_pop(size_relative_y); }
function f32 ui_stack_size_relative_y_top() { return ui_stack_top(size_relative_y); }
function b32  ui_stack_size_relative_y_is_at_bottom() { return ui_stack_is_at_bottom(size_relative_y); }
function void ui_stack_size_relative_y_assert_top_at(u32 at) { ui_stack_assert_top_at(size_relative_y, at); }
#define ui_size_relative_y(val) DeferLoop(ui_stack_size_relative_y_push(val), ui_stack_size_relative_y_pop())

function void ui_stack_padding_fixed_init(f32 bot_val) { ui_stack_init(padding_fixed, bot_val); }
function void ui_stack_padding_fixed_push(f32 val) { ui_stack_push(padding_fixed, val); }
function f32 ui_stack_padding_fixed_pop() { return ui_stack_pop(padding_fixed); }
function f32 ui_stack_padding_fixed_top() { return ui_stack_top(padding_fixed); }
function b32  ui_stack_padding_fixed_is_at_bottom() { return ui_stack_is_at_bottom(padding_fixed); }
function void ui_stack_padding_fixed_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_fixed, at); }
#define ui_padding_fixed(val) DeferLoop(ui_stack_padding_fixed_push(val), ui_stack_padding_fixed_pop())

function void ui_stack_padding_fixed_top_init(f32 bot_val) { ui_stack_init(padding_fixed_top, bot_val); }
function void ui_stack_padding_fixed_top_push(f32 val) { ui_stack_push(padding_fixed_top, val); }
function f32 ui_stack_padding_fixed_top_pop() { return ui_stack_pop(padding_fixed_top); }
function f32 ui_stack_padding_fixed_top_top() { return ui_stack_top(padding_fixed_top); }
function b32  ui_stack_padding_fixed_top_is_at_bottom() { return ui_stack_is_at_bottom(padding_fixed_top); }
function void ui_stack_padding_fixed_top_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_fixed_top, at); }
#define ui_padding_fixed_top(val) DeferLoop(ui_stack_padding_fixed_top_push(val), ui_stack_padding_fixed_top_pop())

function void ui_stack_padding_fixed_bot_init(f32 bot_val) { ui_stack_init(padding_fixed_bot, bot_val); }
function void ui_stack_padding_fixed_bot_push(f32 val) { ui_stack_push(padding_fixed_bot, val); }
function f32 ui_stack_padding_fixed_bot_pop() { return ui_stack_pop(padding_fixed_bot); }
function f32 ui_stack_padding_fixed_bot_top() { return ui_stack_top(padding_fixed_bot); }
function b32  ui_stack_padding_fixed_bot_is_at_bottom() { return ui_stack_is_at_bottom(padding_fixed_bot); }
function void ui_stack_padding_fixed_bot_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_fixed_bot, at); }
#define ui_padding_fixed_bot(val) DeferLoop(ui_stack_padding_fixed_bot_push(val), ui_stack_padding_fixed_bot_pop())

function void ui_stack_padding_fixed_left_init(f32 bot_val) { ui_stack_init(padding_fixed_left, bot_val); }
function void ui_stack_padding_fixed_left_push(f32 val) { ui_stack_push(padding_fixed_left, val); }
function f32 ui_stack_padding_fixed_left_pop() { return ui_stack_pop(padding_fixed_left); }
function f32 ui_stack_padding_fixed_left_top() { return ui_stack_top(padding_fixed_left); }
function b32  ui_stack_padding_fixed_left_is_at_bottom() { return ui_stack_is_at_bottom(padding_fixed_left); }
function void ui_stack_padding_fixed_left_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_fixed_left, at); }
#define ui_padding_fixed_left(val) DeferLoop(ui_stack_padding_fixed_left_push(val), ui_stack_padding_fixed_left_pop())

function void ui_stack_padding_fixed_right_init(f32 bot_val) { ui_stack_init(padding_fixed_right, bot_val); }
function void ui_stack_padding_fixed_right_push(f32 val) { ui_stack_push(padding_fixed_right, val); }
function f32 ui_stack_padding_fixed_right_pop() { return ui_stack_pop(padding_fixed_right); }
function f32 ui_stack_padding_fixed_right_top() { return ui_stack_top(padding_fixed_right); }
function b32  ui_stack_padding_fixed_right_is_at_bottom() { return ui_stack_is_at_bottom(padding_fixed_right); }
function void ui_stack_padding_fixed_right_assert_top_at(u32 at) { ui_stack_assert_top_at(padding_fixed_right, at); }
#define ui_padding_fixed_right(val) DeferLoop(ui_stack_padding_fixed_right_push(val), ui_stack_padding_fixed_right_pop())

function void ui_stack_layout_kind_init(f32 bot_val) { ui_stack_init(layout_kind, bot_val); }
function void ui_stack_layout_kind_push(f32 val) { ui_stack_push(layout_kind, val); }
function f32 ui_stack_layout_kind_pop() { return ui_stack_pop(layout_kind); }
function f32 ui_stack_layout_kind_top() { return ui_stack_top(layout_kind); }
function b32  ui_stack_layout_kind_is_at_bottom() { return ui_stack_is_at_bottom(layout_kind); }
function void ui_stack_layout_kind_assert_top_at(u32 at) { ui_stack_assert_top_at(layout_kind, at); }
#define ui_layout_kind(val) DeferLoop(ui_stack_layout_kind_push(val), ui_stack_layout_kind_pop())

function void ui_stack_child_layout_kind_init(UI_Alignment_Kind bot_val) { ui_stack_init(child_layout_kind, bot_val); }
function void ui_stack_child_layout_kind_push(UI_Alignment_Kind val) { ui_stack_push(child_layout_kind, val); }
function UI_Alignment_Kind ui_stack_child_layout_kind_pop() { return ui_stack_pop(child_layout_kind); }
function UI_Alignment_Kind ui_stack_child_layout_kind_top() { return ui_stack_top(child_layout_kind); }
function b32  ui_stack_child_layout_kind_is_at_bottom() { return ui_stack_is_at_bottom(child_layout_kind); }
function void ui_stack_child_layout_kind_assert_top_at(u32 at) { ui_stack_assert_top_at(child_layout_kind, at); }
#define ui_child_layout_kind(val) DeferLoop(ui_stack_child_layout_kind_push(val), ui_stack_child_layout_kind_pop())

function void ui_stack_resizable_init(b32 bot_val) { ui_stack_init(resizable, bot_val); }
function void ui_stack_resizable_push(b32 val) { ui_stack_push(resizable, val); }
function b32 ui_stack_resizable_pop() { return ui_stack_pop(resizable); }
function b32 ui_stack_resizable_top() { return ui_stack_top(resizable); }
function b32  ui_stack_resizable_is_at_bottom() { return ui_stack_is_at_bottom(resizable); }
function void ui_stack_resizable_assert_top_at(u32 at) { ui_stack_assert_top_at(resizable, at); }
#define ui_resizable(val) DeferLoop(ui_stack_resizable_push(val), ui_stack_resizable_pop())

function void ui_stack_node_color_scheme_init(UI_Node_Color_Scheme bot_val) { ui_stack_init(node_color_scheme, bot_val); }
function void ui_stack_node_color_scheme_push(UI_Node_Color_Scheme val) { ui_stack_push(node_color_scheme, val); }
function UI_Node_Color_Scheme ui_stack_node_color_scheme_pop() { return ui_stack_pop(node_color_scheme); }
function UI_Node_Color_Scheme ui_stack_node_color_scheme_top() { return ui_stack_top(node_color_scheme); }
function b32  ui_stack_node_color_scheme_is_at_bottom() { return ui_stack_is_at_bottom(node_color_scheme); }
function void ui_stack_node_color_scheme_assert_top_at(u32 at) { ui_stack_assert_top_at(node_color_scheme, at); }
#define ui_node_color_scheme(val) DeferLoop(ui_stack_node_color_scheme_push(val), ui_stack_node_color_scheme_pop())

