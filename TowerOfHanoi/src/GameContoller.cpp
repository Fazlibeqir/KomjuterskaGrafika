//
// Created by Beqir on 12.5.2023.
//

#include "GameContoller.h"
#include "GameState.h"
#include "Renderer.h"
#include "inputHandler.h"

float convertScreenToGameX(int x);

GameContoller::GameContoller(GLFWwindow* window) : window_(window) {
    gameState= new GameState();
    renderer =new Renderer(gameState);
    inputHandler=new InputHandler(gameState);
}
GameContoller::~GameContoller(){
    delete gameState;
    delete renderer;
    delete inputHandler;
}
void GameContoller::run() {
    gameState->initialize();
    // Game loop
    while (!gameState->isGameOver()) {
        // Handle user input
        inputHandler->handleInput();

        // Update game state
        gameState->update();

        // Render game
        renderer->render();

    }

    // Game over
    renderer->showGameOverScreen();
}

void GameContoller::handleClick(double d, double d1) {

}
GLFWwindow *GameContoller::getWindow() {
    return window_;
}
float getWindowWidth() {
    int width, height;
    glfwGetWindowSize(window_, &width, &height);
    return static_cast<float>(width);
}



void GameContoller::onMouseClick(int x, int y) {
    // Convert the screen coordinates to game coordinates
    float gameX = convertScreenToGameX(x);
    float gameY = convertScreenToGameY(y);

    // Check if the mouse click is within one of the towers
    for (int i = 0; i < 3; i++) {
        Tower* tower = (Tower *) gameState->getTower(i);
        if (tower->contains(gameX, gameY)) {
            // Handle the mouse click on the tower
            handleTowerClick(tower);
            break;
        }
    }
}
float GameContoller::convertScreenToGameX(int x) {
    // Convert the screen x coordinate to a value between -1 and 1
    float normalizedX = (float)x / (float)WINDOW_WIDTH * 2.0f - 1.0f;

    // Convert the normalized x coordinate to a game coordinate
    float gameX = normalizedX * GAME_WIDTH / 2.0f;

    return gameX;
}

float GameContoller::convertScreenToGameY(int y) {
    int windowHeight = m_gameController->getWindowHeight();
    int gameHeight = gameState->getGameHeight();
    int  scaleY = gameHeight / windowHeight;
    return ((float)gameHeight / 2) - (y * scaleY);
}

float GameContoller::getWindowWidth() {
    return 0;
}



