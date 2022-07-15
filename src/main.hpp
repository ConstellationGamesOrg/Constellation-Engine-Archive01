// Copyright (c) 2022 ConstellationEngine Developers (see [AUTHORS.md](AUTHORS.md))

#ifndef MAIN_HPP
#define MAIN_HPP

// User-Defined Headers
// --------------------
#include "core/window/window.hpp"
#include "core/graphics/graphics.hpp"
#include "core/camera/camera.hpp"
#include "core/input/input.hpp"

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
#include <vector>
#include <unordered_map>
#include <cmath>

using std::vector;
using std::rand; 

int main();



class CubeMonster {
public:
	bool IsDeleted;
	float speed;
	glm::vec3 startingposition;
	float mass;
	float energy;
	CE::core::Object mesh;
	CubeMonster(bool IsDeleted1, float speed1, glm::vec3 startingposition1, float mass1, float energy1, CE::core::Object* mesh1);
};

vector<CubeMonster> tobedestroyed;
vector<CubeMonster> damonsters;
vector<int> todie;
vector<int> alreadytodie;

#endif // MAIN_HPP
