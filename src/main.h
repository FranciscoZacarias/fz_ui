#ifndef MAIN_H
#define MAIN_H

#define DEBUG 1

///////////////////////////////////////////////////////
// @Section: fz_std
#include "fz_base.h"
#include "fz_opengl.h"

///////////////////////////////////////////////////////
// @Section: project
#define PROJECT_NAME S("fz_ui")

global Input_State g_input;
global f32 g_delta_time    = 0.0f;
global u64 g_frame_counter = 0;

// *.h
#include "renderer.h"
#include "ui.h"

// *.c
#include "renderer.c"
#include "ui.c"

global OS_Timer g_frame_timer   = {0};
global f32      g_fps           = 0.0f;

function void input_update();
function void simulation();
function b32  is_game_running();

#endif // MAIN_H
