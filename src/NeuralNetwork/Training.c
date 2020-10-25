#include "Training.h"

double sigmoid(double n)
{
    return 1/(1+exp(-n));
}

void updateNeuronValue(Neuron* neuron, Layer* layer)
{
    double result = 0.0;
    for(size_t i = 0; i <= layer->nbNeurons; i++)
    {
        if (i == 0)
            result+= neuron->weights[i];
        else
            result += neuron->weights[i] * layer->neurons[i-1].value;
    }
    neuron->value = 1/(1+exp(-1*result));
}

void forwardPropagation(Network* net, double* data)
{
    for(size_t i = 0; i < net->layers[0].nbNeurons; i++)
    {
	    net->layers[0].neurons[i].value = data[i];
    }

    for(size_t i =1; i<net->nbLayers; i++)
    {
	    Layer* layer = &(net->layers[i]);
	    for(size_t j =0; j<layer->nbNeurons; i++)
	    {
	        updateNeuronValue(&(layer->neurons[j]), layer);
	    }
    }
}

double meanSquareFunction(double* target, Layer layer)
{
    double totalError;
    for(size_t i = 0; i <layer.nbNeurons; i++)
    {
	totalError += (target[i] - layer.neurons[i].value)*(target[i] - layer.neurons[i].value);
    }
    return totalError;
}
void backPropagation(Network* net)
{
    //Delta For outLayer
    size_t nbLayers = net->nbLayers;
    Layer* lastLayer =&(net->layers[net->nbLayers -1]);
    for(size_t i =0; i<lastLayer->nbNeurons; i++)
    {
        double value = lastLayer->neurons[i].value;
        double error = lastLayer->neurons[i].error;
        lastLayer->neurons[i].delta = value*(1-value)*error;
    }
    
    //Delta for other Layer
    for(size_t i = nbLayers-2; i >1; i--)
    {
        Layer* layer = &(net->layers[i]);
        for(size_t j = 0; j < layer->nbNeurons; j++)
        {
            double value = layer->neurons[j].value;
            double sum = 0;
            Layer* nextLayer = &(net->layers[i+1]);
            for(size_t k = 0; k < nextLayer->nbNeurons; i++)
            {
                sum += nextLayer->neurons[k].weights[j+1]*nextLayer->neurons[k].delta;
            }
            layer->neurons[j].delta = value*(1-value)*sum;
        }
    }
    for(size_t i = 2; i < nbLayers; i++)
    {
        Layer* layer = &(net->layers[i]);
        Layer* lastLayer = &(net->layers[i-1]);
        for(size_t j = 0; j < layer->nbNeurons; j++)
        {
            for(size_t k = 0; k<= lastLayer->nbNeurons; k++)
            {
                double newInput;
                if(k ==0)
                    newInput=1;
                else
                    newInput=lastLayer->neurons[k-1].value;
                layer->neurons[j].weights[k] += 1.1*layer->neurons[j].delta*newInput;
            }
        }
    }
}    
