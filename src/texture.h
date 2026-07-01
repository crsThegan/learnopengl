#pragma once

#include <glad/glad.h>

class Texture2D {
    unsigned int id;

  public:
    Texture2D(const char *path);
    ~Texture2D();

    void use();
};
