#pragma once
#include <vector>
#include "Connection.hpp"
#include "Layer.hpp"
#include <cmath>

class Neuron {
private:
  double m_output_val;
  uint m_own_index;
  double m_gradient;
  std::vector<Connection> m_output_weights;
  static double transfer_function(double x);
  static double transfer_function_derivative(double x);

public:
  Neuron(uint num_outputs, uint own_index);
  double get_output_val() const;
  void set_output_val(double output_val);
  void feed_forward(const Layer &previous_layer);
  void calculate_output_gradients(double target_val);
  void calculate_hidden_gradients(const Layer& next_layer);
  void update_input_weights(const Layer& prev_layer);
};