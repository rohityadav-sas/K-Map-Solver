SOURCES = ./src/fivevar.cpp ./src/fourvar.cpp ./src/grid.cpp ./src/kmapsolver.cpp ./src/main.cpp ./src/threevar.cpp ./src/twovar.cpp

default:
	g++ $(SOURCES) -o game.exe -g -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
	./game.exe