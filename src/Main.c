#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "Ui/Ui.h"
#include "Managers/Manager.h"
#define true 1
#define false 0
#define bool usigned int
static gchar* file;
static gchar* txt;
static GtkWidget* displayCenter;
static bool[] status = {false, false, false, false};
static size_t sizetProcessing = 4;
//Funtion
void onDestroy(GtkWidget *pWidget, gpointer pData);
void onExecute(GtkWidget *pWidget, gpointer pData);
void onSelect(GtkWidget *pWidget, gpointer pData);
void onSave(GtkWidget *pWidget, gpointer pData);
void takeFolder(GtkWidget *button, GtkWidget* fileSelection);
void onProcessing(GtkWidget *pWidget, gpointer pData);
void setFile(gchar* path);
gchar* getFile();
void setTxt(gchar* text);
gchar* getTxt();
void setFile(gchar* path);

enum {
    TEXT_COLUMN,
    TOGGLE_COLUMN,
    N_COLUMN
};

int main(int argc,char** argv)
{
    setFile(NULL);
    GtkWidget* window;
    GtkWidget* exeBtn;
    GtkWidget* selectBtn;
    GtkWidget* saveBtn;
    GtkWidget* processingBtn;
    GtkWidget* processingBtn;
    GtkListStore* processingStore;
    GtkCellRenderer *pCellRenderer;
    GtkTreeViewColumn *pColumn;
    GtkWidget *pListView;
    gtk_init(&argc, &argv);
    char* nameProcessing[]= {"test", "test2","test3", "test4"};

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
    g_signal_connect(G_OBJECT(saveBtn), "released", G_CALLBACK(onSave), NULL);
    g_signal_connect(G_OBJECT(processingBtn),"released", G_CALLBACK(onProcessing), NULL);
    //Define Store
    processingStore = gtk_list_store_new(N_COLUMN,G_TYPE_STRING ,G_TYPE_BOOLEAN);
    //Adding element in store
    for(size_t i= 0;i<sizetProcessing; i++) 
    {
        GtkTreeIter pIter;
        //char* name= nameProcessing[i];
        gtk_list_store_append(processingStore, &pIter);
        gtk_list_store_set(processingStore, &pIter,TEXT_COLUMN ,nameProcessing[i],TOGGLE_COLUMN,FALSE, -1);
    }
    pListView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(processingStore));
    //Adding first Column to the view
    pCellRenderer = gtk_cell_renderer_text_new();
    pColumn = gtk_tree_view_column_new_with_attributes("Processing", pCellRenderer,"text",TEXT_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);
    //Adding second column to the view
    pCellRenderer = gtk_cell_renderer_toggle_new();
    pColumn = gtk_tree_view_column_new_with_attributes("Check", pCellRenderer,"active",TOGGLE_COLUMN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);

    //Define box's
    GtkWidget* toolsBarre = gtk_hbox_new(FALSE, 0);
    GtkWidget* center = gtk_hbox_new(FALSE,0);
    GtkWidget* container = gtk_vbox_new(FALSE,0);
    displayCenter = gtk_vbox_new(FALSE,0);
    //Add button on toolsBarre
    gtk_box_pack_start(GTK_BOX(toolsBarre), selectBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), exeBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), saveBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolsBarre), saveBtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(container), toolsBarre, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(center), displayCenter, FALSE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(center), pListView, FALSE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(container), center, FALSE, FALSE, 0);

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
    exit(EXIT_SUCCESS);
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
    displayPictureGTK(displayCenter, path);
}

void onProcessing(GtkWidget *pWidget, gpointer pData)
{
    if(!loadPicture(getFile()))
    {
        GtkWidget* dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(fileSelection), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Please select a file");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    preview(getFile(), status, sizetProcessing);

}
void onSave(GtkWidget *pWidget, gpointer pData)
{
    exit(EXIT_SUCCESS);
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
