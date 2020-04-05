#pragma once
#include <vector>
#include <string>

#include "entity.h"

#define VPAD 2
#define HPAD 2

#define MAX_DEPTH 3

enum {
    UpdateNone = 0,
    UpdateWin,
    UpdateStairs,
    UpdateDeath
};

class Stage {
public:
    Stage();

    int update();
    void nextFloor();
    void initFloorEnemies();
    void printFloor();
    void printEntities();
    void printWarning(std::string info);
    void printInfo(std::string info);
    bool cellEmpty(int x, int y);

    int maxX;
    int maxY;
    std::vector<std::vector<char>> floor;
    int floorNum;
    
    int warningY;

    Entity player;
    Entity toilet;
    Entity stairs;
    std::vector<Entity> enemies;
};
