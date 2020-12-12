#include "Ui.h"
void displayTxt(GtkWidget* container,char string[])
{
    //Text trad
    GtkWidget *view;
    GtkWidget* scrollbar;
    GtkTextBuffer* buffer = 0;
    displayClear(container);
    //Text display
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text(buffer, string, -1);
    gtk_container_add(GTK_CONTAINER(scrollbar), view);
    gtk_box_pack_start(GTK_CONTAINER(container), scrollbar, TRUE, TRUE, 0);
    gtk_widget_show_all(container);
}

void displayPictureGTK(GtkWidget* container, const char* path)
{
    GtkWidget* scrollbar = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget* picture = gtk_image_new_from_file(path);
    displayClear(container);
    gtk_scrolled_window_add_with_viewport(scrollbar, picture);
    gtk_box_pack_start(GTK_CONTAINER(container), scrollbar,TRUE, TRUE, 0);
    gtk_widget_show_all(container);
}
size_t lenString(char string[])
{
    size_t len = 0;
    while(string[len] !='\0')
    {
        len++;
    }
    return len;
}

void displayClear(GtkWidget* container)
{
    GList *children, *iter;
    g_print("ta mere ne bug pas\n");
    children = gtk_container_get_children(GTK_CONTAINER(container));
    while(children)
    {
        g_print("aller bug");
        gtk_widget_destroy(children->data);
        children = g_list_next(children);
    }
    g_list_free(children);
}
