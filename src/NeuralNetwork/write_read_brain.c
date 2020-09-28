#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "write_read_brain.h"
#include "Brain.h"

int write(FILE* brain_file, Brain* brain)
{
    brain_file = fopen("brain.txt","w"); // Warning : this delete the previous brain and rewrite on it

    if (list != NULL)
    {
        // 4 layers : 784, 784, 784 and 40
        

        fclose(list);
    }

    return 0;
}

int read(FILE* brain_file, Brain* brain)
{
    brain_file = fopen("brain.txt","r"); //read only

    if (list != NULL)
    {
        for (int i = 0; i < 10; i++)
        {

            fscanf(list, "%lf", &f2);
            double_get[i] = f2;

            printf(" %.10f",double_get[i]);
        }

        fclose(list);
    }
    else
    {
        printf("this file doesnt exist or is elsewhere");
        return 1;
    }
    return 0;
}