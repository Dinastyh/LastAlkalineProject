#ifndef _Brain_H
#define _Brain_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Neuron.h"

#define NUMBER_HIDDEN_LAYERS 1 + 1 //3 //layer 0 is counter as a hidden layer, must have at least one hidden layer (2 min)
#define SIZE_LAYERS 2 //784
#define SIZE_LAST_LAYER 1 //66


struct Brain
{
    Neuron** layers;
    Neuron* last_layer;
};
typedef struct Brain Brain;

Brain NewBrain();
void init_random_brain(Brain* brain);

void update_neuron_value(Neuron* neuron, Neuron* layer);
void forward_propagation(Brain* brain, double* data, double* end_data);

double mean_square_function(double* label, double* end_data);
double Sigmoid_prime(double value);
void calculate_gradient(Brain* brain, double* target);
void update_weights(Brain* brain, double learning_rate, double batch_size);
#endif
