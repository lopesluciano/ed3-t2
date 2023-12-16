SRC = ./src
INCLUDE = ./include
OBJ = ./obj
BIN = ./bin

all:
	g++ $(SRC)/*.cpp Main.cpp -I $(INCLUDE) -o $(BIN)/programaTrab

run:
	$(BIN)/programaTrab
