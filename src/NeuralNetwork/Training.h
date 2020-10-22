#ifndef TRAINING
#define TRAINING
double sigmoid(double n);
void forwardPropagation(Network* net, double* data);
double meanSquareFunction(double* target, Layer layer);
double backPropagation(Network* net);
#endif
