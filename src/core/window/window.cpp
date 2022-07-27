// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "window.hpp"
#include <glad/glad.hpp>

namespace CE {
	namespace core {
		int Window::create(int userWidth, int userHeight, std::string userTitle) {
			width = userWidth;
			height = userHeight;
			title = userTitle.c_str();

			// Create the GLFWwindow object
			window = glfwCreateWindow(width, height, title, NULL, NULL);

			// Error handling
			if (!window) {
				printf("GLFW Window creation FAILED!\n");
				glfwTerminate();
				return -1;
			}

			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				printf("GLAD Initialization FAILED!\n");

				return -1;
			}

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			// Configure global OpenGL state
			glEnable(GL_DEPTH_TEST);
#ifdef _WIN32
			glEnable(GL_FRAMEBUFFER_SRGB); // Use the sRGB colourspace
#endif

			// Turn on vsync to limit the FPS to the user's monitor refresh rate and improve frame timing
			glfwSwapInterval(1);

			glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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
			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwWindowShouldClose(window)) {
				shouldClose = true;
			}

			return 0;
		}

		int Window::clear() {
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			return 0;
		}

		int Window::update() {
			float currentFrame = static_cast<float>(glfwGetTime());
			dt = currentFrame - lastTime;
			lastTime = currentFrame;

			defaultKeyInputs();
			keyboardInputCallback(this);

			if (shouldClose == true)
				glfwSetWindowShouldClose(window, true);

			return 0;
		}

		int Window::cleanup() {
			glfwTerminate();

			return 0;
		}

		int Window::unlockMouse() {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			return 0;
		}

		int Window::lockMouse() {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			return 0;
		}

		void Window::defaultKeyInputs() {
			if (CE::core::input::getKeyPress(window, KEY_Q) == GLFW_PRESS) // Check if the Q key was pressed
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);               // If so, change draw mode to GL_FILL

			if (CE::core::input::getKeyPress(window, KEY_E) == GLFW_PRESS) // Check if the E key was pressed
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);               // If so, change draw mode to GL_LINE / wireframe
		}

		int Window::setKeyboardInputCallback(void(*func)(CE::core::Window*)) {
			if (func == nullptr) {
				printf("ERROR: Passing the keyboard input callback function to setKeyboardInputCallback FAILED!\n");

				return -1;
			}

			keyboardInputCallback = func;

			return 0;
		}

		int Window::setMouseInputCallback(void(*func)(GLFWwindow*, double, double)) {
			if (func == nullptr) {
				printf("ERROR: Passing the mouse input callback function to setMouseInputCallback FAILED!\n");

				return -1;
			}

			glfwSetCursorPosCallback(window, func);

			return 0;
		}

		int Window::setMouseScrollCallback(void(*func)(GLFWwindow*, double, double)) {
			if (func == nullptr) {
				printf("ERROR: Passing the mouse scroll callback function to setMouseScrollCallback FAILED!\n");

				return -1;
			}

			glfwSetScrollCallback(window, func);

			return 0;
		}
	}
}

// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow*, int width, int height) {
	glViewport(0, 0, width, height);
}
