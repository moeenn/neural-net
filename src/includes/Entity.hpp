#pragma once
#include <iostream>
#include "Direction.hpp"

class Entity {
private:
  uint m_x, m_y; 

public:
  Entity(uint x, uint y);
  void move(Direction d);
  void display() const;
};