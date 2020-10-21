#define _CRT_SECURE_NO_WARNINGS
#include "write_read_brain.h"

void write_brain(Brain* brain)
{
    FILE* brain_file = fopen("brain.txt","w"); // Warning : this delete the previous brain and rewrite on it
    if (brain_file != NULL)
    {
        for (int i = 0; i < SIZE_LAYERS; i++) //print layer 0
        {
            //fprintf(brain_file,"(%lf) ",brain->layers[0][i].bias);
            fprintf(brain_file,"(%lf) ",brain->layers[0][i].weights[0]);
        }
        fprintf(brain_file,"\n");

        for (int i = 1; i < NUMBER_HIDDEN_LAYERS;i++)//print all hidden layers
        {
            for (int j = 0; j < SIZE_LAYERS; j++)
            {
                //fprintf(brain_file,"(%lf",brain->layers[i][j].bias);
                fprintf(brain_file,"(");
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
            //fprintf(brain_file,"%lf",brain->last_layer[i].bias);
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
        printf("#####\nwrite_brain : brain_file closed \n#####\n");
    }
    else
    {
        printf("write_brain : writing failed \n");
        exit(1);
    }
}


Brain read_brain(char* brain_name)
{
    FILE* brain_file = fopen(brain_name,"r"); //read only
    fseek( brain_file, 0L, SEEK_SET );
    Brain brain = NewBrain();

    if (brain_file != NULL)
    {
        //get layer 0
        for(int i = 0; i < SIZE_LAYERS; i++)
        {
            fscanf(brain_file, "(%lf) ",&brain.layers[0][i].weights[0]);
        }
        fscanf(brain_file,"\n");
        //get hidden layers
        for (int i = 1; i < NUMBER_HIDDEN_LAYERS; i++)
        {
            for(int j = 0; j < SIZE_LAYERS; j++)
            {
                //fscanf(brain_file,"(%lf",&brain.layers[i][j].bias);
                fscanf(brain_file,"(");
                for (int k = 0; k < SIZE_LAYERS; k++)
                {
                    fscanf(brain_file, " %lf",&brain.layers[i][j].weights[k]);
                }
                fscanf(brain_file,") ");
            }
            fscanf(brain_file,"\n");
        }
        //get last layer
        for (int i = 0; i < SIZE_LAST_LAYER; i++)
        {
            //fscanf(brain_file,"(%lf",&brain.last_layer[i].bias);
            fscanf(brain_file,"(");
            for (int j = 0; j < SIZE_LAYERS; j++)
            {
                fscanf(brain_file, " %lf", &brain.last_layer[i].weights[j]);
            }
            fscanf(brain_file,") ");
        }
        fclose(brain_file);
        printf("####\nread_brain : reading complete\n####\n");
    }

    else
    {
        printf("read_brain : this file doesnt exist or is elsewhere\n");
        exit(1);
    }
    return brain;
}

