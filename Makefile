CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Ui.o $(OBJ)/Manager.o $(OBJ)/Bmp24.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Network.o $(OBJ)/Training.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Ui.o $(OBJ)/Manager.o $(OBJ)/Bmp24.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Network.o $(OBJ)/Training.o -lm `pkg-config --cflags --libs gtk+-2.0` -lm `sdl2-config --libs --cflags`

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

$(OBJ)/Network.o : $(SRC)/NeuralNetwork/Network.c
	$(CC) $(CFLAGS) -o $(OBJ)/Network.o -c $(SRC)/NeuralNetwork/Network.c

$(OBJ)/Debug.o : $(SRC)/NeuralNetwork/Debug.c
	$(CC) $(CFLAGS) -o $(OBJ)/Debug.o -c $(SRC)/NeuralNetwork/Debug.c

$(OBJ)/write_read_brain.o : $(SRC)/NeuralNetwork/write_read_brain.c
	$(CC) $(CFLAGS) -o $(OBJ)/write_read_brain.o -c $(SRC)/NeuralNetwork/write_read_brain.c

$(OBJ)/Training.o : $(SRC)/NeuralNetwork/Training.c
	$(CC) $(CFLAGS) -o $(OBJ)/Training.o -c $(SRC)/NeuralNetwork/Training.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
