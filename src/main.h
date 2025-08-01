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

function void input_update();

#endif // MAIN_H