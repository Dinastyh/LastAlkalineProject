CC = gcc
EXEC = LastAlkalineProject
OBJ = obj
SRC = src

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Brain.o $(OBJ)/Neuron.o
	$(CC) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Brain.o $(OBJ)/Neuron.o -lm

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) -o $(OBJ)/Main.o -c $(SRC)/Main.c

$(OBJ)/Brain.o : $(SRC)/NeuralNetwork/Brain.c
	$(CC) -o $(OBJ)/Brain.o -c $(SRC)/NeuralNetwork/Brain.c

$(OBJ)/Neuron.o : $(SRC)/NeuralNetwork/Neuron.c
	$(CC) -o $(OBJ)/Neuron.o -c $(SRC)/NeuralNetwork/Neuron.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
