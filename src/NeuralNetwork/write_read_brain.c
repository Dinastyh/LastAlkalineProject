#define _CRT_SECURE_NO_WARNINGS
#include "write_read_brain.h"

void write_brain(Brain* brain)
{
    FILE* brain_file = fopen("brain.txt","w"); // Warning : this delete the previous brain and rewrite on it

    if (brain_file != NULL)
    {
        for (int i = 0; i < SIZE_LAYERS; i++) //print layer 0
        {
            fprintf(brain_file,"(");
            fprintf(brain_file,"%lf",brain->layers[0][i].bias);
            fprintf(brain_file,") ");
        }
        fprintf(brain_file,"\n");

        for (int i = 1; i < NUMBER_HIDDEN_LAYERS;i++)//print all hidden layers
        {
            for (int j = 0; j < SIZE_LAYERS; j++)
            {
                fprintf(brain_file,"(");
                fprintf(brain_file,"%lf",brain->layers[i][j].bias);
                for(int k = 0; k < SIZE_LAYERS; k++)
                {
                    fprintf(brain_file," %lf", brain->layers[i][j].weights[k]);
                }

                fprintf(brain_file,") ");
            }
            fprintf(brain_file,"\n");
        }

        //print last layer

        for (int i = 0; i < SIZE_LAST_LAYER; i++)
        {
            fprintf(brain_file,"(");
            fprintf(brain_file,"%lf",brain->last_layer[i].bias);
            for(int j = 0; j < SIZE_LAYERS; j++)
            {
                fprintf(brain_file," %lf", brain->last_layer[i].weights[j]);
            }

            fprintf(brain_file,") ");
        }
        fprintf(brain_file,"\n");

        if(fclose(brain_file) == -1)
        {
            exit(2);
        }
        printf("write_brain : brain_file closed \n");
        exit(0);
    }
    else
    {
        printf("write_brain : writing failed \n");
        exit(1);
    }
}

/*
Brain read(FILE* brain_file)
{
    brain_file = fopen("brain.txt","r"); //read only
    Brain* brain = NewBrain();

    if (list != NULL)
    {
        Neuron* current_layer;

            for (int j = 0; j < layer_length; j++)
            {
                //fscanf(brain_file, "(%lf %lf) ", current_layer[j]->weight,current_layer[j]->bias);
                char buffer;
                fscanf(brain_file,"(%lf",current_layer[j]->bias);
                for (k = 0; k < weight_count; k++)
                {
                    fscanf(brain_file, " %lf", current_layer[j]->weights[k]);
                }

                fscanf(brain_file, ") ",&buffer);
                //printf("(%lf %lf) ",current_layer[j].weight,current_layer[j].bias);
            }
            //there should be a \n that we need to empty
            char buffer[10];
            fscanf(brain_file,"\n",buffer);
            printf(brainf_file,"\n");


            reference for how to read a file (I may have fcked up on the pointers)
            fscanf(list, "%lf", &f2);
            double_get[i] = f2;

        }
        fclose(list);
    }
    else
    {
        printf("this file doesnt exist or is elsewhere");
        exit(1);
    }
    return brain;
}
 */
