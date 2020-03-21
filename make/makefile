##################################################################################
#
# FILENAME : makefile
# 
# AUTHOR : epapdev
#
# DATE : 2-2-18
#
# COPYRIGHT : 2007, ARICENT INC.
#
#################################################################################

CC = g++
CFLAGS = -c -g -Wall -Wunused
IFLAGS = -I$(INC)

SRC = ../src
BIN = ../bin
OBJ = ../obj
LIB = ../lib
INC = ../inc
DAT = ../dat

all: $(BIN)/billing.out
    
$(BIN)/billing.out: $(OBJ)/main.o $(OBJ)/functions.o  
	$(CC) $(OBJ)/main.o $(OBJ)/functions.o  -o $(BIN)/billing.out

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC)/main.cpp
	mv main.o $(OBJ)/

$(OBJ)/functions.o: $(SRC)/functions.cpp
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC)/functions.cpp
	mv functions.o $(OBJ)/

clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/*
