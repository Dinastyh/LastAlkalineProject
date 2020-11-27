#ifndef UI
#include <stdlib.h>
#include <gtk/gtk.h>
void displayTxt(GtkWidget* container,char string[]);
size_t lenString(char string[]);
void displayPictureGTK(GtkWidget* container, const char* path);
void displayClear(GtkWidget* container);
#define UI
#endif
