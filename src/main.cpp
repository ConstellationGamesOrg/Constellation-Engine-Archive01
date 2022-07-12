#include "main.hpp"

// Settings
// --------
// Timing
float deltaTime = 0.0f;	// deltaTime is the time between current frame and last frame
float lastFrame = 0.0f;

// Graphics
CE::core::Graphics graphics;

// Window
CE::core::Window window;

// Camera
CE::core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = window.width / 2.0f;
float lastY = window.height / 2.0f;
bool firstMouse = true;

// Input
CE::core::Input input;



// Callback functions
// ------------------
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Input callback. Process all input
void processInput(CE::core::Window window, CE::core::Camera* camera, float deltaTime) {

	if (input.getKeyPress(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if the ESC key was pressed
		glfwSetWindowShouldClose(window.window, true);            // If so, close the window
	if (input.getKeyPress(window.window, GLFW_KEY_Q) == GLFW_PRESS) // Check if the Q key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    // If so, change draw mode to GL_FILL
	if (input.getKeyPress(window.window, GLFW_KEY_E) == GLFW_PRESS) // Check if the E key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    // If so, change draw mode to GL_LINE / wireframe


	if (input.getKeyPress(window.window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::FORWARD, deltaTime);
	if (input.getKeyPress(window.window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::BACKWARD, deltaTime);
	if (input.getKeyPress(window.window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::LEFT, deltaTime);
	if (input.getKeyPress(window.window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::RIGHT, deltaTime);
	if (input.getKeyPress(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::UP, deltaTime);
	if (input.getKeyPress(window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::DOWN, deltaTime);
}

// Mouse callback. Whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// Scroll callback. Whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main() {
	graphics.create();

	window.create(800, 600, "Constellation Engine");

	// Setup any callback functions
	glfwSetFramebufferSizeCallback(window.window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window.window, mouse_callback);
	glfwSetScrollCallback(window.window, scroll_callback);

	// Tell GLFW to capture our mouse
	glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	window.clearColor = { 0.5f, 0.0f, 0.4f, 1.0f };

	// Build and compile our shader program
	// ------------------------------------
	CE::core::Shader cubeShader("data/shaders/cube.vert", "data/shaders/cube.frag");
	
	// Setup vertex data
	std::vector<float> vertices = {
		// Positions           // Texture coords
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
							   
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
							   
		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
							   
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
							   
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
							   
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f
	};



	// Create 10 cubes
	CE::core::Object cube1(vertices, false, true);
	CE::core::Object cube2(vertices, false, true);
	CE::core::Object cube3(vertices, false, true);
	CE::core::Object cube4(vertices, false, true);
	CE::core::Object cube5(vertices, false, true);
	CE::core::Object cube6(vertices, false, true);
	CE::core::Object cube7(vertices, false, true);
	CE::core::Object cube8(vertices, false, true);
	CE::core::Object cube9(vertices, false, true);
	CE::core::Object cube10(vertices, false, true);

	// Set their starting position
	cube1.translate({   0.0f,  0.0f,   0.0f });
	cube2.translate({   2.0f,  5.0f, -15.0f });
	cube3.translate({  -1.5f, -2.2f,  -2.5f });
	cube4.translate({  -3.8f, -2.0f, -12.3f });
	cube5.translate({   2.4f, -0.4f,  -3.5f });
	cube6.translate({  -1.7f,  3.0f,  -7.5f });
	cube7.translate({   1.3f, -2.0f,  -2.5f });
	cube8.translate({   1.5f,  2.0f,  -2.5f });
	cube9.translate({   1.5f,  0.2f,  -1.5f });
	cube10.translate({ -1.3f,  1.0f,  -1.5f });



	// Load and create a texture
	// -------------------------
	CE::core::Texture texture1;
	texture1.loadTexture("data/textures/PixelLogo.png");



	// Tell OpenGL for each sampler to which texture unit it belongs to
	// ----------------------------------------------------------------
	// Activate the shader
	cubeShader.use();
	// Either set it via the texture class
	cubeShader.setInt("texture1", 0);



	// Render loop
	// -----------
	while (!window.shouldClose) {
		// Per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;



		// Input
		// -----
		processInput(window, &camera, deltaTime);

		// TODO: Move this to process input
		if (input.getKeyPress(window.window, GLFW_KEY_RIGHT)) {
			if (window.clearColor[1] < 1.0f) {
				window.clearColor[1] += 0.01f;
			}
			else {
				window.clearColor[1] = 1.0f;
			}
		} if (input.getKeyPress(window.window, GLFW_KEY_LEFT)) {
			if (window.clearColor[1] > 0.0f) {
				window.clearColor[1] -= 0.01f;
			}
			else {
				window.clearColor[1] = 0.0f;
			}
		}

		if (input.getKeyPress(window.window, GLFW_KEY_UP)) {
			if (window.clearColor[0] < 1.0f) {
				window.clearColor[0] += 0.01f;
			}
			else {
				window.clearColor[0] = 1.0f;
			}
		} if (input.getKeyPress(window.window, GLFW_KEY_DOWN)) {
			if (window.clearColor[0] > 0.0f) {
				window.clearColor[0] -= 0.01f;
			}
			else {
				window.clearColor[0] = 0.0f;
			}
		}



		// Render
		// ------
		window.clear();
		// graphics.render();

		// TODO: Move all this stuff to graphics render
		
		// Activate shader
		cubeShader.use();

		// Update projection and view matrix
		window.updateMatrices(&cubeShader, &camera);

		// Bind texture1
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1.textureID);

		// Bind the cubeVAO
		glBindVertexArray(cube1.VAO);

		// Render cubes
		cube1.movementSpeed = 5.0f;
		cube1.translate({ 0.1f, 0.0f, 0.0f }, deltaTime); // This will move the cube by 0.1 on the x axis every frame. Its slow instead of really fast because of delta time
		cube1.rotate(0.0f, { 1.0f, 0.3f, 0.5f }); // How to rotate the cubes
		cube1.set(&cubeShader); // Set/Save the changes
		cube1.draw(); // Now actually draw the cube!
		
		cube1.translate({ 1.0f, 0.3f, 0.5f }); // If you do not add delta time, the cube will jump right to that position in world space, NOT move by that much, it will teleport there.
		cube2.rotate(20.0f, { 1.0f, 0.3f, 0.5f });
		cube2.set(&cubeShader);
		cube2.draw();
		
		cube3.rotate(40.0f, { 1.0f, 0.3f, 0.5f });
		cube3.set(&cubeShader);
		cube3.draw();
		
		cube4.rotate(60.0f, { 1.0f, 0.3f, 0.5f });
		cube4.set(&cubeShader);
		cube4.draw();
		
		cube5.rotate(80.0f, { 1.0f, 0.3f, 0.5f });
		cube5.set(&cubeShader);
		cube5.draw();

		cube6.rotate(100.0f, { 1.0f, 0.3f, 0.5f });
		cube6.set(&cubeShader);
		cube6.draw();
		
		cube7.rotate(120.0f, { 1.0f, 0.3f, 0.5f });
		cube7.set(&cubeShader);
		cube7.draw();
		
		cube8.rotate(140.0f, { 1.0f, 0.3f, 0.5f });
		cube8.set(&cubeShader);
		cube8.draw();
		
		cube9.rotate(160.0f, { 1.0f, 0.3f, 0.5f });
		cube9.set(&cubeShader);
		cube9.draw();
		
		cube10.rotate(180.0f, { 1.0f, 0.3f, 0.5f });
		cube10.set(&cubeShader);
		cube10.draw();

		// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
		glBindVertexArray(0);

		window.update();
	}

	window.cleanup();
	return 0;
}
