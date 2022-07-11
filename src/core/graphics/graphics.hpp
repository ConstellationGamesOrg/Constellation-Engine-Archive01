#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

// 3rd Party Library Headers
// -------------------------
#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Library Headers
// ------------------------
#include <iostream>

namespace CE {
	namespace core {
		class Graphics {
		public:
			int create();
			int create(int versionMajor, int versionMinor);
		};
	}
}


#endif // GRAPHICS_HPP
