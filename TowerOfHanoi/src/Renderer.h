//
// Created by Beqir on 12.5.2023.
//

#ifndef OPENGLPRJ_RENDERER_H
#define OPENGLPRJ_RENDERER_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "OpenGLPrj.hpp"
#include <vector>
#include "Shader.hpp"
#include "Tower.h"
#include "Disk.h"

class Renderer {
public:
    Renderer(int width,int height,const char* title);
    void draw(Tower* towers, int numTowers,int numDisks);
private:
    GLFWwindow* m_window;
    Shader m_shader;
    std::vector<glm::vec2> m_vertices;
    std::vector<unsigned int> m_indices;

    void createTowerVertices(int numTowers);
    void createDiskVertices(int numDisks);
    void drawTower(Tower* tower,int towerIndex);
    void drawDisk(Disk* disk,int diskIndex);
    void useShader();
};


#endif //OPENGLPRJ_RENDERER_H
