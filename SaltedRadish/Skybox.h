#pragma once
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <glm/glm.hpp>

class Skybox {
public:
    Skybox();
    ~Skybox();

    void init();
    void draw(const glm::mat4& view, const glm::mat4& projection) const;

private:
    GLTexture cubemapTexture{};

    GLuint VAO{};
    GLuint VBO{};

    GLSLProgram _shader;
};