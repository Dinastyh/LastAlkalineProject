CC = gcc
EXEC = LastAlakalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Bmp.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o
	$(CC) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Bmp.o $(OBJ)/DisplayPicture.o $(OBJ)/PreProcessPicture.o `sdl2-config --libs --cflags` 

$(OBJ)/Bmp.o : $(SRC)$(PIC)/bmp24.c
	$(CC) -o $(OBJ)/Bmp.o -c $(SRC)$(PIC)/bmp24.c 

$(OBJ)/DisplayPicture.o : $(SRC)$(PIC)/DisplayPicture.c
	$(CC) -o $(OBJ)/DisplayPicture.o -c $(SRC)$(PIC)/DisplayPicture.c

$(OBJ)/PreProcessPicture.o : $(SRC)$(PIC)/PreProcessPicture.c
	$(CC) -o $(OBJ)/PreProcessPicture.o -c $(SRC)$(PIC)/PreProcessPicture.c

$(OBJ)/Main.o : $(SRC)/Main.c $(SRC)$(PIC)/bmp24.h $(SRC)$(PIC)/DisplayPicture.h $(SRC)$(PIC)/PreProcessPicture.h
	$(CC) -o $(OBJ)/Main.o -c $(SRC)/Main.c 

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
