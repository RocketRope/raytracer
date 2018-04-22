

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

FLAGS := -std=c++17 -Wall -Wextra -pedantic -O3 -I$(INC_DIR)
SFML_LIB := -lsfml-graphics-s -lfreetype -ljpeg -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32

all : main.exe
	
run : all
	./main.exe

main.exe : main.cpp $(OBJ)
	g++ $(FLAGS) $^ -o $@ $(SFML_LIB)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc $(INC_DIR)/%.h
	g++ $(FLAGS) $< -c -o $@



