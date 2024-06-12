#include <fstream>
#include "Cube.h"

bool Cube::keys[1024];

void Cube::setColors(glm::vec3 colors[6], glm::vec3 color0, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3,
                     glm::vec3 color4, glm::vec3 color5) {
    colors[0] = color0;
    colors[1] = color1;
    colors[2] = color2;
    colors[3] = color3;
    colors[4] = color4;
    colors[5] = color5;
}

void Cube::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Cube::do_movement() {
    // Camera controls
    GLfloat cameraSpeed = 5.0f * cam.deltaTime;
    if (keys[GLFW_KEY_W])
        cam.cameraPos += cameraSpeed * cam.cameraFront;
    if (keys[GLFW_KEY_S])
        cam.cameraPos -= cameraSpeed * Camera::cameraFront;
    if (keys[GLFW_KEY_A])
        cam.cameraPos -= glm::normalize(glm::cross(Camera::cameraFront, cam.cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        cam.cameraPos += glm::normalize(glm::cross(Camera::cameraFront, cam.cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_SPACE])
        cam.cameraPos += cam.cameraUp * cameraSpeed;
    if (keys[GLFW_KEY_LEFT_SHIFT])
        cam.cameraPos -= cam.cameraUp * cameraSpeed;

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_R]) {
            rotate_Rr();
            keys[GLFW_KEY_R] = false;
        }
    } else if (keys[GLFW_KEY_R]) {
        rotate_R();
        keys[GLFW_KEY_R] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_M]) {
            rotate_Mr();
            keys[GLFW_KEY_M] = false;
        }
    } else if (keys[GLFW_KEY_M]) {
        rotate_M();
        keys[GLFW_KEY_M] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_L]) {
            rotate_Lr();
            keys[GLFW_KEY_L] = false;
        }
    } else if (keys[GLFW_KEY_L]) {
        rotate_L();
        keys[GLFW_KEY_L] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_U]) {
            rotate_Ur();
            keys[GLFW_KEY_U] = false;
        }
    } else if (keys[GLFW_KEY_U]) {
        rotate_U();
        keys[GLFW_KEY_U] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_T]) {
            rotate_Sr();
            keys[GLFW_KEY_T] = false;
        }
    } else if (keys[GLFW_KEY_T]) {
        rotate_S();
        keys[GLFW_KEY_T] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_Y]) {
            rotate_Dr();
            keys[GLFW_KEY_Y] = false;
        }
    } else if (keys[GLFW_KEY_Y]) {
        rotate_D();
        keys[GLFW_KEY_Y] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_F]) {
            rotate_Fr();
            keys[GLFW_KEY_F] = false;
        }
    } else if (keys[GLFW_KEY_F]) {
        rotate_F();
        keys[GLFW_KEY_F] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_H]) {
            rotate_Hr();
            keys[GLFW_KEY_H] = false;
        }
    } else if (keys[GLFW_KEY_H]) {
        rotate_H();
        keys[GLFW_KEY_H] = false;
    }

    if (keys[GLFW_KEY_LEFT_CONTROL]) {
        if (keys[GLFW_KEY_B]) {
            rotate_Br();
            keys[GLFW_KEY_B] = false;
        }
    } else if (keys[GLFW_KEY_B]) {
        rotate_B();
        keys[GLFW_KEY_B] = false;
    }

    if (keys[GLFW_KEY_E]) {
        mixinCube();
        keys[GLFW_KEY_E] = false;
    }

    if (keys[GLFW_KEY_G]) {
        solvingCube();
        keys[GLFW_KEY_G] = false;
    }

    if (keys[GLFW_KEY_N]) {
        save_cube();
        keys[GLFW_KEY_N] = false;
    }

    if (keys[GLFW_KEY_C]) {
        check_invariant();
        keys[GLFW_KEY_C] = false;
    }
}

Cube::Cube() {
    this->cam = Camera();
}

void Cube::init() {
    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                cubePositions[x][y][z].cord = glm::vec3(x, y, z);
            }
        }
    }

    setColors(cubePositions[0][0][0].colors, blue, black, red, black, white, black);
    setColors(cubePositions[0][0][1].colors, black, black, red, black, white, black);
    setColors(cubePositions[0][0][2].colors, black, green, red, black, white, black);
    setColors(cubePositions[0][1][0].colors, blue, black, red, black, black, black);
    setColors(cubePositions[0][1][1].colors, black, black, red, black, black, black);
    setColors(cubePositions[0][1][2].colors, black, green, red, black, black, black);
    setColors(cubePositions[0][2][0].colors, blue, black, red, black, black, yellow);
    setColors(cubePositions[0][2][1].colors, black, black, red, black, black, yellow);
    setColors(cubePositions[0][2][2].colors, black, green, red, black, black, yellow);

    setColors(cubePositions[1][0][0].colors, blue, black, black, black, white, black);
    setColors(cubePositions[1][0][1].colors, black, black, black, black, white, black);
    setColors(cubePositions[1][0][2].colors, black, green, black, black, white, black);
    setColors(cubePositions[1][1][0].colors, blue, black, black, black, black, black);
    setColors(cubePositions[1][1][1].colors, black, black, black, black, black, black);
    setColors(cubePositions[1][1][2].colors, black, green, black, black, black, black);
    setColors(cubePositions[1][2][0].colors, blue, black, black, black, black, yellow);
    setColors(cubePositions[1][2][1].colors, black, black, black, black, black, yellow);
    setColors(cubePositions[1][2][2].colors, black, green, black, black, black, yellow);

    setColors(cubePositions[2][0][0].colors, blue, black, black, orange, white, black);
    setColors(cubePositions[2][0][1].colors, black, black, black, orange, white, black);
    setColors(cubePositions[2][0][2].colors, black, green, black, orange, white, black);
    setColors(cubePositions[2][1][0].colors, blue, black, black, orange, black, black);
    setColors(cubePositions[2][1][1].colors, black, black, black, orange, black, black);
    setColors(cubePositions[2][1][2].colors, black, green, black, orange, black, black);
    setColors(cubePositions[2][2][0].colors, blue, black, black, orange, black, yellow);
    setColors(cubePositions[2][2][1].colors, black, black, black, orange, black, yellow);
    setColors(cubePositions[2][2][2].colors, black, green, black, orange, black, yellow);

    if (loader) {
        load();
    }
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}

bool Cube::draw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Cube", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, cam.mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    Shader *ourShader = load_shader("../shaders/vertixShader.glslv", "../shaders/fragmentShader.glslf");
    init();

    while (!glfwWindowShouldClose(window)) {
        srand(time(0));

        GLfloat currentFrame = glfwGetTime();
        cam.deltaTime = currentFrame - cam.lastFrame;
        cam.lastFrame = currentFrame;

        glfwPollEvents();
        do_movement();

        glClearColor(0.25, 0.25, 0.41, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        GLfloat radius = 5.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;

        glm::mat4 view = glm::lookAt(cam.cameraPos, cam.cameraPos + Camera::cameraFront, cam.cameraUp);

        ourShader->use();
        glBindVertexArray(VAO);

        if (saver) {
            save_state_cube();
        }

        int matrixID = glGetUniformLocation(ourShader->id, "MVP");
        int Colors = glGetUniformLocation(ourShader->id, "Colors");
        for (auto &cubePosition: cubePositions) {
            for (auto &y: cubePosition) {
                for (auto &z: y) {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, z.cord * 1.05f);
                    glm::mat4 MVP = projection * view * model;

                    glUniformMatrix4fv(matrixID, 1, GL_FALSE, glm::value_ptr(MVP));

                    for (int j = 0; j < 6; ++j) {
                        glUniform3fv(Colors, 1, glm::value_ptr(z.colors[j]));
                        glDrawArrays(GL_TRIANGLES, 6 * j, 6);
                    }
                }
            }
        }
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    return false;
}

void Cube::rotate_R() {
    cout << 'R' << ' ';

    glm::vec3 t[3] = {cubePositions[2][2][0].colors[0], cubePositions[2][2][0].colors[3],cubePositions[2][2][0].colors[5]};
    glm::vec3 t1[3] = {cubePositions[2][0][0].colors[0], cubePositions[2][0][0].colors[3],cubePositions[2][0][0].colors[4]};
    cubePositions[2][2][0].colors[0] = cubePositions[2][2][2].colors[5];cubePositions[2][2][0].colors[3] = cubePositions[2][2][2].colors[3];cubePositions[2][2][0].colors[5] = cubePositions[2][2][2].colors[1];

    cubePositions[2][0][0].colors[0] = t[2];
    cubePositions[2][0][0].colors[3] = t[1];
    cubePositions[2][0][0].colors[4] = t[0];

    t[0] = cubePositions[2][0][2].colors[1];
    t[1] = cubePositions[2][0][2].colors[3];
    t[2] = cubePositions[2][0][2].colors[4];

    cubePositions[2][0][2].colors[1] = t1[2];
    cubePositions[2][0][2].colors[3] = t1[1];
    cubePositions[2][0][2].colors[4] = t1[0];

    cubePositions[2][2][2].colors[1] = t[2];
    cubePositions[2][2][2].colors[3] = t[1];
    cubePositions[2][2][2].colors[5] = t[0];

    t[0] = cubePositions[2][2][1].colors[3];
    t[1] = cubePositions[2][2][1].colors[5];

    cubePositions[2][2][1].colors[5] = cubePositions[2][1][2].colors[1];
    cubePositions[2][2][1].colors[3] = cubePositions[2][1][2].colors[3];

    t1[0] = cubePositions[2][1][0].colors[0];
    t1[1] = cubePositions[2][1][0].colors[3];

    cubePositions[2][1][0].colors[0] = t[1];
    cubePositions[2][1][0].colors[3] = t[0];

    t[0] = cubePositions[2][0][1].colors[3];
    t[1] = cubePositions[2][0][1].colors[4];

    cubePositions[2][0][1].colors[3] = t1[1];
    cubePositions[2][0][1].colors[4] = t1[0];

    cubePositions[2][1][2].colors[1] = t[1];
    cubePositions[2][1][2].colors[3] = t[0];
}

void Cube::rotate_Rr() {
    cout << "R'" << ' ';

    rotate_R();
    rotate_R();
    rotate_R();
}

void Cube::rotate_M() {
    cout << "M" << ' ';

    glm::vec3 t[3] = {cubePositions[1][2][0].colors[0], cubePositions[1][2][0].colors[3],
                      cubePositions[1][2][0].colors[5]};
    glm::vec3 t1[3] = {cubePositions[1][0][0].colors[0], cubePositions[1][0][0].colors[3],
                       cubePositions[1][0][0].colors[4]};
    cubePositions[1][2][0].colors[0] = cubePositions[1][2][2].colors[5];
    cubePositions[1][2][0].colors[3] = cubePositions[1][2][2].colors[3];
    cubePositions[1][2][0].colors[5] = cubePositions[1][2][2].colors[1];

    cubePositions[1][0][0].colors[0] = t[2];
    cubePositions[1][0][0].colors[3] = t[1];
    cubePositions[1][0][0].colors[4] = t[0];

    t[0] = cubePositions[1][0][2].colors[1];
    t[1] = cubePositions[1][0][2].colors[3];
    t[2] = cubePositions[1][0][2].colors[4];

    cubePositions[1][0][2].colors[1] = t1[2];
    cubePositions[1][0][2].colors[3] = t1[1];
    cubePositions[1][0][2].colors[4] = t1[0];

    cubePositions[1][2][2].colors[1] = t[2];
    cubePositions[1][2][2].colors[3] = t[1];
    cubePositions[1][2][2].colors[5] = t[0];

    t[0] = cubePositions[1][2][1].colors[3];
    t[1] = cubePositions[1][2][1].colors[5];

    cubePositions[1][2][1].colors[5] = cubePositions[1][1][2].colors[1];
    cubePositions[1][2][1].colors[3] = cubePositions[1][1][2].colors[3];

    t1[0] = cubePositions[1][1][0].colors[0];
    t1[1] = cubePositions[1][1][0].colors[3];

    cubePositions[1][1][0].colors[0] = t[1];
    cubePositions[1][1][0].colors[3] = t[0];

    t[0] = cubePositions[1][0][1].colors[3];
    t[1] = cubePositions[1][0][1].colors[4];

    cubePositions[1][0][1].colors[3] = t1[1];
    cubePositions[1][0][1].colors[4] = t1[0];

    cubePositions[1][1][2].colors[1] = t[1];
    cubePositions[1][1][2].colors[3] = t[0];
}

void Cube::rotate_Mr() {
    cout << "M' ";
    rotate_M();
    rotate_M();
    rotate_M();
}

void Cube::rotate_L() {
    cout << "L ";
    glm::vec3 t[3] = {cubePositions[0][2][0].colors[0], cubePositions[0][2][0].colors[2],
                      cubePositions[0][2][0].colors[5]};
    glm::vec3 t1[3] = {cubePositions[0][0][0].colors[0], cubePositions[0][0][0].colors[2],
                       cubePositions[0][0][0].colors[4]};
    cubePositions[0][2][0].colors[0] = cubePositions[0][2][2].colors[5];
    cubePositions[0][2][0].colors[2] = cubePositions[0][2][2].colors[2];
    cubePositions[0][2][0].colors[5] = cubePositions[0][2][2].colors[1];

    cubePositions[0][0][0].colors[0] = t[2];
    cubePositions[0][0][0].colors[2] = t[1];
    cubePositions[0][0][0].colors[4] = t[0];

    t[0] = cubePositions[0][0][2].colors[1];
    t[1] = cubePositions[0][0][2].colors[2];
    t[2] = cubePositions[0][0][2].colors[4];

    cubePositions[0][0][2].colors[1] = t1[2];
    cubePositions[0][0][2].colors[2] = t1[1];
    cubePositions[0][0][2].colors[4] = t1[0];

    cubePositions[0][2][2].colors[1] = t[2];
    cubePositions[0][2][2].colors[2] = t[1];
    cubePositions[0][2][2].colors[5] = t[0];

    t[0] = cubePositions[0][2][1].colors[2];
    t[1] = cubePositions[0][2][1].colors[5];

    cubePositions[0][2][1].colors[5] = cubePositions[0][1][2].colors[1];
    cubePositions[0][2][1].colors[2] = cubePositions[0][1][2].colors[2];

    t1[0] = cubePositions[0][1][0].colors[0];
    t1[1] = cubePositions[0][1][0].colors[2];

    cubePositions[0][1][0].colors[0] = t[1];
    cubePositions[0][1][0].colors[2] = t[0];

    t[0] = cubePositions[0][0][1].colors[2];
    t[1] = cubePositions[0][0][1].colors[4];

    cubePositions[0][0][1].colors[2] = t1[1];
    cubePositions[0][0][1].colors[4] = t1[0];

    cubePositions[0][1][2].colors[1] = t[1];
    cubePositions[0][1][2].colors[2] = t[0];
}

void Cube::rotate_Lr() {
    cout << "L' ";
    rotate_L();
    rotate_L();
    rotate_L();
}

void Cube::rotate_U() {
    cout << "U ";
    glm::vec3 t[3] = {cubePositions[0][2][2].colors[1], cubePositions[0][2][2].colors[2],
                      cubePositions[0][2][2].colors[5]};
    glm::vec3 t1[3] = {cubePositions[0][2][0].colors[0], cubePositions[0][2][0].colors[2],
                       cubePositions[0][2][0].colors[5]};
    cubePositions[0][2][2].colors[1] = cubePositions[2][2][2].colors[3];
    cubePositions[0][2][2].colors[2] = cubePositions[2][2][2].colors[1];
    cubePositions[0][2][2].colors[5] = cubePositions[2][2][2].colors[5];

    cubePositions[0][2][0].colors[0] = t[1];
    cubePositions[0][2][0].colors[2] = t[0];
    cubePositions[0][2][0].colors[5] = t[2];

    t[0] = cubePositions[2][2][0].colors[0];
    t[1] = cubePositions[2][2][0].colors[3];
    t[2] = cubePositions[2][2][0].colors[5];

    cubePositions[2][2][0].colors[0] = t1[1];
    cubePositions[2][2][0].colors[3] = t1[0];
    cubePositions[2][2][0].colors[5] = t1[2];

    cubePositions[2][2][2].colors[1] = t[1];
    cubePositions[2][2][2].colors[3] = t[0];
    cubePositions[2][2][2].colors[5] = t[2];

    t[0] = cubePositions[0][2][1].colors[2];
    t[1] = cubePositions[0][2][1].colors[5];

    cubePositions[0][2][1].colors[2] = cubePositions[1][2][2].colors[1];
    cubePositions[0][2][1].colors[5] = cubePositions[1][2][2].colors[5];

    t1[0] = cubePositions[1][2][0].colors[0];
    t1[1] = cubePositions[1][2][0].colors[5];

    cubePositions[1][2][0].colors[0] = t[0];
    cubePositions[1][2][0].colors[5] = t[1];

    t[0] = cubePositions[2][2][1].colors[3];
    t[1] = cubePositions[2][2][1].colors[5];

    cubePositions[2][2][1].colors[3] = t1[0];
    cubePositions[2][2][1].colors[5] = t1[1];

    cubePositions[1][2][2].colors[1] = t[0];
    cubePositions[1][2][2].colors[5] = t[1];
}

void Cube::rotate_Ur() {
    cout << "U' ";
    rotate_U();
    rotate_U();
    rotate_U();
}

void Cube::rotate_S() {
    cout << "S ";
    glm::vec3 t[3] = {cubePositions[0][1][2].colors[1], cubePositions[0][1][2].colors[2],
                      cubePositions[0][1][2].colors[5]};
    glm::vec3 t1[3] = {cubePositions[0][1][0].colors[0], cubePositions[0][1][0].colors[2],
                       cubePositions[0][1][0].colors[5]};
    cubePositions[0][1][2].colors[1] = cubePositions[2][1][2].colors[3];
    cubePositions[0][1][2].colors[2] = cubePositions[2][1][2].colors[1];
    cubePositions[0][1][2].colors[5] = cubePositions[2][1][2].colors[5];

    cubePositions[0][1][0].colors[0] = t[1];
    cubePositions[0][1][0].colors[2] = t[0];
    cubePositions[0][1][0].colors[5] = t[2];

    t[0] = cubePositions[2][1][0].colors[0];
    t[1] = cubePositions[2][1][0].colors[3];
    t[2] = cubePositions[2][1][0].colors[5];

    cubePositions[2][1][0].colors[0] = t1[1];
    cubePositions[2][1][0].colors[3] = t1[0];
    cubePositions[2][1][0].colors[5] = t1[2];

    cubePositions[2][1][2].colors[1] = t[1];
    cubePositions[2][1][2].colors[3] = t[0];
    cubePositions[2][1][2].colors[5] = t[2];

    t[0] = cubePositions[0][1][1].colors[2];
    t[1] = cubePositions[0][1][1].colors[5];

    cubePositions[0][1][1].colors[2] = cubePositions[1][1][2].colors[1];
    cubePositions[0][1][1].colors[5] = cubePositions[1][1][2].colors[5];

    t1[0] = cubePositions[1][1][0].colors[0];
    t1[1] = cubePositions[1][1][0].colors[5];

    cubePositions[1][1][0].colors[0] = t[0];
    cubePositions[1][1][0].colors[5] = t[1];

    t[0] = cubePositions[2][1][1].colors[3];
    t[1] = cubePositions[2][1][1].colors[5];

    cubePositions[2][1][1].colors[3] = t1[0];
    cubePositions[2][1][1].colors[5] = t1[1];

    cubePositions[1][1][2].colors[1] = t[0];
    cubePositions[1][1][2].colors[5] = t[1];
}

void Cube::rotate_Sr() {
    cout << "S' ";
    rotate_S();
    rotate_S();
    rotate_S();
}

void Cube::rotate_D() {
    cout << "D ";
    glm::vec3 t[3] = {cubePositions[0][0][2].colors[1], cubePositions[0][0][2].colors[2],
                      cubePositions[0][0][2].colors[4]};
    glm::vec3 t1[3] = {cubePositions[0][0][0].colors[0], cubePositions[0][0][0].colors[2],
                       cubePositions[0][0][0].colors[4]};
    cubePositions[0][0][2].colors[1] = cubePositions[2][0][2].colors[3];
    cubePositions[0][0][2].colors[2] = cubePositions[2][0][2].colors[1];
    cubePositions[0][0][2].colors[4] = cubePositions[2][0][2].colors[4];

    cubePositions[0][0][0].colors[0] = t[1];
    cubePositions[0][0][0].colors[2] = t[0];
    cubePositions[0][0][0].colors[4] = t[2];

    t[0] = cubePositions[2][0][0].colors[0];
    t[1] = cubePositions[2][0][0].colors[3];
    t[2] = cubePositions[2][0][0].colors[4];

    cubePositions[2][0][0].colors[0] = t1[1];
    cubePositions[2][0][0].colors[3] = t1[0];
    cubePositions[2][0][0].colors[4] = t1[2];

    cubePositions[2][0][2].colors[1] = t[1];
    cubePositions[2][0][2].colors[3] = t[0];
    cubePositions[2][0][2].colors[4] = t[2];

    t[0] = cubePositions[0][0][1].colors[2];
    t[1] = cubePositions[0][0][1].colors[4];

    cubePositions[0][0][1].colors[2] = cubePositions[1][0][2].colors[1];
    cubePositions[0][0][1].colors[4] = cubePositions[1][0][2].colors[4];

    t1[0] = cubePositions[1][0][0].colors[0];
    t1[1] = cubePositions[1][0][0].colors[4];

    cubePositions[1][0][0].colors[0] = t[0];
    cubePositions[1][0][0].colors[4] = t[1];

    t[0] = cubePositions[2][0][1].colors[3];
    t[1] = cubePositions[2][0][1].colors[4];

    cubePositions[2][0][1].colors[3] = t1[0];
    cubePositions[2][0][1].colors[4] = t1[1];

    cubePositions[1][0][2].colors[1] = t[0];
    cubePositions[1][0][2].colors[4] = t[1];
}

void Cube::rotate_Dr() {
    cout << "D'";
    rotate_D();
    rotate_D();
    rotate_D();
}

void Cube::rotate_F() {
    cout << "F ";
    glm::vec3 t[3] = {cubePositions[2][0][2].colors[1], cubePositions[2][0][2].colors[3],
                      cubePositions[2][0][2].colors[4]};
    glm::vec3 t1[3] = {cubePositions[0][0][2].colors[1], cubePositions[0][0][2].colors[2],
                       cubePositions[0][0][2].colors[4]};
    cubePositions[2][0][2].colors[1] = cubePositions[2][2][2].colors[1];
    cubePositions[2][0][2].colors[3] = cubePositions[2][2][2].colors[5];
    cubePositions[2][0][2].colors[4] = cubePositions[2][2][2].colors[3];

    cubePositions[0][0][2].colors[1] = t[0];
    cubePositions[0][0][2].colors[2] = t[2];
    cubePositions[0][0][2].colors[4] = t[1];

    t[0] = cubePositions[0][2][2].colors[1];
    t[1] = cubePositions[0][2][2].colors[2];
    t[2] = cubePositions[0][2][2].colors[5];

    cubePositions[0][2][2].colors[1] = t1[0];
    cubePositions[0][2][2].colors[2] = t1[2];
    cubePositions[0][2][2].colors[5] = t1[1];

    cubePositions[2][2][2].colors[1] = t[0];
    cubePositions[2][2][2].colors[3] = t[2];
    cubePositions[2][2][2].colors[5] = t[1];

    t[0] = cubePositions[2][1][2].colors[1];
    t[1] = cubePositions[2][1][2].colors[3];

    cubePositions[2][1][2].colors[1] = cubePositions[1][2][2].colors[1];
    cubePositions[2][1][2].colors[3] = cubePositions[1][2][2].colors[5];

    t1[0] = cubePositions[1][0][2].colors[1];
    t1[1] = cubePositions[1][0][2].colors[4];

    cubePositions[1][0][2].colors[1] = t[0];
    cubePositions[1][0][2].colors[4] = t[1];

    t[0] = cubePositions[0][1][2].colors[1];
    t[1] = cubePositions[0][1][2].colors[2];

    cubePositions[0][1][2].colors[1] = t1[0];
    cubePositions[0][1][2].colors[2] = t1[1];

    cubePositions[1][2][2].colors[1] = t[0];
    cubePositions[1][2][2].colors[5] = t[1];
}

void Cube::rotate_Fr() {
    cout << "F' ";
    rotate_F();
    rotate_F();
    rotate_F();
}

void Cube::rotate_H() {
    cout << "H ";
    glm::vec3 t[3] = {cubePositions[2][0][1].colors[1], cubePositions[2][0][1].colors[3],
                      cubePositions[2][0][1].colors[4]};
    glm::vec3 t1[3] = {cubePositions[0][0][1].colors[1], cubePositions[0][0][1].colors[2],
                       cubePositions[0][0][1].colors[4]};
    cubePositions[2][0][1].colors[1] = cubePositions[2][2][1].colors[1];
    cubePositions[2][0][1].colors[3] = cubePositions[2][2][1].colors[5];
    cubePositions[2][0][1].colors[4] = cubePositions[2][2][1].colors[3];

    cubePositions[0][0][1].colors[1] = t[0];
    cubePositions[0][0][1].colors[2] = t[2];
    cubePositions[0][0][1].colors[4] = t[1];

    t[0] = cubePositions[0][2][1].colors[1];
    t[1] = cubePositions[0][2][1].colors[2];
    t[2] = cubePositions[0][2][1].colors[5];

    cubePositions[0][2][1].colors[1] = t1[0];
    cubePositions[0][2][1].colors[2] = t1[2];
    cubePositions[0][2][1].colors[5] = t1[1];

    cubePositions[2][2][1].colors[1] = t[0];
    cubePositions[2][2][1].colors[3] = t[2];
    cubePositions[2][2][1].colors[5] = t[1];

    t[0] = cubePositions[2][1][1].colors[1];
    t[1] = cubePositions[2][1][1].colors[3];

    cubePositions[2][1][1].colors[1] = cubePositions[1][2][1].colors[1];
    cubePositions[2][1][1].colors[3] = cubePositions[1][2][1].colors[5];

    t1[0] = cubePositions[1][0][1].colors[1];
    t1[1] = cubePositions[1][0][1].colors[4];

    cubePositions[1][0][1].colors[1] = t[0];
    cubePositions[1][0][1].colors[4] = t[1];

    t[0] = cubePositions[0][1][1].colors[1];
    t[1] = cubePositions[0][1][1].colors[2];

    cubePositions[0][1][1].colors[1] = t1[0];
    cubePositions[0][1][1].colors[2] = t1[1];

    cubePositions[1][2][1].colors[1] = t[0];
    cubePositions[1][2][1].colors[5] = t[1];
}

void Cube::rotate_Hr() {
    cout << "H' ";
    rotate_H();
    rotate_H();
    rotate_H();
}

void Cube::rotate_B() {
    cout << "B ";
    glm::vec3 t[3] = {cubePositions[2][0][0].colors[0], cubePositions[2][0][0].colors[3],
                      cubePositions[2][0][0].colors[4]};
    glm::vec3 t1[3] = {cubePositions[0][0][0].colors[0], cubePositions[0][0][0].colors[2],
                       cubePositions[0][0][0].colors[4]};
    cubePositions[2][0][0].colors[0] = cubePositions[2][2][0].colors[0];
    cubePositions[2][0][0].colors[3] = cubePositions[2][2][0].colors[5];
    cubePositions[2][0][0].colors[4] = cubePositions[2][2][0].colors[3];

    cubePositions[0][0][0].colors[0] = t[0];
    cubePositions[0][0][0].colors[2] = t[2];
    cubePositions[0][0][0].colors[4] = t[1];

    t[0] = cubePositions[0][2][0].colors[0];
    t[1] = cubePositions[0][2][0].colors[2];
    t[2] = cubePositions[0][2][0].colors[5];

    cubePositions[0][2][0].colors[0] = t1[0];
    cubePositions[0][2][0].colors[2] = t1[2];
    cubePositions[0][2][0].colors[5] = t1[1];

    cubePositions[2][2][0].colors[0] = t[0];
    cubePositions[2][2][0].colors[3] = t[2];
    cubePositions[2][2][0].colors[5] = t[1];

    t[0] = cubePositions[2][1][0].colors[0];
    t[1] = cubePositions[2][1][0].colors[3];

    cubePositions[2][1][0].colors[0] = cubePositions[1][2][0].colors[0];
    cubePositions[2][1][0].colors[3] = cubePositions[1][2][0].colors[5];

    t1[0] = cubePositions[1][0][0].colors[0];
    t1[1] = cubePositions[1][0][0].colors[4];

    cubePositions[1][0][0].colors[0] = t[0];
    cubePositions[1][0][0].colors[4] = t[1];

    t[0] = cubePositions[0][1][0].colors[0];
    t[1] = cubePositions[0][1][0].colors[2];

    cubePositions[0][1][0].colors[0] = t1[0];
    cubePositions[0][1][0].colors[2] = t1[1];

    cubePositions[1][2][0].colors[0] = t[0];
    cubePositions[1][2][0].colors[5] = t[1];
}

void Cube::rotate_Br() {
    cout << "B' ";
    rotate_B();
    rotate_B();
    rotate_B();
}

void Cube::pifPaf() {
    rotate_R();
    rotate_U();
    rotate_Rr();
    rotate_Ur();
}

void Cube::sunflower_R() {
    rotate_F();
    rotate_U();
    rotate_F();
    rotate_U();
    rotate_F();
    rotate_Ur();
    rotate_Fr();
    rotate_Ur();
    rotate_Fr();
    rotate_Ur();
}

void Cube::sunflower_L() {
    rotate_Fr();
    rotate_Ur();
    rotate_Fr();
    rotate_Ur();
    rotate_Fr();
    rotate_U();
    rotate_F();
    rotate_U();
    rotate_F();
    rotate_U();
}

void Cube::reverse_pifpaf() {
    rotate_L();
    rotate_D();
    rotate_Lr();
    rotate_Dr();
}

void Cube::kill_in_london() {
    rotate_R();
    rotate_U();
    rotate_Rr();
    rotate_Fr();
    pifPaf();
    rotate_Rr();
    rotate_F();
    rotate_R();
    rotate_R();
    rotate_Ur();
    rotate_Rr();
    rotate_Ur();
}

void Cube::infarct() {
    rotate_U();
    rotate_U();
    rotate_R();
    rotate_U();
    rotate_U();
    rotate_Rr();
    rotate_F();
    rotate_F();
    rotate_U();
    rotate_U();
    rotate_L();
    rotate_U();
    rotate_U();
    rotate_Lr();
    rotate_F();
    rotate_F();
}

void Cube::mixinCube() {
    cout << "MIXING CUBE\n";
    for (int i = 0; i < 20; ++i) {
        int x = rand() % 18;
        switch (x) {
            case 0:
                rotate_R();
                break;
            case 1:
                rotate_Rr();
                break;
            case 2:
                rotate_S();
                break;
            case 3:
                rotate_Sr();
                break;
            case 4:
                rotate_L();
                break;
            case 5:
                rotate_Lr();
                break;
            case 6:
                rotate_F();
                break;
            case 7:
                rotate_Fr();
                break;
            case 8:
                rotate_H();
                break;
            case 9:
                rotate_Hr();
                break;
            case 10:
                rotate_B();
                break;
            case 11:
                rotate_Br();
                break;
            case 12:
                rotate_U();
                break;
            case 13:
                rotate_Ur();
                break;
            case 14:
                rotate_M();
                break;
            case 15:
                rotate_Mr();
                break;
            case 16:
                rotate_D();
                break;
            case 17:
                rotate_Dr();
                break;


        }
    }
    cout << "\n";
}

void Cube::solving_the_wrong_cross() {
    if (cubePositions[1][2][2].colors[5] == cubePositions[1][2][1].colors[5]) {
        rotate_U();
    } else if (cubePositions[1][2][2].colors[1] == cubePositions[1][2][1].colors[5]) {
        rotate_F();
        rotate_Ur();
        rotate_R();
        rotate_U();
    } else if (cubePositions[0][1][2].colors[1] == cubePositions[1][2][1].colors[5]) {
        rotate_U();
        rotate_Lr();
        rotate_Ur();
    } else if (cubePositions[2][1][2].colors[1] == cubePositions[1][2][1].colors[5]) {
        rotate_Ur();
        rotate_R();
        rotate_U();
    } else if (cubePositions[1][0][2].colors[1] == cubePositions[1][2][1].colors[5]) {
        rotate_F();
        solving_the_wrong_cross();
    } else if (cubePositions[1][0][2].colors[4] == cubePositions[1][2][1].colors[5]) {
        rotate_F();
        rotate_F();
    } else if (cubePositions[0][1][2].colors[2] == cubePositions[1][2][1].colors[5]) {
        rotate_Sr();
        solving_the_wrong_cross();
    } else if (cubePositions[2][1][2].colors[3] == cubePositions[1][2][1].colors[5]) {
        rotate_S();
        solving_the_wrong_cross();
    } else {
        rotate_U();
        rotate_S();
        rotate_D();
    }
}

void Cube::solving_the_right_cross() {

    if (cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0] &&
        cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3] &&
        cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1] &&
        cubePositions[0][2][1].colors[2] == cubePositions[0][1][1].colors[2] &&
        cubePositions[1][2][0].colors[5] == cubePositions[1][2][1].colors[5] &&
        cubePositions[0][2][1].colors[5] == cubePositions[1][2][1].colors[5] &&
        cubePositions[2][2][1].colors[5] == cubePositions[1][2][1].colors[5] &&
        cubePositions[1][2][2].colors[5] == cubePositions[1][2][1].colors[5]) {
        cross = true;
        return;
    }

    if (cubePositions[0][2][1].colors[2] == cubePositions[0][1][1].colors[2] &&
        cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1]) {
        pifPaf();
        rotate_R();
    } else if (cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3] &&
               cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1]) {
        rotate_U();
        pifPaf();
        rotate_R();
        rotate_Ur();
    } else if (cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0] &&
               cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3]) {
        rotate_U();
        rotate_U();
        pifPaf();
        rotate_R();
        rotate_Ur();
        rotate_Ur();
    } else if (cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0] &&
               cubePositions[0][2][1].colors[2] == cubePositions[0][1][1].colors[2]) {
        rotate_Ur();
        pifPaf();
        rotate_R();
        rotate_Ur();
    } else if (cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0] &&
               cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1] ||
               cubePositions[0][2][1].colors[1] == cubePositions[2][2][1].colors[3] &&
               cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3]) {
        pifPaf();
        rotate_R();
        solving_the_right_cross();
    } else {
        rotate_U();
    }

}

void Cube::solving_first_layout() {
    while (cubePositions[0][0][0].colors[4] != cubePositions[1][0][1].colors[4] ||
           cubePositions[0][0][2].colors[4] != cubePositions[1][0][1].colors[4] ||
           cubePositions[2][0][0].colors[4] != cubePositions[1][0][1].colors[4] ||
           cubePositions[2][0][2].colors[4] != cubePositions[1][0][1].colors[4] ||
           cubePositions[0][0][0].colors[0] != cubePositions[1][0][0].colors[0] ||
           cubePositions[2][0][0].colors[0] != cubePositions[1][0][0].colors[0] ||
           cubePositions[0][0][2].colors[1] != cubePositions[1][0][2].colors[1] ||
           cubePositions[2][0][2].colors[1] != cubePositions[1][0][2].colors[1]) {
        if ((cubePositions[2][0][2].colors[4] == cubePositions[1][0][1].colors[4] &&
             cubePositions[2][0][2].colors[1] != cubePositions[1][1][2].colors[1]) ||
            cubePositions[2][0][2].colors[1] == cubePositions[1][0][1].colors[4] ||
            cubePositions[2][0][2].colors[3] == cubePositions[1][0][1].colors[4]) {
            pifPaf();

            if (cubePositions[2][2][2].colors[1] == cubePositions[1][0][1].colors[4]) {
                while (cubePositions[2][2][2].colors[5] != cubePositions[1][1][2].colors[1]) {
                    rotate_D();
                    rotate_S();
                }
                for (int i = 0; i < 5; ++i) {
                    pifPaf();
                }
            } else if (cubePositions[2][2][2].colors[5] == cubePositions[1][0][1].colors[4]) {
                while (cubePositions[2][2][2].colors[1] != cubePositions[2][1][1].colors[3]) {
                    rotate_D();
                    rotate_S();
                }
                for (int i = 0; i < 3; ++i) {
                    pifPaf();
                }
            } else if (cubePositions[2][2][2].colors[3] == cubePositions[1][0][1].colors[4]) {
                while (cubePositions[2][2][2].colors[5] != cubePositions[2][1][1].colors[3]) {
                    rotate_D();
                    rotate_S();
                }
                for (int i = 0; i < 1; ++i) {
                    pifPaf();
                }
            }
        } else if (cubePositions[2][2][2].colors[1] == cubePositions[1][0][1].colors[4]) {
            while (cubePositions[2][2][2].colors[5] != cubePositions[1][1][2].colors[1]) {
                rotate_D();
                rotate_S();
            }
            for (int i = 0; i < 5; ++i) {
                pifPaf();
            }
        } else if (cubePositions[2][2][2].colors[5] == cubePositions[1][0][1].colors[4]) {
            while (cubePositions[2][2][2].colors[1] != cubePositions[2][1][1].colors[3]) {
                rotate_D();
                rotate_S();
            }
            for (int i = 0; i < 3; ++i) {
                pifPaf();
            }
        } else if (cubePositions[2][2][2].colors[3] == cubePositions[1][0][1].colors[4]) {
            while (cubePositions[2][2][2].colors[5] != cubePositions[2][1][1].colors[3]) {
                rotate_D();
                rotate_S();
            }
            for (int i = 0; i < 1; ++i) {
                pifPaf();
            }
        } else {
            rotate_U();
            rotate_D();
            rotate_S();
        }
    }
}

void Cube::solving_secont_layout() {
    while (cubePositions[0][1][0].colors[0] != cubePositions[1][1][0].colors[0] ||
           cubePositions[2][1][0].colors[0] != cubePositions[1][1][0].colors[0] ||
           cubePositions[0][1][0].colors[2] != cubePositions[0][1][1].colors[2] ||
           cubePositions[0][1][2].colors[2] != cubePositions[0][1][1].colors[2] ||
           cubePositions[0][1][2].colors[1] != cubePositions[1][1][2].colors[1] ||
           cubePositions[2][1][2].colors[1] != cubePositions[1][1][2].colors[1] ||
           cubePositions[2][1][0].colors[3] != cubePositions[2][1][1].colors[3] ||
           cubePositions[2][1][2].colors[3] != cubePositions[2][1][1].colors[3]) {
        if ((cubePositions[2][1][2].colors[1] != cubePositions[1][2][1].colors[5] &&
             cubePositions[2][1][2].colors[3] != cubePositions[1][2][1].colors[5]) &&
            (cubePositions[2][1][2].colors[1] != cubePositions[1][1][2].colors[1] ||
             cubePositions[2][1][2].colors[3] != cubePositions[2][1][1].colors[3])) {
            sunflower_R();
            rotate_Ur();
            while (cubePositions[1][2][2].colors[1] != cubePositions[1][1][2].colors[1]) {
                rotate_S();
                rotate_D();
            }
            if (cubePositions[1][2][2].colors[5] == cubePositions[2][1][1].colors[3]) {
                sunflower_R();
            } else {
                sunflower_L();
            }
        }
        if (cubePositions[1][2][2].colors[1] != cubePositions[1][2][1].colors[5] &&
            cubePositions[1][2][2].colors[5] != cubePositions[1][2][1].colors[5]) {
            while (cubePositions[1][2][2].colors[1] != cubePositions[1][1][2].colors[1]) {
                rotate_S();
                rotate_D();
            }
            if (cubePositions[1][2][2].colors[5] == cubePositions[2][1][1].colors[3]) {
                sunflower_R();
            } else {
                sunflower_L();
            }
        } else {
            rotate_U();
            rotate_S();
            rotate_D();
        }
    }
}

void Cube::solving_second_cross() {
    while (cubePositions[1][2][0].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[2][2][1].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[0][2][1].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[1][2][2].colors[5] != cubePositions[1][2][1].colors[5]) {

        if (cubePositions[1][2][0].colors[5] == cubePositions[1][2][1].colors[5] &&
            cubePositions[2][2][1].colors[5] == cubePositions[1][2][1].colors[5]) {
            rotate_Ur();
            rotate_F();
            pifPaf();
            pifPaf();
            rotate_Fr();
        } else if (cubePositions[1][2][0].colors[5] == cubePositions[1][2][1].colors[5] &&
                   cubePositions[0][2][1].colors[5] == cubePositions[1][2][1].colors[5]) {
            rotate_F();
            pifPaf();
            pifPaf();
            rotate_Fr();
        } else if (cubePositions[1][2][2].colors[5] == cubePositions[1][2][1].colors[5] &&
                   cubePositions[0][2][1].colors[5] == cubePositions[1][2][1].colors[5]) {
            rotate_U();
            rotate_F();
            pifPaf();
            pifPaf();
            rotate_Fr();
        } else if (cubePositions[1][2][0].colors[5] == cubePositions[1][2][1].colors[5] &&
                   cubePositions[2][2][1].colors[5] == cubePositions[1][2][1].colors[5]) {
            rotate_Ur();
            rotate_Ur();
            rotate_F();
            pifPaf();
            pifPaf();
            rotate_Fr();
        } else if (cubePositions[1][2][2].colors[5] == cubePositions[1][2][1].colors[5] &&
                   cubePositions[1][2][0].colors[5] == cubePositions[1][2][1].colors[5]) {
            rotate_Ur();
            rotate_F();
            pifPaf();
            rotate_Fr();
        } else if (cubePositions[0][2][1].colors[5] == cubePositions[1][2][1].colors[5] &&
                   cubePositions[2][2][1].colors[5] == cubePositions[1][2][1].colors[5]) {
            rotate_F();
            pifPaf();
            rotate_Fr();
        } else {
            rotate_F();
            pifPaf();
            rotate_Fr();
        }
    }
}

void Cube::solving_PLL() {
    while (cubePositions[0][2][0].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[2][2][0].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[0][2][2].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[2][2][2].colors[5] != cubePositions[1][2][1].colors[5]) {
        if (cubePositions[0][2][0].colors[0] == cubePositions[1][2][1].colors[5]) {
            reverse_pifpaf();
            reverse_pifpaf();
            reverse_pifpaf();
            reverse_pifpaf();
        }
        if (cubePositions[0][2][0].colors[2] == cubePositions[1][2][1].colors[5]) {

            reverse_pifpaf();
            reverse_pifpaf();
        } else {
            rotate_U();
        }
    }
}

void Cube::solving_edges_last_layout() {
    while (cubePositions[1][2][0].colors[0] != cubePositions[1][1][0].colors[0] ||
           cubePositions[0][2][1].colors[2] != cubePositions[0][1][1].colors[2] ||
           cubePositions[2][2][1].colors[3] != cubePositions[2][1][1].colors[3] ||
           cubePositions[1][2][2].colors[1] != cubePositions[1][1][2].colors[1]) {

        if (cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0] &&
            cubePositions[0][2][1].colors[2] == cubePositions[0][1][1].colors[2]) {
            kill_in_london();
        } else if (cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0] &&
                   cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3]) {
            rotate_Ur();
            kill_in_london();
        } else if (cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1] &&
                   cubePositions[0][2][1].colors[2] == cubePositions[0][1][1].colors[2]) {
            rotate_U();
            kill_in_london();
        } else if (cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1] &&
                   cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3]) {
            rotate_U();
            rotate_U();
            kill_in_london();
        } else if (cubePositions[1][2][2].colors[1] == cubePositions[1][1][2].colors[1] &&
                   cubePositions[1][2][0].colors[0] == cubePositions[1][1][0].colors[0]) {
            kill_in_london();
        } else if (cubePositions[2][2][1].colors[3] == cubePositions[2][1][1].colors[3] &&
                   cubePositions[0][2][1].colors[2] == cubePositions[0][1][1].colors[2]) {
            kill_in_london();
        } else {
            rotate_U();
        }
    }
}

void Cube::solving_OLL() {

    while (cubePositions[0][0][0].colors[0] != cubePositions[0][1][0].colors[0] ||
           cubePositions[0][2][0].colors[0] != cubePositions[0][1][0].colors[0]) {
        if (cubePositions[0][0][0].colors[0] == cubePositions[1][0][0].colors[0]) {
            infarct();
        } else if (cubePositions[0][0][2].colors[1] == cubePositions[1][0][2].colors[1]) {
            rotate_Lr();
            rotate_Rr();
            rotate_Mr();
        } else if (cubePositions[0][2][2].colors[1] == cubePositions[1][0][2].colors[1]) {
            rotate_Lr();
            rotate_Rr();
            rotate_Mr();
            rotate_Lr();
            rotate_Rr();
            rotate_Mr();
        } else if (cubePositions[0][2][0].colors[5] == cubePositions[1][2][0].colors[5]) {
            rotate_L();
            rotate_R();
            rotate_M();
        } else {
            infarct();
        }
    }
}

void Cube::solvingCube() {
    cout << "SOLVING CUBE \n";
    // 1 step неправильный крест
    while (cubePositions[1][2][0].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[0][2][1].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[2][2][1].colors[5] != cubePositions[1][2][1].colors[5] ||
           cubePositions[1][2][2].colors[5] != cubePositions[1][2][1].colors[5]) {
        solving_the_wrong_cross();
    }
    // 1 шаг правильный крест
    while (!cross) {
        solving_the_right_cross();
    }
    cross = false;

    rotate_R();
    rotate_R();
    rotate_L();
    rotate_L();
    rotate_M();
    rotate_M();

    //первый слой
    solving_first_layout();

    //второй слой
    solving_secont_layout();

    //желтый крест
    solving_second_cross();

    solving_PLL();

    solving_edges_last_layout();

    rotate_Fr();
    rotate_Br();
    rotate_Hr();

    solving_OLL();

    rotate_F();
    rotate_B();
    rotate_H();
    cout << '\n';
}

void Cube::load() {
    string filename;
    cin >> filename;
    std::ifstream input(filename);
    if (!input) {
        std::cout << "Error with File" << '\n';
    } else {
        loader = false;
        std::string cube_string;
        std::getline(input, cube_string);
        set_state_cube(cube_string);
        std::cout << "The cube was successfully initialized from the file." << '\n';
    }
}

void Cube::set_state_cube(string a) {
    cubePositions[0][2][0].colors[5] = getColor(a[0]);
    cubePositions[1][2][0].colors[5] = getColor(a[1]);
    cubePositions[2][2][0].colors[5] = getColor(a[2]);
    cubePositions[0][2][1].colors[5] = getColor(a[3]);
    cubePositions[1][2][1].colors[5] = getColor(a[4]);
    cubePositions[2][2][1].colors[5] = getColor(a[5]);
    cubePositions[0][2][2].colors[5] = getColor(a[6]);
    cubePositions[1][2][2].colors[5] = getColor(a[7]);
    cubePositions[2][2][2].colors[5] = getColor(a[8]);

    cubePositions[0][2][0].colors[2] = getColor(a[9]);
    cubePositions[0][2][1].colors[2] = getColor(a[10]);
    cubePositions[0][2][2].colors[2] = getColor(a[11]);
    cubePositions[0][1][0].colors[2] = getColor(a[12]);
    cubePositions[0][1][1].colors[2] = getColor(a[13]);
    cubePositions[0][1][2].colors[2] = getColor(a[14]);
    cubePositions[0][0][0].colors[2] = getColor(a[15]);
    cubePositions[0][0][1].colors[2] = getColor(a[16]);
    cubePositions[0][0][2].colors[2] = getColor(a[17]);

    cubePositions[0][2][2].colors[1] = getColor(a[18]);
    cubePositions[1][2][2].colors[1] = getColor(a[19]);
    cubePositions[2][2][2].colors[1] = getColor(a[20]);
    cubePositions[0][1][2].colors[1] = getColor(a[21]);
    cubePositions[1][1][2].colors[1] = getColor(a[22]);
    cubePositions[2][1][2].colors[1] = getColor(a[23]);
    cubePositions[0][0][2].colors[1] = getColor(a[24]);
    cubePositions[1][0][2].colors[1] = getColor(a[25]);
    cubePositions[2][0][2].colors[1] = getColor(a[26]);

    cubePositions[2][2][2].colors[3] = getColor(a[27]);
    cubePositions[2][2][1].colors[3] = getColor(a[28]);
    cubePositions[2][2][0].colors[3] = getColor(a[29]);
    cubePositions[2][1][2].colors[3] = getColor(a[30]);
    cubePositions[2][1][1].colors[3] = getColor(a[31]);
    cubePositions[2][1][0].colors[3] = getColor(a[32]);
    cubePositions[2][0][2].colors[3] = getColor(a[33]);
    cubePositions[2][0][1].colors[3] = getColor(a[34]);
    cubePositions[2][0][0].colors[3] = getColor(a[35]);

    cubePositions[2][2][0].colors[0] = getColor(a[36]);
    cubePositions[1][2][0].colors[0] = getColor(a[37]);
    cubePositions[0][2][0].colors[0] = getColor(a[38]);
    cubePositions[2][1][0].colors[0] = getColor(a[39]);
    cubePositions[1][1][0].colors[0] = getColor(a[40]);
    cubePositions[0][1][0].colors[0] = getColor(a[41]);
    cubePositions[2][0][0].colors[0] = getColor(a[42]);
    cubePositions[1][0][0].colors[0] = getColor(a[43]);
    cubePositions[0][0][0].colors[0] = getColor(a[44]);

    cubePositions[0][0][2].colors[4] = getColor(a[45]);
    cubePositions[1][0][2].colors[4] = getColor(a[46]);
    cubePositions[2][0][2].colors[4] = getColor(a[47]);
    cubePositions[0][0][1].colors[4] = getColor(a[48]);
    cubePositions[1][0][1].colors[4] = getColor(a[49]);
    cubePositions[2][0][1].colors[4] = getColor(a[50]);
    cubePositions[0][0][0].colors[4] = getColor(a[51]);
    cubePositions[1][0][0].colors[4] = getColor(a[52]);
    cubePositions[2][0][0].colors[4] = getColor(a[53]);
}

glm::vec3 Cube::getColor(char s) {
    switch (s) {
        case 'r':
            return red;
            break;
        case 'y':
            return yellow;
            break;
        case 'b':
            return blue;
            break;
        case 'w':
            return white;
            break;
        case 'o':
            return orange;
            break;
        case 'g':
            return green;
            break;
    }
}

void Cube::load_file() {
    loader = true;
}

void Cube::save_state_cube() {
//    string filename;
//    cin >> filename;
    std::ofstream output("text.txt");
    if (!output) {
        std::cout << "Error with File" << '\n';
    } else {
        loader = false;
        output << get_state_cube();
        std::cout << "Cube state saved successfully." << '\n';
    }
}

string Cube::get_state_cube() {
    string s;

    s += colorToChar(cubePositions[0][2][0].colors[5]);
    s += colorToChar(cubePositions[1][2][0].colors[5]);
    s += colorToChar(cubePositions[2][2][0].colors[5]);
    s += colorToChar(cubePositions[0][2][1].colors[5]);
    s += colorToChar(cubePositions[1][2][1].colors[5]);
    s += colorToChar(cubePositions[2][2][1].colors[5]);
    s += colorToChar(cubePositions[0][2][2].colors[5]);
    s += colorToChar(cubePositions[1][2][2].colors[5]);
    s += colorToChar(cubePositions[2][2][2].colors[5]);

    s += colorToChar(cubePositions[0][2][0].colors[2]);
    s += colorToChar(cubePositions[0][2][1].colors[2]);
    s += colorToChar(cubePositions[0][2][2].colors[2]);
    s += colorToChar(cubePositions[0][1][0].colors[2]);
    s += colorToChar(cubePositions[0][1][1].colors[2]);
    s += colorToChar(cubePositions[0][1][2].colors[2]);
    s += colorToChar(cubePositions[0][0][0].colors[2]);
    s += colorToChar(cubePositions[0][0][1].colors[2]);
    s += colorToChar(cubePositions[0][0][2].colors[2]);

    s += colorToChar(cubePositions[0][2][2].colors[1]);
    s += colorToChar(cubePositions[1][2][2].colors[1]);
    s += colorToChar(cubePositions[2][2][2].colors[1]);
    s += colorToChar(cubePositions[0][1][2].colors[1]);
    s += colorToChar(cubePositions[1][1][2].colors[1]);
    s += colorToChar(cubePositions[2][1][2].colors[1]);
    s += colorToChar(cubePositions[0][0][2].colors[1]);
    s += colorToChar(cubePositions[1][0][2].colors[1]);
    s += colorToChar(cubePositions[2][0][2].colors[1]);

    s += colorToChar(cubePositions[2][2][2].colors[3]);
    s += colorToChar(cubePositions[2][2][1].colors[3]);
    s += colorToChar(cubePositions[2][2][0].colors[3]);
    s += colorToChar(cubePositions[2][1][2].colors[3]);
    s += colorToChar(cubePositions[2][1][1].colors[3]);
    s += colorToChar(cubePositions[2][1][0].colors[3]);
    s += colorToChar(cubePositions[2][0][2].colors[3]);
    s += colorToChar(cubePositions[2][0][1].colors[3]);
    s += colorToChar(cubePositions[2][0][0].colors[3]);

    s += colorToChar(cubePositions[2][2][0].colors[0]);
    s += colorToChar(cubePositions[1][2][0].colors[0]);
    s += colorToChar(cubePositions[0][2][0].colors[0]);
    s += colorToChar(cubePositions[2][1][0].colors[0]);
    s += colorToChar(cubePositions[1][1][0].colors[0]);
    s += colorToChar(cubePositions[0][1][0].colors[0]);
    s += colorToChar(cubePositions[2][0][0].colors[0]);
    s += colorToChar(cubePositions[1][0][0].colors[0]);
    s += colorToChar(cubePositions[0][0][0].colors[0]);

    s += colorToChar(cubePositions[0][0][2].colors[4]);
    s += colorToChar(cubePositions[1][0][2].colors[4]);
    s += colorToChar(cubePositions[2][0][2].colors[4]);
    s += colorToChar(cubePositions[0][0][1].colors[4]);
    s += colorToChar(cubePositions[1][0][1].colors[4]);
    s += colorToChar(cubePositions[2][0][1].colors[4]);
    s += colorToChar(cubePositions[0][0][0].colors[4]);
    s += colorToChar(cubePositions[1][0][0].colors[4]);
    s += colorToChar(cubePositions[2][0][0].colors[4]);

    return s;
}

char Cube::colorToChar(glm::vec3 a) {
    if (a == red) {
        return 'r';
    } else if (a == yellow) {
        return 'y';
    } else if (a == white) {
        return 'w';
    } else if (a == orange) {
        return 'o';
    } else if (a == blue) {
        return 'b';
    } else if (a == green) {
        return 'g';
    }
}

void Cube::save_cube() {
    loader = true;
}

void Cube::check_invariant() {
    for (int i = 0; i < 200; ++i) {
        solvingCube();
    }
    if (cubePositions[0][0][0].colors[0] != cubePositions[0][1][0].colors[0] ||
        cubePositions[0][2][0].colors[0] != cubePositions[0][1][0].colors[0]) {
        cout << "Невозможно собрать";
    } else {
        cout << "Возможно собрать";
    }
}
