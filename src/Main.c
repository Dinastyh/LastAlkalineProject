#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "Ui/Ui.h"
#include <stdbool.h>
#include "Managers/Manager.h"
#define NUMBERPRO 4
static gchar* file = NULL;
static gchar* txt = NULL;
static GtkWidget* displayCenter;
static bool status[] = {false, false, false, false};
static gchar* nameProcessing[]= {"test", "test2","test3", "test4"};
//Funtion
void onDestroy(GtkWidget *pWidget, gpointer pData);
void onExecute(GtkWidget *pWidget, gpointer pData);
void onSelect(GtkWidget *pWidget, gpointer pData);
void onSave(GtkWidget *pWidget, gpointer pData);
void takeFolder(GtkWidget *button, GtkWidget* fileSelection);
void onProcessing(GtkWidget *pWidget, gpointer pData);
void onCheckPro(GtkWidget* button, gpointer data);
void setFile(gchar* path);
gchar* getFile();
void setTxt(gchar* text);
gchar* getTxt();
void setFile(gchar* path);

int main(int argc,char** argv)
{
    gtk_rc_parse("theme/gnome-breeze-master/Breeze-dark-gtk/gtk-2.0/gtkrc");
    GtkWidget* window;
    GtkWidget* exeBtn;
    GtkWidget* selectBtn;
    GtkWidget* saveBtn;
    GtkWidget* processingBtn;
    GtkListStore* processingStore;
    GtkCellRenderer *pCellRenderer;
    GtkTreeViewColumn *pColumn;
    GtkWidget *pListView;
    gtk_init(&argc, &argv);
    GtkWidget* proBtns[]={NULL, NULL, NULL, NULL};

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //Define Action on destroy window
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(onDestroy), NULL);
    //Set title 
    gtk_window_set_title(GTK_WINDOW(window), "LastAlkalineProject");
    //Define buntons
    exeBtn = gtk_button_new_with_label("Execute");
    selectBtn = gtk_button_new_with_label("Select");
    saveBtn = gtk_button_new_with_label("Save");
    processingBtn = gtk_button_new_with_label("Processing");

    //Define box's
    GtkWidget* toolsBarre = gtk_hbox_new(FALSE, 0);
    GtkWidget* center = gtk_hbox_new(FALSE,0);
    GtkWidget* container = gtk_vbox_new(FALSE,0);
    GtkWidget* processingBarre = gtk_vbox_new(FALSE,0);
    gtk_container_set_border_width(GTK_CONTAINER(processingBarre), 10);
    displayCenter = gtk_vbox_new(FALSE,0); 

    //Connect tool's barre
    g_signal_connect(G_OBJECT(exeBtn), "released", G_CALLBACK(onExecute), NULL);
    g_signal_connect(G_OBJECT(selectBtn), "released", G_CALLBACK(onSelect), NULL);
    g_signal_connect(G_OBJECT(saveBtn), "released", G_CALLBACK(onSave), NULL);
    g_signal_connect(G_OBJECT(processingBtn),"released", G_CALLBACK(onProcessing), NULL);

    //Add button on toolsBarre
    gtk_box_pack_start(GTK_BOX(toolsBarre), selectBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), exeBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), saveBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), processingBtn, FALSE, FALSE, 0);

    //Define butons + connect to callback
    for(int i = NUMBERPRO-1; i> -1; i--)
    {
        proBtns[i] = gtk_check_button_new_with_label(nameProcessing[i]);
        g_signal_connect(G_OBJECT(proBtns[i]), "released", G_CALLBACK(onCheckPro), NULL);
        gtk_box_pack_start(GTK_BOX(processingBarre), proBtns[i], FALSE, FALSE, 0);
    }

    //Add box in container
    gtk_box_pack_start(GTK_BOX(container), toolsBarre, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(center), processingBarre, FALSE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(center), displayCenter, TRUE, TRUE,0);
    gtk_box_pack_start(GTK_BOX(container), center, TRUE, TRUE, 0);

    //Add on Window
    gtk_container_add(GTK_CONTAINER(window), container);
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
    char* output = managerExec(getFile(), status,NUMBERPRO);
    setTxt(output);
    displayTxt(displayCenter, output);
}
void onSelect(GtkWidget *pWidget, gpointer pData)
{
    GtkWidget* fileSelection =  gtk_file_selection_new(g_locale_to_utf8("Select a file", -1, NULL, NULL, NULL));
    gtk_widget_show(fileSelection);
    gtk_window_set_modal(GTK_WINDOW(fileSelection), TRUE);
    g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fileSelection)->ok_button), "released", G_CALLBACK(takeFolder), fileSelection);
    g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(fileSelection)->cancel_button), "released", G_CALLBACK(gtk_widget_destroy), fileSelection);
}

void takeFolder(GtkWidget* button, GtkWidget* fileSelection)
{ 
    const gchar* path;
    path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(fileSelection));
    setFile(path);
    //If the file is not a Bmp24
    if(!loadPicture(path))
    {
        GtkWidget* dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(fileSelection), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "You have selected :\n%s\nThis file is not a Bmp24, please try another file", path);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(fileSelection);
        return;
    }
    gtk_widget_destroy(fileSelection);
    displayPictureGTK(displayCenter, path);
}

void onProcessing(GtkWidget *pWidget, gpointer pData)
{
    if(!loadPicture(getFile()))
    {
        GtkWidget* dialog;
        GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Please select a file");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
        return;
    }
    preview(getFile(), status, NUMBERPRO);

}
void onSave(GtkWidget *pWidget, gpointer pData)
{
    if(getTxt()==NULL)
    {
        GtkWidget* dialog;
        GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "You must run the texe detection before save it");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
        return;
    }
    FILE* saveFile = fopen("out.lap", "w");
    if(saveFile != NULL)
    {
        fputs(getTxt(), saveFile);
        fclose(saveFile);
    }
    else
    {
        GtkWidget* dialog;
        GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "File can't be save, please check if you have the permission to to it");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_destroy(window);
        return;
    }

}

void onCheckPro(GtkWidget* button, gpointer data)
{
    size_t index = 0;
    gchar* name = gtk_button_get_label(GTK_BUTTON(button));
    for(size_t i =0; i<NUMBERPRO; i++)
    {
        if(name == nameProcessing[i])
        {
            index = i;
            break;
        }
    }
    status[index] = !status[index];
}

void setFile(gchar* path)
{
    file = path;
}

gchar* getFile()
{
    return file;
}

void setTxt(gchar* text)
{
    txt = text;
}

gchar* getTxt()
{
    return txt;
}
