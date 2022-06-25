#include "main.h"

int main() {
	core_graphics_graphicsInit(NULL);

	struct core_window_Window window;

	core_window_windowInit(&window, 800, 600, "");

	return 0;
}
