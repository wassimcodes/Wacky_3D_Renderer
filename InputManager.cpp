#include "InputManager.h"

// Global variables for mouse input
bool leftMouseButtonPressed = false;
double lastMouseX, lastMouseY;
float pitch = 0.0f, yaw = 0.0f;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            leftMouseButtonPressed = true;
            glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
        }
        else if (action == GLFW_RELEASE) {
            leftMouseButtonPressed = false;
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    if (leftMouseButtonPressed) {
        double xOffset = xpos - lastMouseX;
        double yOffset = lastMouseY - ypos; // Reversed since y-coordinates go from bottom to top

        const float sensitivity = 0.1f;
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;

        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}
