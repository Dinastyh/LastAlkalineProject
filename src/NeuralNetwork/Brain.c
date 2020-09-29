#include <stdio.h>
#include <math.h>
#include "Brain.h"
#include "Neuron.h"

Brain* NewBrain()
{
    Brain* brain = malloc(sizeof(Brain));
    brain->layer0 = calloc(784,sizeof(Neuron*));
    brain->layer1 = calloc(784,sizeof(Neuron*));
    brain->layer2 = calloc(784,sizeof(Neuron*));
    brain->layer3 = calloc(66,sizeof(Neuron*));
    return brain;
}

double SigmoidSum(const Neuron* layer)
{
    double result = 0;
    for(int i = 0; i < 784; i++)
    {
	    result += layer[i].weight;
    }
    return result;
}

void NeuronUpdate(Neuron* neuron, double sigSum)
{
    neuron->value = 1/(1+exp(-1*(sigSum - neuron->bias);
}

void init_random_brain(Brain brain)// pointer or not ?
{
    // 4 layers : 784, 784, 784 and 66
    for (int i = 0; i < 4; i++)
    {
        int layer_length;
        switch (i)
        {
            case 0:
                current_layer[] = brain->layer0;
                layer_length = 784;
                break;

            case 1:
                current_layer[] = brain->layer1;
                //layer_length = 784;
                break;

            case 2:
                current_layer[] = brain->layer2;
                //layer_length = 784;
                break;

            case 3:
                current_layer[] = brain->layer3;
                layer_length = 66;
                break;

            default:
                printf("init_random_brain : switch case i is not recognized");
                return(1);
        }
        for (int j = 0; j < layer_length)
        {
            init_random_neuron(current_layer[j]); //pointer or not ?
        }
}