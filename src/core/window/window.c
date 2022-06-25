#include "window.h"

int core_window_windowInit(struct core_window_Window* window, int width, int height, char* title) {
// 	if (window == NULL) {
// #ifndef DEBUG
// 		printf("WARNING: No core_window_Window object was given to core_window_windowInit. You will not be able to use this window object in the future (You will probably need to).\n");
// #endif
// 	}

	if (width == 0) {
		width = 800;
	}

	if (height == 0) {
		height = 600;
	}

	if (strcmp(title, "") == 0) {
		title = "Constellation Engine Window";
	}

// 	struct core_window_Window* window = {
// 		width = width;
// 		height = height;
// 		title = title;
//
// 		window = glfwCreateWindow(width, height, title, NULL, NULL);
// 	}

// 	window.width = width;
// 	window.height = height;
// 	window.title = title;
//
// 	window.window = glfwCreateWindow(width, height, title, NULL, NULL);
//
// 	if (window.window == NULL) {
// 		printf("Window creation FAILED!\n");
//
// 		glfwTerminate();
// 		return -1;
// 	}
//
// 	glfwMakeContextCurrent(window.window);

	window->width = width;
	window->height = height;
	window->title = title;

	window->window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window->window == NULL) {
		printf("Window creation FAILED!\n");

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("GLAD initialization FAILED!\n");

		return -1;
	}

	glViewport(0, 0, window->width, window->height);

	return 0;
}
