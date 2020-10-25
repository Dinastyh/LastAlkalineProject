CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Network.o $(OBJ)/Training.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Debug.o $(OBJ)/write_read_brain.o $(OBJ)/Network.o $(OBJ)/Training.o -lm

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

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
