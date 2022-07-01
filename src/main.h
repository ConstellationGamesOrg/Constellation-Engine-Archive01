#ifndef MAINH
#define MAINH

// Constellation Engine
#include "core/graphics/graphics.h"
#include "core/input/input.h"
#include "core/window/window.h"

// Thirdparty
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <cglm/cglm.h>

// Standard
#include <stdio.h>

// Macros
#define _DEBUG

// Functions
int main();

void processInput(struct core_window_Window* window);

#endif
