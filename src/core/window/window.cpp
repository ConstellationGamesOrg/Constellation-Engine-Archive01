// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "window.hpp"
#include <glad/glad.hpp>

namespace CE {
	namespace core {
		int Window::create(int userWidth, int userHeight, std::string userTitle, bool userFullscreen) {
			width = userWidth;
			height = userHeight;
			title = userTitle.c_str();
			fullscreen = userFullscreen;

			if (SDL_Init(SDL_INIT_VIDEO) < 0)
				sdlDie("Couldn't initialize SDL");

			atexit(SDL_Quit);
			SDL_GL_LoadLibrary(NULL); // Default is fine

			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			if (fullscreen) {
				window = SDL_CreateWindow(
					userTitle.c_str(),
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL
				);
			} else {
				window = SDL_CreateWindow(
					userTitle.c_str(),
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					width, height, SDL_WINDOW_OPENGL
				);
			}

			// Error handling
			if (window == NULL) {
				sdlDie("Couldn't set video mode");
			}

			mainContext = SDL_GL_CreateContext(window);

			if (mainContext == nullptr) {
				sdlDie("Failed to create OpenGL context");
			}

			printf("OpenGL loaded\n");
			gladLoadGLLoader(SDL_GL_GetProcAddress);
			printf("Vendor:   %s\n", glGetString(GL_VENDOR));
			printf("Renderer: %s\n", glGetString(GL_RENDERER));
			printf("Version:  %s\n", glGetString(GL_VERSION));

			mouseCaptured = true;
			SDL_SetRelativeMouseMode(SDL_TRUE);

			// Configure global OpenGL state
			glEnable(GL_DEPTH_TEST);
#ifdef _WIN32
			glEnable(GL_FRAMEBUFFER_SRGB); // Use the sRGB colourspace
#endif

			// Turn on vsync to limit the FPS to the user's monitor refresh rate and improve frame timing
			SDL_GL_SetSwapInterval(1);

			return 0;
		}

		int Window::updateMatrices(CE::core::Shader* shader, CE::core::Camera* camera) {
			// Projection matrix
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
			shader->setMat4("projection", projection);

			// View transformation
			glm::mat4 view = glm::mat4(1.0f);
			view = camera->GetViewMatrix();
			shader->setMat4("view", view);

			return 0;
		}

		int Window::refresh() {
			SDL_GL_SwapWindow(window);
			SDL_PollEvent(&event);
			SDL_GetWindowSize(window, &width, &height);

			if (mouseCaptured == true)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			else if (mouseCaptured == false)
				SDL_SetRelativeMouseMode(SDL_FALSE);

			return 0;
		}

		int Window::clear() {
			glViewport(0, 0, width, height);
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			return 0;
		}

		void Window::defaultInputs() {
			if (event.type == SDL_QUIT) {
				shouldClose = true;
			}
		}

		int Window::update(CE::core::Camera* camera) {
			//float currentFrame = static_cast<float>(glfwGetTime());
			//dt = currentFrame - lastTime;
			//lastTime = currentFrame;

			defaultInputs();

			if (inputCallback != nullptr)
				inputCallback(this, camera);
			else
				printf("WARNING: the inputCallback function has not been set\n");

			return 0;
		}

		void Window::sdlDie(std::string message) {
			fprintf(stderr, "%s: %s\n", message.c_str(), SDL_GetError());
			exit(2);
		}

		int Window::cleanup() {
			SDL_GL_DeleteContext(mainContext);
			SDL_DestroyWindow(window);
			SDL_Quit();

			return 0;
		}

		int Window::setInputCallback(void(*func)(CE::core::Window*, CE::core::Camera*)) {
			if (func == nullptr) {
				printf("ERROR: Passing the input callback function to setInputCallback FAILED!\n");

				return -1;
			}

			inputCallback = func;

			return 0;
		}
	}
}
