#include "../material.h"

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>

Material Material::getPearl() {
    Material pearl;
    pearl.ambient = glm::vec3(0.25f, 0.20725f, 0.20725f);
    pearl.diffuse = glm::vec3(1.0f, 0.829f, 0.829f);
    pearl.specular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
    pearl.shininess = 0.088f;

    return pearl;
}
