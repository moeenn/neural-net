#pragma once
#include <vector>
#include "Connection.hpp"

class Neuron {
private:
  double m_output_val;
  std::vector<Connection> m_output_weights;

public:
  Neuron(uint num_outputs);
};