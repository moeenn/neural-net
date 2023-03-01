#include "Connection.hpp"
#include "RandomGenerator.hpp"

Connection::Connection() {
  /* connection weight must be random */
  m_weight = RandomGenerator::rand();
  m_delta_weight = 0;
}