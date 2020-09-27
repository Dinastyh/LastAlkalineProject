CC = gcc
EXEC = LastAlakalineProject
OBJ = obj
SRC = src

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o
	$(CC) -o $(EXEC) $(OBJ)/Main.o

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) -o $(OBJ)/Main.o -c $(SRC)/Main.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
