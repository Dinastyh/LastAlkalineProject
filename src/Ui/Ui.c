#include "Ui.h"

static void activate(GtkApplication* app, gpointer userData)
{
    GtkWidget *window;

    window = gtk_application_window__new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LastAlkalineProject");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_widget_show_all(window);
}
