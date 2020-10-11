#include "Debug.h"

void print_layer(Neuron* layer, int choice) //0 is first layer, NUMBER_HIDDEN_LAYERS + 1 is last, else is hidden
{
    switch (choice)
    {
        case 0:
            printf("\n#### LAYER 0 #### \n");
            for (int i = 0; i < SIZE_LAYERS; i++)
            {
                printf("(");
                printf("%lf",layer[i].bias);
                printf(") ");
            }
            printf("\n");
            break;

        case NUMBER_HIDDEN_LAYERS + 1:
            printf("\n#### LAST LAYER #### \n");
            for (int i = 0; i < SIZE_LAST_LAYER; i++)
            {
                printf("(");
                printf("%lf",layer[i].bias);
                for(int j = 0; j < SIZE_LAYERS; j++)
                {
                    Neuron neuron = layer[i];
                    printf(" %lf", neuron.weights[j]);
                }
                printf(") ");
            }
            printf("\n");
            break;
        default:
            printf("\n#### LAYER %d #### \n",choice);
            for (int i = 0; i < SIZE_LAYERS; i++)
            {
                printf("(");
                printf("%lf",layer[i].bias);
                for(int j = 0; j < SIZE_LAYERS; j++)
                {
                    Neuron neuron = layer[i];
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
    print_layer(brain->last_layer, NUMBER_HIDDEN_LAYERS + 1);
}

