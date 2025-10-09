// @Hephaestus generated code 2025-October-09 14:26:43

/* Pointer to the current UI node */
typedef struct Node_stack Node_stack;
struct Node_stack { UI_Node* data[32]; u32 top_index; UI_Node* bottom_val; };
function void ui_stack_push_node(UI_Context* ctx, UI_Node* value) { Node_stack* s = &ctx->node_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function UI_Node* ui_stack_pop_node(UI_Context* ctx) { Node_stack* s = &ctx->node_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function UI_Node* ui_stack_top_node(UI_Context* ctx) { Node_stack* s = &ctx->node_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_node(UI_Context* ctx) { return ctx->node_stack.top_index == 0; }
function void ui_stack_assert_top_at_node(UI_Context* ctx, u32 at) { if(ctx->node_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->node_stack), at, ctx->node_stack.top_index)); }
#define defer_node(val) DeferLoop(ui_stack_push_node(&ui_context, (val)), ui_stack_pop_node(&ui_context))

/* Top-left corner position */
typedef struct Top_Left_stack Top_Left_stack;
struct Top_Left_stack { Vec2f32 data[32]; u32 top_index; Vec2f32 bottom_val; };
function void ui_stack_push_top_left(UI_Context* ctx, Vec2f32 value) { Top_Left_stack* s = &ctx->top_left_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Vec2f32 ui_stack_pop_top_left(UI_Context* ctx) { Top_Left_stack* s = &ctx->top_left_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Vec2f32 ui_stack_top_top_left(UI_Context* ctx) { Top_Left_stack* s = &ctx->top_left_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_top_left(UI_Context* ctx) { return ctx->top_left_stack.top_index == 0; }
function void ui_stack_assert_top_at_top_left(UI_Context* ctx, u32 at) { if(ctx->top_left_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->top_left_stack), at, ctx->top_left_stack.top_index)); }
#define defer_top_left(val) DeferLoop(ui_stack_push_top_left(&ui_context, (val)), ui_stack_pop_top_left(&ui_context))

/* Default X size equals window width */
typedef struct Size_X_stack Size_X_stack;
struct Size_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_size_x(UI_Context* ctx, f32 value) { Size_X_stack* s = &ctx->size_x_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_size_x(UI_Context* ctx) { Size_X_stack* s = &ctx->size_x_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_size_x(UI_Context* ctx) { Size_X_stack* s = &ctx->size_x_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_size_x(UI_Context* ctx) { return ctx->size_x_stack.top_index == 0; }
function void ui_stack_assert_top_at_size_x(UI_Context* ctx, u32 at) { if(ctx->size_x_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->size_x_stack), at, ctx->size_x_stack.top_index)); }
#define defer_size_x(val) DeferLoop(ui_stack_push_size_x(&ui_context, (val)), ui_stack_pop_size_x(&ui_context))

/* Default Y size equals window height */
typedef struct Size_Y_stack Size_Y_stack;
struct Size_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_size_y(UI_Context* ctx, f32 value) { Size_Y_stack* s = &ctx->size_y_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_size_y(UI_Context* ctx) { Size_Y_stack* s = &ctx->size_y_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_size_y(UI_Context* ctx) { Size_Y_stack* s = &ctx->size_y_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_size_y(UI_Context* ctx) { return ctx->size_y_stack.top_index == 0; }
function void ui_stack_assert_top_at_size_y(UI_Context* ctx, u32 at) { if(ctx->size_y_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->size_y_stack), at, ctx->size_y_stack.top_index)); }
#define defer_size_y(val) DeferLoop(ui_stack_push_size_y(&ui_context, (val)), ui_stack_pop_size_y(&ui_context))

/* Horizontal padding */
typedef struct Padding_X_stack Padding_X_stack;
struct Padding_X_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_padding_x(UI_Context* ctx, f32 value) { Padding_X_stack* s = &ctx->padding_x_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_padding_x(UI_Context* ctx) { Padding_X_stack* s = &ctx->padding_x_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_padding_x(UI_Context* ctx) { Padding_X_stack* s = &ctx->padding_x_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_padding_x(UI_Context* ctx) { return ctx->padding_x_stack.top_index == 0; }
function void ui_stack_assert_top_at_padding_x(UI_Context* ctx, u32 at) { if(ctx->padding_x_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->padding_x_stack), at, ctx->padding_x_stack.top_index)); }
#define defer_padding_x(val) DeferLoop(ui_stack_push_padding_x(&ui_context, (val)), ui_stack_pop_padding_x(&ui_context))

/* Vertical padding */
typedef struct Padding_Y_stack Padding_Y_stack;
struct Padding_Y_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_padding_y(UI_Context* ctx, f32 value) { Padding_Y_stack* s = &ctx->padding_y_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_padding_y(UI_Context* ctx) { Padding_Y_stack* s = &ctx->padding_y_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_padding_y(UI_Context* ctx) { Padding_Y_stack* s = &ctx->padding_y_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_padding_y(UI_Context* ctx) { return ctx->padding_y_stack.top_index == 0; }
function void ui_stack_assert_top_at_padding_y(UI_Context* ctx, u32 at) { if(ctx->padding_y_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->padding_y_stack), at, ctx->padding_y_stack.top_index)); }
#define defer_padding_y(val) DeferLoop(ui_stack_push_padding_y(&ui_context, (val)), ui_stack_pop_padding_y(&ui_context))

/* Left spacing (not clipped) */
typedef struct Spacing_Left_stack Spacing_Left_stack;
struct Spacing_Left_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_spacing_left(UI_Context* ctx, f32 value) { Spacing_Left_stack* s = &ctx->spacing_left_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_spacing_left(UI_Context* ctx) { Spacing_Left_stack* s = &ctx->spacing_left_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_spacing_left(UI_Context* ctx) { Spacing_Left_stack* s = &ctx->spacing_left_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_spacing_left(UI_Context* ctx) { return ctx->spacing_left_stack.top_index == 0; }
function void ui_stack_assert_top_at_spacing_left(UI_Context* ctx, u32 at) { if(ctx->spacing_left_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->spacing_left_stack), at, ctx->spacing_left_stack.top_index)); }
#define defer_spacing_left(val) DeferLoop(ui_stack_push_spacing_left(&ui_context, (val)), ui_stack_pop_spacing_left(&ui_context))

/* Right spacing (not clipped) */
typedef struct Spacing_Right_stack Spacing_Right_stack;
struct Spacing_Right_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_spacing_right(UI_Context* ctx, f32 value) { Spacing_Right_stack* s = &ctx->spacing_right_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_spacing_right(UI_Context* ctx) { Spacing_Right_stack* s = &ctx->spacing_right_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_spacing_right(UI_Context* ctx) { Spacing_Right_stack* s = &ctx->spacing_right_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_spacing_right(UI_Context* ctx) { return ctx->spacing_right_stack.top_index == 0; }
function void ui_stack_assert_top_at_spacing_right(UI_Context* ctx, u32 at) { if(ctx->spacing_right_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->spacing_right_stack), at, ctx->spacing_right_stack.top_index)); }
#define defer_spacing_right(val) DeferLoop(ui_stack_push_spacing_right(&ui_context, (val)), ui_stack_pop_spacing_right(&ui_context))

/* Top spacing (not clipped) */
typedef struct Spacing_Top_stack Spacing_Top_stack;
struct Spacing_Top_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_spacing_top(UI_Context* ctx, f32 value) { Spacing_Top_stack* s = &ctx->spacing_top_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_spacing_top(UI_Context* ctx) { Spacing_Top_stack* s = &ctx->spacing_top_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_spacing_top(UI_Context* ctx) { Spacing_Top_stack* s = &ctx->spacing_top_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_spacing_top(UI_Context* ctx) { return ctx->spacing_top_stack.top_index == 0; }
function void ui_stack_assert_top_at_spacing_top(UI_Context* ctx, u32 at) { if(ctx->spacing_top_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->spacing_top_stack), at, ctx->spacing_top_stack.top_index)); }
#define defer_spacing_top(val) DeferLoop(ui_stack_push_spacing_top(&ui_context, (val)), ui_stack_pop_spacing_top(&ui_context))

/* Bottom spacing (not clipped) */
typedef struct Spacing_Bottom_stack Spacing_Bottom_stack;
struct Spacing_Bottom_stack { f32 data[32]; u32 top_index; f32 bottom_val; };
function void ui_stack_push_spacing_bottom(UI_Context* ctx, f32 value) { Spacing_Bottom_stack* s = &ctx->spacing_bottom_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function f32 ui_stack_pop_spacing_bottom(UI_Context* ctx) { Spacing_Bottom_stack* s = &ctx->spacing_bottom_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function f32 ui_stack_top_spacing_bottom(UI_Context* ctx) { Spacing_Bottom_stack* s = &ctx->spacing_bottom_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_spacing_bottom(UI_Context* ctx) { return ctx->spacing_bottom_stack.top_index == 0; }
function void ui_stack_assert_top_at_spacing_bottom(UI_Context* ctx, u32 at) { if(ctx->spacing_bottom_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->spacing_bottom_stack), at, ctx->spacing_bottom_stack.top_index)); }
#define defer_spacing_bottom(val) DeferLoop(ui_stack_push_spacing_bottom(&ui_context, (val)), ui_stack_pop_spacing_bottom(&ui_context))

/* Default alignment along Y */
typedef struct Alignment_Kind_stack Alignment_Kind_stack;
struct Alignment_Kind_stack { UI_Alignment_Kind data[32]; u32 top_index; UI_Alignment_Kind bottom_val; };
function void ui_stack_push_alignment_kind(UI_Context* ctx, UI_Alignment_Kind value) { Alignment_Kind_stack* s = &ctx->alignment_kind_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function UI_Alignment_Kind ui_stack_pop_alignment_kind(UI_Context* ctx) { Alignment_Kind_stack* s = &ctx->alignment_kind_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function UI_Alignment_Kind ui_stack_top_alignment_kind(UI_Context* ctx) { Alignment_Kind_stack* s = &ctx->alignment_kind_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_alignment_kind(UI_Context* ctx) { return ctx->alignment_kind_stack.top_index == 0; }
function void ui_stack_assert_top_at_alignment_kind(UI_Context* ctx, u32 at) { if(ctx->alignment_kind_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->alignment_kind_stack), at, ctx->alignment_kind_stack.top_index)); }
#define defer_alignment_kind(val) DeferLoop(ui_stack_push_alignment_kind(&ui_context, (val)), ui_stack_pop_alignment_kind(&ui_context))

/* Width filling strategy */
typedef struct Width_Kind_stack Width_Kind_stack;
struct Width_Kind_stack { UI_Width_Kind data[32]; u32 top_index; UI_Width_Kind bottom_val; };
function void ui_stack_push_width_kind(UI_Context* ctx, UI_Width_Kind value) { Width_Kind_stack* s = &ctx->width_kind_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function UI_Width_Kind ui_stack_pop_width_kind(UI_Context* ctx) { Width_Kind_stack* s = &ctx->width_kind_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function UI_Width_Kind ui_stack_top_width_kind(UI_Context* ctx) { Width_Kind_stack* s = &ctx->width_kind_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_width_kind(UI_Context* ctx) { return ctx->width_kind_stack.top_index == 0; }
function void ui_stack_assert_top_at_width_kind(UI_Context* ctx, u32 at) { if(ctx->width_kind_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->width_kind_stack), at, ctx->width_kind_stack.top_index)); }
#define defer_width_kind(val) DeferLoop(ui_stack_push_width_kind(&ui_context, (val)), ui_stack_pop_width_kind(&ui_context))

/* Height filling strategy */
typedef struct Height_Kind_stack Height_Kind_stack;
struct Height_Kind_stack { UI_Height_Kind data[32]; u32 top_index; UI_Height_Kind bottom_val; };
function void ui_stack_push_height_kind(UI_Context* ctx, UI_Height_Kind value) { Height_Kind_stack* s = &ctx->height_kind_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function UI_Height_Kind ui_stack_pop_height_kind(UI_Context* ctx) { Height_Kind_stack* s = &ctx->height_kind_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function UI_Height_Kind ui_stack_top_height_kind(UI_Context* ctx) { Height_Kind_stack* s = &ctx->height_kind_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_height_kind(UI_Context* ctx) { return ctx->height_kind_stack.top_index == 0; }
function void ui_stack_assert_top_at_height_kind(UI_Context* ctx, u32 at) { if(ctx->height_kind_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->height_kind_stack), at, ctx->height_kind_stack.top_index)); }
#define defer_height_kind(val) DeferLoop(ui_stack_push_height_kind(&ui_context, (val)), ui_stack_pop_height_kind(&ui_context))

/* Node color scheme override */
typedef struct Node_Color_Scheme_stack Node_Color_Scheme_stack;
struct Node_Color_Scheme_stack { UI_Node_Color_Scheme data[32]; u32 top_index; UI_Node_Color_Scheme bottom_val; };
function void ui_stack_push_node_color_scheme(UI_Context* ctx, UI_Node_Color_Scheme value) { Node_Color_Scheme_stack* s = &ctx->node_color_scheme_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function UI_Node_Color_Scheme ui_stack_pop_node_color_scheme(UI_Context* ctx) { Node_Color_Scheme_stack* s = &ctx->node_color_scheme_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function UI_Node_Color_Scheme ui_stack_top_node_color_scheme(UI_Context* ctx) { Node_Color_Scheme_stack* s = &ctx->node_color_scheme_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_node_color_scheme(UI_Context* ctx) { return ctx->node_color_scheme_stack.top_index == 0; }
function void ui_stack_assert_top_at_node_color_scheme(UI_Context* ctx, u32 at) { if(ctx->node_color_scheme_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->node_color_scheme_stack), at, ctx->node_color_scheme_stack.top_index)); }
#define defer_node_color_scheme(val) DeferLoop(ui_stack_push_node_color_scheme(&ui_context, (val)), ui_stack_pop_node_color_scheme(&ui_context))

/* Default border color */
typedef struct Border_Color_stack Border_Color_stack;
struct Border_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_border_color(UI_Context* ctx, Color value) { Border_Color_stack* s = &ctx->border_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_border_color(UI_Context* ctx) { Border_Color_stack* s = &ctx->border_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_border_color(UI_Context* ctx) { Border_Color_stack* s = &ctx->border_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_border_color(UI_Context* ctx) { return ctx->border_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_border_color(UI_Context* ctx, u32 at) { if(ctx->border_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->border_color_stack), at, ctx->border_color_stack.top_index)); }
#define defer_border_color(val) DeferLoop(ui_stack_push_border_color(&ui_context, (val)), ui_stack_pop_border_color(&ui_context))

/* Default background color */
typedef struct Background_Color_stack Background_Color_stack;
struct Background_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_background_color(UI_Context* ctx, Color value) { Background_Color_stack* s = &ctx->background_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_background_color(UI_Context* ctx) { Background_Color_stack* s = &ctx->background_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_background_color(UI_Context* ctx) { Background_Color_stack* s = &ctx->background_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_background_color(UI_Context* ctx) { return ctx->background_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_background_color(UI_Context* ctx, u32 at) { if(ctx->background_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->background_color_stack), at, ctx->background_color_stack.top_index)); }
#define defer_background_color(val) DeferLoop(ui_stack_push_background_color(&ui_context, (val)), ui_stack_pop_background_color(&ui_context))

/* Background color on hover */
typedef struct Background_Hover_Color_stack Background_Hover_Color_stack;
struct Background_Hover_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_background_hover_color(UI_Context* ctx, Color value) { Background_Hover_Color_stack* s = &ctx->background_hover_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_background_hover_color(UI_Context* ctx) { Background_Hover_Color_stack* s = &ctx->background_hover_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_background_hover_color(UI_Context* ctx) { Background_Hover_Color_stack* s = &ctx->background_hover_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_background_hover_color(UI_Context* ctx) { return ctx->background_hover_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_background_hover_color(UI_Context* ctx, u32 at) { if(ctx->background_hover_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->background_hover_color_stack), at, ctx->background_hover_color_stack.top_index)); }
#define defer_background_hover_color(val) DeferLoop(ui_stack_push_background_hover_color(&ui_context, (val)), ui_stack_pop_background_hover_color(&ui_context))

/* Background color when active */
typedef struct Background_Active_Color_stack Background_Active_Color_stack;
struct Background_Active_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_background_active_color(UI_Context* ctx, Color value) { Background_Active_Color_stack* s = &ctx->background_active_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_background_active_color(UI_Context* ctx) { Background_Active_Color_stack* s = &ctx->background_active_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_background_active_color(UI_Context* ctx) { Background_Active_Color_stack* s = &ctx->background_active_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_background_active_color(UI_Context* ctx) { return ctx->background_active_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_background_active_color(UI_Context* ctx, u32 at) { if(ctx->background_active_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->background_active_color_stack), at, ctx->background_active_color_stack.top_index)); }
#define defer_background_active_color(val) DeferLoop(ui_stack_push_background_active_color(&ui_context, (val)), ui_stack_pop_background_active_color(&ui_context))

/* Default text color */
typedef struct Text_Color_stack Text_Color_stack;
struct Text_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_text_color(UI_Context* ctx, Color value) { Text_Color_stack* s = &ctx->text_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_text_color(UI_Context* ctx) { Text_Color_stack* s = &ctx->text_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_text_color(UI_Context* ctx) { Text_Color_stack* s = &ctx->text_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_text_color(UI_Context* ctx) { return ctx->text_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_text_color(UI_Context* ctx, u32 at) { if(ctx->text_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->text_color_stack), at, ctx->text_color_stack.top_index)); }
#define defer_text_color(val) DeferLoop(ui_stack_push_text_color(&ui_context, (val)), ui_stack_pop_text_color(&ui_context))

/* Text color on hover */
typedef struct Text_Hover_Color_stack Text_Hover_Color_stack;
struct Text_Hover_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_text_hover_color(UI_Context* ctx, Color value) { Text_Hover_Color_stack* s = &ctx->text_hover_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_text_hover_color(UI_Context* ctx) { Text_Hover_Color_stack* s = &ctx->text_hover_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_text_hover_color(UI_Context* ctx) { Text_Hover_Color_stack* s = &ctx->text_hover_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_text_hover_color(UI_Context* ctx) { return ctx->text_hover_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_text_hover_color(UI_Context* ctx, u32 at) { if(ctx->text_hover_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->text_hover_color_stack), at, ctx->text_hover_color_stack.top_index)); }
#define defer_text_hover_color(val) DeferLoop(ui_stack_push_text_hover_color(&ui_context, (val)), ui_stack_pop_text_hover_color(&ui_context))

/* Text color when active */
typedef struct Text_Active_Color_stack Text_Active_Color_stack;
struct Text_Active_Color_stack { Color data[32]; u32 top_index; Color bottom_val; };
function void ui_stack_push_text_active_color(UI_Context* ctx, Color value) { Text_Active_Color_stack* s = &ctx->text_active_color_stack; u32 cap = (u32)(sizeof(s->data) / sizeof(s->data[0])); u32 idx = (s->top_index < cap) ? s->top_index++ : s->top_index; s->data[idx] = value; }
function Color ui_stack_pop_text_active_color(UI_Context* ctx) { Text_Active_Color_stack* s = &ctx->text_active_color_stack; return (s->top_index > 0) ? s->data[--s->top_index] : s->bottom_val; }
function Color ui_stack_top_text_active_color(UI_Context* ctx) { Text_Active_Color_stack* s = &ctx->text_active_color_stack; return (s->top_index > 0) ? s->data[s->top_index-1] : s->bottom_val; }
function b32 ui_stack_is_at_bottom_text_active_color(UI_Context* ctx) { return ctx->text_active_color_stack.top_index == 0; }
function void ui_stack_assert_top_at_text_active_color(UI_Context* ctx, u32 at) { if(ctx->text_active_color_stack.top_index != at) emit_fatal(Sf(ctx->arena, "UI: %s not at expected top value: '%u'. Actual value: '%u'", Stringify(ctx->text_active_color_stack), at, ctx->text_active_color_stack.top_index)); }
#define defer_text_active_color(val) DeferLoop(ui_stack_push_text_active_color(&ui_context, (val)), ui_stack_pop_text_active_color(&ui_context))

// Put this macro on UI_Context
#define UI_Config_Stacks \
Node_stack node_stack; \
Top_Left_stack top_left_stack; \
Size_X_stack size_x_stack; \
Size_Y_stack size_y_stack; \
Padding_X_stack padding_x_stack; \
Padding_Y_stack padding_y_stack; \
Spacing_Left_stack spacing_left_stack; \
Spacing_Right_stack spacing_right_stack; \
Spacing_Top_stack spacing_top_stack; \
Spacing_Bottom_stack spacing_bottom_stack; \
Alignment_Kind_stack alignment_kind_stack; \
Width_Kind_stack width_kind_stack; \
Height_Kind_stack height_kind_stack; \
Node_Color_Scheme_stack node_color_scheme_stack; \
Border_Color_stack border_color_stack; \
Background_Color_stack background_color_stack; \
Background_Hover_Color_stack background_hover_color_stack; \
Background_Active_Color_stack background_active_color_stack; \
Text_Color_stack text_color_stack; \
Text_Hover_Color_stack text_hover_color_stack; \
Text_Active_Color_stack text_active_color_stack; \
/* Macro end */