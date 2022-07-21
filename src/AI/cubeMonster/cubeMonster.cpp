#include "cubeMonster.hpp"

CE::AI::CubeMonster::CubeMonster(bool IsDeleted1, float speed1, glm::vec3 startingposition1, float mass1, float energy1, CE::core::Object* mesh1) {
	IsDeleted = IsDeleted1;
	speed = speed1;
	startingposition = startingposition1;
	mass = mass1;
	energy = energy1;
	mesh = *mesh1;
}

bool CE::AI::CubeMonster::CheckIfCollision(CubeMonster cubemonster) {
	if (mesh.position.x +  0.5 >= cubemonster.mesh.position.x && cubemonster.mesh.position.x + 0.5 >= mesh.position.x
		 && mesh.position.z + 0.5 >= cubemonster.mesh.position.z && cubemonster.mesh.position.z + 0.5 >= mesh.position.z)
		return true;

	return false;
}

void CE::AI::CubeMonster::MeetAndKill(CubeMonster cubemonster) {
	if (CheckIfCollision(cubemonster)) {
		if (mass > cubemonster.mass) {
			cubemonster.IsDeleted = true;
			energy -= 100000;
			energy += cubemonster.energy;

			std::cout << "kill " << std::endl;
		} else if (cubemonster.mass > mass) {
			IsDeleted = true;
			cubemonster.energy = energy / 2;
			cubemonster.energy += cubemonster.energy;

			std::cout << "kill " << std::endl;
		}
	}
}
