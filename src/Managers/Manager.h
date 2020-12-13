#ifndef MANAGER
#define MANAGER
#include <stdio.h>
#include "../PictureUtils/Bmp24.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "../NeuralNetwork/Network.h"
#include "../NeuralNetwork/Debug.h"
#include "../NeuralNetwork/Training.h"
#include "../NeuralNetwork/write_read_brain.h"
#include "../PictureUtils/DisplayPicture.h"
#include "../PictureUtils/PreProcessPicture.h"
void processingBasic(Picture* picture, bool status[], size_t len);
char* managerExec(const char* path, bool status[], size_t len);
int loadPicture(const char* path);
void onExit(GtkWidget* button, gpointer data);
void preview(const char* path, bool status[], size_t len);
#endif
