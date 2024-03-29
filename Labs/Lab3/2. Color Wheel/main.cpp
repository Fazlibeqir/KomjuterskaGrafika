#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>
#include <vector>
#include <iostream>


const std::string program_name = ("GLSL Shader class example");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, program_name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("../res/shaders/shader.vert",
                     "../res/shaders/shader.frag"
    );


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
//        float vertices[] = {
//        // positions         // colors
//         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
//         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
//
//    };
    std::vector<float> vertices;
    std::vector<float> colors;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.5f);
    vertices.push_back(0.5f);
    vertices.push_back(0.5f);

    float radius = 0.6f;
    float angle;
    int numAngles = 360;
    float x, y, z = 0.0f;
    auto twoPi = glm::two_pi<float>();
   //RGB
//     for (auto i = 0; i < numAngles + 2; i++){
//        float r=glm::cos(twoPi*i/numAngles);
//        float g=glm::cos(twoPi*(i+120)/numAngles);
//        float b=glm::cos(twoPi*(i+240)/numAngles);
//        colors.push_back(r);
//        colors.push_back(b);
//        colors.push_back(g);
//    }
    //HSL to RGB
    for (auto i = 0; i < numAngles + 2; i++) {
        float hue = 360.0f * i / numAngles;
        float saturation = 1.0f;
        float lightness = 0.5f;
        float chroma = (1.0f - std::abs(2.0f * lightness - 1.0f)) * saturation;
        float intermediateChroma = chroma * (1.0f - std::abs(fmod(hue / 60.0f, 2.0f) - 1.0f));
        float amountIsAddedToColor = lightness - chroma / 2.0f;
        float r, g, b;
        if (hue < 60.0f) {
            r = chroma;
            g = intermediateChroma;
            b = 0.0f;
        } else if (hue < 120.0f) {
            r = intermediateChroma;
            g = chroma;
            b = 0.0f;
        } else if (hue < 180.0f) {
            r = 0.0f;
            g = chroma;
            b = intermediateChroma;
        } else if (hue < 240.0f) {
            r = 0.0f;
            g = intermediateChroma;
            b = chroma;
        } else if (hue < 300.0f) {
            r = intermediateChroma;
            g = 0.0f;
            b = chroma;
        } else {
            r = chroma;
            g = 0.0f;
            b = intermediateChroma;
        }
        r += amountIsAddedToColor;
        g += amountIsAddedToColor;
        b += amountIsAddedToColor;
        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);
    }

    for (auto i = 0; i < numAngles + 1; i++) {
        angle = (twoPi * i) / numAngles;
        x = radius * glm::cos(angle);
        y = radius * glm::sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(colors[i * 3]);
        vertices.push_back(colors[i * 3 + 1]);
        vertices.push_back(colors[i * 3 + 2]);
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);


    // render loop
    // -----------
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numAngles + 2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

