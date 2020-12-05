#include "Ui.h"
void displayTxt(GtkWidget* container,char string[])
{
    //Text trad
    GtkWidget *label;
    GtkWidget* scrollbar;
    GtkTextBuffer* buffer = 0;
    GtkTextIter start,end;
    GtkTextIter iter;
    gchar* stringUtf8 = g_locale_to_utf8(string, lenString(string), NULL, NULL, NULL);
    displayClear(container);
    //Text display
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_end(GTK_CONTAINER(container), scrollbar, TRUE, TRUE, 0);
    label = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(label));
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    gtk_text_buffer_insert(buffer, &iter, stringUtf8, -1);
    gtk_container_add(GTK_CONTAINER(scrollbar), label);
    g_free(stringUtf8);
    gtk_widget_show(label);
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

    children = gtk_container_get_children(GTK_CONTAINER(container));
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}
