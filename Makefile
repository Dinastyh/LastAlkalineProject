CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Network.o $(OBJ)/Training.o $(OBJ)/Bmp24.o $(OBJ)/PreProcessPicture.o $(OBJ)/DisplayPicture.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Network.o $(OBJ)/Training.o $(OBJ)/Bmp24.o $(OBJ)/PreProcessPicture.o $(OBJ)/DisplayPicture.o -lm `sdl2-config --libs --cflags`

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) $(CFLAGS) -o $(OBJ)/Main.o -c $(SRC)/Main.c

$(OBJ)/Network.o : $(SRC)/NeuralNetwork/Network.c
	$(CC) $(CFLAGS) -o $(OBJ)/Network.o -c $(SRC)/NeuralNetwork/Network.c

$(OBJ)/Debug.o : $(SRC)/NeuralNetwork/Debug.c
	$(CC) $(CFLAGS) -o $(OBJ)/Debug.o -c $(SRC)/NeuralNetwork/Debug.c

$(OBJ)/write_read_brain.o : $(SRC)/NeuralNetwork/write_read_brain.c
	$(CC) $(CFLAGS) -o $(OBJ)/write_read_brain.o -c $(SRC)/NeuralNetwork/write_read_brain.c

$(OBJ)/Training.o : $(SRC)/NeuralNetwork/Training.c
	$(CC) $(CFLAGS) -o $(OBJ)/Training.o -c $(SRC)/NeuralNetwork/Training.c

$(OBJ)/Bmp24.o : $(SRC)$(PIC)/bmp24.c
	$(CC) $(CFLAGS) -o $(OBJ)/Bmp24.o -c $(SRC)$(PIC)/bmp24.c

$(OBJ)/PreProcessPicture.o : $(SRC)$(PIC)/PreProcessPicture.c
	$(CC) $(CFLAGS) -o $(OBJ)/PreProcessPicture.o -c $(SRC)$(PIC)/PreProcessPicture.c

$(OBJ)/DisplayPicture.o : $(SRC)$(PIC)/DisplayPicture.c
	$(CC) $(CFLAGS) -o $(OBJ)/DisplayPicture.o -c $(SRC)$(PIC)/DisplayPicture.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
