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

void processingBasic(Picture* picture, bool status[], size_t len)
{

    blackAndWhite(picture);
    if(status[0])
        {grayscale(picture);}
    if(status[1])
        {strengthenEdge(picture);}
    if(status[2])
        {detectEdge(picture);}
    if(status[3])
        {upContrast(picture);}
    if(status[4])
        {pushBack(picture);}
    if(status[5])
        {lowPassFilter(picture, 3, 3);}
    if(status[6])
        invert(picture);
    if(status[7])
        {grayscaleLuminate(picture);}
    if(status[8])
        {*picture = rotate(*picture, 90.0);}
    if(status[9])
        {*picture = rotate(*picture, 180.0);}
    if(status[10])
        {detectAngle(picture);}
} 

void preview(const char* path, bool status[], size_t len)
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
    remove("tmp.bmp");
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

char* managerExec(const char* path, bool status[], size_t lenStatus)
{
    char* output = malloc(sizeof(char));
    output[0]='\0';
    Picture picture = newPicture(path, "tmp.bmp");
    Network net = readNetwork("network096Regu.txt");
    processingBasic(&picture, status, lenStatus);
    Data data = createData(&picture);
    char back = '\n'; 
    char space = ' ';
    size_t len = 0;
    char* control = NULL;
    for(int i = 0; i< data.length; i++)
    {
        //Check for add \n
        if(i!=0){
            len++;
            control = realloc(output, sizeof(char)*(len+1));
            if(control)
            {
                output = control;
                control = NULL;
            }
            output[len-1]=back;
            output[len]='\0';
        }
        //open line
        Data* line = &((Data*)(data.thing))[i];
        for(int j = 0; j< line->length; j++)
        {
            //Check pour add space
            if(j!=0){
                len++;
                control = realloc(output, sizeof(char)*(len+1));
                if(control)
                {
                    output = control;
                    control = NULL;
                }
                output[len-1]=space;
                output[len]='\0';
            }
            //open word
            Data* word = &((Data*)(line->thing))[j];
            for(int k=0; k<word->length; k++)
            {
                //open cheractere
                Data* charactere = &((Data*)(word->thing))[k];
                int result = forwardPropagationTest(&net, charactere->thing);
                //Filtre result
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
                        case 3: c = '?'; 
                                break;
                        default:
                                c = '/'; //error if c is /
                                break;
                    }
                }
                //Append result filtre
                len++;
                control = realloc(output, sizeof(char)*(len+1));
                if(control)
                {
                    output = control;
                    control = NULL;
                }
                output[len-1]=c;
                output[len] = '\0';
            }
        }
    }

    freeNetwork(&net);
    return output;
}
