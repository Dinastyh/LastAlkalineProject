#ifndef _Debug_H
#define _Debug_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Network.h"
#include <time.h>

//#include "Brain.h"
//#include "Neuron.h"

void printLayerWeigths(Layer layer);
void printLayerValues(Layer layer);
void printLayerDerivatives(Layer layer);

void printNetwork(Network* net);
void print_vector(int size, double* data);
Network demoWriteRead(int sizeInput, int sizeOutput, int nbHidden, int sizeHidden);
void demoTraining(Network* net, double* input, double* desiredOutput);
void checkForwardPropagation(Network* net, double* input, double* target); //given input, print output
void TestNetwork(Network* net, size_t nbElement);
//void check_backpropagation(Brain* brain);

#endif
