#include "Ui.h"
void displayTxt(GtkWidget* container,char string[])
{
    GtkWidget *label;
    GtkWidget* gtk_label_new(const char* str);
    gchar* stringUtf8 = g_locale_to_utf8(string, lenString(string), NULL, NULL, NULL);
    label = gtk_label_new(stringUtf8);
    g_free(stringUtf8);
    displayClear(container);
    gtk_box_pack_start(GTK_CONTAINER(container), label, FALSE, TRUE, 0);
    gtk_widget_show(label);
}

void displayPicture(GtkWidget* container, const char* path)
{
    GtkWidget* picture = gtk_image_new_from_file(path);
    displayClear(container);
    gtk_box_pack_start(GTK_CONTAINER(container), "",FALSE, TRUE, 0);
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

    children = gtk_container_get_children(GTK_CONTAINER(container));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}
