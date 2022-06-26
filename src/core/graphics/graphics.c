#include "graphics.h"

int core_graphics_setGlVer(struct core_graphics_settings* graphicsSettings, int verMajor, int verMinor) {
	graphicsSettings->verMajor = verMajor;
	graphicsSettings->verMinor = verMinor;

	return 0;
}

int core_graphics_graphicsSettings(struct core_graphics_settings* graphicsSettings) {
	glfwInit();

	if (graphicsSettings != NULL) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, graphicsSettings->verMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, graphicsSettings->verMinor);
	} else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return 0;
}

int core_graphics_createObj(struct core_graphics_obj* graphicsObj, struct core_graphics_world* graphicsWorld, float vertices[], char* vertPath, char* fragPath) {
	if (graphicsObj == NULL) {
#ifdef DEBUG
		printf("WARNING: No graphicsObj object was passed to core_graphics_createObj. You will not be able to use this object in the future (you will need to)\n");
#endif
		return -1;
	}

	if (graphicsWorld == NULL) {
#ifdef DEBUG
		printf("WARNING: No graphicsworld object was passed to core_graphics_createObj. You will not be able to use this object in the future (you will need to)\n");
#endif
		return -1;
	}

	if (vertPath == NULL) {
#ifdef DEBUG
		printf("WARNING: No vertPath was passed to core_graphics_createObj. Shader loading and compilation will fail.\n");
#endif
		return -1;
	}

	if (fragPath == NULL) {
#ifdef DEBUG
		printf("WARNING: No fragPath was passed to core_graphics_createObj. Shader loading and compilation will fail.\n");
#endif
		return -1;
	}

	// Generate IDs for the buffers
	glGenBuffers(1, &graphicsObj->VBO);
	glGenVertexArrays(1, &graphicsObj->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, graphicsObj->VBO);
	
	// Copy the vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	const char* vertexShaderSource = util_readFile(vertPath);

	if (vertexShaderSource == NULL)
		return -1;

	graphicsObj->vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(graphicsObj->vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(graphicsObj->vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(graphicsObj->vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(graphicsObj->vertexShader, 512, NULL, infoLog);
#ifdef DEBUG
		printf("ERROR: Compilation of shader at %s FAILED Full output:\n%s\n", vertPath, infoLog);
#endif
	}

	graphicsObj->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fragmentShaderSource = util_readFile(fragPath);

	glShaderSource(graphicsObj->fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(graphicsObj->fragmentShader);

	glGetShaderiv(graphicsObj->fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(graphicsObj->fragmentShader, 512, NULL, infoLog);
#ifdef DEBUG
		printf("ERROR: Compilation of shader at %s FAILED Full output:\n%s\n", fragPath, infoLog);
#endif
	}

	graphicsWorld->shaderProgram = glCreateProgram();

	glAttachShader(graphicsWorld->shaderProgram, graphicsObj->vertexShader);
	glAttachShader(graphicsWorld->shaderProgram, graphicsObj->fragmentShader);

	glLinkProgram(graphicsWorld->shaderProgram);

	glGetProgramiv(graphicsWorld->shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(graphicsWorld->shaderProgram, 512, NULL, infoLog);

#ifdef DEBUG
		printf("WARNING: Linking shaders to the shader program FAILED Full output:\n%s\n", infoLog);
#endif
		return -1;
	}

	glUseProgram(graphicsWorld->shaderProgram);

	// Cleanup
	glDeleteShader(graphicsObj->vertexShader);
	glDeleteShader(graphicsObj->fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	return 0;
}

int core_graphics_render(struct core_graphics_obj* graphicsObj, struct core_graphics_world* graphicsWorld) {
	glUseProgram(graphicsWorld->shaderProgram);
	glBindVertexArray(graphicsObj->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return 0;
}
