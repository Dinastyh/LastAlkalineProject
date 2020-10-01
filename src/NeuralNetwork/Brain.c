#include <stdio.h>
#include <math.h>
#include "Brain.h"
#include "Neuron.h"

Brain* NewBrain()
{
    Brain* brain = malloc(sizeof(Brain));
    brain->layers = calloc(4, sizeof(Neuron*));
    for(int i = 0; i <3; i++)
    {
	brain->layers[i] = calloc(784, sizeof(Neuron*));
    }
    brain->layers[3] = calloc(66,sizeof(Neuron*)); 
    return brain;
}

double SigmoidSum(const Neuron* layer, Neuron neuron)
{
    double result = 0;
    for(int i = 0; i < 784; i++)
    {
	    result += neuron.weights[i]*layer[i].value;
    }
    return result;
}

void NeuronUpdate(Neuron* neuron, double sigSum)
{
    neuron->value = 1/(1+exp(-1*(sigSum - neuron->bias);
}

void init_random_brain(Brain* brain)
{
    for(int i = 0; i < 3; i++)
    {
	for(int j = 0; j <784; j++)
	    {
		init_random_neuron(brain->layers[i][j];
	    }
    }

    for (int i = 0; i < 66;i++ )
    {
        init_random_neuron(brain->layers[3][i]);
    }
}

double* forward_propagation(Brain* brain, double* data)
{
    for(int i = 0; i<784; i++)
    {
	brain->layers[0][i].value = data[i];
    }
    
    for(int i = 1; i<3; i++)
    {
	for(int j = 0; j<784; j++)
	{   
	    //Update ALL values for layers 0 -> 1 and 1->2
	    double sigsum = Sigmoid(&(brain->layers[i-1], brain->layers[i][j];
	    NeuronUpdate(&(brain->layers[i][j]), sigsum);
	}
    }

    for(int i = 0; i <66; i++)
    {
	double sigsum = Sigmoid(&(brain->layers[2], brain->layers[3][i];
	NeuronUpdate(&(brain->layers[3][i]), sigsum);
    }

    double* end_value[66];
    for(int i = 0; i<66; i++)
    {
	end_value[i] = layers[3][i].value;
    }
    return end_value;
}
