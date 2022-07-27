#include "light.hpp"

namespace CE {
	namespace core {
		Light::use(CE::core::Shader shader) {
			glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, glm::value_ptr(pos));
		}
	}
}
