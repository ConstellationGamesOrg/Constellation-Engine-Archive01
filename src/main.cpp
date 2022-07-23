// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "main.hpp"

// Settings
// --------
// Timing
float deltaTime = 0.0f;	// deltaTime is the time between current frame and last frame
float lastFrame = 0.0f;

CE::core::Graphics graphics;
CE::core::Window window;
CE::core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
CE::core::Input input;

float lastX = window.width / 2.0f;
float lastY = window.height / 2.0f;
bool firstMouse = true;

std::vector<CE::AI::CubeMonster> tobedestroyed;
std::vector<CE::AI::CubeMonster> damonsters;
std::vector<int> todie;
std::vector<int> alreadytodie;

// Callback functions
// ------------------
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Input callback. Process all input
void processInput(CE::core::Window window, CE::core::Camera* camera, float deltaTime) {
	if (input.getKeyPress(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if the ESC key was pressed
		glfwSetWindowShouldClose(window.window, true);                   // If so, close the window
	if (input.getKeyPress(window.window, GLFW_KEY_Q) == GLFW_PRESS)      // Check if the Q key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                       // If so, change draw mode to GL_FILL
	if (input.getKeyPress(window.window, GLFW_KEY_E) == GLFW_PRESS)      // Check if the E key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);                       // If so, change draw mode to GL_LINE / wireframe

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

	if (glfwGetKey(window.window, GLFW_KEY_F) == GLFW_PRESS)
		glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	// Setup callback functions
	glfwSetFramebufferSizeCallback(window.window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window.window, mouse_callback);
	glfwSetScrollCallback(window.window, scroll_callback);

	window.clearColor = {0.5f, 0.0f, 0.4f, 1.0f};

	// Build and compile the shader program
	// ------------------------------------
	CE::core::Shader cubeShader("data/shaders/cube.vert", "data/shaders/cube.frag");

	// Setup vertex data
	std::vector<float> vertices = {
	//    X      Y      Z       X     Y
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

	// Create cubes
	for (int i = 0; i < 20; i++) {
		CE::core::Object cubemesh(vertices, false, true);
		glm::vec3 value = {(float)(std::rand() % 10), 0.0f, (float)(std::rand() % 10)};
		CE::AI::CubeMonster monster(false, std::rand()% 20 +10, value, std::rand() % 10, 4000000, &cubemesh);

		monster.mesh.translate({0.0f, 0.0f, 2.3f});
		damonsters.push_back(monster);
	}

	std::vector <CE::core::Object*> cubes;

	for (int i = 0; i <= 5; i++) {
		CE::core::Object* newCubePointer = new CE::core::Object(vertices, false, true);
		cubes.push_back(newCubePointer);
	}

	// Set each cube's starting position
	cubes[0]->translate({  0.0f,   0.0f,   0.0f});
	cubes[1]->translate({  2.0f,   5.0f, -15.0f});
	cubes[2]->translate({ -1.5f,  -2.2f,  -2.5f});
	cubes[3]->translate({ -3.8f,  -2.0f, -12.3f});
	cubes[4]->translate({  2.4f,  -0.4f,  -3.5f});
	cubes[5]->translate({ -1.7f,   3.0f,  -7.5f});

	// Load and create a texture
	// -------------------------
	CE::core::Texture texture1;
	texture1.load("data/textures/PixelLogo.png");

	cubeShader.use();

	// Tell OpenGL which sampler each texture unit belongs to
	// ------------------------------------------------------
	cubeShader.setInt("texture1", 0);

	// Program loop
	// ------------
	while (!window.shouldClose) {
		// Update dt, fps, etc.
		// --------------------
		window.update();

		// Input
		// -----
		processInput(window, &camera, window.dt);

		// Render
		// ------
		window.clear();

		cubeShader.use();

		window.updateMatrices(&cubeShader, &camera);

	 	texture1.bind();

		// Bind the cubeVAO
		glBindVertexArray(cubes[0]->VAO);

		if (damonsters.size() == 0) {
			std::cout << "Everybody died..." << std::endl;
		}

		// For loop, iterating through each "monster" once.
		for (long unsigned int i = 0; i < damonsters.size();) {
			if (damonsters[i].mesh.position.x > 30 || damonsters[i].mesh.position.z> 30 ||
					damonsters[i].mesh.position.x < -30|| damonsters[i].mesh.position.z > -30) {
				damonsters[i].mesh.position.x = std::rand() % 10;
				damonsters[i].mesh.position.z = std::rand() % 10;
				damonsters[i].mesh.movementSpeed -= 40;
			}

		    // Deleted bool, if deleted is true, the things gets deleted in the else statement otherwise the process is allowed to continue.
			if (damonsters[i].deleted != true) {
				// Drains energy based on speed and mass. Mass particularly but didn't seem to stop "fortress" cubes.
				damonsters[i].energy -= damonsters[i].speed * pow(damonsters[i].mass, 3);

				if (damonsters[i].energy > 0) {
					if (damonsters[i].energy >= 2000000) {
						if (damonsters.size() < 80) {
							CE::core::Object cubemesh(vertices, false, true);
							CE::AI::CubeMonster monster = damonsters[i];

							monster.speed *= (std::rand() % 3 + 99) / 1000000000000000 + 1 ;
							monster.mass *= (std::rand() % 3 + 99) / 10000000000000000;
							monster.energy = 4000000;
							monster.mesh.translate(glm::vec3(damonsters[i].mesh.position.x + std::rand() % 6 - 3, 0, damonsters[i].mesh.position.z + std::rand() % 6 - 3));

							damonsters.push_back(monster);
							damonsters[i].energy -= 4000;
						}
					}

					damonsters[i].mesh.movementSpeed = damonsters[i].speed; // You can change each cube's speed, default 2.5f
					damonsters[i].mesh.translate({std::rand() % 3 - 1, 0,  std::rand() % 3 - 1}, deltaTime);
					damonsters[i].mesh.set(&cubeShader);
					damonsters[i].mesh.draw();

					i++;
				} else {
					damonsters.erase(damonsters.begin() + i);
				}
			} else {
				damonsters.erase(damonsters.begin() + i);
			}
		} for (long unsigned int i = 0; i < damonsters.size(); i++) {
			for (long unsigned int j = 0; j < damonsters.size(); j++)
				damonsters[i].meetAndKill(damonsters[j]);
		}

		glBindVertexArray(cubes[0]->VAO);

		// Update + render the cubes
		float rd = 0.0f;
		for (int i = 0; i <= 5; i++) {
			cubes[i]->rotate(rd, {1.0f, 0.3f, 0.5f});
			cubes[i]->set(&cubeShader);
			cubes[i]->draw();

			rd += 20.0f;
		}

		cubes[0]->movementSpeed = 0.5f; // You can change each cube's speed, default 2.5f
		cubes[0]->translate({ 0.0f, 0.0f, -1.0f}, window.dt); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time

		// If you do not add delta time, the cube will almost instantaneously jump right to that position in world space, NOT move by that much, it will teleport there.
		cubes[1]->translate({ 2.0f,  5.0f, -15.0f});

		// Unbind VAO (It's always a good thing to unbind buffers/arrays to prevent strange bugs)
		glBindVertexArray(0);
	}

	for (size_t i = 0; i < cubes.size(); i++) {
		delete cubes[i];
	}

	window.cleanup();

	return 0;
}
