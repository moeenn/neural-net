#include "Direction.hpp"
#include "Entity.hpp"
#include <iostream>

int main() {
  Entity e{30, 50};
  e.move(Direction::RIGHT);
  e.move(Direction::DOWN);

  e.display();
}
