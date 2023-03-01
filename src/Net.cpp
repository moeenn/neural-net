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
    uint num_outputs = layer_num == max_layers - 1 ? 0 : (next_layer.size() + 1);

    /* create neurons plus one bias neuron */
    for (uint neuron_num = 0; neuron_num < max_neurons + 1; neuron_num++) {
      layer.push_back(Neuron(num_outputs));
    }

    m_layers.push_back(layer);
  }
}

// void Net::feed_forward(const std::vector<double> &input_vals) {

// }

// void Net::back_propagate(const std::vector<double> &target_vals) {

// }

//  void Net::get_results(std::vector<double> &result_vals) const {

//  }