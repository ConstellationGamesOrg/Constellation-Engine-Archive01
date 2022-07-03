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

int core_graphics_createObj(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj, float vertices[], int verticesSize, char* vertPath, char* fragPath) {
	if (graphicsObj == NULL) {
		printf("WARNING: No graphicsObj object was passed to core_graphics_createObj. You will not be able to use this object in the future (you will need to)\n");
		return -1;
	}

	if (shaderObj == NULL) {
		printf("WARNING: No graphicsworld object was passed to core_graphics_createObj. You will not be able to use this object in the future (you will need to)\n");
		return -1;
	}

	if (vertPath == NULL) {
		printf("WARNING: No vertPath was passed to core_graphics_createObj. Shader loading and compilation will fail.\n");
		return -1;
	}

	if (fragPath == NULL) {
		printf("WARNING: No fragPath was passed to core_graphics_createObj. Shader loading and compilation will fail.\n");
		return -1;
	}

	// Build and compile shaderProgram

	core_graphics_shader_create(shaderObj, vertPath, fragPath);

	// Generate IDs for the buffers
	glGenVertexArrays(1, &graphicsObj->VAO);
	glGenBuffers(1, &graphicsObj->VBO);

	// Bind the VAO first then bind + set vertex buffers then configure vertex attribs
    glBindVertexArray(graphicsObj->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, graphicsObj->VBO);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	// Position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Colour attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return 0;
}

int core_graphics_render(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj) {
	core_graphics_shader_use(shaderObj);
	glBindVertexArray(graphicsObj->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 9);

	return 0;
}

int core_graphics_cleanup(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj) {
	glDeleteVertexArrays(1, &graphicsObj->VAO);
	glDeleteBuffers(1, &graphicsObj->VBO);
	glDeleteProgram(shaderObj->ID);

	return 0;
}

void core_graphics_shader_create(struct core_graphics_shader* shaderObj, char* vertPath, char* fragPath) {
	// Vertex Shader
	unsigned int vertexShader;
	const char* vertexShaderSource = util_readFile(vertPath);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for shader compilation errors
	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

		printf("ERROR: Compilation of vertex shader at %s FAILED Full output:\n%s\n", vertPath, infoLog);
	}

	// Fragment shader
	unsigned int fragmentShader;
	const char* fragmentShaderSource = util_readFile(fragPath);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check for shader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

		printf("ERROR: Compilation of fragment shader at %s FAILED Full output:\n%s\n", fragPath, infoLog);
	}

	// Link shaders
	shaderObj->ID = glCreateProgram();

	glAttachShader(shaderObj->ID, vertexShader);
	glAttachShader(shaderObj->ID, fragmentShader);

	glLinkProgram(shaderObj->ID);

	// Check for linking errors
	glGetProgramiv(shaderObj->ID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderObj->ID, 512, NULL, infoLog);
		printf("WARNING: Linking shaders to the shader program FAILED Full output:\n%s\n", infoLog);
	}

	// Cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void core_graphics_shader_use(struct core_graphics_shader* shaderObj) {
	glUseProgram(shaderObj->ID);
}

void core_graphics_shader_setBool(struct core_graphics_shader* shaderObj, const char* name, bool value) {
	glUniform1i(glGetUniformLocation(shaderObj->ID, name), (int)value);
}
void core_graphics_shader_setInt(struct core_graphics_shader* shaderObj, const char* name, int value) {
	glUniform1i(glGetUniformLocation(shaderObj->ID, name), value);
}
void core_graphics_shader_setFloat(struct core_graphics_shader* shaderObj, const char* name, float value) {
	glUniform1f(glGetUniformLocation(shaderObj->ID, name), value);
}
