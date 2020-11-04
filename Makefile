CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Bmp24.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture $(OBJ)/Network.c $(OBJ)/Training.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Network.o $(OBJ)/Neuron.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Bmp24.o $(OBJ)/Training.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o -lm `sdl2-config --libs --cflags`

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) $(CFLAGS) -o $(OBJ)/Main.o -c $(SRC)/Main.c

$(OBJ)/write_read_brain.o : $(SRC)/NeuralNetwork/write_read_brain.c
    $(CC) $(CFLAGS) -o $(OBJ)/write_read_brain.o -c $(SRC)/NeuralNetwork/write_read_brain.c

$(OBJ)/Network.o : $(SRC)/NeuralNetwork/Network.c
	$(CC) $(CFLAGS) -o $(OBJ)/Network.o -c $(SRC)/NeuralNetwork/Network.c

$(OBJ)/Debug.o : $(SRC)/NeuralNetwork/Debug.c
	$(CC) $(CFLAGS) -o $(OBJ)/Debug.o -c $(SRC)/NeuralNetwork/Debug.c

$(OBJ)/write_read_brain.o : $(SRC)/NeuralNetwork/write_read_brain.c
	$(CC) $(CFLAGS) -o $(OBJ)/write_read_brain.o -c $(SRC)/NeuralNetwork/write_read_brain.c

$(OBJ)/Bmp24.o : $(SRC)$(PIC)/bmp24.c
	$(CC) -o $(OBJ)/Bmp24.o -c $(SRC)$(PIC)/bmp24.c

$(OBJ)/PreProcessPicture.o : $(SRC)$(PIC)/PreProcessPicture.c
	$(CC) -o $(OBJ)/PreProcessPicture.o -c $(SRC)$(PIC)/PreProcessPicture.c

$(OBJ)/Training.o : $(SRC)/NeuralNetwork/Training.c
	$(CC) $(CFLAGS) -o $(OBJ)/Training.o -c $(SRC)/NeuralNetwork/Training.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
