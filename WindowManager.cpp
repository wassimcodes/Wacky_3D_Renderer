#include <glad/glad.h>
#include "WindowManager.h"
#include <iostream>


GLFWwindow* WindowManager::createWindow(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    glViewport(0, 0, width, height);
    return window;
}

void WindowManager::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}