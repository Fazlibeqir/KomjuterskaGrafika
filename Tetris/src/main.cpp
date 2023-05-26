#include <OpenGLPrj.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include "Shader.hpp"


const std::string program_name = ("Tetris");

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const int M=20;
const int N=10;

int field[M][N]={0};
struct Point{
    int x,y;
}a[4],b[4];
int figures[7][4]={
        1,3,5,7, // I
        2,4,5,7, // Z
        3,5,4,6, // S
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
};
bool check(){
    for(auto & i : a){
        if(i.x<0||i.x>=N||i.y>=M)
            return false;
        else if (field[i.y][i.x])
            return false;
    }
    return true;
}
void drawBackground(Shader & shader)
{
    // Set up vertices and texture coordinates
    float vertices[] = {
            // positions        // texture coordinates
            -5.0f, -5.0f, 0.0f,  0.0f, 5.0f, // bottom left
            5.0f, -5.0f, 0.0f,  5.0f, 5.0f, // bottom right
            -5.0f,  5.0f, 0.0f,  0.0f, 0.0f, // top left
            5.0f,  5.0f, 0.0f,  5.0f, 0.0f  // top right
    };
    unsigned int indices[] = {
            0, 1, 2, // first triangle
            1, 2, 3  // second triangle
    };

    // Create and bind vertex array object (VAO) and vertex buffer object (VBO)
    unsigned int VAO, VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image and create texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../res/textures/background.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load background texture" << std::endl;
    }
    stbi_image_free(data);

    // Render the background quad
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void drawField(Shader & shader){
    // Set up vertices and texture coordinates
    float vertices[] = {
            // positions        // texture coordinates
            -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, // bottom left
            1.0f, -1.0f, 0.0f,  1.0f, 1.0f, // bottom right
            -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, // top left
            1.0f,  1.0f, 0.0f,  1.0f, 0.0f  // top right
    };
    unsigned int indices[] = {
            0, 1, 2, // first triangle
            1, 2, 3  // second triangle
    };

    // Create and bind vertex array object (VAO) and vertex buffer object (VBO)
    unsigned int VAO, VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image and create texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../res/textures/frame.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load background texture" << std::endl;
    }
    stbi_image_free(data);

    // Render the background quad
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void drawCurrentFigure(Shader& shader){
    // Set up vertices and texture coordinates
    float vertices[] = {
            // positions        // texture coordinates
            -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, // bottom left
            1.0f, -1.0f, 0.0f,  1.0f, 1.0f, // bottom right
            -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, // top left
            1.0f,  1.0f, 0.0f,  1.0f, 0.0f  // top right
    };
    unsigned int indices[] = {
            0, 1, 2, // first triangle
            1, 2, 3  // second triangle
    };

    // Create and bind vertex array object (VAO) and vertex buffer object (VBO)
    unsigned int VAO, VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load and create a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image and create texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../res/textures/tiles.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load background texture" << std::endl;
    }
    stbi_image_free(data);

    // Render the background quad
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, program_name.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // load and create a texture
    // -------------------------
    std::string shader_location("../res/shaders/");

    std::string used_shaders("shader");

    Shader shader(shader_location + used_shaders + std::string(".vert"),
                     shader_location + used_shaders + std::string(".frag"));

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawBackground(shader);
//        drawField(shader);
//        drawCurrentFigure(shader);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

