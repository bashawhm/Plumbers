#include "entity.h"

Entity::Entity() {
    int x = 0;
    int y = 0;
}

void Entity::moveBy(int _x, int _y) {
    x += _x;
    y += _y;
}
