//
// Created by Beqir on 12.5.2023.
//

#ifndef OPENGLPRJ_DISK_H
#define OPENGLPRJ_DISK_H

#include "Tower.h"

class Disk {
public:
    Disk(int size, Tower* tower);

    Disk(int i);

    int getSize()const;
    Tower*getTower()const;
    void setTower(Tower* tower);
    float getXPosition() const;
    float getZPosition() const;
private:
    int m_size;
    Tower* m_tower;
};


#endif //OPENGLPRJ_DISK_H
