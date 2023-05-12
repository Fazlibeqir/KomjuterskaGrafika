//
// Created by Beqir on 12.5.2023.
//

#include <stdexcept>
#include "Tower.h"

Tower::Tower() {};
Tower::Tower(int id) :m_id(id){}
void Tower::addDisk(Disk* disk) {
    m_disks.push_back(disk);
}
float Tower::getXPosition() const {
    return m_XPosition;
}
float Tower::getZPosition() const {
    return m_ZPosition;
}
Disk* Tower::removeTopDisk() {
    if (m_disks.empty()){
        return nullptr;
    }
    Disk* topDisk=m_disks.back();
    m_disks.pop_back();
    return topDisk;
}
Disk* Tower::getTopDisk() const {
    if (m_disks.empty()) {
        return nullptr;
    }

    return m_disks.back();
}
int Tower::getNumDisks() const {
    return m_disks.size();
}
std::vector<Disk*>& Tower::getDisks() {
    return m_disks;
}

const std::vector<Disk*>& Tower::getDisks() const {
    return m_disks;
}

void Tower::pushDisk(Disk *pDisk) {
    if (!m_disks.empty() && pDisk->getSize() > m_disks.back()->getSize()) {
        // Trying to place a larger disk on top of a smaller disk is not allowed
        throw std::invalid_argument("Invalid move: Cannot place a larger disk on top of a smaller disk.");
    }
    m_disks.push_back(pDisk);
}

