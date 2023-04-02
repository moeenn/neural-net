#include <cstdlib>
#include <ctime>
#include <iostream>

#define LIMIT 2000

uint rand_int() {
  const double val = (std::rand() / double(RAND_MAX));
  return val < 0.5 ? 0 : 1;
}

/**
 *  Exclusive OR (XOR) training data
 *  1, 1 = 0
 *  1, 0 = 1
 *  0, 1 = 1
 *  0, 0 = 0
 */
int main() {
  std::srand(time(NULL));

  std::cout << "topology: 2 4 1\n";
  for (uint i = 0; i < LIMIT; i++) {
    uint a = rand_int();
    uint b = rand_int();

    uint ex_or = a ^ b;

    std::cout << "in: " << a << " " << b << "\n"
              << "out: " << ex_or << "\n";
  }
}
