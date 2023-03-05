#include "Neuron.hpp"

/* num_outputs is the number of layers in the next (to the right) layer */
Neuron::Neuron(uint num_outputs, uint own_index) {
  for (uint nconn = 0; nconn < num_outputs; nconn++) {
    Connection conn{};
    m_output_weights.push_back(conn);
  }

  m_own_index = own_index;
}

double Neuron::get_output_val() const { return m_output_val; }

void Neuron::set_output_val(double output_val) { m_output_val = output_val; }

void Neuron::feed_forward(const Layer &previous_layer) {
  double sum = 0.0;

  /**
   *  sum all the output_values of all neurons in the previous layer including
   *  the bias neuron
   */
  for (uint neuron_num = 0; neuron_num < previous_layer.size(); neuron_num++) {
    sum +=
        previous_layer[neuron_num].m_output_val *
        previous_layer[neuron_num].m_output_weights[m_own_index].get_weight();
  }

  m_output_val = Neuron::transfer_function();
}

double Neuron::transfer_function(double x) {
  /**
   *  hyperbolic tangent function
   *  tanh (x) = (e^x - e^-x) / (e^x + e^-x)
   *
   *  tanh range -> [-1.0..1.0]
   */
  return std::tanh(x);
}

double Neuron::transfer_function_derivative(double x) {
  /**
   *  actual formulae
   *  d/dx tanh (x) = 1 - tanh^2 (x)
   *
   *  here we will use the shortcut formuale for quick approximation
   */
  return 1.0 - (x * x);
}

void Neuron::calculate_output_gradients(double target_val) {
  double delta = target_val - m_output_val;
  m_gradient = delta * Neuron::transfer_function_derivative(m_output_val);
}

void Neuron::calculate_hidden_gradients(const Layer& next_layer) {
  
}

void Neuron::update_input_weights(const Layer& prev_layer) {

}