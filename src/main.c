#include "main.h"

int main() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

	core_graphics_graphicsSettings(NULL);

	struct core_window_Window window;

	vec4 clearColor = {0.3f, 0.3f, 0.4f, 1.0f};

	core_window_windowInit(&window, 800, 600, "Constellation Engine Window", clearColor);

	struct core_graphics_world graphicsWorld;
	struct core_graphics_obj graphicsObj;

	core_graphics_createObj(&graphicsObj, &graphicsWorld, vertices, "res/shaders/triangle/triangle.vert", "res/shaders/triangle/triangle.frag");

	while (!window.shouldClose) {
		if (core_input_isPressed(&window, KEY_ESCAPE) == 1) {
			window.shouldClose = true;
		}

		if (core_input_isPressed(&window, KEY_RIGHT) == 1) {
			window.clearColor[1] += 0.01f;
		}
		
		if (core_input_isPressed(&window, KEY_LEFT) == 1) {
			window.clearColor[1] -= 0.01f;
		}

		if (core_input_isPressed(&window, KEY_UP) == 1) {
			window.clearColor[0] += 0.01f;
		}
		
		if (core_input_isPressed(&window, KEY_DOWN) == 1) {
			window.clearColor[0] -= 0.01f;
		}

		core_window_clear(&window);

		core_graphics_render(&graphicsObj, &graphicsWorld);

		core_window_update(&window);
	}

	core_window_cleanup();
	return 0;
}
