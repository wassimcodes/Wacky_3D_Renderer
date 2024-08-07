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
    glfwSetFramebufferSizeCallback(window, WindowManager::framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback); // Use InputManager's callback
    glfwSetCursorPosCallback(window, cursorPositionCallback); // Use InputManager's callback

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

         // Top face
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

         // Bottom face
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
   
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        ourShader.use();

        // Create transformations
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(cubeRotationX), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(cubeRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);

        // Render cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw skybox
        glm::vec3 cameraPos = glm::vec3(3.0f * sin(glm::radians(yaw)), 3.0f * sin(glm::radians(pitch)), 3.0f * cos(glm::radians(yaw)));
        glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);

        skybox.render(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: De-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // GLFW: terminate, clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}
