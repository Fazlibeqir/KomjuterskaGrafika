#include <GLFW/glfw3.h>
#include "OpenGLPrj.hpp"
#include <iostream>
#include "glad/glad.h"

struct Disk{
    int size;
    float x,y;
    const float color;
};
struct Tower {
    int top;
    Disk disks[4];
};


int main(){

    return 0;
}
