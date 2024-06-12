#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <ctime>

#include "lib/glew-cmake/include/GL/glew.h"
#include "lib/glfw/include/GLFW/glfw3.h"
#include "lib/glm/glm/glm.hpp"
#include "lib/glm/glm/gtc/matrix_transform.hpp"
#include "lib/glm/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera.h"

using namespace std;

struct cubic {
    glm::vec3 colors[6];
    glm::vec3 cord;
};

class Cube {
private:
    void init();
    GLFWwindow *window;
    GLuint VBO, VAO;
    static bool keys[1024];
    const GLuint WIDTH = 800, HEIGHT = 600;
    cubic cubePositions[3][3][3];
    bool cross = false;
    bool loader = false;
    bool saver = false;

    class Camera cam;

    //moves
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
    void do_movement();

    //COLORS
    const glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);
    const glm::vec3 yellow = glm::vec3(1.0f, 1.0f, 0.0f);
    const glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);
    const glm::vec3 orange = glm::vec3(1.0f, 0.4f, 0.0f);
    void setColors(glm::vec3 colors[], glm::vec3 color0, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3, glm::vec3 color4, glm::vec3 color5);

    //rotation
    void rotate_R();
    void rotate_Rr();
    void rotate_M();
    void rotate_Mr();
    void rotate_L() ;
    void rotate_Lr();
    void rotate_U();
    void rotate_Ur();
    void rotate_S();
    void rotate_Sr();
    void rotate_D();
    void rotate_Dr();
    void rotate_F();
    void rotate_Fr();
    void rotate_H();
    void rotate_Hr();
    void rotate_B();
    void rotate_Br();
    void pifPaf();
    void sunflower_R();
    void sunflower_L();
    void reverse_pifpaf();
    void kill_in_london();
    void infarct();

    //scrumble and solve
    void mixinCube();
    void solving_the_wrong_cross();
    void solving_the_right_cross();
    void solving_first_layout();
    void solving_secont_layout();
    void solving_second_cross();
    void solving_PLL();
    void solving_edges_last_layout();
    void solving_OLL();
    void solvingCube();

    //load and save

    void set_state_cube(string a);
    glm::vec3 getColor(char s);
    void load_file();

    void save_state_cube();
    string get_state_cube();
    char colorToChar(glm::vec3 a);

    //check invarian (eazy aproach)
    void check_invariant();
public:
    bool draw();
    Cube();
    ~Cube();
    void load();
    void save_cube();
};

#endif
