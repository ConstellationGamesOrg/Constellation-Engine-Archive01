#ifndef CUBEMONSTER_HPP
#define CUBEMONSTER_HPP

// CE
#include "../../core/graphics/graphics.hpp"

// Thirdparty
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard
#include <iostream>
#include <vector>
#include <cmath>

namespace CE {
	namespace AI {
		class CubeMonster {
		public:
			bool IsDeleted;
			float speed;
			glm::vec3 startingposition;
			float mass;
			float energy;
			CE::core::Object mesh;
			CubeMonster(bool IsDeleted1, float speed1, glm::vec3 startingposition1, float mass1, float energy1, CE::core::Object* mesh1);

			bool CheckIfCollision(CubeMonster cubemonster);
			void MeetAndKill(CubeMonster cubemonster);
		};
	}
}

#endif // CUBEMONSTER_HPP
