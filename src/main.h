#ifndef MAIN_H
#define MAIN_H

#define DEBUG 1

///////////////////////////////////////////////////////
// @Section: fz_std
#include "fz_base.h"
#include "fz_opengl.h"

///////////////////////////////////////////////////////
// @Section: project

#define PROJECT_NAME S("fz_render_2d")

// *.h
#include "camera2d.h"
#include "renderer.h"

// *.c
#include "camera2d.c"
#include "renderer.c"

global Camera2D g_camera;
global Input_State g_input;

global OS_Timer g_frame_timer   = {0};
global u64      g_frame_counter = 0;
global f32      g_delta_time    = 0.0f;
global f32      g_fps           = 0.0f;

global Texture_Info g_tex_black;
global Texture_Info g_tex_red;
global Texture_Info g_tex_color_blue;
global Texture_Info g_tex_color_yellow;

function void input_update();
function void simulation();
function b32  is_game_running();
function void camera2d_update(Camera2D* camera, Input_State, f32 delta_time);

#endif // MAIN_H
