#include "Net.hpp"
#include <iostream>
#include <vector>

int main() {
  /* three layers total, with 3, 2 and 1 neurons respectively */
  std::vector<uint> topology{3, 2, 1};
  Net net{topology};

  std::vector<double> input_vals, target_vals, result_vals;

  /* training phase */
  net.feed_forward(input_vals);
  net.back_propagate(target_vals);

  /* deployment phase */
  net.get_results(result_vals);
}
