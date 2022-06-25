#include "main.h"

int main() {
	core_graphics_graphicsInit(NULL);

	struct core_window_Window window;

	vec4 clearColour = {0.3f, 0.3f, 0.4f, 1.0f};

	core_window_windowInit(&window, 800, 600, "Constellation Engine Window", clearColour);

	while (!window.shouldClose) {
		if (core_input_isPressed(&window, KEY_ESCAPE) == 1) {
			window.shouldClose = true;
		}

		core_window_refresh(&window);
	}

	core_window_cleanup();
	return 0;
}
