#ifndef NETWORK
#define NETWORK
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Neuron
{
    size_t nbWeights;
    double value, dedout, doutdnet, dnetdw;
    double* weights;
    double* dw;
};
typedef struct Neuron Neuron;

struct Layer
{
    size_t nbNeurons;
    Neuron* neurons;
};
typedef struct Layer Layer;

struct Network
{
    size_t nbLayers;
    size_t sizeInput;
    size_t sizeOutput;
    size_t sizeHidden;
    Layer* layers;
};
typedef struct Network Network;
Network newNetwork(size_t sizeInput, size_t sizeHidden, size_t sizeOutput, size_t nbHiddenLayers);
Layer newLayer(size_t sizeLayer, size_t sizePreviousLayer);
Neuron newNeuron(size_t nbWeights);

void freeNetwork(Network* net);
void freeLayer(Layer* layer);

double boxMuller();

void initNeuron(Neuron* Neuron);
void initNetwork(Network* net);
#endif
