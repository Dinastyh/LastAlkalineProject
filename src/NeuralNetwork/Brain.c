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
