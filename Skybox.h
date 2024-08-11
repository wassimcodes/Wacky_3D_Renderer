#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/shader_s.h"

class Skybox {
public:
    Skybox(std::vector<std::string> faces);
    void render(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int loadCubemap(std::vector<std::string> faces);
    unsigned int cubemapTexture;
    unsigned int skyboxVAO, skyboxVBO;
    Shader skyboxShader;
};