// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "main.hpp"

CE::core::Graphics graphics;
CE::core::Window window;
CE::core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
CE::core::Input input;

bool moved;
CE::core::Camera_Movement cMovement;

// Callback functions
// ------------------
/*
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}*/

// Input callback. Process all input
void processInput(CE::core::Window* window, CE::core::Camera* camera) {
	if (window->event.type == SDL_KEYDOWN) {
		/*auto sym = window->event.key.keysym.sym;

		if (sym == SDLK_ESCAPE) {
			window->shouldClose = true;
		} if (sym == SDLK_q) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} if (sym == SDLK_e) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} if (sym == SDLK_w) {
			camera->ProcessKeyboard(CE::core::FORWARD, window->dt);
		} if (sym == SDLK_s) {
			camera->ProcessKeyboard(CE::core::BACKWARD, window->dt);
		}*/
		switch (window->event.key.keysym.sym) {
			case SDLK_ESCAPE:
				window->shouldClose = true;

			case SDLK_q:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			case SDLK_e:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			case SDLK_w:
				camera->ProcessKeyboard(CE::core::FORWARD, 0.03f);

			case SDLK_s:
				camera->ProcessKeyboard(CE::core::BACKWARD, window->dt);

			case SDLK_a:
				camera->ProcessKeyboard(CE::core::LEFT, window->dt);

			case SDLK_d:
				camera->ProcessKeyboard(CE::core::RIGHT, window->dt);

			case SDLK_SPACE:
				camera->ProcessKeyboard(CE::core::UP, window->dt);

			case SDLK_f:
				window->mouseCaptured = false;
		}
	}
}

// Mouse callback. Whenever the mouse moves, this function is called
void mouse_callback(int x, int y) {
	camera.ProcessMouseMovement(x, y);
}
/*
// Scroll callback. Whenever the mouse scroll wheel scrolls, this function is called
void scroll_callback() {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}*/

int main() {
	window.create(800, 600, "Constellation Engine", false);

	SDL_Event event;

	//window.setInputCallback(processInput);

	// Setup callback functions
	/*glfwSetFramebufferSizeCallback(window.window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window.window, mouse_callback);
	glfwSetScrollCallback(window.window, scroll_callback);*/

	//window.clearColor = { 0.5f, 0.0f, 0.4f, 1.0f };
	window.clearColor = {0.2f, 0.3f, 0.3f, 1.0f};

	// Build and compile our shader program
	// ------------------------------------
	CE::core::Shader ourShader("data/shaders/cube.vert", "data/shaders/cube.frag");

	// Load our model
	// --------------
	CE::core::Model ourModel("data/models/cube/ConstellationGamesCube.obj");

	// Program loop
	// ------------
	while (!window.shouldClose) {
		window.update(&camera);

		while(SDL_PollEvent(&event)) {
			processInput(&window, &camera);
		}

		int x = 0;
		int y = 0;

		SDL_GetMouseState(&x, &y);
		mouse_callback(x, y);

		// Render
		// ------
		window.clear();

		// Activate shader
		ourShader.use();

		window.updateMatrices(&ourShader, &camera);

		// Render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		ourShader.setMat4("model", model);
		ourModel.Draw(ourShader);

		window.refresh();
	}

	window.cleanup();

	return 0;
}
