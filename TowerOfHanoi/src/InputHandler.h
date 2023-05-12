//
// Created by Beqir on 13.5.2023.
//

#ifndef OPENGLPRJ_INPUTHANDLER_H
#define OPENGLPRJ_INPUTHANDLER_H

#include <GLFW/glfw3.h>
#include "GameContoller.h"

class InputHandler {
public:
    InputHandler(GameContoller* gameController);
    void processInput(GLFWwindow* window);

    void handleInput();

private:
    GameContoller* m_gameController;
};

#endif //OPENGLPRJ_INPUTHANDLER_H
