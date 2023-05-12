//
// Created by Beqir on 12.5.2023.
//

#include "Disk.h"

Disk::Disk(int size, Tower *tower) :m_size(size),m_tower(tower){}
int Disk::getSize() const {
    return m_size;
}
Tower* Disk::getTower() const {
    return m_tower;
}
void Disk::setTower(Tower *tower) {
    m_tower=tower;
}
float Disk::getXPosition() const {
    return m_tower->getXPosition();
}
float Disk::getZPosition() const {
    return m_tower->getZPosition();
}

Disk::Disk(int i):m_size(i) {}
