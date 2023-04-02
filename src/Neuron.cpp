#include "Neuron.hpp"

/* initialize static data members */
double Neuron::m_eta = 0.15;
double Neuron::m_alpha = 0.5;

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

  m_output_val = Neuron::transfer_function(sum);
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
  // sum of derivatives of the next layer
  double dow = sum_dow(next_layer);
  m_gradient = dow * Neuron::transfer_function_derivative(m_output_val);

}

double Neuron::sum_dow(const Layer &next_layer) const {
  double sum = 0.0;

  // sum our contribution of errors at nodes we feed
  // excluding the bias neuron
  for (uint n = 0; n < next_layer.size() - 1; n++) {
    sum += (m_output_weights[n]).get_weight() * (next_layer[n]).m_gradient; 
  }

  return sum;
}

void Neuron::update_input_weights(Layer& prev_layer) {
  // weights to be updated are in the connection container in the neurons in the
  // previous layer
  for (uint n = 0; n < prev_layer.size(); n++) {
    Neuron &neuron = prev_layer[n];
    double old_delta_weight = (neuron.m_output_weights[m_own_index]).get_delta_weight();

    // eta -> individual input magnified by gradient and train rate 
    // eta = 0.0 slow learner, 0.2 medium learner, 1.0 reckless leaner
    // alpha -> momentum i.e. fraction of the previous delta weight
    // alpha = 0.0 no momentum, 0.5 moderate momentum

    double new_delta_weight = 
      (m_eta * neuron.get_output_val() * m_gradient)
      + (m_alpha * old_delta_weight);

    (neuron.m_output_weights[m_own_index]).set_delta_weight(new_delta_weight);
    (neuron.m_output_weights[m_own_index]).set_weight(
      (neuron.m_output_weights[m_own_index]).get_weight() + new_delta_weight
    );
  }
}