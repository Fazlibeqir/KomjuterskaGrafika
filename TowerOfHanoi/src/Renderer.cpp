#include "Renderer.h"

Renderer::Renderer(int width, int height, const char* title): m_shader("shaders/shader.vert","shaders/shader.frag"){
    //initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //create a window with specified parameters
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::draw(Tower* towers, int numTowers, int numDisks){
    //create the vertices for each tower and disk
    createTowerVertices(numTowers);
    createDiskVertices(numDisks);
    //then draw the towers and disks
    useShader();
    for(int i = 0; i < numTowers; i++){
        drawTower(&towers[i], i);
        for(int j = 0; j < towers[i].getNumDisks(); j++){
            drawDisk(towers[i].getDisks()[j], j);
        }
    }
    glfwSwapBuffers(m_window);
}

void Renderer::createTowerVertices(int numTowers){
    m_vertices.clear();
    m_indices.clear();
    float towerHeight = 0.2f;
    float towerWidth = 0.1f;
    float towerXStart = -0.5f;
    float towerYStart = -0.2f;
    float towerZStart = -0.5f;
    float towerXIncrement = 0.15f;
    float towerYIncrement = 0.3f;
    float towerZIncrement = 0.5f;
    for(int i = 0; i < numTowers; i++){
        //create the bottom face of the tower
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerYStart + i*towerYIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerYStart + i*towerYIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerYStart + i*towerYIncrement + towerHeight));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerYStart + i*towerYIncrement + towerHeight));
        //create the top face of the tower
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerZStart + i*towerZIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerZStart + i*towerZIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerZStart + i*towerZIncrement + towerHeight));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerZStart + i*towerZIncrement + towerHeight));
        //create the bottom left side of the tower
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerYStart + i*towerYIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerYStart + i*towerYIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerZStart + i*towerZIncrement));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerZStart + i*towerZIncrement));
        //create the bottom right side of the tower
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerYStart + i*towerYIncrement + towerHeight));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerYStart + i*towerYIncrement + towerHeight));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement + towerWidth, towerZStart + i*towerZIncrement + towerHeight));
        m_vertices.push_back(glm::vec2(towerXStart + i*towerXIncrement, towerZStart + i*towerZIncrement + towerHeight));
    }
    for(int i = 0; i < m_vertices.size(); i++){
        m_indices.push_back(i);
    }
}

void Renderer::createDiskVertices(int numDisks){
    //the bottom of the disks should be at y = 0.1f
    float diskXStart = -0.5f;
    float diskYStart = 0.1f;
    float diskZStart = -0.5f;
    float diskXIncrement = 0.15f;
    float diskYIncrement = 0.3f;
    float diskZIncrement = 0.5f;
    for(int i = 0; i < numDisks; i++){
        //create the bottom face of the disk
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskYStart + i*diskYIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskYStart + i*diskYIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskYStart + i*diskYIncrement + 0.02f));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskYStart + i*diskYIncrement + 0.02f));
        //create the top face of the disk
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskZStart + i*diskZIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskZStart + i*diskZIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskZStart + i*diskZIncrement + 0.02f));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskZStart + i*diskZIncrement + 0.02f));
        //create the bottom left side of the disk
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskYStart + i*diskYIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskYStart + i*diskYIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskZStart + i*diskZIncrement));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskZStart + i*diskZIncrement));
        //create the bottom right side of the disk
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskYStart + i*diskYIncrement + 0.02f));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskYStart + i*diskYIncrement + 0.02f));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement + 0.02f, diskZStart + i*diskZIncrement + 0.02f));
        m_vertices.push_back(glm::vec2(diskXStart + i*diskXIncrement, diskZStart + i*diskZIncrement + 0.02f));
    }
    for(int i = 0; i < m_vertices.size(); i++){
        m_indices.push_back(i);
    }
}

void Renderer::drawTower(Tower* tower, int towerIndex){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(tower->getXPosition(), 0.0f, tower->getZPosition()));
    m_shader.setMat4("model", model);
    glBindVertexArray(towerIndex);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::drawDisk(Disk* disk, int diskIndex){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(disk->getXPosition(), 0.0f, disk->getZPosition()));
    m_shader.setMat4("model", model);
    glBindVertexArray(diskIndex);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::useShader(){
    m_shader.use();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}