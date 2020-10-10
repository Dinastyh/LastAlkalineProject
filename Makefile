CC = gcc
EXEC = LastAlakalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Bmp.o
	$(CC) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Bmp.o

$(OBJ)/Bmp.o : $(SRC)$(PIC)/bmp24.c
	$(CC) -o $(OBJ)/Bmp.o -c $(SRC)$(PIC)/bmp24.c 
	
$(OBJ)/Main.o : $(SRC)$(PIC)/Main.c $(SRC)$(PIC)/bmp24.h
	$(CC) -o $(OBJ)/Main.o -c $(SRC)$(PIC)/Main.c 

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
