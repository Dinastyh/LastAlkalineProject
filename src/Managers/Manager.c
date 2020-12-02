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
    Picture picture = newPicture(path, "tmp.bmp");
    //Faut rajouter tous les pretraitement ici
    savePicture(picture);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Preview"); 
    char* newPath = malloc(100*sizeof(char));
    getcwd(newPath, 100);
    strcat(newPath, "/");
    strcat(newPath, picture.name);
    g_print("path: %s\n",newPath);
    GtkWidget *gPicture = gtk_image_new_from_file(newPath);
    GtkWidget* box = gtk_vbox_new(FALSE, 0);
    GtkWidget* exitBtn = gtk_button_new_with_label("Exit");
    g_signal_connect(G_OBJECT(exitBtn), "released", G_CALLBACK(onExit), window);
    gtk_box_pack_start(GTK_BOX(box), gPicture, TRUE, TRUE,0);
    gtk_box_pack_start(GTK_BOX(box), exitBtn, FALSE, FALSE,0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    remove(newPath);
    free(newPath);
}

void onExit(GtkWidget* button, gpointer data)
{
    GtkWidget* window = data;
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    for(GList *iter = children; iter != NULL; iter = g_list_next(iter))
    {
        GtkWidget* box = iter->data;
        GList *bChil = gtk_container_get_children(GTK_CONTAINER(box));
        for(GList *j = bChil; j != NULL; j = g_list_next(j))
        {
            gtk_widget_destroy(GTK_WIDGET(j->data));
        }
        gtk_widget_destroy(GTK_WIDGET(iter->data));
        g_list_free(box);
    }
    g_list_free(children);
    gtk_widget_destroy(window);
}
