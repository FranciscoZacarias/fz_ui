#ifndef MAIN_H
#define MAIN_H

#define DEBUG 1

///////////////////////////////////////////////////////
// @Section: fz_std
#include "fz_base.h"
#include "fz_window.h"
#include "fz_opengl.h"

///////////////////////////////////////////////////////
// @Section: project

#define Project_Name S("Turtle")

// *.h
#include "camera.h"
#include "renderer.h"

// *.c
#include "camera.c"
#include "renderer.c"

global Camera g_camera;

OS_Timer g_frame_timer;
u64      g_frame_counter;
f32      g_delta_time;
u32      g_fps;

function void input_update();

#endif // MAIN_H