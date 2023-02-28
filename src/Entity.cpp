#include "Entity.hpp"

Entity::Entity(uint x, uint y) : m_x(x), m_y(y) {}

void Entity::move(Direction d) {
  switch (d) {
    case Direction::UP:
      m_y += 1;
      break;

    case Direction::DOWN:
      m_y -= 1;
      break;

    case Direction::LEFT:
      m_x -= 1;
      break;

    case Direction::RIGHT:
      m_x += 1;
      break;
  }
}

void Entity::display() const {
  std::cout << "Entity(x=" << m_x << ", y=" << m_y << ")\n"; 
}