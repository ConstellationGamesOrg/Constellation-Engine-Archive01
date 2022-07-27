// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "main.hpp"

CE::core::Graphics graphics;
CE::core::Window window;
CE::core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Callback functions
// ------------------
// Input callback. Process all input
void processInput(CE::core::Window* window) {
	if (CE::core::input::getKeyPress(window->window, KEY_ESCAPE) == 1) // Check if the ESC key was pressed
		window->shouldClose = true;                            // If so, close the window

	if (CE::core::input::getKeyPress(window->window, KEY_W) == 1)
		camera.ProcessKeyboard(CE::core::FORWARD, window->dt);
	if (CE::core::input::getKeyPress(window->window, GLFW_KEY_S) == 1)
		camera.ProcessKeyboard(CE::core::BACKWARD, window->dt);
	if (CE::core::input::getKeyPress(window->window, KEY_A) == 1)
		camera.ProcessKeyboard(CE::core::LEFT, window->dt);
	if (CE::core::input::getKeyPress(window->window, KEY_D) == 1)
		camera.ProcessKeyboard(CE::core::RIGHT, window->dt);
	if (CE::core::input::getKeyPress(window->window, KEY_SPACE) == 1)
		camera.ProcessKeyboard(CE::core::UP, window->dt);
	if (CE::core::input::getKeyPress(window->window, KEY_LEFT_SHIFT) == 1)
		camera.ProcessKeyboard(CE::core::DOWN, window->dt);

	if (CE::core::input::getKeyPress(window->window, KEY_F) == 1)
		window->unlockMouse();
	if (CE::core::input::getKeyPress(window->window, MOUSE_BUTTON_LEFT) == 1)
		window->lockMouse();
}

// Mouse callback. Whenever the mouse moves, this function is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	camera.ProcessMouseMovement(window, xposIn, yposIn);
}

// Scroll callback. Whenever the mouse scroll wheel scrolls, this function is called
void scroll_callback(GLFWwindow*, double, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main() {
	graphics.create();

	window.create(800, 600, "Constellation Engine");

	// Set callback functions
	window.setKeyboardInputCallback(processInput);
	window.setMouseInputCallback(mouse_callback);
	window.setMouseScrollCallback(scroll_callback);

	//window.clearColor = {0.5f, 0.0f, 0.4f, 1.0f};
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
		window.update();

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
