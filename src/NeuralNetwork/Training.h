#ifndef TRAINING
#define TRAINING
#include "Network.h"

double sigmoid(double n);
void forwardPropagation(Network* net, double* data);
double meanSquareFunction(double* target, Layer* layer);
void backPropagation(Network* net);
void gradientDescent(Network* net, double learningRate);
#endif
