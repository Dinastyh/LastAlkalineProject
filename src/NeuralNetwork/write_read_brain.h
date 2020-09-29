#ifndef _write_read_brain_H
#define _write_read_brain_H
#include "Brain.h"

int write(FILE* brain_file, Brain* brain);
Brain read(FILE* brain_file);

#endif