#include "camera.h"
#include "glm/detail/func_geometric.hpp"

#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

static glm::mat4 lookAt(glm::vec3 position, glm::vec3 target,
                        glm::vec3 worldUp);

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 worldUp) {
    this->pos = pos;
    this->front = front;
    this->worldUp = worldUp;
}

Camera::Camera(float x, float y, float z) {
    pos = glm::vec3(x, y, z);
    *this = Camera(pos);
}

void Camera::setPos(glm::vec3 pos) { this->pos = pos; }
void Camera::setPos(float x, float y, float z) {
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

glm::vec3 Camera::getPos() const { return pos; }

void Camera::moveForward(float offset) { setPos(pos + offset * front); }

void Camera::moveBackwards(float offset) { setPos(pos - offset * front); }

void Camera::moveRight(float offset) { setPos(pos + offset * right()); }

void Camera::moveLeft(float offset) { setPos(pos - offset * right()); }

glm::mat4 Camera::view() const { return lookAt(pos, pos + front, worldUp); }

glm::vec3 Camera::getFront() const { return front; }

glm::vec3 Camera::right() const {
    return glm::normalize(glm::cross(front, worldUp));
}

void Camera::updateFront(float pitch, float yaw) {
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(dir);
}

void Camera::setFov(float fov) { this->fov = fov; }
float Camera::getFov() const { return fov; }

static glm::mat4 lookAt(glm::vec3 position, glm::vec3 target,
                        glm::vec3 worldUp) {
    glm::mat4 mat(1.0f);

    glm::vec3 front = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
    glm::vec3 up = glm::normalize(glm::cross(right, front));

    mat[0] = glm::vec4(right, 0.0f);
    mat[1] = glm::vec4(up, 0.0f);
    mat[2] = glm::vec4(-front, 0.0f);
    mat[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    mat = glm::transpose(mat);

    mat = glm::translate(mat, -position);

    return mat;
}
