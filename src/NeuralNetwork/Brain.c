#include "Brain.h"

Brain* NewBrain()
{
    Brain* brain = malloc(sizeof(Brain));
    brain->layers = malloc(NUMBER_HIDDEN_LAYERS*sizeof(Neuron*) + 1);

    //first layer
    brain->layers[0] = calloc(SIZE_LAYERS, sizeof(struct Neuron) + 1);
    for(int i = 0; i < SIZE_LAYERS; i++)
        brain->layers[0][i] = NewNeuron(0);

    // hidden layers except first one
    for(int i = 1; i < NUMBER_HIDDEN_LAYERS; i++)
    {
	    brain->layers[i] = calloc(SIZE_LAYERS, sizeof(Neuron) + 1);
	    for(int j = 0; j < SIZE_LAYERS;j++)
        {
	        brain->layers[i][j] = NewNeuron(SIZE_LAYERS);
        }
    }

    //last layer
    brain->last_layer = calloc(SIZE_LAST_LAYER,sizeof(Neuron) + 1);
    for(int j = 0; j < SIZE_LAST_LAYER;j++)
    {
        brain->last_layer[j] = NewNeuron(SIZE_LAYERS);
    }

    return brain;
}

double SigmoidSum(const Neuron* layer, Neuron neuron)
{
    double result = 0;
    for(int i = 0; i < SIZE_LAYERS; i++)
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
    for(int i = 0; i < NUMBER_HIDDEN_LAYERS; i++)
    {
	for(int j = 0; j <SIZE_LAYERS; j++)
	    {
            //printf("i= %d j= %d", i, j);
            init_random_neuron(&(brain->layers[i][j]));
	    }

    }

    for (int i = 0; i < SIZE_LAST_LAYER;i++ )
    {
        init_random_neuron(&(brain->last_layer[i]));
    }
}

void forward_propagation(Brain* brain, double* data, double* end_data)
{
    //We need one variable end-data to use this function (double end_data[SIZE_LAST_LAYER])
    for(int i = 0; i<SIZE_LAYERS; i++)
    {
        brain->layers[0][i].value = data[i];
    }

    for(int i = 1; i<NUMBER_HIDDEN_LAYERS; i++)
    {
        for(int j = 0; j<SIZE_LAYERS; j++)
        {
            //Update ALL values for layers 0 -> 1 and 1->2
            double sigsum = SigmoidSum(brain->layers[i-1], brain->layers[i][j]);
            NeuronUpdate(&(brain->layers[i][j]), sigsum);
        }
    }

    for(int i = 0; i <SIZE_LAST_LAYER; i++)
    {
        double sigsum = SigmoidSum(brain->layers[2], brain->last_layer[i]);
        NeuronUpdate(&(brain->last_layer[i]), sigsum);
    }

    for(int i = 0; i<SIZE_LAST_LAYER; i++)
    {
        end_data[i] = brain->last_layer[i].value;
    }
}

double mean_square_function(double* target, double* end_data) // target = label = ground truth = what we want
{
   //del_out lenght must be equal with lend_data lenght
   double total_error;
   for(int i =0; i <SIZE_LAST_LAYER; i++)
   {
       total_error += 0.5*(target[i] - end_data[i])*(target[i] - end_data[i]);
   }
   return total_error;
}

void calculate_gradient(Brain* brain, double* target)// calculate each gradient for each neuron and accept batch
{
    for(int i = 0; i < SIZE_LAST_LAYER; i++)// last layer
    {
        double value = brain->last_layer[i].value;
        brain->last_layer[i].gradient += (value - target[i]) * Sigmoid_prime(value);
    }

    for(int j = 0; j < SIZE_LAYERS; j++)// layer 3
    {
        double value = brain->layers[2][j].value;
        double gradient_sum;
        for(int i = 0; i < SIZE_LAST_LAYER; i++)
        {
            gradient_sum += brain->last_layer[i].gradient * brain->last_layer[i].weights[i];
        }
        brain->layers[2][j].gradient += gradient_sum * Sigmoid_prime(value);
    }

    for(int j = 0; j < SIZE_LAYERS; j++) //layer 2
    {
        double value = brain->layers[1][j].value;
        double gradient_sum;
        for(int i = 0; i < SIZE_LAYERS; i++)
        {
            gradient_sum += brain->layers[2][i].gradient * brain->layers[2][i].weights[i];
        }
        brain->layers[2][j].gradient += gradient_sum * Sigmoid_prime(value);
    }
}

void update_weights(Brain* brain, double learning_rate, double batch_size)
{
    // batch_size is a int but division is decimal, gradient is averaged by batch and reset after update
    for(int i = 1; i < NUMBER_HIDDEN_LAYERS; i++)//layers 2 and 3
    {
        for(int j = 0; j < SIZE_LAYERS; j++)//neurons in layer
        {
            for (int k = 0; k < SIZE_LAYERS; k++)//each weight
            {
                brain->layers[i][j].weights[k] -= learning_rate * 
		        brain->layers[i][j].gradient * brain->layers[i-1][j].value / batch_size;
            }
            brain->layers[i][j].gradient = 0;
        }
    }
    //last layer
    for(int j = 0; j < SIZE_LAST_LAYER; j++)//neurons in layer
    {
        for (int k = 0; k < SIZE_LAYERS; k++)//each weight
        {
            brain->last_layer[j].weights[k] -= learning_rate * brain->last_layer[j].gradient * brain->layers[2][j].value / batch_size;
        }
        brain->last_layer[j].gradient = 0;
    }
}

//training goes as follow : randomly pick n pictures with their tags and calculate their gradient (they sum up)
//update the weights at the end of the batch with average of gradient (& gradient is reset)
//should reduce the error function and converge to error->0 after multiple training steps

