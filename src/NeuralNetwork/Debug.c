#include "Debug.h"
#include "Brain.h"
#include <stdlib.h>
#include <stdio.h>

void print_layer(Neuron* layer, int choice) //0 is first layer, NUMBER_HIDDEN_LAYERS + 1 is last, else is hidden
{
    Neuron neuron;
    switch (choice)
    {
        case 0:
            printf("\n#### LAYER 0, SIZE : %d #### \n", SIZE_LAYERS);
            for (int i = 0; i < SIZE_LAYERS; i++)
            {
                printf("() ");
            }
            printf("\n");
            break;

        case NUMBER_HIDDEN_LAYERS:
            printf("\n#### LAST LAYER, SIZE : %d #### \n", SIZE_LAST_LAYER);
            for (int i = 0; i < SIZE_LAST_LAYER; i++)
            {
                neuron = layer[i];
                printf("(");
                for(int j = 0; j < SIZE_LAYERS; j++)
                {
                    printf(" %lf", neuron.weights[j]);
                }
                printf(") ");
            }
            printf("\n");
            break;
        default:
            printf("\n#### LAYER %d, SIZE : %d #### \n",choice,SIZE_LAYERS);
            for (int i = 0; i < SIZE_LAYERS; i++)
            {
                neuron = layer[i];
                printf("(");
                for(int j = 0; j < SIZE_LAYERS; j++)
                {
                    printf(" %lf", neuron.weights[j]);
                }
                printf(") ");
            }
            printf("\n");
            break;
    }
}

void print_brain(Brain* brain)
{
    for (int i = 0; i < NUMBER_HIDDEN_LAYERS;i++)
    {
        print_layer(brain->layers[i], i);
    }
    print_layer(brain->last_layer, NUMBER_HIDDEN_LAYERS);
}

void print_vector(int size, double* data)
{
    for(int i = 0; i< size; i++)
    {
	    printf("Data[%d] = %lf\n",i,data[i]);
    }
}

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

/*
void check_backpropagation(Brain* brain)
{
    
}
*/