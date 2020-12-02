#ifndef MANAGER
#define MANAGER
#include <stdio.h>
#include "../PictureUtils/Bmp24.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <string.h>
int loadPicture(const char* path);
void onExit(GtkWidget* button, gpointer data);
void preview(const char* path, unsigned int status[], size_t len);
#endif
