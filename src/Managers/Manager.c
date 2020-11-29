#include "Manager.h"
#define true 1
#define false 0
int loadPicture(const char* path)
{
    if(path == NULL)
        return false;
    if(!(isPictureValid(path)))
        return false;
    return true;
}

void preview(const char* path, unsigned int status[], size_t len)
{
    Picture picture = newPicture(path, "tmp");
    //Faut rajouter tous les pretraitement ici
    savePicture(picture);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Preview"); 
    char* newPath = malloc(100*sizeof(char));
    getcwd(newPath, 100);
    strcat(newPath, picture.name); 
    GtkWidget *gPicture = gtk_image_new_from_file(newPath);
    gtk_container_add(GTK_CONTAINER(window), gPicture);
    gtk_widget_show_all(window);
    gtk_widget_destroy(window);
    gtk_widget_destroy(gPicture);
    remove(newPath);
    free(newPath);
}
