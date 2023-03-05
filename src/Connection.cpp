#include "Connection.hpp"
#include "RandomGenerator.hpp"

Connection::Connection() {
  /* connection weight must be random */
  m_weight = RandomGenerator::rand();
  m_delta_weight = 0;
}

double Connection::get_weight() const { return m_weight; }
void Connection::set_delta_weight(double delta) { m_delta_weight = delta; }

double Connection::get_delta_weight() const { return m_delta_weight; }
void Connection::set_weight(double weight) { m_weight = weight; }