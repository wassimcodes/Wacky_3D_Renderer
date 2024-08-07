// InputManager.h

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>

// Global variables for mouse input
extern bool leftMouseButtonPressed;
extern bool middleMouseButtonPressed;
extern double lastMouseX, lastMouseY;
extern float pitch, yaw;
extern float cubeRotationX, cubeRotationY;


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

#endif // INPUTMANAGER_H
