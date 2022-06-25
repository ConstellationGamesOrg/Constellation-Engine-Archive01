#include "input.h"

int core_input_isPressed(struct core_window_Window* window, int key) {
	if (glfwGetKey(window->window, key)) {
		return 1;
	}

	return 0;
}
