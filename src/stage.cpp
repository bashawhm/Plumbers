#include "stage.h"
#include "color.h"

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
    return UpdateNone;
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
}

void Stage::printWarning(string info) {
    mvprintw(warningY + VPAD, HPAD, "%s", info.c_str());
}

void Stage::printInfo(string info) {
    attron(A_BOLD | COLOR_PAIR(ColorToilet));
    mvprintw(0, 0, "%s", info.c_str());
    attroff(A_BOLD | COLOR_PAIR(ColorToilet));
}
