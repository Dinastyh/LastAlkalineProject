CC = gcc
EXEC = LastAlkalineProject
OBJ = obj
SRC = src

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/list_io.o
	$(CC) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/list_io.o

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) -o $(OBJ)/Main.o -c $(SRC)/Main.c

$(OBJ)/list_io.o : $(SRC)/list_io/list_io.c
	$(CC) -o $(OBJ)/list_io.o -c $(SRC)/list_io/list_io.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
