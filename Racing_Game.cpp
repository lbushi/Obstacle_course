// Racing_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "Shape.h"
#include "Shader.h"
#include "Camera.h"
#include "Car.h"
#include "stbi_image.h"
#include "Environment.h"
#include "Obstacle.h"
#include <random>
#include <ctime>
#include "Orb.h"
using namespace std;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
void framebuffer_size_callback(GLFWwindow*, int, int);
void keyboard_callback(GLFWwindow*, int, int, int, int);
void jump_up();
void jump_down();
void allow_jump();
Camera camera = Camera();
glm::vec3 car_direction = glm::vec3(0.0f, 0.0f, -1.0f);
int Clock = -1; // this clock is set into motion when the player jumps and reset to -1 after the jump is over
bool game_paused = 0;
const glm::vec3 car_direction_straight = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 car_direction_left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 car_direction_right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 car_direction_up = glm::vec3(0.0f, 1.0f, 0.0f);
const float sensitivity = 0.1f;
const int obstacle_number = 100;
const int obstacle_space = 150;
const int clock_peak = 15; // the peak roughly models how long one half-jump will be
int going_up = -1;
const float left_bound = -5.0f;
const float right_bound = 5.0f;
const int no_of_orbs = 100;
static float randomize_height() {
    int random = rand();
    if (random % 2) {
        return 3.0f;
    }
    else {
        return 7.0f;
    }
}
static float randomize_width() {
    int random = rand();
    if (random % 2) {
        return 5.0f;
    }
    else {
        return 7.5f;
    }

}
static int randomize_pos() {
    int random = rand();
    if (random % 2) {
        return 0;
    }
    else {
        return 5;
    }
}
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TurboRacer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyboard_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_ALWAYS);
    srand(time(NULL)); //seed for the next calls to rand() in the randomize functions above
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 16000.0f);
    glm::mat4 view = glm::mat4(1.0f);
    Shader program = Shader("C:\\Users\\LBUSHI\\source\\repos\\Racing_Game\\Racing_Game\\VertexShader.txt", "C:\\Users\\LBUSHI\\source\\repos\\Racing_Game\\Racing_Game\\FragmentShader.txt");
    vector<Shape> stripes;
    for (int i = 0; i < 100; ++i) {
        float vertices[] = {
            -1.0f, -4.0f, -160 * i - 0.1f, 0.0f, 0.0f, 0.0f,
            -1.0f, -4.0f, -160 * i - 40.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -4.0f, -160 * i - 40.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -4.0f, -160 * i - 40.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -4.0f, -160 * i - 0.1f, 0.0f, 0.0f, 0.0f,
            -1.0f, -4.0f, -160 * i - 0.1f, 0.0f, 0.0f, 0.0f
        };
        stripes.emplace_back(Shape(vertices, sizeof(vertices), &program));
    }
    float vertices[] = {
        -5.0f, -4.0f, -0.1f, 1.0f, 1.0f, 1.0f,
        -5.0f, -4.0f, -16000.0f, 1.0f, 1.0f, 1.0f,
        5.0f, -4.0f, -16000.0f, 1.0f, 1.0f, 1.0f,
        5.0f, -4.0f, -16000.0f, 1.0f, 1.0f, 1.0f,
       5.0f, -4.0f, -0.1f, 1.0f, 1.0f, 1.0f,
        -5.0f, -4.0f, -0.1f, 1.0f, 1.0f, 1.0f
    };
    Shape shape = Shape(vertices, sizeof(vertices), &program);
    float car_vertices[] = {
        -1.0f, -4.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -4.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -4.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -4.0f, -5.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -5.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -7.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -4.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -4.0f, -5.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -5.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, -7.0f , 1.0f, 0.0f, 0.0f,
        1.0f, -4.0f, -7.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -4.0f, -7.0f , 1.0f, 0.0f, 0.0f,
    };
    Car car = Car(2.0f, 0.0f, car_vertices, sizeof(car_vertices), car_direction, &program);
    car.attach_Observer(&camera);
    vector<Obstacle> obstacles;
    for (int i = 1; i <= obstacle_number; ++i) {
        float pos_x = randomize_pos();
        float width = randomize_width();
        float height = randomize_height();
        if (-pos_x + width > 5.0f) {
            pos_x += 2.5f;
        }
        float vertices[] = {
            -pos_x, -4.0f, -obstacle_space * i, 0.0f, 0.0f, 1.0f,
            -pos_x, -4.0f + height, -obstacle_space * i, 0.0f, 0.0f, 1.0f,
            -pos_x + width, -4.0f + height, -obstacle_space * i, 0.0f, 0.0f, 1.0f,
            -pos_x + width, -4.0f + height, -obstacle_space * i, 0.0f, 0.0f, 1.0f,
            -pos_x + width, -4.0f, -obstacle_space * i, 0.0f, 0.0f, 1.0f,
            -pos_x, -4.0f, -obstacle_space * i, 0.0f, 0.0f, 1.0f
        };
        obstacles.emplace_back(Obstacle(vertices, sizeof(vertices), &program, -obstacle_space * i, -pos_x, width, height));
    }
    for (auto& obstacle : obstacles) {
        camera.attach_Observer(&obstacle);
        car.attach_Observer(&obstacle);
    }
    vector<Orb> orbs;
    for (int i = 0; i < no_of_orbs; ++i) 
    {
        float pos_z = -rand() % 200 - 600 + ((i == 0) ? 0.0f : orbs[i - 1].get_z());
        float vertices[] = {
            -2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f, 
            //the base in the middle ends here
            2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            0.0f, -4.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
             0.0f, -4.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            0.0f, -4.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            0.0f, -4.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f, 
            // bottom half of orb ends here
            2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            0.0f, -1.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
             0.0f, -1.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,
            -2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            0.0f, -1.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z - 10.0f, 1.0f, 0.0f, 1.0f,
            2.0f, -2.5f, pos_z, 1.0f, 0.0f, 1.0f,
            0.0f, -1.0f, pos_z - 5.0f, 1.0f, 0.0f, 1.0f,

        };
        orbs.emplace_back(Orb(vertices, sizeof(vertices), &program, pos_z, -2.0f));
    }
    for (auto& orb : orbs) {
        car.attach_Observer(&orb);
    }
    float env_vertices[] = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f
    };
    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    unsigned char* env_data = stbi_load("C:\\Users\\LBUSHI\\source\\repos\\Racing_Game\\Racing_Game\\nebula.jpg", &width, &height, &channels, 0);
    Shader env_program = Shader("C:\\Users\\LBUSHI\\source\\repos\\Racing_Game\\Racing_Game\\EnvVertexShader.txt", "C:\\Users\\LBUSHI\\source\\repos\\Racing_Game\\Racing_Game\\EnvFragmentShader.txt");
    Environment env = Environment(env_vertices, sizeof(env_vertices), env_data, width, height, &env_program);
    program.setFloat(0.0f, "brightness");
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glDepthMask(GL_FALSE);
        env.draw();
        if (going_up == 1 && !game_paused) {
            jump_up();
        }
        else if (going_up == 0 && !game_paused) {
            jump_down();
        }
        car.set_direction(car_direction);
        if (game_paused) {
            car.set_direction(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        program.setMatrix4(projection, "proj");
        program.setMatrix4(view, "view");
        program.setMatrix4(model, "model");
        shape.draw();
        glDepthMask(GL_TRUE);
        for (auto& stripe : stripes) {
            stripe.draw();
        }
        for (auto& obstacle : obstacles) {
            obstacle.draw();
        }
        for (auto& orb : orbs) {
            orb.draw();
        }
        car.draw();
        camera.change_pos();
        view = camera.view();
        if (car.check_collision()) {
            std::cout << "You hit an obstacle!\nGame over!";
            break;
        }
        camera.notify_Observers();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void keyboard_callback(GLFWwindow*, int key, int s, int action, int m) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        game_paused = !game_paused;
    }
    else if (game_paused) {
        return;
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        allow_jump();
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        car_direction += sensitivity * car_direction_right;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        car_direction -= sensitivity * car_direction_right;
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        car_direction += sensitivity * car_direction_left;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        car_direction -= sensitivity * car_direction_left;
    }
}

void jump_up() {
    going_up = 1;
    ++Clock;
    car_direction += sensitivity / 70 * static_cast<float>((clock_peak - Clock))  * car_direction_up;
    if (Clock == 2 * clock_peak) {
        Clock = 2 * clock_peak + 1;
        jump_down();
    }
}
void jump_down() {
    going_up = 0;
    --Clock;
    car_direction += sensitivity / 70 * static_cast<float>((clock_peak - Clock)) * car_direction_up;
    if (Clock == 0) {
        going_up = -1;
        Clock = -1;
    }
}
void allow_jump() {
    if (Clock != -1) {
        return;
    }
    jump_up();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*TODO:
COLLISION DETECTION WITH OBSTACLES -DONE
ADD TEXTURES TO THE PATH
DO NOT ALLOW THE CAR TO GO OUTSIDE OF THE PATH BOUNDARIES
ADD PAUSE FUNCTIONALITY
*/
