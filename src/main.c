#include "main.h"

int main() {
	float vertices[] = {
	// X      Y      Z      X     Y
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	core_graphics_graphicsSettings(NULL);

	struct core_window_Window windowObj;

	vec4 clearColor = {0.3f, 0.3f, 0.4f, 1.0f};

	core_window_windowInit(&windowObj, 800, 600, "Constellation Engine Window", clearColor);

	struct core_graphics_shader shaderObj;
	struct core_graphics_obj graphicsObj;

	core_graphics_createObj(&graphicsObj, &shaderObj, vertices, sizeof(vertices), "res/img/Pixel Logo.png", "res/shaders/triangle/triangle.vert", "res/shaders/triangle/triangle.frag");

	while (!windowObj.shouldClose) {
		if (core_input_isPressed(&windowObj, KEY_ESCAPE) == 1) {
			windowObj.shouldClose = true;
		}

		if (core_input_isPressed(&windowObj, KEY_RIGHT) == 1) {
			if (windowObj.clearColor[1] < 1.0f) {
				windowObj.clearColor[1] += 0.01f;
			} else {
				windowObj.clearColor[1] = 1.0f;
			}
		} if (core_input_isPressed(&windowObj, KEY_LEFT) == 1) {
			if (windowObj.clearColor[1] > 0.0f) {
				windowObj.clearColor[1] -= 0.01f;
			} else {
				windowObj.clearColor[1] = 0.0f;
			}
		}

		if (core_input_isPressed(&windowObj, KEY_UP) == 1) {
			if (windowObj.clearColor[0] < 1.0f) {
				windowObj.clearColor[0] += 0.01f;
			} else {
				windowObj.clearColor[0] = 1.0f;
			}
		} if (core_input_isPressed(&windowObj, KEY_DOWN) == 1) {
			if (windowObj.clearColor[0] > 0.0f) {
				windowObj.clearColor[0] -= 0.01f;
			} else {
				windowObj.clearColor[0] = 0.0f;
			}
		}

		core_window_clear(&windowObj);

		core_graphics_render(&graphicsObj, &shaderObj);

		core_window_update(&windowObj);
	}

	core_graphics_cleanup(&graphicsObj, &shaderObj);
	core_window_cleanup();

	return 0;
}
