CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
EXEC = LastAlkalineProject
OBJ = obj
SRC = src
PIC = /PictureUtils

all : $(EXEC)

$(EXEC) : $(OBJ)/Main.o $(OBJ)/Ui.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)/Main.o $(OBJ)/Ui.o `pkg-config --cflags --libs gtk+-2.0`

$(OBJ)/Main.o : $(SRC)/Main.c
	$(CC) $(CFLAGS) -o $(OBJ)/Main.o -c $(SRC)/Main.c `pkg-config --cflags --libs gtk+-2.0`

$(OBJ)/Ui.o : $(SRC)/Ui/Ui.c
	$(CC) $(CFLAGS) -o $(OBJ)/Ui.o -c $(SRC)/Ui/Ui.c `pkg-config --cflags --libs gtk+-2.0`

clearOBJ :
	rm -r $(OBJ)/*.o

clearAll : clearOBJ
	rm $(EXEC)
