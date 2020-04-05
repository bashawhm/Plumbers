#pragma once

#include <ncurses.h>

enum {
    ColorNormal = 0,
    ColorToilet,
    ColorPlayer,
    ColorEnemy,
    ColorStairs
};

static void initColor() {
    start_color();

    init_pair(ColorNormal, COLOR_WHITE, COLOR_BLACK);
    init_pair(ColorToilet, COLOR_YELLOW, COLOR_BLACK);
    init_pair(ColorPlayer, COLOR_CYAN, COLOR_BLACK);
    init_pair(ColorEnemy, COLOR_RED, COLOR_BLACK);
    init_pair(ColorStairs, COLOR_MAGENTA, COLOR_BLACK);
}
