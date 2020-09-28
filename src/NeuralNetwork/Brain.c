#include <stdio.h>
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
