#include "Ui.h"
void displayTxt(GtkWidget* container,char string[])
{
    GtkWidget *label;
    GtkWidget* gtk_label_new(const char* str);
    gchar* stringUtf8 = g_locale_to_utf8(string, lenString(string), NULL, NULL, NULL);
    label = gtk_label_new(stringUtf8);
    g_free(stringUtf8);
    gtk_container_add(GTK_CONTAINER(container), label);
    gtk_widget_show(label);
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
