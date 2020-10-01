#ifndef _Brain_H
#define _Brain_H
#include "Neuron.h"

struct Brain
{
    Neuron* layers;
};
typedef struct Brain Brain;

Brain* NewBrain();
double SigmoidSum(const Neuron* layer, Neuron neuron);
void NeuronUpdate(Neuron* neuron, double sigSum);
void init_random_brain(Brain* brain);
double* forward_propagation(Brain* brain, double* data);
#endif
