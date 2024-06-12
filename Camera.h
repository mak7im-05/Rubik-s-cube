#ifndef CAMERA_H
#define CAMERA_H

#include "lib/glew-cmake/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtc/matrix_transform.hpp"
#include "lib/glm/glm/gtc/type_ptr.hpp"

class Camera {
private:
public:
    static GLfloat lastX,lastY;
    static bool firstMouse;
    static GLfloat yaw;
    static GLfloat pitch;
    static glm::vec3 cameraFront;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat deltaTime = 0.0f;    // Время, прошедшее между последним и текущим кадром
    GLfloat lastFrame = 0.0f;

    Camera();
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
};

#endif
