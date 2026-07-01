#include "../material.h"

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>

Material Material::getGold() {
    Material gold;
    gold.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
    gold.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
    gold.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
    gold.shininess = 0.4f;

    return gold;
}
