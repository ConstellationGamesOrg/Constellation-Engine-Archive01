#pragma once

#include <glad/glad.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CE {
	namespace core {
		class Light {
			glm::vec3 pos(0.f, 0.f, 10.f);

			int use(CE::core::Shader shader);
		};
	}
}
