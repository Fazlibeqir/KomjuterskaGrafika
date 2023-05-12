//
// Created by Beqir on 12.5.2023.
//

#ifndef OPENGLPRJ_TOWER_H
#define OPENGLPRJ_TOWER_H
#include <vector>
#include "Disk.h"
class Tower {
public:
    Tower();
    Tower(int id);
    ~Tower();
    void addDisk(Disk* disk);
    Disk* removeTopDisk();
    Disk* getTopDisk()const;
    std::vector<Disk*>& getDisks();
    const std::vector<Disk*>& getDisks() const;
    int getNumDisks()const;
    float getXPosition()const;
    float getZPosition()const;

    void pushDisk(Disk *pDisk);

private:
    int m_id;
    float m_XPosition;
    float m_ZPosition;
    std::vector<Disk*> m_disks;
};


#endif //OPENGLPRJ_TOWER_H
