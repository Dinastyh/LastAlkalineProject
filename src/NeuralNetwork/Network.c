#include "Network.h"
#include <time.h>

Network newNetwork(size_t sizeInput, size_t sizeHidden, size_t sizeOutput, size_t nbHiddenLayers)
{
    Network net =
    {
	0,
	0,
	0,
	0,
	NULL
    };
    
    net.nbLayers = nbHiddenLayers + 2; // hiddens + input + output
    net.sizeInput = sizeInput;
    net.sizeOutput = sizeOutput;
    net.sizeHidden = sizeHidden;

    net.layers = calloc(net.nbLayers, sizeof(struct Layer));

    net.layers[0] = newLayer(sizeInput, 0);

    for(size_t i = 1; i < nbHiddenLayers + 1; i++)
    {
        net.layers[i] = newLayer(sizeHidden, net.layers[i-1].nbNeurons);
    }

    net.layers[net.nbLayers - 1] = newLayer(sizeOutput, net.layers[net.nbLayers - 2].nbNeurons);

    return net;
}

Layer newLayer(size_t sizeLayer, size_t sizePreviousLayer)
{
    Layer layer =
    {
	0,
	NULL
    };

    layer.nbNeurons = sizeLayer;
    layer.neurons = calloc(sizeLayer, sizeof(struct Neuron));

    for(size_t i = 0; i < sizeLayer; i++)
    {
        layer.neurons[i] = newNeuron(sizePreviousLayer);
    }

    return layer;
}

Neuron newNeuron(size_t nbWeights)
{
    Neuron neuron =
    {
	0,
	0,
	0,
	0,
    0,
	NULL,
    NULL
    };

    if(nbWeights != 0)
        nbWeights++;

    neuron.nbWeights = nbWeights; // nbweights = size layer + bias
    neuron.value = 0;
    neuron.dedout = 0;
    neuron.doutdnet = 0;
    neuron.dnetdw = 0;

    neuron.weights = calloc(nbWeights, sizeof(double));
    neuron.dw = calloc(nbWeights, sizeof(double));
    
    return neuron;
}

void freeNetwork(Network* net)
{
    for(size_t i = 0; i< net->nbLayers; i++)
    {
	    freeLayer(&(net->layers[i]));
    }
    free(net);
}

void freeLayer(Layer* layer)
{
    for(size_t i= 0; i< layer->nbNeurons; i++)
    {
	    free(&(layer->neurons[i]));
    }
}

double boxMuller() //box-muller for gaussian distribution (polar method).
{
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;

    if (r == 0 || r > 1) 
	    return boxMuller();
    return u * sqrt(-2 * log(r) / r) / 3;
}

void initNeuron(Neuron* neuron)
{
    for(size_t i = 0; i < neuron->nbWeights; i++)
    {
	    neuron->weights[i] = ((double) rand() / (RAND_MAX)) * 4 - 2;
    }
}

void initNetwork(Network* net)
{
    srand ( time(NULL) );
    for(size_t i = 0; i < net->nbLayers; i++)
    {
        Layer* layer = &net->layers[i];
        for(size_t j = 0; j < layer->nbNeurons; j++)
        {
            initNeuron(&(layer->neurons[j]));
        }
    }
}
