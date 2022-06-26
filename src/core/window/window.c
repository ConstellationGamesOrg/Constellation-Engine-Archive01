#include "window.h"

int core_window_windowInit(struct core_window_Window* window, int width, int height, char* title, vec4 clearColor) {
	if (window == NULL) {
#ifdef DEBUG
		printf("WARNING: No core_window_Window object was given to core_window_windowInit. You will not be able to use this window object in the future (you will need to).\n");
#endif
	}

	if (width == 0) {
		width = 800;
	}

	if (height == 0) {
		height = 600;
	}

	if (strcmp(title, "") == 0) {
		title = "Constellation Engine Window";
	}

	window->width = width;
	window->height = height;
	window->shouldClose = 0;

	window->title = title;

	window->window = glfwCreateWindow(width, height, title, NULL, NULL);

	window->clearColor[0] = clearColor[0];
	window->clearColor[1] = clearColor[1];
	window->clearColor[2] = clearColor[2];
	window->clearColor[3] = clearColor[3];

	if (window->window == NULL) {
		printf("ERROR: Window creation FAILED!\n");

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("ERROR: GLAD initialization FAILED!\n");

		return -1;
	}

	glViewport(0, 0, window->width, window->height);

	glfwSetFramebufferSizeCallback(window->window, core_window_framebufferSizeCallback);

	return 0;
}

int core_window_clear(struct core_window_Window* window) {
	glClearColor(window->clearColor[0], window->clearColor[1], window->clearColor[2], window->clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	return 0;
}

int core_window_update(struct core_window_Window* window) {
	if (window == NULL) {
		printf("ERROR: No core_window_Window object was given to the core_window_refresh function.\n");

		return -1;
	}

	glfwSwapBuffers(window->window);
	glfwPollEvents();

	if (glfwWindowShouldClose(window->window)) {
		window->shouldClose = 1;
	}

	return 0;
}

int core_window_cleanup() {
	glfwTerminate();

	return 0;
}

void core_window_framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	UNUSED(window);
	glViewport(0, 0, width, height);
}
