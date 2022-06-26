#include "graphics.h"

int core_graphics_setGlVer(struct graphicsSettings* graphicsSettings, int verMajor, int verMinor) {
	graphicsSettings->verMajor = verMajor;
	graphicsSettings->verMinor = verMinor;

	return 0;
}

int core_graphics_graphicsInit(struct graphicsSettings* graphicsSettings) {
	glfwInit();

	if (graphicsSettings != NULL) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, graphicsSettings->verMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, graphicsSettings->verMinor);
	} else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifndef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return 0;
}
