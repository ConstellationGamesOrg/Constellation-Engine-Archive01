#ifndef GRAPHICSH
#define GRAPHICSH

// CE
#include "../../util/util.h"

// Thirdparty
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard
#include <stdio.h>
#include <string.h>

struct core_graphics_settings {
	int verMajor;
	int verMinor;
};

struct core_graphics_world {
	unsigned int shaderProgram;
};

struct core_graphics_obj {
	unsigned int VBO;
	unsigned int VAO;
	unsigned int vertexShader;
	unsigned int fragmentShader;
};

// Functions
int core_graphics_setGlVer(struct core_graphics_settings* graphicsSettings, int verMajor, int verMinor);
int core_graphics_graphicsSettings(struct core_graphics_settings* graphicsSettings);
int core_graphics_createObj(struct core_graphics_obj* graphicsObj, struct core_graphics_world* graphicsWorld, float vertices[], char* vertPath, char* fragPath);
int core_graphics_render(struct core_graphics_obj* graphicsObj, struct core_graphics_world* graphicsWorld);
int core_graphics_cleanup(struct core_graphics_obj* graphicsObj, struct core_graphics_world* graphicsWorld);

#endif
