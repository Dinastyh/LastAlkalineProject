#ifndef _Brain_H
#define _Brain_H
#include "Neuron.h"

struct Brain
{
    Neuron* layer0;
    Neuron* layer1;
    Neuron* layer2;
    Neuron* layer3;
}
typedef struct Brain Brain;

Brain* NewBrain();
#endif
