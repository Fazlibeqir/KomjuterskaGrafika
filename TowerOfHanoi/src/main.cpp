#include <GLFW/glfw3.h>
#include "OpenGLPrj.hpp"
#include <iostream>
#include "glad/glad.h"

const int numDisks = 5;
const float poleXOffset = 0.6f;
const float diskXOffset = 0.2f;
const float diskHeight = 0.1f;
const float poleHeight = 1.0f;
const float poleRadius = 0.05f;
const float* blue = glm::value_ptr(glm::vec3(0.0f, 0.0f, 1.0f));
const float* green = glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f));
const float* red = glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f));
const float* white = glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f));

struct Disk{
    int size;
    float x,y;
    const float color;
};
struct Tower {
    int top;
    Disk disks[4];
};
const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set the OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tower of Hanoi", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Main game loop
    while (!glfwWindowShouldClose(window)) {
        // Handle user input

        // Update the game state

        // Render the scene

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
