#pragma once
#include "stage.h"

#include <vector>

//Prepare fpr the quickest A* implimentation you'll ever see
//Beware...

class Move {
public:
    int x;
    int y;
};

class State {
public:
    State(int _g, int _enemyX, int _enemyY, State *_parent, Stage *stage);
    State(const State &s);

    bool atGoal();
    int h() const;
    std::vector<State> succ();
    Move nextMove();


    int enemyX;
    int enemyY;
    Stage *stage;

    int g;
    State *parent;
    std::vector<State> history;
};
