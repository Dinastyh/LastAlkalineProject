#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Brain.h"
#include "Neuron.h"

Brain* NewBrain()
{
    Brain* brain = malloc(sizeof(Brain));
    brain->layers = malloc(3*sizeof(Neuron*)); 
    for(int i = 0; i <3; i++)
    {
	brain->layers[i] = calloc(784, sizeof(Neuron));
    }
    brain->last_layer = calloc(66,sizeof(Neuron*)); 
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
    neuron->value = 1/(1+exp(-1*(sigSum - neuron->bias)));
}

void init_random_brain(Brain* brain)
{
    for(int i = 0; i < 3; i++)
    {
	for(int j = 0; j <784; j++)
	    {
		init_random_neuron(&(brain->layers[i][j]));
	    }
    }

    for (int i = 0; i < 66;i++ )
    {
        init_random_neuron(&(brain->last_layer[i]));
    }
}

void forward_propagation(Brain* brain, double* data, double* end_data)
{
    //We need one variable end-data to use this function (double end_data[66])
    for(int i = 0; i<784; i++)
    {
	brain->layers[0][i].value = data[i];
    }
    
    for(int i = 1; i<3; i++)
    {
	for(int j = 0; j<784; j++)
	{   
	    //Update ALL values for layers 0 -> 1 and 1->2
	    double sigsum = SigmoidSum(brain->layers[i-1], brain->layers[i][j]);
	    NeuronUpdate(&(brain->layers[i][j]), sigsum);
	}
    }

    for(int i = 0; i <66; i++)
    {
	double sigsum = SigmoidSum(brain->layers[2], brain->last_layer[i]);
	NeuronUpdate(&(brain->last_layer[i]), sigsum);
    }

    for(int i = 0; i<66; i++)
    {
	end_data[i] = brain->last_layer[i].value;
    }
}

void mean_square_function(double* label, double* end_data, double* del_out)
{
   //del_out lenght must be equal with lend_data lenght
   for(int i =0; i <66; i++)
   {
       del_out[i] = (label[i] - end_data[i])* (end_data[i] *(1-end_data[i]));
   }
}


