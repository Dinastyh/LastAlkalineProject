#ifndef _Debug_H
#define _Debug_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Network.h"
//#include "Brain.h"
//#include "Neuron.h"

void print_layer(Layer layer);
void printNetwork(Network* net);
void print_vector(int size, double* data);
//void check_forward_propagation(Brain* brain);
//void check_backpropagation(Brain* brain);

#endif
