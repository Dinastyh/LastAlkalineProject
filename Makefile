CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Brain.o $(OBJ)/Neuron.o $(OBJ)/Debug.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Brain.o $(OBJ)/Neuron.o $(OBJ)/Debug.o -lm

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) $(CFLAGS) -o $(OBJ)/Main.o -c $(SRC)/Main.c

$(OBJ)/Brain.o : $(SRC)/NeuralNetwork/Brain.c
	$(CC) $(CFLAGS) -o $(OBJ)/Brain.o -c $(SRC)/NeuralNetwork/Brain.c

$(OBJ)/Neuron.o : $(SRC)/NeuralNetwork/Neuron.c
	$(CC) $(CFLAGS) -o $(OBJ)/Neuron.o -c $(SRC)/NeuralNetwork/Neuron.c

$(OBJ)/Debug.o : $(SRC)/NeuralNetwork/Debug.c
	$(CC) $(CFLAGS) -o $(OBJ)/Debug.o -c $(SRC)/NeuralNetwork/Debug.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
