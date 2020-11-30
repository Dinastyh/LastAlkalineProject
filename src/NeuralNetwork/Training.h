#ifndef TRAINING
#define TRAINING
#include "Network.h"

double sigmoid(double n);
void forwardPropagation(Network* net, double* data, double* target);
double meanSquareFunction(Layer* layer, double* target);
void backPropagation(Network* net);
void gradientDescent(Network* net, double learningRate, double lambda, size_t batchSize);
void training(Network* net, size_t nbEpoch, size_t batchSize, size_t nbElement);
#endif
