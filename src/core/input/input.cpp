// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#include "input.hpp"

namespace CE {
	namespace core {
		int Input::getKeyPress(GLFWwindow* window, int key) {
			if (glfwGetKey(window, key)) {
				return 1;
			}

			return 0;
		}
	}
}