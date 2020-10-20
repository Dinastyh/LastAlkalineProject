#ifndef _NEURON_H
#define _NEURON_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Neuron
{
    double value, gradient, error;
    double* weights;
};
typedef struct Neuron Neuron;

Neuron NewNeuron(int nb_weights);
double box_muller();
void init_random_neuron(Neuron* neuron);

#endif
