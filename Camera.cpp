#include "Camera.h"

glm::vec3 Camera::cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
bool Camera::firstMouse = false;
GLfloat Camera::pitch = 0;
GLfloat Camera::yaw = 0;
GLfloat Camera::lastY = 0;
GLfloat Camera::lastX = 0;

void Camera::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.1;    // Change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

Camera::Camera() {
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    lastX = 400, lastY = 300;
    yaw = -90.0f;
    pitch = 0.0f;
    firstMouse = true;
}