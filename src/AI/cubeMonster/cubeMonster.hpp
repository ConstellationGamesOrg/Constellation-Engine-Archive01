#ifndef CUBEMONSTER_HPP
#define CUBEMONSTER_HPP

#include <glad/glad.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

namespace CE {
    namespace AI {
        class CubeMonster
        {
            CubeMonster();
            virtual ~CubeMonster();
        };
    }
}
#endif // CUBEMONSTER_HPP