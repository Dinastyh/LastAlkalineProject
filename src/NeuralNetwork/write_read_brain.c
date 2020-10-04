#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "write_read_brain.h"
#include "Brain.h"

int write(FILE* brain_file, Brain brain)
{
    brain_file = fopen("brain.txt","w"); // Warning : this delete the previous brain and rewrite on it

    if (list != NULL)
    {
        Neuron* current_layer[];
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
                    printf("write_brain : switch case i is not recognized");
                    return(1);
            }
            for (int j = 0; j < layer_length)
            {
                fprintf(brain_file,"(");
                fprintf(brain_file,"%lf %lf",current_layer[j].weight,current_layer[j].bias);
                fprintf(brain_file,") ");
            }
            fprintf(brainf_file,"\n")
        }
        fclose(list);
    }

    return 0;
}

Brain read(FILE* brain_file)
{
    brain_file = fopen("brain.txt","r"); //read only
    Brain* brain = NewBrain();

    if (list != NULL)
    {
        Neuron* current_layer[];
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
                    printf("read_brain : switch case i is not recognized");
                    exit(1);
            }
            for (int j = 0; j < layer_length)
            {
                fscanf(brain_file, "(%lf %lf) ", current_layer[j]->weight,current_layer[j]->bias);
                printf("(%lf %lf) ",current_layer[j].weight,current_layer[j].bias);
            }
            //there should be a \n that we need to empty
            char buffer[10];
            fscanf(brain_file,"\n",buffer);
            printf(brainf_file,"\n");

            /*
            reference for how to read a file (I may have fcked up on the pointers)
            fscanf(list, "%lf", &f2);
            double_get[i] = f2;
            */
        }
        fclose(list);
    }
    else
    {
        printf("this file doesnt exist or is elsewhere");
        exit(1);
    }
    exit(0);
}