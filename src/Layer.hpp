#pragma once
#include <vector>

/* prevent circular dependency by defining forward ref to Neuron class */
class Neuron;
typedef std::vector<Neuron> Layer;