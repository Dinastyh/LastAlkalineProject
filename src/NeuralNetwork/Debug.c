#include "Debug.h"
#include "write_read_brain.h"
#include "Training.h"

void printLayerWeigths(Layer layer)
{
    size_t nbNeurons = layer.nbNeurons;
    size_t nbWeights = layer.neurons[0].nbWeights;
    for(size_t i = 0; i < nbNeurons; i++)
    {
        printf("(");
        for(size_t j = 0; j < nbWeights; j++)
        {
            printf("%lf ",layer.neurons[i].weights[j]);
        }
        printf(") ");
    }
    printf("\n");
}

void printLayerValues(Layer layer)
{
    for(size_t i = 0; i < layer.nbNeurons; i++)
    {
        printf("neuron %zu value : %lf ",i,layer.neurons[i].value);
    }
    printf("\n");
}

void printLayerDerivatives(Layer layer)
{
    size_t nbWheights = layer.neurons[0].nbWeights;

    for(size_t i = 0; i < layer.nbNeurons; i++)
    {
        Neuron neuron = layer.neurons[i];
        printf("neuron %zu ",i);
        printf("dedout : %lf, ",neuron.dedout);
        printf("doutdnet : %lf\n",neuron.doutdnet);

        printf("delta weights : \n");
        for(size_t i = 0; i < nbWheights; i++)
        {
            printf("%lf ",neuron.dw[i]);
        }
        printf("\n");
    }
    printf("\n");
}

void printNetwork(Network* net)
{
    for (size_t i = 0; i < net->nbLayers;i++)
    {
        printf("##### LAYER %zu #####",i);
        printLayerWeigths(net->layers[i]);
    }
    printf("\n");
}

void print_vector(int size, double* data)
{
    for(int i = 0; i< size; i++)
    {
	    printf("Data[%d] = %lf\n",i,data[i]);
    }
}

void checkForwardPropagation(Network* net, double* input, double* target)
{
    printf("Data In\n");
    print_vector(net->sizeInput, input);
    printf("Target\n");
    print_vector(net->sizeOutput, target);
    forwardPropagation(net, input, target);

    //printLayerValues(net->layers[net->nbLayers-1]);
}

#if 0
Network demoWriteRead(int sizeInput, int sizeOutput, int nbHidden, int sizeHidden)
{
    srand (time ( NULL));
    Network net = newNetwork(sizeInput,sizeHidden,sizeOutput,nbHidden);
    initNetwork(&net);
    printNetwork(&net);

    writeNetwork(&net);

    Network net2 = readNetwork("network.txt");
    printNetwork(&net2);

    return net2;
}

void demoTraining(Network* net, double* input, double* desiredOutput)
{
    int nb_trainings = 500;
    for (int i = 0; i < nb_trainings; i++) // one training
    {
        printf("Forward prop start :\n");
        forwardPropagation(net, input, desiredOutput);
        double cost = meanSquareFunction(desiredOutput, &(net->layers[net->nbLayers-1]));
        printf("Total cost : %lf\n", cost);
        printf("Backpropagation start :\n");
        backPropagation(net);
        printf("### backpropagation end ###\n\n");

        gradientDescent(net,0.3);
    }
    printf("#### training end ####\n");
}

#endif




