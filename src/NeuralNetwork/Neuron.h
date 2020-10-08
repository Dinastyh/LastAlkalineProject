#ifndef _NEURON_H
#define _NEURON_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Neuron
{
    double bias, value, gradient;
    double* weights;
};
typedef struct Neuron Neuron;

Neuron NewNeuron(double bias);
void init_random_neuron(Neuron* neuron);

#endif
