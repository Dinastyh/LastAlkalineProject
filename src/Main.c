#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "Ui/Ui.h"
#include <stdbool.h>
#include "Managers/Manager.h"
#define NUMBERPRO 11
static gchar* file = NULL;
static gchar* txt = NULL;
static GtkWidget* displayCenter;
static bool status[NUMBERPRO] = {0};
static gchar* nameProcessing[]= {"Gray scale", "Strenghen edge","Detect Edge",
    "Up contrast", "Push Back", "Low pass filter", "Invert",
    "Gray scale luminate", "Rotate 90", "Rotate 180", "Automatic rotate"};
static GtkWidget* proBtns[]={NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,NULL, NULL};
static GtkWidget* exeBtn;
static GtkWidget* selectBtn;
static GtkWidget* saveBtn;
static GtkWidget* processingBtn;
//Funtion
void onDestroy(GtkWidget *pWidget, gpointer pData);
void onExecute(GtkWidget *pWidget, gpointer pData);
void onSelect(GtkWidget *pWidget, gpointer pData);
void onSave(GtkWidget *pWidget, gpointer pData);
void onProcessing(GtkWidget *pWidget, gpointer pData);
void onCheckPro(GtkWidget* button, gpointer data);
void setFile(gchar* path);
gchar* getFile();
void setTxt(gchar* text);
gchar* getTxt();
void setFile(gchar* path);

int main(int argc,char** argv)
{
    GtkWidget* window; 
    GtkListStore* processingStore;
    GtkCellRenderer *pCellRenderer;
    GtkTreeViewColumn *pColumn;
    GtkWidget *pListView;
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
    processingBtn = gtk_button_new_with_label("Processing");

    //Define box's
    GtkWidget* toolsBarre = gtk_hbox_new(FALSE, 0);
    GtkWidget* center = gtk_hbox_new(FALSE,0);
    GtkWidget* container = gtk_vbox_new(FALSE,0);
    GtkWidget* processingBarre = gtk_vbox_new(FALSE,0);
    gtk_container_set_border_width(GTK_CONTAINER(processingBarre), 10);
    displayCenter = gtk_vbox_new(FALSE,0);
    //Disable some btn
    gtk_widget_set_sensitive(exeBtn, FALSE);
    gtk_widget_set_sensitive(saveBtn, FALSE);
    gtk_widget_set_sensitive(processingBtn, FALSE);

    //Connect tool's barre
    g_signal_connect(G_OBJECT(exeBtn), "released", G_CALLBACK(onExecute), window);
    g_signal_connect(G_OBJECT(selectBtn), "released", G_CALLBACK(onSelect), window);
    g_signal_connect(G_OBJECT(saveBtn), "released", G_CALLBACK(onSave), window);
    g_signal_connect(G_OBJECT(processingBtn),"released", G_CALLBACK(onProcessing), window);

    //Add button on toolsBarre
    gtk_box_pack_start(GTK_BOX(toolsBarre), selectBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), exeBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), saveBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), processingBtn, FALSE, FALSE, 0);

    //Define butons + connect to callback
    for(size_t i = 0; i < NUMBERPRO; i++)
    {
        proBtns[i] = gtk_check_button_new_with_label(nameProcessing[i]);
        gtk_widget_set_sensitive(proBtns[i], FALSE);
        g_signal_connect(G_OBJECT(proBtns[i]), "released", G_CALLBACK(onCheckPro), NULL);
        gtk_box_pack_start(GTK_BOX(processingBarre), proBtns[i], FALSE, FALSE, 0);
    }

    for(size_t i = 0; i < NUMBERPRO; i++)
    {
        status[i] = false;
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
    if(!loadPicture(getFile()))
    {
        GtkWidget* dialog;
        GtkWidget* window = pData;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
         GTK_BUTTONS_OK, "Please select a file");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    char* output = managerExec(getFile(), status, NUMBERPRO);
    setTxt(output);
    displayTxt(displayCenter, output);
    setFile(NULL);
    gtk_widget_set_sensitive(exeBtn, FALSE);
    gtk_widget_set_sensitive(selectBtn,TRUE);
    gtk_widget_set_sensitive(saveBtn, TRUE);
    gtk_widget_set_sensitive(processingBtn, FALSE);
    for(size_t i = 0; i < NUMBERPRO; i++)
    {
        gtk_widget_set_sensitive(proBtns[i], FALSE);
    }
}

void onSelect(GtkWidget *pWidget, gpointer pData)
{
    GtkWidget* window = pData;
    GtkWidget* fileSelection = gtk_file_chooser_dialog_new("Selection File", window, GTK_FILE_CHOOSER_ACTION_OPEN,
     ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if(gtk_dialog_run(GTK_DIALOG(fileSelection)) == GTK_RESPONSE_ACCEPT)
    {
        gchar* path = NULL;
        path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileSelection));
        if(!loadPicture(path))
        {
            GtkWidget* dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(fileSelection), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
             "You have selected :\n%s\nThis file is not a Bmp24, please try another file", path);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            gtk_widget_destroy(fileSelection);
            setFile(NULL);
            return;
        }
        setFile(path);
        gtk_widget_destroy(fileSelection);
        for(size_t i = 0; i < NUMBERPRO; i++)
        {
            gtk_widget_set_sensitive(proBtns[i], TRUE);
        }
        gtk_widget_set_sensitive(selectBtn, FALSE);
        gtk_widget_set_sensitive(processingBtn, TRUE);
        gtk_widget_set_sensitive(exeBtn, TRUE);
        displayPictureGTK(displayCenter, path);
    }
    else
    {
        gtk_widget_destroy(fileSelection);
    }
}

void onProcessing(GtkWidget *pWidget, gpointer pData)
{
    if(!getFile())
    {
        GtkWidget* dialog;
        GtkWidget* window = pData;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
         "Please select a file");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        setFile(NULL);
        return;
    }
    preview(getFile(), status, NUMBERPRO);
}
void onSave(GtkWidget *pWidget, gpointer pData)
{
    GtkWidget* window = pData;
    if(getTxt()==NULL)
    {
        GtkWidget* dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
         "You must run the texe detection before save it");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    GtkWidget* fileSelection = gtk_file_chooser_dialog_new("Selection File", window, 
            GTK_FILE_CHOOSER_ACTION_SAVE, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Save"), GTK_RESPONSE_ACCEPT, NULL);
    if(gtk_dialog_run(GTK_DIALOG(fileSelection)) == GTK_RESPONSE_ACCEPT)
    {
        gchar* path = NULL;
        path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileSelection));
        FILE* saveFile = fopen(path, "w");
        if(saveFile != NULL)
        {
            fputs(getTxt(), saveFile);
            fclose(saveFile);
        }
        else
        {
            GtkWidget* dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
             "File can't be save, please check if you have the permission to to it");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            gtk_widget_destroy(fileSelection);
            return;
        }
    }
    gtk_widget_destroy(fileSelection);
}

void onCheckPro(GtkWidget* button, gpointer data)
{
    gchar* name = gtk_button_get_label(GTK_BUTTON(button));
    for(size_t i =0; i<NUMBERPRO; i++)
    {
        if(strcmp(name,nameProcessing[i]) == 0)
        {
            status[i] = !(status[i]);
            break;
        }
    }
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
