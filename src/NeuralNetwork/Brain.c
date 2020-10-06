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

double Sigmoid_prime(double value)
{
    return value*(1-value);
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

double mean_square_function(double* target, double* end_data) // target = label = ground truth = what we want
{
   //del_out lenght must be equal with lend_data lenght
   double total_error;
   for(int i =0; i <66; i++)
   {
       total_error += 0.5*(target[i] - end_data[i])*(target[i] - end_data[i]);
   }
   return total_error;
}

void calculate_gradient(brain* brain, double* target)// calculate each gradient for each neuron and accept batch
{
    for(int i = 0; i < 66)// last layer
    {
        double value = last_layer[i].value;
        brain->last_layer[i].gradient += (value - target[i]) * Sigmoid_prime(value);
    }

    for(int j = 0; j < 784; j++)// layer 3
    {
        double value = layers[2][i].value;
        double gradient_sum;
        for(int i = 0; i < 66; i++)
        {
            gradient_sum += last_layer[i].gradient * last_layer[i].weight[i];
        }
        brain->layers[2][j].gradient += gradient_sum * Sigmoid_prime(value);
    }

    for(int j = 0; j < 784; j++) //layer 2
    {
        double value = layers[1][i].value;
        double gradient_sum;
        for(int i = 0; i < 784; i++)
        {
            gradient_sum += layers[2][i].gradient * layers[2][i].weight[i];
        }
        brain->layers[2][j].gradient += gradient_sum * Sigmoid_prime(value);
    }
}

void update_weights(brain* brain, double learning_rate, double batch_size)
{
    // batch_size is a int but division is decimal, gradient is averaged by batch and reset after update
    for(int i = 1; i < 3; i++)//layers 2 and 3
    {
        for(int j = 0; j < 784; j++)//neurons in layer
        {
            for (int k = 0; k < 784; k++)//each weight
            {
                brain->layers[i][j].weight[k] -= learning_rate * brain->layers[i][j].gradient * brain->layers[i-1][j].value / batch_size;
            }
            brain->layers[i][j].gradient = 0;
        }
    }
    //last layer
    for(int j = 0; j < 66; j++)//neurons in layer
    {
        for (int k = 0; k < 784; k++)//each weight
        {
            brain->last_layer[j].weight[k] -= learning_rate * brain->last_layer[j].gradient * brain->layers[2][j].value / batch_size;
        }
        brain->last_layer[j].gradient = 0;
    }
}

//training goes as follow : randomly pick n pictures with their tags and calculate their gradient (they sum up)
//update the weights at the end of the batch with average of gradient (& gradient is reset)
//should reduce the error function and converge to error->0 after multiple training steps

