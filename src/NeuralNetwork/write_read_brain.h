#ifndef _write_read_brain_H
#define _write_read_brain_H
#include "Network.h"

void writeNetwork(Network* net);
Network readNetwork(char* netName);
char charFromImage(Network* net, char* filename);
#endif