#pragma once
#include <iostream>
#include <vector>
#include "Layer.hpp"
#include <cassert>

class Net {
private:
  std::vector<Layer> m_layers;
  double m_error;
  double m_recent_avg_error;
  double m_recent_avg_smoothing_factor;

public:
  Net(const std::vector<uint> &topology);
  void feed_forward(const std::vector<double> &input_vals);
  void back_propagate(const std::vector<double> &target_vals);
  void get_results(std::vector<double> &result_vals) const;
};