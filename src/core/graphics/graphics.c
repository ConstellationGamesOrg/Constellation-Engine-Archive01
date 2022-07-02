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

int core_graphics_createObj(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj, float vertices[], int verticesSize, unsigned int indices[], int indicesSize, char* vertPath, char* fragPath) {
	if (graphicsObj == NULL) {
#ifdef _DEBUG
		printf("WARNING: No graphicsObj object was passed to core_graphics_createObj. You will not be able to use this object in the future (you will need to)\n");
#endif
		return -1;
	}

	if (graphicsObj == NULL) {
#ifdef _DEBUG
		printf("WARNING: No graphicsObj object was passed to core_graphics_createObj. You will not be able to use this object in the future (you will need to)\n");
#endif
		return -1;
	}

	if (vertPath == NULL) {
#ifdef _DEBUG
		printf("WARNING: No vertPath was passed to core_graphics_createObj. Shader loading and compilation will fail.\n");
#endif
		return -1;
	}

	if (fragPath == NULL) {
#ifdef _DEBUG
		printf("WARNING: No fragPath was passed to core_graphics_createObj. Shader loading and compilation will fail.\n");
#endif
		return -1;
	}

	// Build and compile shaderProgram
	core_graphics_shader_create(shaderObj, vertPath, fragPath);

	// Generate IDs for the buffers
	glGenVertexArrays(1, &graphicsObj->VAO);
	glGenBuffers(1, &graphicsObj->VBO);
	glGenBuffers(1, &graphicsObj->EBO);

	// Bind the VAO first then bind + set vertex buffers then configure vertex attribs
    glBindVertexArray(graphicsObj->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, graphicsObj->VBO);

    // Copy the vertex data into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, graphicsObj->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}

int core_graphics_render(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj) {
	if (graphicsObj->texture != NULL) {
		glBindTexture(GL_TEXTURE_2D, graphicsObj->texture->ID);
	}

	core_graphics_shader_use(shaderObj);

	glBindVertexArray(graphicsObj->VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // No need to unbind it every time

	return 0;
}

int core_graphics_cleanup(struct core_graphics_obj* graphicsObj, struct core_graphics_shader* shaderObj) {
	glDeleteVertexArrays(1, &graphicsObj->VAO);
	glDeleteBuffers(1, &graphicsObj->VBO);
	glDeleteBuffers(1, &graphicsObj->EBO);
	glDeleteProgram(shaderObj->ID);

	return 0;
}

void core_graphics_shader_create(struct core_graphics_shader* shaderObj, char* vertPath, char* fragPath) {
	// Vertex Shader
	const char* vertexShaderSource = util_readFile(vertPath);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
	const char* fragmentShaderSource = util_readFile(fragPath);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

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

void core_graphics_shadersetBool(struct core_graphics_shader* shaderObj, char* name, bool value) {
	glUniform1i(glGetUniformLocation(shaderObj->ID, name), (int)value);
}

void core_graphics_shadersetInt(struct core_graphics_shader* shaderObj, char* name, int value) {
	glUniform1i(glGetUniformLocation(shaderObj->ID, name), value);
}

void core_graphics_shadersetFloat(struct core_graphics_shader* shaderObj, char* name, float value) {
	glUniform1f(glGetUniformLocation(shaderObj->ID, name), value);
}

void core_graphics_texture_create(struct core_graphics_texture* textureObj, char* filePath, int width, int height, int nrChannels, int hasAlpha) {
	glGenTextures(1, &textureObj->ID);
	glBindTexture(GL_TEXTURE_2D, textureObj->ID);

	// Set texture wrapping params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture filtering params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (data) {
		if (hasAlpha) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
#ifdef _DEBUG
		printf("ERORR: Texture loading FAILED\n");
#endif
	}

	stbi_image_free(data);
}

void core_graphics_texture_apply(struct core_graphics_obj* graphicsObj, struct core_graphics_texture* textureObj) {
	graphicsObj->texture = textureObj;
}
