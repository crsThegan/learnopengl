#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>

class Material {
  public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float shininess;

    static Material getGold();
    static Material getPearl();
};
