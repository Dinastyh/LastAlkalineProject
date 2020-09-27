CC = gcc
EXEC = LastAlakalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Bmp.o
	$(CC) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Bmp.o

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) -o $(OBJ)/Main.o -c $(SRC)/Main.c

$(OBJ)/Bmp.o : $(SRC)$(PIC)/Bmp.c
	$(CC) -o $(OBJ)/Bmp.o -c $(SRC)$(PIC)/Bmp.c

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
