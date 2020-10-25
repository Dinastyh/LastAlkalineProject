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

    for(size_t i = 1; i < net->nbLayers; i++)
    {
	    Layer* layer = &(net->layers[i]);
	    for(size_t j = 0; j < layer->nbNeurons; j++)
	    {
	        updateNeuronValue(&(layer->neurons[j]), layer);
	        printf("layer %zu neuron %zu value %lf\n",i,j,layer->neurons[j].value);
	    }
    }
}

double meanSquareFunction(double* target, Layer* layer)
{
    double totalError;
    for(size_t i = 0; i < layer->nbNeurons; i++)
    {
        double value = layer->neurons[i].value;
        layer->neurons[i].error =  target[i] - value;
	    totalError += (target[i] - value);
    }
    return totalError;
}

//calculate delta
void backPropagation(Network* net)
{
    //Delta For outLayer
    size_t nbLayers = net->nbLayers;
    Layer *lastLayer = &(net->layers[net->nbLayers - 1]);

    for (size_t i = 0; i < lastLayer->nbNeurons; i++)
    {
        double value = lastLayer->neurons[i].value;
        double error = lastLayer->neurons[i].error;
        printf("neuron %zu error %lf\n", i, error);
        lastLayer->neurons[i].delta = value * (1 - value) * error;
        printf("last layer neuron %zu delta %lf\n", i, lastLayer->neurons[i].delta);
    }

    //Delta for other Layer
    //printf("nbLayers is %zu\n",nbLayers);
    for (size_t i = nbLayers - 2; i > 0; i--)
    {
        Layer *layer = &(net->layers[i]);
        for (size_t j = 0; j < layer->nbNeurons; j++)
        {
            double value = layer->neurons[j].value;
            double sum = 0;
            Layer *nextLayer = &(net->layers[i + 1]);
            for (size_t k = 0; k < nextLayer->nbNeurons; k++)
            {
                sum += nextLayer->neurons[k].weights[j + 1] * nextLayer->neurons[k].delta;
            }
            printf(" layer %zu neuron %zu sum %lf\n",i,j,sum);
            layer->neurons[j].delta = value * (1 - value) * sum;
            printf(" layer %zu neuron %zu delta %lf\n",i,j,layer->neurons[j].delta);
        }
        //printf("coucou\n");
    }
    //printf("coucou2\n");
}

//stochastic gradient descent
void gradientDescent(Network* net, double learningRate)
{
    size_t nbLayers = net->nbLayers;
    for(size_t i = 1; i < nbLayers; i++)
    {
        Layer* layer = &(net->layers[i]);
        Layer* lastLayer = &(net->layers[i-1]);
        for(size_t j = 0; j < layer->nbNeurons; j++)
        {
            for(size_t k = 0; k <= lastLayer->nbNeurons; k++)
            {
                double newInput;
                if(k == 0)
                    newInput = 1;
                else
                    newInput = lastLayer->neurons[k-1].value;
                layer->neurons[j].weights[k] += learningRate*layer->neurons[j].delta*newInput;
                layer->neurons[j].delta = 0;
            }
        }
    }
}    