#include "ai.h"
#include "stage.h"

#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ncurses.h>

using namespace std;

State::State(int _g, int _enemyX, int _enemyY, State *_parent, Stage *_stage) {
    g = _g;
    enemyX = _enemyX;
    enemyY = _enemyY;
    parent = _parent;
    stage = _stage;
}

State::State(const State &s) {
    g = s.g;
    enemyX = s.enemyX;
    enemyY = s.enemyY;
    parent = s.parent;
    stage = s.stage;
}

bool State::atGoal() {
    if ((enemyX+1 == stage->player.x || enemyX-1 == stage->player.x) && (enemyY-1 == stage->player.y || enemyY+1 == stage->player.y)) {
        return true;
    }
    return false;
}

int State::h() const {
    return abs(stage->player.x - enemyX) + abs(stage->player.y - enemyY);    
}                            

vector<State> State::succ() {
    vector<State> states;

    if (stage->cellEmpty(enemyX-1, enemyY)) {
        State s(g+1, enemyX-1, enemyY, this, stage);
        states.push_back(s);
    }
    if (stage->cellEmpty(enemyX+1, enemyY)) {
        State s(g+1, enemyX+1, enemyY, this, stage);
        states.push_back(s);
    }
    if (stage->cellEmpty(enemyX, enemyY-1)) {
        State s(g+1, enemyX, enemyY-1, this, stage);
        states.push_back(s);
    }
    if (stage->cellEmpty(enemyX, enemyY+1)) {
        State s(g+1, enemyX, enemyY+1, this, stage);
        states.push_back(s);
    }
    return states;
}

Move reverseList(State s) {
    cerr << "------------------" << endl; 
    Move m;
    State *p = &s;
    while (p -> parent != NULL) {
        cerr << "p: " << p << endl;
        cerr << "p->parent: " << p->parent << endl;
/*        clear();
        string info = "p: " + to_string((long)p) + " g: " + to_string(p->g);
        s.stage -> printInfo(info);
        refresh();*/
        m.x = p -> enemyX;
        m.y = p -> enemyY;
        p = p -> parent;
    }
    m.x = p -> enemyX - m.x;
    m.y = p -> enemyY - m.y;
    return m;    
}

bool cmp(const State &s1, const State &s2) {
    return (s1.h() + s1.g) < (s2.h() + s2.g);
}

Move State::nextMove() {
    Move m;
    m.x = 0;
    m.y = 0;
    State s1(g+1, enemyX-1, enemyY, this, stage);
    State s2(g+1, enemyX+1, enemyY, this, stage);
    State s3(g+1, enemyX, enemyY-1, this, stage);
    State s4(g+1, enemyX, enemyY+1, this, stage);
    int min = 10000000;
    int i = 0;
    if (stage->cellEmpty(enemyX-1, enemyY)) {
        min = s1.h();
        i = 1;
    }
    if (min > s2.h() && stage->cellEmpty(enemyX+1, enemyY)) {
        min = s2.h();
        i = 2;
    }
    if (min > s3.h() && stage->cellEmpty(enemyX, enemyY-1)) {
        min = s3.h();
        i = 3;
    }
    if (min > s4.h() && stage->cellEmpty(enemyX, enemyY+1)) {
        min = s4.h();
        i = 4;
    }
    if (i == 1) {
        m.x = -1;
        m.y = 0;
    } else if (i == 2) {
        m.x = 1;
        m.y = 0;
    } else if (i == 3) {
        m.x = 0;
        m.y = -1;
    } else if (i == 4) {
        m.x = 0;
        m.y = 1;
    }
    return m;

    
        




/*    list<State> fringe;
    vector<State> result;
    fringe.push_back(*this);
    while (1) {
        if (fringe.size() == 0) {
            //Error
            Move m;
            m.x = 0;
            m.y = 0;
            return m;
        }

        State node = *(fringe.begin());
        cerr << "node.parent: " << node.parent << endl;
        fringe.pop_front();

        if (node.atGoal()) {
            return reverseList(node);
        }
        result.push_back(node);
        cerr << "&result[result.size()-1]: " << &result[result.size()-1] << endl;
        vector<State> kids = result[result.size()-1].succ();
        for (int i = 0; i < kids.size(); i++) {
            kids[i].parent = &(result[result.size()-1]);
            kids[i].history = node.history;
            kids[i].history.push_back(node);
            fringe.push_back(kids[i]);
        }
        fringe.sort(cmp);
    }
    */
}
