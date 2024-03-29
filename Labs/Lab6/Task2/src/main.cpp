#include <OpenGLPrj.hpp>
#include <GLFW/glfw3.h>
#include <Camera.hpp>
#include <Shader.hpp>
#include <iostream>
#include <string>
#include <vector>

const std::string program_name = ("Camera");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float lastX = SCR_WIDTH / 2.0f;
static float lastY = SCR_HEIGHT / 2.0f;
static bool firstMouse = true;

// timing
static float deltaTime = 0.0f; // time between current frame and last frame
static float lastFrame = 0.0f;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        program_name.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // tell GLFW to capture our mouse
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

  // build and compile our shader program
  // ------------------------------------
  std::string shader_location("../res/shaders/");

  std::string used_shaders("shader");

  Shader ourShader(shader_location + used_shaders + std::string(".vert"),
                   shader_location + used_shaders + std::string(".frag"));

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
    std::vector<float> vertices;
    std::vector<float> vertices2;
    std::vector<float> vertices3;
    std::vector<float> vertices4;

    float angle=0;
    int numPoints=32;
    float radius= 0.3f;
    float radius2= 0.4f;

    for(int i=0;i<=numPoints;i++){
        float x= radius * glm::sin(glm::two_pi<float>()*angle/360);
        float y= radius * glm::cos(glm::two_pi<float>()*angle/360);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0);

        vertices2.push_back(x);
        vertices2.push_back(y);
        vertices2.push_back(-0.2f);

        vertices3.push_back(x);
        vertices3.push_back(y);
        vertices3.push_back(0);

        vertices3.push_back(x);
        vertices3.push_back(y);
        vertices3.push_back(-0.2f);

        x=radius2 *glm::sin(glm::two_pi<float>()*angle/360);
        y=radius2 *glm::cos(glm::two_pi<float>()*angle/360);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0);

        vertices2.push_back(x);
        vertices2.push_back(y);
        vertices2.push_back(-0.2f);

        vertices4.push_back(x);
        vertices4.push_back(y);
        vertices4.push_back(0);

        vertices4.push_back(x);
        vertices4.push_back(y);
        vertices4.push_back(-0.2f);


        angle += 360.0f / numPoints;
    }
    vertices.insert(vertices.end(), vertices2.begin(), vertices2.end());
    vertices.insert(vertices.end(), vertices3.begin(), vertices3.end());
    vertices.insert(vertices.end(), vertices4.begin(), vertices4.end());

    std::vector<float> vertices5 ={
            0.0f, -0.5f, -0.2f, 0.5f,  -0.5f, -0.2f,
            0.5f,  0.5f,  -0.2f, 0.5f,  0.5f,  -0.2f,
            0.0f, 0.5f,  -0.2f, -0.0f, -0.5f, -0.2f,

            -0.0f, -0.5f, 0.0f,  0.5f,  -0.5f, 0.0f,
            0.5f,  0.5f,  0.0f,  0.5f,  0.5f,  0.0f,
            -0.0f, 0.5f,  0.0f,  -0.0f, -0.5f, 0.0f,

            -0.0f, 0.5f,  0.0f,  -0.0f, 0.5f,  -0.2f,
            -0.0f, -0.5f, -0.2f, -0.0f, -0.5f, -0.2f,
            -0.0f, -0.5f, 0.0f,  -0.0f, 0.5f,  0.0f,

            0.5f,  0.5f,  0.0f,  0.5f,  0.5f,  -0.2f,
            0.5f,  -0.5f, -0.2f, 0.5f,  -0.5f, -0.2f,
            0.5f,  -0.5f, 0.0f,  0.5f,  0.5f,  0.0f,

            -0.0f, -0.5f, -0.2f, 0.5f,  -0.5f, -0.2f,
            0.5f,  -0.5f, 0.0f,  0.5f,  -0.5f, 0.0f,
            -0.0f, -0.5f, 0.0f,  -0.0f, -0.5f, -0.2f,

            -0.0f, 0.5f,  -0.2f, 0.5f,  0.5f,  -0.2f,
            0.5f,  0.5f,  0.0f,  0.5f,  0.5f,  0.0f,
            -0.0f, 0.5f,  0.0f,  -0.0f, 0.5f,  -0.2f
    };
    vertices.insert(vertices.end(), vertices5.begin(), vertices5.end());

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    int uniform= glGetUniformLocation(ourShader.ID, "ChangeColor");
    // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // activate shader
    ourShader.use();

    // pass projection matrix to shader (note that in this case it could change
    // every frame)
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Zoom), SCR_WIDTH * 1.0f / SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("view", view);

    // render boxes
    glBindVertexArray(VAO);
    glm::mat4 model =glm::mat4(1.0f);
    ourShader.setMat4("model", model);
    //Draw The "O"
    glUniform3f(uniform, 0.50, 0.70, 1.00);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 66);
    glDrawArrays(GL_TRIANGLE_STRIP, 66, 66);
   glDrawArrays(GL_TRIANGLE_STRIP, 66*2, 66);
    glDrawArrays(GL_TRIANGLE_STRIP, 66*3, 66);

    //Draw the "I"
    glUniform3f(uniform, 0.25, 0.35, 0.50);
    model= glm::translate(model, glm::vec3(-1,0,0));
    ourShader.setMat4("model",model);
    glDrawArrays(GL_TRIANGLES, 66*4, 36);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
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

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposd, double yposd) {
  float xpos = static_cast<float>(xposd);
  float ypos = static_cast<float>(yposd);
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
