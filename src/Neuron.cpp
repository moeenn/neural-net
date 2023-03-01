#include "Neuron.hpp"

/* num_outputs is the number of layers in the next (to the right) layer */
Neuron::Neuron(uint num_outputs) {
  for (uint nconn = 0; nconn < num_outputs; nconn++) {
    Connection conn{};
    m_output_weights.push_back(conn);
  }
}