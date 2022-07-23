#include "cubeMonster.hpp"

CE::AI::CubeMonster::CubeMonster(bool deleted1, float speed1, glm::vec3 startingposition1, float mass1, float energy1, CE::core::Object* mesh1) {
	deleted = deleted1;
	speed = speed1;
	startingposition = startingposition1;
	mass = mass1;
	energy = energy1;
	mesh = *mesh1;
}

bool CE::AI::CubeMonster::checkCollision(CubeMonster cubemonster) {
	if (mesh.position.x +  0.5 >= cubemonster.mesh.position.x && cubemonster.mesh.position.x + 0.5 >= mesh.position.x
		 && mesh.position.z + 0.5 >= cubemonster.mesh.position.z && cubemonster.mesh.position.z + 0.5 >= mesh.position.z)
		return true;

	return false;
}

void CE::AI::CubeMonster::meetAndKill(CubeMonster cubemonster) {
	if (checkCollision(cubemonster)) {
		if (mass > cubemonster.mass) {
			cubemonster.deleted = true;
			energy -= 100000;
			energy += cubemonster.energy;
		} else if (cubemonster.mass > mass) {
			deleted = true;
			cubemonster.energy = energy / 2;
			cubemonster.energy += cubemonster.energy;
		}
	}
}
