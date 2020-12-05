#define _CRT_SECURE_NO_WARNINGS
#include "write_read_brain.h"
#include "../PictureUtils/Bmp24.h"
#include "Debug.h"

void writeNetwork(Network* net)
{
    FILE* netFile = fopen("network.txt","w"); // Warning : this delete the previous network and rewrite on it

    if (netFile == NULL)
    {
        printf("writeNetwork : open failed \n");
        exit(1);
    }
    else
    {
        //store data concerning the network
        fprintf(netFile,"%zu %zu %zu %zu\n",net->nbLayers - 2, net->sizeInput, net->sizeOutput, net->sizeHidden);
        for (size_t i = 0; i < net->nbLayers; i++) // each layer
        {
            Layer layer = net->layers[i];

            for(size_t j = 0; j < layer.nbNeurons; j++) //each neuron
            {
                Neuron neuron = layer.neurons[j];

                fprintf(netFile,"(");
                for(size_t k = 0; k < neuron.nbWeights; k++)
                {
                    fprintf(netFile,"%lf ",neuron.weights[k]);
                }
                fprintf(netFile,") ");
            }
            fprintf(netFile,"\n");
        }

        if(fclose(netFile) == -1)
        {
            printf("writeNetwork: fclose failed\n");
            exit(2);
        }
        printf("#####\nwriteNetwork : net_file closed \n#####\n");
    }
}

Network readNetwork(char* netName)
{
    FILE* netFile = fopen(netName,"r"); //read only
    fseek(netFile, 0L, SEEK_SET );

    size_t nbHiddenLayers;
    size_t sizeInput;
    size_t sizeOutput;
    size_t sizeHidden;

    fscanf(netFile, "%zu %zu %zu %zu\n", &nbHiddenLayers, &sizeInput, &sizeOutput, &sizeHidden);
    Network net = newNetwork(sizeInput, sizeHidden, sizeOutput, nbHiddenLayers);

    if (netFile != NULL)
    {
        for(size_t i = 0; i < nbHiddenLayers + 2; i++)
        {
            Layer layer = net.layers[i];
            for(size_t j = 0; j < layer.nbNeurons; j++)
            {
                Neuron neuron = layer.neurons[j];
                fscanf(netFile,"(");
                for(size_t k = 0; k < neuron.nbWeights; k++)
                {
                    fscanf(netFile, "%lf ",&net.layers[i].neurons[j].weights[k]);
                }
                fscanf(netFile,") ");
            }
            fscanf(netFile,"\n");
        }

        fclose(netFile);
        printf("####\nreadNetwork : reading complete\n####\n");
    }

    else
    {
        printf("readNetwork : this file doesnt exist or is elsewhere\n");
        exit(1);
    }
    return net;
}

char charFromImage(Network* net, char* filename)
{
    char c;
    double *data = malloc(net->sizeInput * sizeof(double));
    pictureToArray(data, filename);

    int result = forwardPropagationTest(net, data);
    if(result >= 4 && result <= 13)
    {
        c = result + 44; // '0' - 4
    }
    else if(result >= 14 && result <= 39)
    {
        c = result + 51;
    }
    else if(result >= 40 && result <= 65)
    {
        c = result + 57;
    }
    else
    {
        switch (result)
        {
        case 0:
            c = '!';
            break;
        case 1:
            c = '.';
            break;
        case 2:
            c = ':';
            break;
        case 3:
            c = '?';
            break;
        default:
            c = '/'; //error if c is /
            break;
        }
    }
    return c;
}

