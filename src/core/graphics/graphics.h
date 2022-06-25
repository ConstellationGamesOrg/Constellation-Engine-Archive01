#ifndef GRAPHICSH
#define GRAPHICSH

// Thirdparty
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard
#include <stdio.h>

struct graphicsSettings {
	int verMajor;
	int verMinor;
};

// Functions
int core_graphics_setGlVer(struct graphicsSettings* graphicsSettings, int verMajor, int verMinor);
int core_graphics_graphicsInit(struct graphicsSettings* graphicsSettings);

#endif
