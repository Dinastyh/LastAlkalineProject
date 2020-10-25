#include "Network.h"

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
    net.layers[0] = newLayer(sizeInput, NULL, &(net.layers[1]));
    for(size_t i = 1; i < nbHiddenLayers+1; i++)
    {
        net.layers[i] = newLayer(sizeHidden, &(net.layers[i-1]), &(net.layers[i+1]));
    }
    net.layers[net.nbLayers-1] = newLayer(sizeOutput, &(net.layers[net.nbLayers-2]), NULL);
    return net;
}

Layer newLayer(size_t sizeLayer, Layer* previousLayer, Layer* nextLayer)
{
    Layer layer =
    {
	NULL,
	NULL,
	0,
	NULL	
    };
    layer.nbNeurons = sizeLayer;
    layer.neurons = calloc(sizeLayer, sizeof(struct Neuron));
    layer.nextLayer = nextLayer;
    layer.previousLayer = previousLayer;
    if(previousLayer)
    {
        for(size_t i = 0; i < sizeLayer; i++)
        {
            layer.neurons[i] = newNeuron(previousLayer->nbNeurons);
        }
    }
    else //previous layer undefined (NULL)
    {
        for(size_t i = 0; i < sizeLayer; i++)
        {
            layer.neurons[i] = newNeuron(0);
        }

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
	NULL
    };
    neuron.nbWeights = nbWeights + 1; // nbweights = size layer + bias
    neuron.value = 0;
    neuron.delta = 0;
    neuron.error = 0;
    neuron.weights = calloc(nbWeights, sizeof(double));
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
    for(size_t i =0; i < neuron->nbWeights; i++)
    {
	    neuron->weights[i] = boxMuller();
    }
}

void initNetwork(Network* net)
{
    for(size_t i = 0; i < net->nbLayers; i++)
    {
        Layer layer = net->layers[i];
        for(size_t j = 0; j < layer.nbNeurons; j++)
        {
            initNeuron(&(layer.neurons[j]));
        }
    }
}
