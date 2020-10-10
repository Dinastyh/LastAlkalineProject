#include "Debug.h"

void print_brain(Brain* brain)
{
    Neuron* current_layer;
    // 4 layers : 784, 784, 784 and 66
    for (int i = 0; i < 4; i++)
    {
        int layer_length;
        int weight_count;
        switch (i)
        {
            case 0:
                current_layer = brain->layers[0];
                layer_length = 784;
                weight_count = 0;
                break;

            case 1:
                current_layer = brain->layers[1];
                weight_count = 784;
                //layer_length = 784;
                break;

            case 2:
                current_layer = brain->layers[2];
                //layer_length = 784;
                //weight_count = 784;
                break;

            case 3:
                current_layer = brain->last_layer;
                layer_length = 66;
                //weight_count = 784;
                break;

            default:
                printf("Debug/print_brain : switch case i is not recognized");
                exit(1);
        }
        printf("\n#### LAYER %d ### \n",i);
        for (int j = 0; j < layer_length; j++)
        {
            printf("(");
            printf("%lf",current_layer[j].bias);
            for(int k = 0; k < weight_count; k++)
            {
                Neuron neuron = current_layer[j];
                printf(" %lf", neuron.weights[k]);
            }

            printf(") ");
        }
        printf("\n");
    }
}
