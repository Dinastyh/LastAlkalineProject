#ifndef _Debug_H
#define _Debug_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Network.h"
#include <time.h>
#include "write_read_brain.h"
#include "Training.h"
//#include "Brain.h"
//#include "Neuron.h"

void print_layer(Layer layer);
void printNetwork(Network* net);
void print_vector(int size, double* data);
Network demoWriteRead(int sizeInput, int sizeOutput, int nbHidden, int sizeHidden);
void demoTraining(Network* net, double* input, double* desiredOutput);
//void check_forward_propagation(Brain* brain);
//void check_backpropagation(Brain* brain);

#endif
