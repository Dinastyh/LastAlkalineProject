#include "Brain.h"

Brain NewBrain()
{
    Brain brain = {
            NULL,
            NULL
    };

    brain.layers = malloc(NUMBER_HIDDEN_LAYERS*sizeof(Neuron*) + 1);

    //first layer
    brain.layers[0] = calloc(SIZE_LAYERS, sizeof(struct Neuron) + 1);
    for(int i = 0; i < SIZE_LAYERS; i++)
        brain.layers[0][i] = NewNeuron(0);

    // hidden layers except first one
    for(int i = 1; i < NUMBER_HIDDEN_LAYERS; i++)
    {
	    brain.layers[i] = calloc(SIZE_LAYERS, sizeof(Neuron) + 1);
	    for(int j = 0; j < SIZE_LAYERS;j++)
        {
	        brain.layers[i][j] = NewNeuron(SIZE_LAYERS);
        }
    }

    //last layer
    brain.last_layer = calloc(SIZE_LAST_LAYER,sizeof(Neuron) + 1);
    for(int j = 0; j < SIZE_LAST_LAYER;j++)
    {
        brain.last_layer[j] = NewNeuron(SIZE_LAYERS);
    }

    return brain;
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

void update_neuron_value(Neuron* neuron, Neuron* layer)
{
    double result = 0.0;
    for(int i = 0; i < SIZE_LAYERS; i++)
    {
        result += neuron->weights[i] * layer[i].value;
    }
    neuron->value = 1/(1+exp(-1*(result - neuron->bias)));
}

void forward_propagation(Brain* brain, double* data, double* end_data)
{
    //We need one variable end-data to use this function (double end_data[SIZE_LAST_LAYER])
    for(int i = 0; i < SIZE_LAYERS; i++)
    {
        brain->layers[0][i].value = data[i];
    }

    for(int i = 1; i < NUMBER_HIDDEN_LAYERS; i++)
    {
        for(int j = 0; j < SIZE_LAYERS; j++)
        {
            //Update all neuron values for hidden layers
            update_neuron_value(&brain->layers[i][j],brain->layers[i-1]);
            //printf("layer %d neuron %d value : %lf \n",i,j,brain->layers[i][j].value);
        }
    }

    for(int i = 0; i < SIZE_LAST_LAYER; i++)
    {
        update_neuron_value(&brain->last_layer[i],brain->layers[NUMBER_HIDDEN_LAYERS-1]);
    }

    for(int i = 0; i < SIZE_LAST_LAYER; i++)
    {
        end_data[i] = brain->last_layer[i].value;
    }
}

double mean_square_function(double* target, double* end_data) // target = label = ground truth = what we want
{
   //del_out lenght must be equal with lend_data lenght
   double total_error;
   for(int i = 0; i < SIZE_LAST_LAYER; i++)
   {
       total_error += 0.5*(target[i] - end_data[i])*(target[i] - end_data[i]);
   }
   return total_error;
}

double Sigmoid_prime(double value)
{
    return value*(1-value);
}

void calculate_gradient(Brain* brain, double* target)// calculate each gradient for each neuron and accept batch (not yet)
{
    for(int i = 0; i < SIZE_LAST_LAYER; i++)// last layer
    {
        double value = brain->last_layer[i].value;
        brain->last_layer[i].gradient += (value - target[i]) * Sigmoid_prime(value);

        //brain->last_layer[i].gradient += (brain->last_layer[i].value - target[i]) * Sigmoid_prime(brain->last_layer[i].value);
    }

    for(int i = 0; i < SIZE_LAYERS; i++)// layer just before last layer, each neuron
    {
        Neuron neuron = brain->layers[NUMBER_HIDDEN_LAYERS - 1][i];
        double gradient_sum;
        for(int j = 0; j < SIZE_LAST_LAYER; j++) //each weight to last layer
        {
            gradient_sum += brain->last_layer[j].gradient * brain->last_layer[j].weights[j];
        }
        neuron.gradient += gradient_sum * Sigmoid_prime(neuron.value);
    }

    for(int i = NUMBER_HIDDEN_LAYERS - 1; i > 1; i--) //layers from back to front
    {
        for(int j = 0; j < SIZE_LAYERS;j++) //each neuron of layer i compute gradient to neuron layer i-1
        {
            Neuron neuron = brain->layers[i-1][j];
            double gradient_sum;
            for(int k = 0; k < SIZE_LAYERS; k++) //each weight
            {
                gradient_sum += brain->layers[i][k].gradient * brain->layers[i][k].weights[k];
            }
            neuron.gradient += gradient_sum * Sigmoid_prime(neuron.value);
        }
    }
}

void update_weights(Brain* brain, double learning_rate, double batch_size) //batch size only 1
{
    // batch_size is a int but division is decimal, gradient is averaged by batch and reset after update
    for(int i = 1; i < NUMBER_HIDDEN_LAYERS; i++)//layers 2 and 3
    {
        for(int j = 0; j < SIZE_LAYERS; j++)//neurons in layer
        {
            Neuron neuron = brain->layers[i][j];
            for (int k = 0; k < SIZE_LAYERS; k++)//each weight
            {
                neuron.weights[k] -= learning_rate *
		        neuron.gradient * brain->layers[i-1][k].value / batch_size;
            }
            brain->layers[i][j].gradient = 0;
        }
    }
    //last layer
    for(int j = 0; j < SIZE_LAST_LAYER; j++)//neurons in layer
    {
        Neuron neuron = brain->last_layer[j];
        for (int k = 0; k < SIZE_LAYERS; k++)//each weight
        {
            neuron.weights[k] -= learning_rate * neuron.gradient * brain->layers[NUMBER_HIDDEN_LAYERS-1][k].value / batch_size;
        }
        neuron.gradient = 0;
    }
}

//training goes as follow : randomly pick n pictures with their tags and calculate their gradient (they sum up)
//update the weights at the end of the batch with average of gradient (& gradient is reset)
//should reduce the error function and converge to error->0 after multiple training steps

