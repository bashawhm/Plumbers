#include "stage.h"
#include "color.h"
#include "ai.h"

#include <ncurses.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

Stage::Stage() {
    srand(time(NULL));
    getmaxyx(stdscr, maxY, maxX);
    floorNum = 1;
    warningY = 0;
    nextFloor();
}

int Stage::update() {
    getmaxyx(stdscr, maxY, maxX);
    warningY = floor.size() + VPAD;
    if (floorNum == MAX_DEPTH && player.x == toilet.x && player.y == toilet.y) {
        return UpdateWin;
    }

    for (int i = 0; i < enemies.size(); i++) {
        State s(0, enemies[i].x, enemies[i].y, NULL, this);
        Move m = s.nextMove();
        enemies[i].moveBy(m.x, m.y);
    }

    return UpdateNone;
}

void Stage::initFloorEnemies() {
    int width = 10 * floorNum;
    for (int i = 0; i < floorNum; i++) {
        Entity e;
        e.x = 1 + rand() % (width-2);
        e.y = 1 + rand() % (width-2);
        enemies.push_back(e);
    }
}

void Stage::nextFloor() {
    floor.clear();
    int width = 10 * floorNum;
    for (int i = 0; i < width; i++) {
        vector<char> line; 
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == width-1 || j == width-1) {
                line.push_back('#');
            } else {
                line.push_back('.');
            }
        }
        floor.push_back(line);
    }
    player.x = 1 + rand() % (width-2);
    player.y = 1 + rand() % (width-2);

    initFloorEnemies();

    if (floorNum == MAX_DEPTH) {
        toilet.x = 1 + rand() % (width-2);
        toilet.y = 1 + rand() % (width-2);
    }
}

void Stage::printFloor() {
    for (int i = 0; i < floor.size(); i++) {
        for (int j = 0; j < floor[i].size(); j++) {
            mvprintw(j + VPAD, i + HPAD, "%c", floor[i][j]);
        }
    }
}

void Stage::printEntities() {
    //Print Player
    attron(A_BOLD | COLOR_PAIR(ColorPlayer));
    mvprintw(player.y + VPAD, player.x + HPAD, "@");
    attroff(A_BOLD | COLOR_PAIR(ColorPlayer));

    //Print Toilet
    if (floorNum == MAX_DEPTH) {
        attron(A_BOLD | COLOR_PAIR(ColorToilet));
        mvprintw(toilet.y + VPAD, toilet.x + HPAD, "T");
        attroff(A_BOLD | COLOR_PAIR(ColorToilet));
    }

    //Print Totally, definitely, probably, Souless Hazmat Suits with
    //absolutely nothing in them
    for (int i = 0; i < enemies.size(); i++) {
        attron(A_BOLD | COLOR_PAIR(ColorEnemy));
        mvprintw(enemies[i].y + VPAD, enemies[i].x + HPAD, "H");
        attroff(A_BOLD | COLOR_PAIR(ColorEnemy));
    }
}

void Stage::printWarning(string info) {
    mvprintw(warningY + VPAD, HPAD, "%s", info.c_str());
}

void Stage::printInfo(string info) {
    attron(A_BOLD | COLOR_PAIR(ColorToilet));
    mvprintw(0, 0, "%s", info.c_str());
    attroff(A_BOLD | COLOR_PAIR(ColorToilet));
}

bool Stage::cellEmpty(int x, int y) {
    if (floor[x][y] != '.') {
        return false;
    }

    if (player.x == x && player.y == y) {
        return false;
    }
    
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].x == x && enemies[i].y == y) {
            return false;
        }
    }

    return true;
}
