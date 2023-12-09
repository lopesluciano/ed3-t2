SRC = ./src
INCLUDE = ./include
OBJ = ./obj
BIN = ./bin

all:
	g++ $(SRC)/*.cpp -I $(INCLUDE) -o $(BIN)/programaTrab

run:
	$(BIN)/programaTrab
