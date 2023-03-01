#pragma once
#include <iostream>
#include <vector>
#include "Layer.hpp"

class Net {
private:
  std::vector<Layer> m_layers;

public:
  Net(const std::vector<uint> &topology);
  void feed_forward(const std::vector<double> &input_vals);
  void back_propagate(const std::vector<double> &target_vals);
  void get_results(std::vector<double> &result_vals) const;
};