#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vsPath, const char *fsPath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vsFile, fsFile;

    vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vsFile.open(vsPath);
        fsFile.open(fsPath);

        std::stringstream vsStream, fsStream;
        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();

        vsFile.close();
        fsFile.close();

        vertexCode = vsStream.str();
        fragmentCode = fsStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "Error: could not read shader file" << std::endl;
    }

    const char *vsCode = vertexCode.c_str();
    const char *fsCode = fragmentCode.c_str();

    unsigned int vs, fs;
    int success;
    char infoLog[512];

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsCode, NULL);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
        std::cout << "Error of vs comp\n" << infoLog << std::endl;
    }

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsCode, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, sizeof(infoLog), NULL, infoLog);
        std::cout << "Error of fs comp\n" << infoLog << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, sizeof(infoLog), NULL, infoLog);
        std::cout << "Error of shader program linking\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::use() { glUseProgram(id); }

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
}
