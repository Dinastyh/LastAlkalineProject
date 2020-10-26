#include "Debug.h"

void print_layer(Layer layer)
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

void printNetwork(Network* net)
{
    for (size_t i = 0; i < net->nbLayers;i++)
    {
        printf("##### LAYER %zu #####",i);
        print_layer(net->layers[i]);
    }
}

void print_vector(int size, double* data)
{
    for(int i = 0; i< size; i++)
    {
	    printf("Data[%d] = %lf\n",i,data[i]);
    }
}

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
        forwardPropagation(net, input);
        double cost = meanSquareFunction(desiredOutput, &(net->layers[net->nbLayers-1]));
        printf("Total cost : %lf\n", cost);
        printf("Backpropagation start :\n");
        backPropagation(net);
        printf("### backpropagation end ###\n\n");

        gradientDescent(net,0.3);
    }
    printf("#### training end ####\n");
}




#if 0
void check_forward_propagation(Brain* brain)
{
    double data[2] ={rand()%2, rand()%2};
    double end_data[1] = {0.0};
    printf("Data In\n");
    print_vector(2,data);
    forward_propagation(brain, data, end_data);
    printf("Data Out\n");
    print_vector(1, end_data);
}
#endif
/*
void check_backpropagation(Brain* brain)
{
    
}
*/