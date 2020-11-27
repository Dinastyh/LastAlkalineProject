CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Ui.o $(OBJ)/Manager.o $(OBJ)/Bmp24.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Ui.o $(OBJ)/Manager.o $(OBJ)/Bmp24.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o `pkg-config --cflags --libs gtk+-2.0` -lm `sdl2-config --libs --cflags`

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) $(CFLAGS) -o $(OBJ)/Main.o -c $(SRC)/Main.c `pkg-config --cflags --libs gtk+-2.0`

$(OBJ)/Ui.o : $(SRC)/Ui/Ui.c
	$(CC) $(CFLAGS) -o $(OBJ)/Ui.o -c $(SRC)/Ui/Ui.c `pkg-config --cflags --libs gtk+-2.0`

$(OBJ)/Manager.o : $(SRC)/Managers/Manager.c
	$(CC) $(CFLAGS) -o $(OBJ)/Manager.o -c $(SRC)/Managers/Manager.c `pkg-config --cflags --libs gtk+-2.0`

$(OBJ)/Bmp24.o : $(SRC)$(PIC)/Bmp24.c
	$(CC) $(CFLAGS) -o $(OBJ)/Bmp24.o -c $(SRC)$(PIC)/Bmp24.c -lm `sdl2-config --libs --cflags`

$(OBJ)/DisplayPicture.o : $(SRC)$(PIC)/DisplayPicture.c
	$(CC) $(CFLAGS) -o $(OBJ)/DisplayPicture.o -c $(SRC)$(PIC)/DisplayPicture.c -lm `sdl2-config --libs --cflags`

$(OBJ)/PreProcessPicture.o : $(SRC)$(PIC)/PreProcessPicture.c
	$(CC) $(CFLAGS) -o $(OBJ)/PreProcessPicture.o -c $(SRC)$(PIC)/PreProcessPicture.c -lm `sdl2-config --libs --cflags`

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
