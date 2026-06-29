#pragma once

#include <glad/glad.h>

class Texture2D {
    unsigned int id;

  public:
    Texture2D(const char *path, GLenum src_chan);
    ~Texture2D();

    void use();
};
