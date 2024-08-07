#include "InputManager.h"

// Global variables for mouse input
bool leftMouseButtonPressed = false;
bool middleMouseButtonPressed = false;
double lastMouseY = 0.0, lastMouseX = 0.0;
float pitch = 0.0f, yaw = 0.0f;
float cubeRotationX = 0.0f, cubeRotationY = 0.0f;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            leftMouseButtonPressed = true;
            glfwGetCursorPos(window, &lastMouseY, &lastMouseX);
        }
        else if (action == GLFW_RELEASE) {
            leftMouseButtonPressed = false;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (action == GLFW_PRESS) {
            middleMouseButtonPressed = true;
            glfwGetCursorPos(window, &lastMouseY, &lastMouseX);
        }
        else if (action == GLFW_RELEASE) {
            middleMouseButtonPressed = false;
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double ypos, double xpos) {
    if (leftMouseButtonPressed) {
        double yOffset = ypos - lastMouseY;
        double xOffset = xpos-lastMouseX ; // Reversed since y-coordinates go from bottom to top

        const float rotationSensitivity = 0.6f;
        cubeRotationX += xOffset * rotationSensitivity;
        cubeRotationY += yOffset * rotationSensitivity;

        lastMouseY = ypos;
        lastMouseX = xpos;
    }

    if (middleMouseButtonPressed) {
        double xOffset = ypos - lastMouseY;
        double yOffset = lastMouseX - xpos; 

        const float sensitivity = 0.1f;
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;

        lastMouseY = ypos;
        lastMouseX = xpos;
    }
}
