#ifndef _Brain_H
#define _Brain_H
#include "Neuron.h"

struct Brain
{
    Neuron** layers;
    Neuron* last_layer;
};
typedef struct Brain Brain;

Brain* NewBrain();
double SigmoidSum(const Neuron* layer, Neuron neuron);
void NeuronUpdate(Neuron* neuron, double sigSum);
void init_random_brain(Brain* brain);
void forward_propagation(Brain* brain, double* data, double* end_data);
void mean_square_function(double* label, double* end_data, double* del_out);
#endif
