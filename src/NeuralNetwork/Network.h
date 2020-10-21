#ifndef NETWORK
#define NETWORK
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Neuron
{
    double nbWeights;
    double value, delta, error;
    double* weights;
};
typedef struct Neuron Neuron;

struct Layer
{
    struct Layer* previousLayer;
    struct Layer* nextLayer;
    size_t nbNeurons;
    Neuron* neurons;
};
typedef struct Layer Layer;

struct Network
{
    size_t nbLayers;
    Layer* layers;
};
typedef struct Network Network;
Network newNetwork(size_t sizeInput, size_t sizeHidden, size_t sizeOutput, size_t nbHiddenLayers);
Layer newLayer(size_t sizeLayer, Layer* previousLayer, Layer* nextLayer);
Neuron newNeuron(size_t nbWeights);
void freeNetwork(Network* net);
void freeLayer(Layer* layer);
double boxMuller();
void initNeuron(Neuron* Neuron);
void initNetwork(Network* net);
#endif
