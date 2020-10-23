#include "Training.h"

double sigmoid(double n)
{
    return 1/(1+exp(-v));
}

void updateNeuronValue(Neuron* neuron, Layer layer)
{
    double result = 0.0;
    for(int i = 0; i <= layer.nbNeurons; i++)
    {
        if (i == 0)
            result+= neuron->weights[i];
        else
            result += neuron->weights[i] * layer.neurons[i-1].value;
    }
    neuron->value = 1/(1+exp(-1*result));
}

void forwardPropagation(Network* net, double* data)
{
    for(size_t i = 0; i < net->layers[0].nbNeurons; i++)
    {
	net->layers[0].neurons[i] = data[i];
    }

    for(size_t i =1; i<net->nbLayers; i++)
    {
	Layer* layer = *(net->layers[i]);
	for(size_t j =0; j<layer->nbNeurons; i++)
	{
	    updateNeuronValue(&(layers->neurons[j]), layer);
	}
    }
}

double meanSquareFunction(double* target, Layer layer)
{
    double totalError;
    for(int i = 0; i <layer.nbNeurons; i++)
    {
	totalError += (target[i] - layer.neurons[i].value)*(target[i] - layer.neurons[i].value);
    }
    return totalError;

double backPropagation(Network* net)
{
}    
