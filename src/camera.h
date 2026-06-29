#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

class Camera {
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 worldUp;

    float fov = 45.0f;

  public:
    Camera(glm::vec3 pos, glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f));
    Camera(float x, float y, float z);

    void setPos(glm::vec3 pos);
    void setPos(float x, float y, float z);

    glm::vec3 getPos() const;

    void moveForward(float offset);
    void moveBackwards(float offset);
    void moveRight(float offset);
    void moveLeft(float offset);

    glm::mat4 view() const;

    glm::vec3 getFront() const;
    glm::vec3 right() const;

    void updateFront(float pitch, float yaw);

    void setFov(float fov);
    float getFov() const;
};
