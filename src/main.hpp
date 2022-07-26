// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#ifndef MAIN_HPP
#define MAIN_HPP

// User-Defined Headers
// --------------------
#include "core/window/window.hpp"
#include "core/graphics/graphics.hpp"
#include "core/camera/camera.hpp"
#include "core/input/input.hpp"
#include "core/model/model.hpp"

// 3rd Party Library Headers
// -------------------------
#include <glad/glad.hpp>
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif
#ifdef __APPLE__
#include <SDL2/sdl.h>
#include <SDL2/SDL_opengl.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_opengl.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Library Headers
// ------------------------
#include <iostream>
#include <vector>

int main();

#endif // MAIN_HPP
