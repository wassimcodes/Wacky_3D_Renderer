#include "camera.h"

Camera::Camera(glm::vec3 initPosition, glm::vec3 initTarget, glm::vec3 initUp, float initDistance)
    : position(initPosition), target(initTarget), up(initUp), pitch(0.0f), yaw(0.0f), distance(initDistance) {}

glm::mat4 Camera::getViewMatrix() {
    // Calculate the new camera position based on pitch and yaw
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    position = target + glm::normalize(direction) * distance;

    return glm::lookAt(position, target, up);
}

void Camera::updateRotation(float pitchOffset, float yawOffset) {
    pitch += pitchOffset;
    yaw += yawOffset;

    // Constrain the pitch angle to avoid flipping
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}
