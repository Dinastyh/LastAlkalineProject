#include <string.h>
#include "Training.h"
#include "Network.h"
#include "../PictureUtils/Bmp24.h"
#include "write_read_brain.h"

double sigmoid(double n)
{
    return 1/(1+exp(-n));
}

void updateNeuronValue(Neuron* neuron, Layer* layer) // one neuron and the previous layer
{
    double result = 0.0;
    for(size_t i = 0; i < neuron->nbWeights; i++)
    {
        if (i == 0)
            result += neuron->weights[i];
        else
            result += neuron->weights[i] * layer->neurons[i-1].value;
    }
    //printf("neuron net : %lf\n", result);
    neuron->value = sigmoid(result);
}

void forwardPropagation(Network* net, double* data, double* target)
{
    Layer* layer = &(net->layers[0]); //first layer

    for(size_t i = 0; i < layer->nbNeurons; i++)
    {
	    layer->neurons[i].value = data[i];
    }

    for(size_t i = 1; i < net->nbLayers; i++)
    {
	    layer = &(net->layers[i]);
	    for(size_t j = 0; j < layer->nbNeurons; j++)
	    {
            double sum = 0;
            for(size_t k = 0; k<= net->layers[i-1].nbNeurons; k++)
            {
                if (k == 0)
                    sum += layer->neurons[j].weights[k];
                else
                    sum += layer->neurons[j].weights[k] * net->layers[i-1].neurons[k-1].value;
            }
            layer->neurons[j].value = 1 / (1 + exp(-sum));
	        //printf("layer %zu neuron %zu value %lf\n",i,j,layer->neurons[j].value);
	    }
    }

    layer = &(net->layers[net->nbLayers-1]); // last layer

    for(size_t i = 0; i < layer->nbNeurons; i++) 
    {
        double value = layer->neurons[i].value;
        //printf("last layer neuron %zu value %lf\n",i,layer->neurons[i].value);
        layer->neurons[i].dedout = value - target[i];
        //printf("last layer neuron %zu target[i] %lf value %lf\n",i,target[i],layer->neurons[i].value);
    }
}

double meanSquareFunction(Layer* layer, double* target)
{
    double totalError;
    for(size_t i = 0; i < layer->nbNeurons; i++)
    {
        double value = layer->neurons[i].value;
        layer->neurons[i].dedout = 0.5 * (target[i] - value) * (target[i] - value);
	    totalError += (target[i] - value);
    }
    return totalError;
}

double logarithmicCostFunction(Layer* layer, double* target)
{
    double totalError;
    for(size_t i = 0; i < layer->nbNeurons; i++)
    {
        double value = layer->neurons[i].value;
        layer->neurons[i].dedout = value - target[i];
	    totalError += (target[i] - value);
    }
    return totalError;
}

//calculate deltas
void backPropagation(Network* net)
{
    //Deltas For output layer
    size_t nbLayers = net->nbLayers;
    Layer *lastLayer = &(net->layers[nbLayers - 1]);

    for (size_t i = 0; i < lastLayer->nbNeurons; i++)
    {
        Neuron* neuron = &lastLayer->neurons[i];
        neuron->doutdnet = neuron->value * (1 - neuron->value);

        for(size_t j = 0; j <= neuron->nbWeights; j++)
        {
            if(j == 0)
            {
                neuron->dw[j] = 1;
            }
            else
            {
                neuron->dw[j] = net->layers[nbLayers - 2].neurons[j - 1].value;
            }
        }
        //printf("last layer neuron %zu delta %lf\n", i, lastLayer->neurons[i].delta);
    }

    //Delta for other Layer
    //printf("nbLayers is %zu\n",nbLayers);
    for (size_t i = nbLayers - 2; i > 0; i--) //starting last hidden layer
    {
        Layer* layer = &(net->layers[i]);
        Layer* previousLayer = &(net->layers[i - 1]);
        Layer* nextLayer = &(net->layers[i + 1]);

        for (size_t j = 0; j < layer->nbNeurons; j++)
        {
            Neuron* neuron = &layer->neurons[j];
            neuron->doutdnet = neuron->value * (1 - neuron->value);

            neuron->dedout = 0;
            //find total error dedout for neuron aka sum of : dedout * doutdnet * weights[j]
            for (size_t k = 0; k < nextLayer->nbNeurons; k++)
            {
                Neuron nextneuron = nextLayer->neurons[k];
                neuron->dedout += nextneuron.dedout * nextneuron.doutdnet
                                * nextneuron.weights[j+1];
            }

            for(size_t k = 0; k < neuron->nbWeights; k++)
            {
                if(k == 0)
                {
                    neuron->dw[k] = 1;
                }
                else
                {
                    neuron->dw[k] = previousLayer->neurons[k - 1].value;
                }
            }
        }
    }
}

//stochastic gradient descent
void gradientDescent(Network* net, double learningRate, double lambda, size_t batchSize) // lambda is regularization param
{
    size_t nbLayers = net->nbLayers;
    for(size_t i = 1; i < nbLayers; i++)
    {
        Layer* layer = &(net->layers[i]);
        for(size_t j = 0; j < layer->nbNeurons; j++)
        {
            Neuron* neuron = &layer->neurons[j];
            for(size_t k = 0; k < neuron->nbWeights; k++)
            {
                neuron->weights[k] = (neuron->weights[k] - learningRate * neuron->dedout * neuron->doutdnet 
                                    * neuron->dw[k] - learningRate* lambda * neuron->weights[k])/batchSize;
            }
        }
    }
}

void training(Network* net, size_t nbEpoch, size_t batchSize, size_t nbElement, double learningRate)
{
    size_t nbOutput = net->sizeOutput;
    double *data = malloc(net->sizeInput * sizeof(double));

    for(size_t i = 0; i < nbEpoch; i++)
    {
        if(i % 5000 == 0)
            printf("Epoch %ld\n", i);
        if(i % 50000 == 0)
                writeNetwork(net);
        for(size_t j = 0; j < batchSize; j++)
        {
            //choose random data, forward prop and label
            //int rndint = rand() % nbElement;
            size_t iterator = i % nbElement;

            char filenameStart[100] = "datasetNoRotationNoOffset/";
            char id[10];
            sprintf(id, "%zu", iterator);
            strcat(filenameStart, id);
            strcat(filenameStart, ".bmp");
            //printf("filename %s\n", filenameStart);

            pictureToArray(data, filenameStart);

            double *target = calloc(nbOutput, sizeof(double));
            int label = iterator % nbOutput;
            target[label] = 1.0;

            forwardPropagation(net, data, target);
            backPropagation(net);
            free(target);
        }
        
        double regularizationParam = 1/100; // tried 1/1k
        gradientDescent(net, learningRate, regularizationParam, batchSize);
    }
    free(data);
}
