//
// Created by Beqir on 12.5.2023.
//

#ifndef OPENGLPRJ_GAMECONTOLLER_H
#define OPENGLPRJ_GAMECONTOLLER_H
#include "GameState.h"
#include "Renderer.h"
#include "inputHandler.h"


class GameContoller {
public:
    GameContoller(GLFWwindow* window);
    ~GameContoller();
    void run();

    void handleClick(double d, double d1);

    GLFWwindow *getWindow();
    float convertScreenToGameX(int x);
    float convertScreenToGameY(int y);
    void onMouseClick(int x, int y);

    float getWindowWidth();

private:
    float WINDOW_WIDTH;
    float GAME_WIDTH;
    GLFWwindow* window_;
    GameState* gameState;
    Renderer* renderer;
    InputHandler* inputHandler;



};


#endif //OPENGLPRJ_GAMECONTOLLER_H
