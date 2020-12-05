#include <string.h>
#include "Debug.h"
#include "write_read_brain.h"
#include "Training.h"
#include "../PictureUtils/Bmp24.h"

void printLayerWeigths(Layer layer)
{
    size_t nbNeurons = layer.nbNeurons;
    size_t nbWeights = layer.neurons[0].nbWeights;
    for(size_t i = 0; i < nbNeurons; i++)
    {
        printf("(");
        for(size_t j = 0; j < nbWeights; j++)
        {
            printf("%lf ",layer.neurons[i].weights[j]);
        }
        printf(") ");
    }
    printf("\n");
}

void printLayerValues(Layer layer)
{
    for(size_t i = 0; i < layer.nbNeurons; i++)
    {
        printf("neuron %zu value : %lf ",i,layer.neurons[i].value);
    }
    printf("\n");
}

void printLayerDerivatives(Layer layer)
{
    size_t nbWheights = layer.neurons[0].nbWeights;

    for(size_t i = 0; i < layer.nbNeurons; i++)
    {
        Neuron neuron = layer.neurons[i];
        printf("neuron %zu ",i);
        printf("dedout : %lf, ",neuron.dedout);
        printf("doutdnet : %lf\n",neuron.doutdnet);

        printf("delta weights : \n");
        for(size_t i = 0; i < nbWheights; i++)
        {
            printf("%lf ",neuron.dw[i]);
        }
        printf("\n");
    }
    printf("\n");
}

void printNetwork(Network* net)
{
    for (size_t i = 0; i < net->nbLayers;i++)
    {
        printf("##### LAYER %zu #####",i);
        printLayerWeigths(net->layers[i]);
    }
    printf("\n");
}

void print_vector(int size, double* data)
{
    for(int i = 0; i< size; i++)
    {
	    printf("Data[%d] = %lf", i, data[i]);
    }
}

void checkForwardPropagation(Network* net, double* input, double* target)
{
    printf("Data In\n");
    print_vector(net->sizeInput, input);
    printf("Target\n");
    print_vector(net->sizeOutput, target);
    forwardPropagation(net, input, target);

    //printLayerValues(net->layers[net->nbLayers-1]);
}

int forwardPropagationTest(Network* net, double* data)
{
    Layer* layer = &(net->layers[0]); //first layer

    for(size_t i = 0; i < layer->nbNeurons; i++)
    {
	    layer->neurons[i].value = data[i];
    }

    for(size_t i = 1; i < net->nbLayers; i++)
    {
	    layer = &(net->layers[i]);
	    for(size_t j = 0; j < layer->nbNeurons; j++)
	    {
            double sum = 0;
            for(size_t k = 0; k<= net->layers[i-1].nbNeurons; k++)
            {
                if (k == 0)
                    sum += layer->neurons[j].weights[k];
                else
                    sum += layer->neurons[j].weights[k] * net->layers[i-1].neurons[k-1].value;
            }
            layer->neurons[j].value = 1 / (1 + exp(-sum));
	    }
    }

    int predictedResult = 0;
    double max = 0;
    layer = &(net->layers[net->nbLayers - 1]); //last layer

    for(size_t i = 0; i < net->sizeOutput; i++)
    {
        //printf("last layer values %lf ",layer->neurons[i].value);
        if(layer->neurons[i].value > max)
        {
            max = layer->neurons[i].value;
            predictedResult = i;
        }
    }
    //printf("\n");
    return predictedResult;
}

void TestNetwork(Network* net, size_t nbElement)
{
    double nbSuccess = 0;
    double nbFailure = 0;
    int nbOutput = net->sizeOutput;
    int predictedResult;
    double *data = malloc(net->sizeInput * sizeof(double));
    size_t offset = 0; //264;

    for(size_t i = 0; i < nbElement; i++)
    {
        FILE *source, *target;
        int sourceLength;

        char filename[200] = "datasetNoRotationNoOffset/";
        char failname[100] = "failures/";
        char id[10];
        sprintf(id, "%ld", i + offset);
        //printf("id : %s\n", id);
        strcat(filename, id);
        strcat(failname, id);
        strcat(filename, ".bmp");
        strcat(failname, ".bmp");

        if((i+offset) % 500 == 0)
            printf("filename : %s\n", filename);

        pictureToArray(data, filename);
        int label = i % nbOutput;

        predictedResult = forwardPropagationTest(net, data);
        if (predictedResult == label)
        {
            nbSuccess++;
        }
        else
        {
            nbFailure++;
            source = fopen(filename, "rb");

            fseek(source, 0, SEEK_END);
            sourceLength = ftell(source);

            fseek(source, 0, SEEK_SET);
            target = fopen(failname, "wb"); 

            for(int j = 0; j < sourceLength; j++)
            {
                fputc(fgetc(source), target);
            }

            fclose(source);
            fclose(target);
        }
    }
    printf("nbSuccess = %lf, nbFailure = %lf\n", nbSuccess, nbFailure);
    double accuracy = (nbElement - nbFailure)/nbElement;
    printf("Accuracy = %lf\n", accuracy);
}

#if 0
Network demoWriteRead(int sizeInput, int sizeOutput, int nbHidden, int sizeHidden)
{
    srand (time ( NULL));
    Network net = newNetwork(sizeInput,sizeHidden,sizeOutput,nbHidden);
    initNetwork(&net);
    printNetwork(&net);

    writeNetwork(&net);

    Network net2 = readNetwork("network.txt");
    printNetwork(&net2);

    return net2;
}

void demoTraining(Network* net, double* input, double* desiredOutput)
{
    int nb_trainings = 500;
    for (int i = 0; i < nb_trainings; i++) // one training
    {
        printf("Forward prop start :\n");
        forwardPropagation(net, input, desiredOutput);
        double cost = meanSquareFunction(desiredOutput, &(net->layers[net->nbLayers-1]));
        printf("Total cost : %lf\n", cost);
        printf("Backpropagation start :\n");
        backPropagation(net);
        printf("### backpropagation end ###\n\n");

        gradientDescent(net,0.3);
    }
    printf("#### training end ####\n");
}

#endif




