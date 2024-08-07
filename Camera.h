#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float pitch;
    float yaw;
    float distance;

    Camera(glm::vec3 initPosition, glm::vec3 initTarget, glm::vec3 initUp, float initDistance);

    glm::mat4 getViewMatrix();

    void updateRotation(float pitchOffset, float yawOffset);
};
