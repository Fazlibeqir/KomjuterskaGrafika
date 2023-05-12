//
// Created by Beqir on 12.5.2023.
//

#include "GameState.h"
#include <vector>
GameState::GameState(int numDisks, int numTowers) : numDisks_(numDisks),numTowers_(numTowers){
    for (int i = 0; i < numTowers_; i++) {
        towers_.emplace_back();
    }
    for (int i = 0; i < numDisks_; i++) {
        disks_.emplace_back(i+1);
    }
    for (int i = numDisks_-1; i >= 0 ; i--) {
        towers_[0].addDisk(&disks_[i]);
    }
}

int GameState::getNumDisks() const {
    return numDisks_;
}
int GameState::getNumTowers() const {
    return numTowers_;
}
const Tower& GameState::getTower(int index) const {
    return towers_[index];
}
bool GameState::moveDisk(int sourceTower, int destTower) {
    if (towers_[sourceTower].getNumDisks()==0){
        return false;
    }
    Disk disk = *towers_[sourceTower].getTopDisk();

    // Make sure the destination tower is valid
    if (destTower < 0 || destTower >= numTowers_ || destTower == sourceTower) {
        return false;
    }

    // Make sure the move is legal (smaller disks can't be placed on top of larger disks)
    if (towers_[destTower].getNumDisks() > 0 && towers_[destTower].getTopDisk()->getSize() < disk.getSize()) {
        return false;
    }

    // Move the disk
    towers_[sourceTower].removeTopDisk();
    towers_[destTower].addDisk(&disk);

    return true;
}

void GameState::initialize() {
    // Initialize the positions of the disks on the towers
    for (int i = numDisks_; i > 0; i--) {
        this->towers_[0].pushDisk(new Disk(i));
    }

    // Set the current tower and selected disk to null
    current_tower = -1;
    selected_disk = nullptr;

    // Initialize any other necessary variables
    moves = 0;
    completed = false;
}

bool GameState::isGameOver() {
    // Check if all disks are on the final tower in the correct order
    if (towers_[2].getNumDisks() == numDisks_) {
        for (int i = numDisks_; i > 0; i--) {
            Disk* disk = towers_[2].getTopDisk();
            if (disk->getSize() != i) {
                return false;
            }
            towers_[2].removeTopDisk(disk);
        }
        return true;
    }
    return false;
}


void GameState::update() {
    // Handle moving the selected disk to a new tower

    if (selected_disk != nullptr && current_tower != -1 && reinterpret_cast<Tower *>(current_tower) != selected_tower) {
        Tower& from_tower = towers_[current_tower];
        Tower& to_tower = towers_[selected_tower];

        // Check if the move is valid
        if (to_tower.getNumDisks() == 0 || selected_disk->getSize() < to_tower.getTopDisk()->getSize()) {
            // Move the disk to the new tower
            from_tower.removeTopDisk(); // remove the selected disk from the current tower
            to_tower.addDisk(selected_disk); // add the selected disk to the new tower
            selected_disk = nullptr; // deselect the disk
            current_tower = -1; // deselect the tower
            moves++; // increment the number of moves
        }
    }

    // Check if the game is over
    if (isGameOver()) {
        completed = true;
    }
}

int GameState::getGameHeight() const {
    return windowHeight_;
}


