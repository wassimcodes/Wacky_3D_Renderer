#pragma once

#include <GLFW/glfw3.h>

// Global variables for mouse input
extern bool leftMouseButtonPressed;
extern double lastMouseX, lastMouseY;
extern float pitch, yaw;

// Function declarations
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
