#ifndef WINDOWH
#define WINDOWH

// Thirdparty
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard
#include <stdio.h>
#include <string.h>

// Structs
struct core_window_Window {
	int width;
	int height;
	char* title;

	GLFWwindow* window;
};

// Functions
int core_window_windowInit(struct core_window_Window* window, int width, int height, char* title);


#endif
