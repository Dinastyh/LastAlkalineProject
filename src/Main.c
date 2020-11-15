#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Ui/Ui.h"
#include <gtk/gtk.h>

void onDestroy(GtkWidget *pWidget, gpointer pData);
void onExecute(GtkWidget *pWidget, gpointer pData);
void onSelect(GtkWidget *pWidget, gpointer pData);
void onSave(GtkWidget *pWidget, gpointer pData);

int main(int argc,char** argv)
{ 
    GtkWidget* window;
    GtkWidget* exeBtn;
    GtkWidget* selectBtn;
    GtkWidget* saveBtn;
    gtk_init(&argc, &argv);


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //Define Action on destroy window
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(onDestroy), NULL);
    //Set title 
    gtk_window_set_title(GTK_WINDOW(window), "LastAlkalineProject");
    //Define buntons
    exeBtn = gtk_button_new_with_label("Execute");
    selectBtn = gtk_button_new_with_label("Select");
    saveBtn = gtk_button_new_with_label("Save");
    
    g_signal_connect(G_OBJECT(exeBtn), "released", G_CALLBACK(onExecute), NULL);
    g_signal_connect(G_OBJECT(selectBtn), "released", G_CALLBACK(onSelect), NULL);
    g_signal_connect(G_OBJECT(saveBtn), "released", G_CALLBACK(onSelect), NULL);
    
    //Define box's
    GtkWidget* toolsBarre = gtk_hbox_new(FALSE, 0);
    GtkWidget* displayCenter = gtk_vbox_new(FALSE,0);
    //Add button on toolsBarre
    gtk_box_pack_start(GTK_BOX(toolsBarre), selectBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), exeBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), saveBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(displayCenter), toolsBarre, FALSE, FALSE, 0);
    //Add on Window
    displayTxt(displayCenter, "hsefahflkjhrglkahjdgkjhdlfgjkhalkfhgldkjffffffffffffffffffaruhgpairhgiherihgalkrghladhrjhlkjhlajhglkjharjghjahrjgrjgjarjnejfwuenfjnwjefnnwenfljbrlkbalkrgjb");
    gtk_container_add(GTK_CONTAINER(window), displayCenter);
    gtk_widget_show_all(window);
    gtk_main();
    return EXIT_SUCCESS;
}

void onDestroy(GtkWidget *pWidget, gpointer pData)
{
    gtk_main_quit();
    exit(EXIT_SUCCESS);
}

void onExecute(GtkWidget *pWidget, gpointer pData)
{
    exit(EXIT_SUCCESS);
}
void onSelect(GtkWidget *pWidget, gpointer pData)
{
    exit(EXIT_SUCCESS);
}
void onSave(GtkWidget *pWidget, gpointer pData)
{
    exit(EXIT_SUCCESS);
}
