#include "Net.hpp"
#include "Neuron.hpp"

Net::Net(const std::vector<uint> &topology) {
  const uint max_layers = topology.size();
  for (uint layer_num = 0; layer_num < max_layers; layer_num++) {
    Layer layer{};
    uint max_neurons = topology[layer_num];

    Layer next_layer = m_layers[layer_num + 1];

    /**
     *  adjust for bias neuron in the next layer
     *  the last layer will have no output weights (it is the output layer)
     */
    uint num_outputs =
        layer_num == max_layers - 1 ? 0 : (next_layer.size() + 1);

    /* create neurons plus one bias neuron */
    for (uint neuron_num = 0; neuron_num < max_neurons + 1; neuron_num++) {
      layer.push_back(Neuron(num_outputs, neuron_num));
    }

    m_layers.push_back(layer);
  }
}

void Net::feed_forward(const std::vector<double> &input_vals) {
  /* adjust for bias neuron */
  assert(input_vals.size() == m_layers[0].size() - 1);

  /* assign input values to each neuron in input (i.e. first) layer */
  for (uint i = 0; i < input_vals.size(); i++) {
    m_layers[0][i].set_output_val(input_vals[i]);
  }

  /* perform forward propagation */
  for (uint layer_num = 1; layer_num < m_layers.size(); layer_num++) {
    Layer &previous_layer = m_layers[layer_num - 1];

    /* adjust for bias neuron */
    for (uint neuron_num = 0; neuron_num < m_layers[layer_num].size() - 1;
         neuron_num++) {
      (m_layers[layer_num][neuron_num]).feed_forward(previous_layer);
    }
  }
}

void Net::back_propagate(const std::vector<double> &target_vals) {
  /**
   *  calculate overall net error
   *  RMS - Root mean square error
   *  rms = ()^(1/2)
   */
  Layer &output_layer = m_layers.back();

  m_error = 0.0;
  for (uint n = 0; n < output_layer.size(); n++) {
    double delta = target_vals[n] - (output_layer[n]).get_output_val();
    m_error += delta * delta;
  }

  m_error /= output_layer.size() - 1;
  m_error = std::sqrt(m_error); /* RMS */

  /* implement recent average measure */
  m_recent_avg_error =
      (m_recent_avg_error * m_recent_avg_smoothing_factor + m_error) /
      (m_recent_avg_smoothing_factor + 1.0);

  /* calculate output layer gradients */
  for (uint n = 0; n < output_layer.size() - 1; n++) {
    (output_layer[n]).calculate_output_gradients(target_vals[n]);
  }

  /* calculate hidden layer gradients */
  for (uint layer_n = m_layers.size() - 2; layer_n > 0; layer_n--) {
    Layer &hidden_layer = m_layers[layer_n];
    Layer &next_layer = m_layers[layer_n + 1];

    for (uint n = 0; n < hidden_layer.size(); n++) {
      (hidden_layer[n]).calculate_hidden_gradients(next_layer);
    }
  }

  /**
   *  for all layer from output layer to the first hidden layer, update
   *  connection weights
   */
  // exclude input layer
  for (uint layer_n = m_layers.size() - 1; layer_n > 0; layer_n--) {
    Layer &layer = m_layers[layer_n];
    Layer &prev_layer = m_layers[layer_n - 1];

    for (uint n = 0; n < layer.size() - 1; n++) {
      (layer[n]).update_input_weights(prev_layer);
    }
  }
}

void Net::get_results(std::vector<double> &result_vals) const {
  result_vals.clear();

  for (uint n = 0; n < m_layers.back().size() - 1; n++) {
    double output_val = (m_layers.back()[n]).get_output_val(); 
    result_vals.push_back(output_val);
  }
}