

# FZ_UI
A rough prototype for an immediate mode UI in C. This was my second iteration of the prototype, where I tried to use a different approach to the underlying UI tree. Essentially, each node of the tree is a quad with some optionally displayed text, and each node has functionality that can be attached to it. With this approach, building widgets becomes almost a scripting task - you just create nodes and attach functionality to them.

> A UI window with some buttons and checkboxes

[](/assets/readme/fz_ui.PNG)

> fz_ui window
A UI window with debug enabled. While keeping in mind that every quad is a node with optional text, here you can see:

Node boundries and clip quad. In most nodes here, the clip is slithgly smaller due to padding added.
Buttons, Labels and checkboxes.
Each node's cursor (defined with a small X), that shows where the next child of this node would've been drawn.
Vertical and horizontal layouts.
fz_ui window boundries


The following code is how you define this window in the application space:

```c
// Booleans defined in the global scope for the checkboxes:
global b32 a = false;
global b32 b = false;
global b32 c = false;

entry_point()
{
  for (;;)
  {
    // ...

    ui_top_left(vec2f32(200,200))
    ui_size_fixed_x(x) ui_size_fixed_y(y)
    ui_window(S("Test Window"))
    {
      ui_padding_fixed(5)
      ui_row(S("Test Row"), 100)
      {
        ui_label(S("Label"));
        ui_button(S("Button 1"));
        ui_checkbox(S("Checkbox a"), &a);
        ui_checkbox(S("Checkbox b"), &b);
      }
      ui_padding_fixed(5)
      ui_row(S("Test Row 2"), 100)
      {
        ui_checkbox(S("Checkbox a"), &a);
      }
      ui_padding_fixed(5)
      ui_column(S("Test column"), 200)
      {
        ui_label(S("More checkboxes"));
        ui_checkbox(S("Checkbox b"), &b);
        ui_checkbox(S("Checkbox c"), &c);
      }
    }
    
    // ...
  }
}
```