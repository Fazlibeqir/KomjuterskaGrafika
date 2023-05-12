//
// Created by Beqir on 13.5.2023.
//

#include "InputHandler.h"

InputHandler::InputHandler(GameContoller* gameController) {
    m_gameController = gameController;
}

void InputHandler::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        m_gameController->handleClick(xpos, ypos);
    }
}

void InputHandler::handleInput() {
    // Get the window handle from the game controller
    GLFWwindow* window = m_gameController->getWindow();
    int windowHeight=m_gameController->getWindowHeight();
    // Check if the escape key was pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    // Check if the left mouse button was pressed
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Get the position of the mouse cursor
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Convert the mouse position to screen coordinates
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float x = (float)xpos / (float)m_gameController->getWindowWidth()*2.0f-1.0f;
        float y = -(float)ypos / (float)windowHeight*2.0f+1.0f;

        // Pass the mouse coordinates to the game controller
        m_gameController->onMouseClick(x, y);
    }
}



