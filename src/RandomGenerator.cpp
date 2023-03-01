#include "RandomGenerator.hpp"
#include <cstdlib>

double RandomGenerator::rand() {
  return std::rand() / double(RAND_MAX);
}