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

void processingBasic(Picture* picture, unsigned int status[], size_t len)
{
    blackAndWhite(picture);
} 

void preview(const char* path, unsigned int status[], size_t len)
{
    Picture picture = newPicture(path, "tmp.bmp");
    //PreProcesseing
    processingBasic(&picture, status, len);
    savePicture(&picture);
    //Load picture to display
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Preview"); 
    char* newPath = malloc(100*sizeof(char));
    //New Path construction
    getcwd(newPath, 100);
    strcat(newPath, "/");
    strcat(newPath, picture.name);
    //Display picutre from the new path
    GtkWidget *gPicture = gtk_image_new_from_file(newPath);
    GtkWidget* box = gtk_vbox_new(FALSE, 0);
    GtkWidget* exitBtn = gtk_button_new_with_label("Exit");
    g_signal_connect(G_OBJECT(exitBtn), "released", G_CALLBACK(onExit), window);
    gtk_box_pack_start(GTK_BOX(box), gPicture, TRUE, TRUE,0);
    gtk_box_pack_start(GTK_BOX(box), exitBtn, FALSE, FALSE,0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    //remove(newPath);
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

char* managerExec(const char* path, unsigned int status[], size_t len)
{
    Picture picture = newPicture(path, "tmp.bmp");
    Network net = readNetwork("network096Regu.txt");
    processingBasic(&picture, status, len);
    Data data = createData(&picture);
    char back = '\n';
    char space = ' ';
    char* output = ""; 
    for(int i = 0; i< data.length; i++)
    {
        if(i!=0)
            strncat(output,&back,1);
        Data* line = data.thing+i;
        for(int j = 0; j< line->length; j++)
        {
            if(j!=0)
                strncat(output,&space,1);
            Data* word = line->thing+j;
            for(int k=0; k<word->length; k++)
            {
                Data* charactere = word->thing+k;
                int result = forwardPropagationTest(&net, charactere->thing);
                char c;
                if(result >= 4 && result <= 13)
                {
                    c = result + 44; // '0' - 4
                }
                else if(result >= 14 && result <= 39)
                {
                    c = result + 51;
                }
                else if(result >= 40 && result <= 65)
                {
                    c = result + 57;
                }
                else
                {
                    switch (result)
                    {
                        case 0:
                            c = '!';
                            break;
                        case 1:
                            c = '.';
                            break;
                        case 2:
                            c = ':';
                            break;
                        case 3:
                            c = '?';
                            break;
                        default:
                            c = '/'; //error if c is /
                            break;
                    }
                }
                strncat(output,&c,1);
            }
        }
    }
    freeNetwork(&net);
    return output;
}
