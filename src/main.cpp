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
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Input callback. Process all input
void processInput(CE::core::Window* window, CE::core::Camera* camera) {
	if (input.getKeyPress(window->window, KEY_ESCAPE) == GLFW_PRESS) // Check if the ESC key was pressed
		glfwSetWindowShouldClose(window->window, true);               // If so, close the window
	if (input.getKeyPress(window->window, KEY_Q) == GLFW_PRESS)       // Check if the Q key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                    // If so, change draw mode to GL_FILL
	if (input.getKeyPress(window->window, KEY_E) == GLFW_PRESS)       // Check if the E key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);                    // If so, change draw mode to GL_LINE / wireframe

	if (input.getKeyPress(window->window, KEY_W) == 1)
		camera->ProcessKeyboard(CE::core::FORWARD, window->dt);
	if (input.getKeyPress(window->window, GLFW_KEY_S) == 1)
		camera->ProcessKeyboard(CE::core::BACKWARD, window->dt);
	if (input.getKeyPress(window->window, KEY_A) == 1)
		camera->ProcessKeyboard(CE::core::LEFT, window->dt);
	if (input.getKeyPress(window->window, KEY_D) == 1)
		camera->ProcessKeyboard(CE::core::RIGHT, window->dt);
	if (input.getKeyPress(window->window, KEY_SPACE) == 1)
		camera->ProcessKeyboard(CE::core::UP, window->dt);
	if (input.getKeyPress(window->window, KEY_LEFT_SHIFT) == 1)
		camera->ProcessKeyboard(CE::core::DOWN, window->dt);

	if (glfwGetKey(window->window, KEY_F) == GLFW_PRESS)
		glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetMouseButton(window->window, MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// Mouse callback. Whenever the mouse moves, this function is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	camera.ProcessMouseMovement(window, xposIn, yposIn);
}

// Scroll callback. Whenever the mouse scroll wheel scrolls, this function is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main() {
	graphics.create();

	window.create(800, 600, "Constellation Engine");

	window.setInputCallback(processInput);

	// Setup callback functions
	glfwSetFramebufferSizeCallback(window.window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window.window, mouse_callback);
	glfwSetScrollCallback(window.window, scroll_callback);

	//window.clearColor = { 0.5f, 0.0f, 0.4f, 1.0f };
	window.clearColor = { 0.2f, 0.3f, 0.3f, 1.0f };

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
