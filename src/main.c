#include "main.h"

int main() {
	float vertices[] = {
		// X     Y     Z      R     G     B       X     Y
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top right
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom left
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top left
	};

	unsigned int indices[] = {
		0, 1, 3,   // Triangle 1
		1, 2, 3    // Triangle 2
	};

	float texCoords[] = {
		0.0f, 0.0f,  // Bottom left corner
		1.0f, 0.0f,  // Bottom right corner
		0.0f, 1.0f,  // Top left corner
		1.0f, 1.0f,  // Top right corner
	};

	core_graphics_graphicsSettings(NULL);

	struct core_window_Window window;

	vec4 clearColor = {0.3f, 0.3f, 0.4f, 1.0f};

	core_window_windowInit(&window, 800, 600, "Constellation Engine Window", clearColor);

	struct core_graphics_shader shaderObj;
	struct core_graphics_obj graphicsObj;

	core_graphics_createObj(&graphicsObj, &shaderObj, vertices, sizeof(vertices), indices, sizeof(indices), "res/shaders/triangle/triangle.vert", "res/shaders/triangle/triangle.frag");

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

		core_graphics_render(&graphicsObj, &shaderObj);

		core_window_update(&window);
	}

	core_window_cleanup();
	return 0;
}
