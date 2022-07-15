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

// Callback functions
// ------------------
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Input callback. Process all input
void processInput(CE::core::Window window, CE::core::Camera* camera, float deltaTime) {

	if (input.getKeyPress(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)     // Check if the ESC key was pressed
		glfwSetWindowShouldClose(window.window, true);                   // If so, close the window
	if (input.getKeyPress(window.window, GLFW_KEY_Q) == GLFW_PRESS)          // Check if the Q key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                       // If so, change draw mode to GL_FILL
	if (input.getKeyPress(window.window, GLFW_KEY_E) == GLFW_PRESS)          // Check if the E key was pressed
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
}

// Mouse callback. Whenever the mouse moves, this function is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse) {
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

// Scroll callback. Whenever the mouse scroll wheel scrolls, this function is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
bool CheckIfCollision(CubeMonster cubemonster1, CubeMonster cubemonster2)
{
	
	if (cubemonster1.mesh.position.x +  0.5 >= cubemonster2.mesh.position.x && cubemonster2.mesh.position.x + 0.5 >= cubemonster1.mesh.position.x
		 && cubemonster1.mesh.position.z + 0.5 >= cubemonster2.mesh.position.z && cubemonster2.mesh.position.z + 0.5 >= cubemonster1.mesh.position.z)
	{

		return true;
	}
	return false; 
}
void MeetAndKill(int i, int j )
{
	
			if (CheckIfCollision(damonsters[i], damonsters[j]) && i != j)
			{
				if (damonsters[i].mass > damonsters[j].mass)
				{
					damonsters[j].IsDeleted = true;
					damonsters[i].energy -= 100000;
					damonsters[i].energy += damonsters[j].energy;
					std::cout << j << "kill " << std::endl;
					

				}
				if (damonsters[j].mass > damonsters[i].mass)
				{
					damonsters[i].IsDeleted = true;
					damonsters[j].energy = damonsters[i].energy / 2;
					damonsters[j].energy += damonsters[j].energy;
					std::cout << i << "kill " << std::endl;
				}
				else
				{


				}
				
			}


	


}
int main() {
	graphics.create();

	window.create(800, 600, "Constellation Engine");

	// Setup callback functions
	glfwSetFramebufferSizeCallback(window.window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window.window, mouse_callback);
	glfwSetScrollCallback(window.window, scroll_callback);

	// Tell GLFW to capture the mouse
	glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	// Create 10 cubes
	CE::core::Object cube1(vertices, false, true);
	CE::core::Object cube2(vertices, false, true);
	CE::core::Object cube3(vertices, false, true);
	CE::core::Object cube4(vertices, false, true);
	CE::core::Object cube5(vertices, false, true);
	CE::core::Object cube6(vertices, false, true);
	

	for (int i = 0; i < 20; i++)
	{
	  
	  CE::core::Object cubemesh(vertices, false, true);
	  glm::vec3 value { rand() % 10, 0, rand() % 10 };
	  CubeMonster monster(false, rand()% 20 +10, value, rand() % 10, 4000000, &cubemesh);
	  monster.mesh.translate({ 0.0f,  0.0f,   2.3f });
	  damonsters.push_back(monster);
	}
  
	// Set their starting position
	cube1.translate({   0.0f,  0.0f,   2.3f });
	cube2.translate({   2.0f,  0.0f, 4.5f });
	cube3.translate({  -1.5f, 0.0f,  6.1f });
	cube4.translate({  -3.8f, 0.0f,  5.6f });
	cube5.translate({   2.4f, 0.0f,   4.7f });
	cube6.translate({  -1.7f,  0.0f,   4.3f });


	// Load and create a texture
	// -------------------------
	CE::core::Texture texture1;
	texture1.loadTexture("data/textures/PixelLogo.png");

	cubeShader.use();

	// Tell OpenGL which sampler each texture unit belongs to
	// ------------------------------------------------------
	cubeShader.setInt("texture1", 0);

	// Program loop
	// ------------
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
	

		// Update projection and view matrix
		window.updateMatrices(&cubeShader, &camera);

		// Bind texture1
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1.textureID);

		// Bind the cubeVAO
		glBindVertexArray(cube1.VAO);

		//From here onwards you are entering the land of messy code. 
		//Checks if any are alive. 

		if (damonsters.size() == 0)
		{

			std::cout << "0 left alive! " << std::endl;
		}
		//For loop, iterating through each "monster" once. 
		for (int i = 0; i < damonsters.size();)
		{
			if (damonsters[i].mesh.position.x > 30|| damonsters[i].mesh.position.z> 30||
				damonsters[i].mesh.position.x < -30|| damonsters[i].mesh.position.z> -30)
			{
				damonsters[i].mesh.position.x = rand() % 10;
				damonsters[i].mesh.position.z = rand() % 10;
				damonsters[i].mesh.movementSpeed -= 40;
				
				

			}
		    //Deleted bool, if deleted is true, the things gets deleted in the else statement otherwise the process is allowed to continue. 
			if (damonsters[i].IsDeleted != true)
			{
				std::cout << damonsters[i].energy << std::endl;
				//drains energy based on speed and mass. Mass particularly but didn't seem to stop "fortress" cubes.  
				damonsters[i].energy -= damonsters[i].speed * pow(damonsters[i].mass, 3);
                
				if (damonsters[i].energy > 0)
				{
					std::cout << damonsters[i].speed << "speed" <<std::endl;
					if (damonsters[i].energy >= 2000000)
					{
						if (damonsters.size() < 80)
						{
							CE::core::Object cubemesh(vertices, false, true);
							CubeMonster monster = damonsters[i];
							monster.speed *= (rand() % 3 + 99) / 1000000000000000 + 1 ;
							monster.mass *= (rand() % 3 + 99) / 10000000000000000;
							monster.energy = 4000000;
							monster.mesh.translate(glm::vec3(damonsters[i].mesh.position.x + rand() % 6 - 3,0, damonsters[i].mesh.position.z + rand() % 6 - 3));
						
							damonsters.push_back(monster);
							damonsters[i].energy -= 4000;

						}
						

					}

					damonsters[i].mesh.movementSpeed = damonsters[i].speed; // You can change each cube's speed, default 2.5f
					damonsters[i].mesh.translate({ rand() % 3 - 1, 0,  rand() % 3 - 1 }, deltaTime);
					damonsters[i].mesh.set(&cubeShader);
					damonsters[i].mesh.draw();
					i++; 

				}
				else
				{

					damonsters.erase(damonsters.begin() + i
					);

				}

			}
			else
			{

				damonsters.erase(damonsters.begin() + i);
			}
			
			
			
			

		}
		for (int i = 0; i < damonsters.size(); i++)
		{
			for (int j = 0; j < damonsters.size(); j++)
			{
				MeetAndKill(i, j);

			}

		}

	
		
		
		
		
		/*
		// Render cubes
		cube1.movementSpeed = 4; // You can change each cube's speed, default 2.5f
		cube1.translate({ rand() % 3 - 1, 0,  rand() % 3 - 1 }, deltaTime); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time
		cube1.set(&cubeShader); // Set/Save the changes
		cube1.draw(); // Now actually draw the cube!
		
		cube2.movementSpeed = 4; // You can change each cube's speed, default 2.5f
		cube2.translate({ rand() % 3 - 1, 0,  rand() % 3 - 1 }, deltaTime); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time
		cube2.set(&cubeShader); // Set/Save the changes
		cube2.draw(); // Now actually draw the cube!
		
		cube3.movementSpeed = 4; // You can change each cube's speed, default 2.5f
		cube3.translate({ rand() % 3 - 1,  0,  rand() % 3 - 1 }, deltaTime); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time
		cube3.set(&cubeShader); // Set/Save the changes
		cube3.draw(); // Now actually draw the cube!
		
		cube4.movementSpeed = 4; // You can change each cube's speed, default 2.5f
		cube4.translate({ rand() % 3 - 1,  0,  rand() % 3 - 1 }, deltaTime); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time
		cube4.set(&cubeShader); // Set/Save the changes
		cube4.draw(); // Now actually draw the cube!
		
		cube5.movementSpeed =4; // You can change each cube's speed, default 2.5f
		cube5.translate({ rand() % 3 - 1,  0,  rand() % 3 - 1 }, deltaTime); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time
		cube5.set(&cubeShader); // Set/Save the changes
		cube5.draw(); // Now actually draw the cube!
		
		cube6.movementSpeed = 4;// You can change each cube's speed, default 2.5f
		cube6.translate({ rand() % 3 - 1, 0,  rand() % 3 - 1 }, deltaTime); // This will move the cube by 0.1 on the z axis every frame. Its slow instead of really fast because of delta time
		cube6.set(&cubeShader); // Set/Save the changes
		cube6.draw(); // Now actually draw the cube!
		*/

		// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
		glBindVertexArray(0);
		std::cout << damonsters.size() << std::endl;
		window.update();
	}

	window.cleanup();

	return 0;
}

CubeMonster::CubeMonster(bool IsDeleted1, float speed1, glm::vec3 startingposition1, float mass1, float energy1, CE::core::Object* mesh1)
{
	IsDeleted = IsDeleted1;
	speed = speed1;
	startingposition = startingposition1;
	mass = mass1;
	energy = energy1;
	mesh = *mesh1;
}
