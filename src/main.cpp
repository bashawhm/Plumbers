#include<ncurses.h>
#include<unistd.h>
#include<stdlib.h>

#include"stage.h"
#include"input.h"
#include"color.h"

using namespace std;

void printStory() {
    mvprintw(VPAD, HPAD, "Richard Nixon is Director of Plumbers.");
    mvprintw(VPAD+1, HPAD, "Melania Trumps SOLID GOLD TOILET contains valuble intel.");
    mvprintw(VPAD+2, HPAD, "The toilet is in Trump Reactor 1.");
    mvprintw(VPAD+3, HPAD, "Nixon is ordering the Plumbers to air drop into the reactor.");
    mvprintw(VPAD+4, HPAD, "The Plumbers are going to fetch the toilet.");
    mvprintw(VPAD+5, HPAD, "Plumber is you.");
    mvprintw(VPAD+6, HPAD, "Now go and fight your way through endless squads of totally, definitely,");
    mvprintw(VPAD+7, HPAD, "probably souless hazmat suits with absolutely nothing in them.");
    mvprintw(VPAD+9, HPAD, "Press any key to enter the reactor...");

}

void printWin() {
    mvprintw(VPAD, HPAD, "Congradulations! You have successfully retrieved the GOLDEN TOILET.");
    mvprintw(VPAD+1, HPAD, "You bring the golden toilet back to director Nixon.");
    mvprintw(VPAD+2, HPAD, "The Nixon is pleased.");
    mvprintw(VPAD+3, HPAD, "He cracks open the solid gold toilet and takes out a makeup bag.");
    mvprintw(VPAD+4, HPAD, "You are confused.");
    mvprintw(VPAD+5, HPAD, "He pulls out a tube of lipstick.");
    mvprintw(VPAD+6, HPAD, "It's not his shade.");
    mvprintw(VPAD+7, HPAD, "He says to you:");
    mvprintw(VPAD+9, HPAD+2, "\"The coordinates to Trump Space One microscopically carved into this tube.\"");
    mvprintw(VPAD+10, HPAD+2, "\"You're next mission is to infultrait this space station, and rescue the other toilets...\"");
    mvprintw(VPAD+11, HPAD+2, "\"Now go and get the microfiche reader!\"");
    
}

int main() {
    initscr();
    noecho();
    curs_set(false);
    initColor();

    Stage stage;
    clear();
    stage.printInfo("The Golden Toilet 8!");
    printStory();
    refresh();

    while(1) {
        int input = getch();
        clear();
        string info = "Trump Reactor 1, Level " + to_string(stage.floorNum);
        stage.printInfo(info);
        switch (input) {
        case KeyEsc: {
            endwin();
            exit(1);
            break;             
        }
        case KeyN: {
            stage.floorNum++;
            stage.nextFloor();
            break;
        }
        case KeyW: {
            if (stage.cellEmpty(stage.player.x, stage.player.y-1)) {
                stage.player.moveBy(0, -1);
            }
            break;           
        }
        case KeyS: {
            if (stage.cellEmpty(stage.player.x, stage.player.y+1)) {
                stage.player.moveBy(0, 1);
            }
            break;           
        }
        case KeyA: {
            if (stage.cellEmpty(stage.player.x-1, stage.player.y)) {
                stage.player.moveBy(-1, 0);
            }
            break;           
        }
        case KeyD: {
            if (stage.cellEmpty(stage.player.x+1, stage.player.y)) {
                stage.player.moveBy(1, 0);
            }
            break;           
        }
        default:
            string warning = "Key: ";
            warning += to_string(input);
            stage.printWarning(warning);
        }

        int stat = stage.update();
        if (stat == UpdateWin) {
            break;
        }

        stage.printFloor();
        stage.printEntities();
        refresh();
        usleep(15);
    }
    clear();
    stage.printInfo("The Golden Toilet 8!");
    printWin();
    refresh();
    getch();

    endwin();
    return 0;
}
