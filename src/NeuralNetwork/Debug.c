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