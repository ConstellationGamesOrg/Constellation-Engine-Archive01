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
				// Failed to create GLFW window. If you have an Intel GPU, they are not 3.3 compatible.
				glfwTerminate();
				return -1;
			}

			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				// Failed to initialize GLAD

				return -1;
			}

			// Configure global OpenGL state
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_FRAMEBUFFER_SRGB); // Use sRGB
			glfwSwapInterval(1); // Turn on vsync for smoother rendering and so OpenGL doesn't draw faster than the monitor refresh rate. Otherwise the program might use 100% CPU and GPU

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

		int Window::update() {
			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwWindowShouldClose(window)) {
				shouldClose = true;
			}

			return 0;
		}

		int Window::clear()
		{
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			return 0;
		}

		int Window::cleanup() {
			glfwTerminate();

			return 0;
		}
	}
}
