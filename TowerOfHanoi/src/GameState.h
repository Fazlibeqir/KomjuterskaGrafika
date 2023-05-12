//
// Created by Beqir on 12.5.2023.
//

#ifndef OPENGLPRJ_GAMESTATE_H
#define OPENGLPRJ_GAMESTATE_H
#include <vector>
#include "Tower.h"
#include "Disk.h"

class GameState {
public:
    GameState(int numDisks, int numTowers);
    int getNumDisks() const;
    int getNumTowers() const;
    const Tower& getTower(int index) const;
    bool moveDisk(int sourceTower,int destTower);

    void initialize();

    bool isGameOver();
    void update();

    int getGameHeight() const;

private:
    int numDisks_;
    int numTowers_;
    int windowHeight_;
    int current_tower{};
    Disk* selected_disk{};
    Tower* selected_tower;
    int moves{};
    bool completed{};
    std::vector<Tower> towers_;
    std::vector<Disk> disks_;



};


#endif //OPENGLPRJ_GAMESTATE_H
