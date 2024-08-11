#pragma once

#include <GLFW/glfw3.h>

extern bool leftMouseButtonPressed;
extern bool middleMouseButtonPressed;
extern double lastMouseX, lastMouseY;
extern float pitch, yaw;
extern float cubeRotationX, cubeRotationY;


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);


