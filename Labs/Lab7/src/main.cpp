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

float JumpAcceleration=20.0f;
float CrouchPosition=-0.5f;
float CrouchTime=0.2f;
float ReturnTime=0.2f;

float jumpVel=0.0f;
bool isJumping= false;
bool isCrouching=false;
float crouchTimer=0.0f;
float returnTimer=0.0f;
float groundLevel=0.0f;
float initialY=0.0f; //position before all

float easeOutCubic(float t){{
    t-=1.0f;
        return t*t*t+1.0f;
}}

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
    float vertices[] = {
            -50, -0.1f, -50,  0.0f, 0.0f,
            50,  -0.1f, -50, 1.0f, 0.0f,
            50,  0.0f,  -50,  1.0f, 1.0f,
            50,  0.0f,  -50, 1.0f, 1.0f,
            -50, 0.0f,  -50,  0.0f, 1.0f,
            -50, -0.1f, -50, 0.0f, 0.0f,

            -50, -0.1f, 50,  0.0f, 0.0f,
            50,  -0.1f, 50,  1.0f, 0.0f,
            50,  0.0f,  50,  1.0f, 1.0f,
            50,  0.0f,  50,  1.0f, 1.0f,
            -50, 0.0f,  50,  0.0f, 1.0f,
            -50, -0.1f, 50,  0.0f, 0.0f,

            -50, 0.0f,  50,  1.0f, 0.0f,
            -50, 0.0f,  -50, 1.0f, 1.0f,
            -50, -0.1f, -50, 0.0f, 1.0f,
            -50, -0.1f, -50, 0.0f, 1.0f,
            -50, -0.1f, 50,  0.0f, 0.0f,
            -50, 0.0f,  50,  1.0f, 0.0f,

            50,  0.0f,  50,  1.0f, 0.0f,
            50,  0.0f,  -50, 1.0f, 1.0f,
            50,  -0.1f, -50, 0.0f, 1.0f,
            50,  -0.1f, -50, 0.0f, 1.0f,
            50,  -0.1f, 50,  0.0f, 0.0f,
            50,  0.0f,  50,  1.0f, 0.0f,

            -50, -0.1f, -50, 0.0f, 1.0f,
            50,  -0.1f, -50, 1.0f, 1.0f,
            50,  -0.1f, 50,  1.0f, 0.0f,
            50,  -0.1f, 50,  1.0f, 0.0f,
            -50, -0.1f, 50,  0.0f, 0.0f,
            -50, -0.1f, -50, 0.0f, 1.0f,

            -50, 0.0f,  -50, 0.0f, 50.0f,
            50,  0.0f,  -50, 50.0f, 50.0f,
            50,  0.0f,  50,  50.0f, 0.0f,
            50,  0.0f,  50,  50.0f, 0.0f,
            -50, 0.0f,  50,  0.0f, 0.0f,
            -50, 0.0f,  -50, 0.0f, 50.0f };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        reinterpret_cast<void *>(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // load and create a texture
  // -------------------------
  unsigned int texture1;
  // texture 1
  // ---------
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping parameters
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
      GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(
      true); // tell stb_image.h to flip loaded texture's on the y-axis.
  // The FileSystem::getPath(...) is part of the GitHub repository so we can
  // find files on any IDE/platform; replace it with your own image path.
  unsigned char *data = stbi_load("../res/textures/container.jpg", &width,
                                  &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
   ourShader.use();
  ourShader.setInt("texture1", 0);

//  camera.Position.y=8;
 camera.MovementSpeed=8;
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

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

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
      // calculate the model matrix for each object and pass it to shader before
      // drawing
      glm::mat4 model = glm::mat4(
          1.0f); // make sure to initialize matrix to identity matrix first
      model = glm::translate(model, glm::vec3(0,-4,0));
      ourShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    if(isJumping){
        camera.Position.y+=jumpVel*deltaTime;
        jumpVel-=JumpAcceleration*deltaTime;

        if(camera.Position.y<=groundLevel){
            camera.Position.y=groundLevel;
            isJumping= false;
            jumpVel=0.0f;
            initialY=groundLevel;
            returnTimer=0.0f;
        }
    }else{
        if(isCrouching){
            if(crouchTimer<CrouchTime){
                float t=crouchTimer/CrouchTime;
                float smoothing= easeOutCubic(t);
                camera.Position.y=glm::mix(camera.Position.y,CrouchPosition,smoothing);
                crouchTimer+=deltaTime;
                initialY=camera.Position.y;
                returnTimer=0.0f;
            }else{
                camera.Position.y=CrouchPosition;
            }
        }else{
            crouchTimer=0.0f;

            if(returnTimer<ReturnTime){
                float t=returnTimer/ReturnTime;
                float smoothing= easeOutCubic(t);
                camera.Position.y=glm::mix(camera.Position.y,initialY, smoothing);
                returnTimer+=deltaTime;
            }else{
                camera.Position.y=initialY;
            }
        }
    }


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
  if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)==GLFW_PRESS)
      isCrouching=true;
  if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)==GLFW_RELEASE && isCrouching)
  {
      isCrouching= false;
      camera.Position.y=1;
  }
  if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS && !isJumping)
  {
      jumpVel=10;
      isJumping= true;
  }
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
