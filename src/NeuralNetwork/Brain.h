#ifndef _Brain_H
#define _Brain_H
#include "Neuron.h"
#define SIZE_LAYERS 784
#define SIZE_LAST_LAYER 66
#define NUMBER_HIDDEN_LAYERS 3

struct Brain
{
    Neuron** layers;
    Neuron* last_layer;
};
typedef struct Brain Brain;

Brain* NewBrain();
double SigmoidSum(const Neuron* layer, Neuron neuron);
double Sigmoid_prime(double value);
void NeuronUpdate(Neuron* neuron, double sigSum);
void init_random_brain(Brain* brain);
void forward_propagation(Brain* brain, double* data, double* end_data);
double mean_square_function(double* label, double* end_data);
void calculate_gradient(Brain* brain, double* target);
void update_weights(Brain* brain, double learning_rate, double batch_size);
#endif
