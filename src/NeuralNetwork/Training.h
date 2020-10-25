#ifndef TRAINING
#define TRAINING
#include "Network.h"

double sigmoid(double n);
void forwardPropagation(Network* net, double* data);
double meanSquareFunction(double* target, Layer layer);
void backPropagation(Network* net);
#endif
