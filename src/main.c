#include "main.h"

int main() {
	float vertices[] = {
	//    X      Y     Z      R     G     B
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
	};
	core_graphics_graphicsSettings(NULL);

	struct core_window_Window window;

	vec4 clearColor = {0.3f, 0.3f, 0.4f, 1.0f};

	core_window_windowInit(&window, 800, 600, "Constellation Engine Window", clearColor);

	struct core_graphics_world graphicsWorld;
	struct core_graphics_obj graphicsObj;

	core_graphics_createObj(&graphicsObj, &graphicsWorld, vertices, 9 * sizeof(float), "res/shaders/triangle/triangle.vert", "res/shaders/triangle/triangle.frag");

	while (!window.shouldClose) {
		if (core_input_isPressed(&window, KEY_ESCAPE) == 1) {
			window.shouldClose = true;
		}

		if (core_input_isPressed(&window, KEY_RIGHT) == 1) {
			if (window.clearColor[1] < 1.0f) {
				window.clearColor[1] += 0.01f;
			} else {
				window.clearColor[1] = 1.0f;
			}
		} if (core_input_isPressed(&window, KEY_LEFT) == 1) {
			if (window.clearColor[1] > 0.0f) {
				window.clearColor[1] -= 0.01f;
			} else {
				window.clearColor[1] = 0.0f;
			}
		}

		if (core_input_isPressed(&window, KEY_UP) == 1) {
			if (window.clearColor[0] < 1.0f) {
				window.clearColor[0] += 0.01f;
			} else {
				window.clearColor[0] = 1.0f;
			}
		} if (core_input_isPressed(&window, KEY_DOWN) == 1) {
			if (window.clearColor[0] > 0.0f) {
				window.clearColor[0] -= 0.01f;
			} else {
				window.clearColor[0] = 0.0f;
			}
		}

		core_window_clear(&window);

		core_graphics_render(&graphicsObj, &graphicsWorld);

		core_window_update(&window);
	}

	core_graphics_cleanup(&graphicsObj, &graphicsWorld);
	core_window_cleanup();

	return 0;
}
