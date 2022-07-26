// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#ifndef WINDOW_HPP
#define WINDOW_HPP

// User-Defined Headers
// --------------------
#include "../graphics/graphics.hpp"
#include "../camera/camera.hpp"

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
#include <string>
#include <stdio.h>

namespace CE {
	namespace core {
		class Window {
		public:
			struct SDL_Window *window;
			SDL_GLContext mainContext;

			bool fullscreen = false;
			int width = 800;
			int height = 600;

			const char* title;

			bool shouldClose = false;
			bool mouseCaptured = false;
			float dt = 0.03f;

			glm::vec4 clearColor;
			SDL_Event event;
			void(*inputCallback)(CE::core::Window*, CE::core::Camera*);

			int create(int userWidth, int userHeight, std::string userTitle, bool userFullscreen);
			int updateMatrices(CE::core::Shader* shader, CE::core::Camera* camera);
			int update(CE::core::Camera* camera);
			void sdlDie(std::string message);
			int clear();
			int refresh();
			int cleanup();
			int setInputCallback(void(*func)(CE::core::Window*, CE::core::Camera*));
		private:
			float lastTime = 0.0f;

			void defaultInputs();
		};
	}
}

#endif // WINDOW_HPP
