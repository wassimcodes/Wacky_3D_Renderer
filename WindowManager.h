#pragma once

#include <GLFW/glfw3.h>

class WindowManager {
public:
    static GLFWwindow* createWindow(int width, int height, const char* title);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

