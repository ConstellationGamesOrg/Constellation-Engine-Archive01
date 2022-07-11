// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

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



// Callback functions
// ------------------
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Input callback. Process all input
void processInput(CE::core::Window window, CE::core::Camera* camera, float deltaTime) {

	if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if the ESC key was pressed
		glfwSetWindowShouldClose(window.window, true);            // If so, close the window
	if (glfwGetKey(window.window, GLFW_KEY_Q) == GLFW_PRESS) // Check if the Q key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    // If so, change draw mode to GL_FILL
	if (glfwGetKey(window.window, GLFW_KEY_E) == GLFW_PRESS) // Check if the E key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    // If so, change draw mode to GL_LINE / wireframe


	if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::FORWARD, deltaTime);
	if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::BACKWARD, deltaTime);
	if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::LEFT, deltaTime);
	if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::RIGHT, deltaTime);
	if (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(CE::core::UP, deltaTime);
	if (glfwGetKey(window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
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
	CE::utils::Shader cubeShader("data/shaders/cube.vert", "data/shaders/cube.frag");
	
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
	std::vector<glm::vec3> cubePositions = {
	glm::vec3( 0.0f,  0.0f,   0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f,  -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f,  -3.5f),
	glm::vec3(-1.7f,  3.0f,  -7.5f),
	glm::vec3( 1.3f, -2.0f,  -2.5f),
	glm::vec3( 1.5f,  2.0f,  -2.5f),
	glm::vec3( 1.5f,  0.2f,  -1.5f),
	glm::vec3(-1.3f,  1.0f,  -1.5f)
	};



	// Setup VAO and VBO // TODO: Move this to some graphics create object function
	// -----------------
	// Vertex Buffer Object // Vertex Array Object
	unsigned int VBO, cubeVAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &cubeVAO);

	// VBO
	// Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), &vertices.front(), GL_STATIC_DRAW); // https://stackoverflow.com/questions/7173494/vbos-with-stdvector
	// GL_STATIC_DRAW: Data will be modified once and used many times
	// GL_DYNAMIC_DRAW: Data will be modified repeatedly and used many times
	// GL_STREAM_DRAW: Data will be modified once and used at most a few times


	// cubeVAO
	// Bind the Vertex Array Object first, then set vertex buffer(s), and then configure vertex attributes(s)
	glBindVertexArray(cubeVAO);

	// Then set our vertex attributes pointers
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Please note that we put 5 * sizeof(float) here because we have 3 floats for position and 2 floats for texture
	glEnableVertexAttribArray(0);
	// Texture attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);



	// Load and create a texture // TODO: Move this to a texture module in utils/
	// -------------------------
	unsigned int texture1;

	// texture1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set the texture filtering parameters (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // Tell stb_image.h to flip loaded texture's on the y-axis. The standard OpenGL texture coordinate system is upside down. (Because texture coordinates go from 0 to 1 and not 0 to -1)
	unsigned char* data = stbi_load("data/textures/PixelLogo.png", &width, &height, &nrComponents, 0);  // logo.png has transparency, so make sure to tell OpenGL the data type is of GL_RGBA (4 channels)
	if (data) {
		GLenum format = GL_RGBA; // Assume GL_RGBA (images with alpha channel) because they are the most commonly used by me (also removes compiler warnings)
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);



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

		if (glfwGetKey(window.window, GLFW_KEY_RIGHT)) {
			if (window.clearColor[1] < 1.0f) {
				window.clearColor[1] += 0.01f;
			}
			else {
				window.clearColor[1] = 1.0f;
			}
		} if (glfwGetKey(window.window, GLFW_KEY_LEFT)) {
			if (window.clearColor[1] > 0.0f) {
				window.clearColor[1] -= 0.01f;
			}
			else {
				window.clearColor[1] = 0.0f;
			}
		}

		if (glfwGetKey(window.window, GLFW_KEY_UP)) {
			if (window.clearColor[0] < 1.0f) {
				window.clearColor[0] += 0.01f;
			}
			else {
				window.clearColor[0] = 1.0f;
			}
		} if (glfwGetKey(window.window, GLFW_KEY_DOWN)) {
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

		// Projection matrix
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window.width) / static_cast<float>(window.height), 0.1f, 100.0f);
		cubeShader.setMat4("projection", projection);

		// View transformation
		glm::mat4 view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		cubeShader.setMat4("view", view);

		// Bind texture1
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Bind the cubeVAO
		glBindVertexArray(cubeVAO);

		// Render cubes
		for (unsigned int i = 0; i < cubePositions.size(); i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
		glBindVertexArray(0);

		window.update();
	}

	// Clean up // TODO: Move clean up to graphics cleanup
	// --------
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(cubeShader.ID);

	window.cleanup();
	return 0;
}