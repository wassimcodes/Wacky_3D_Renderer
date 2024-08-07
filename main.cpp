#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Math-related libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Shaders-related header files
#include "Shader/shader_s.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// Project header files
#include "WindowManager.h"
#include "InputManager.h"
#include "Skybox.h"

int main() {

    // dimensions
    int wWidth = 1280;
    int wHeight = 720;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = WindowManager::createWindow(wWidth, wHeight, "Wacky 3D Software");

    // Set GLFW callbacks
    //glfwSetFramebufferSizeCallback(window, WindowManager::framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Shader linking
    Shader ourShader("VertexShader.vert", "FragmentShader.frag");

    // Cube Vertices with Triangles
    float vertices[] = {
        // Positions          // Texture Coords
        // Front face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        // Back face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         // Bottom face
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

         // Top face
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/brickwall.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    ourShader.use();
    ourShader.setInt("texture1", 0);

    // Set up view and projection matrices
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(wWidth) / float(wHeight), 0.1f, 100.0f);

    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    stbi_image_free(data);

    // Configure skybox
    std::vector<std::string> faces
    {
        "C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/Daylight Box_Pieces/Daylight Box_Right.png",
        "C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/Daylight Box_Pieces/Daylight Box_Left.png",
        "C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/Daylight Box_Pieces/Daylight Box_Top.png",
        "C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/Daylight Box_Pieces/Daylight Box_Bottom.png",
        "C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/Daylight Box_Pieces/Daylight Box_Front.png",
        "C:/Users/woule/Documents/c++/Wacky_3D_Renderer/Resources/Daylight Box_Pieces/Daylight Box_Back.png"
    };

    Skybox skybox(faces);

    while (!glfwWindowShouldClose(window)) {


        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // activate shader
        ourShader.use();

        // create transformations
        // Set model matrix for transformations
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(pitch), glm::vec3(-3.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 3, 0.0f));
        ourShader.setMat4("model", model);

        // render container
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // draw skybox
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // Update the view matrix and projection matrix here based on your camera's setup
        skybox.render(view, projection);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
