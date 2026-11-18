all: compile link

compile:
	g++ -I ./include/ -o ./lib/Shape.o -c ./src/Shape.cpp
	g++ -I ./include/ -o ./lib/Rectangle.o -c ./src/Rectangle.cpp
	g++ -I ./include/ -o ./lib/Triangle.o -c ./src/Triangle.cpp
	g++ -I ./include/ -o ./lib/Star.o -c ./src/Star.cpp
	g++ -I ./include/ -o ./lib/ShapeNode.o -c ./src/ShapeNode.cpp
	g++ -I ./include/ -o ./lib/ShapeList.o -c ./src/ShapeList.cpp
	g++ -I ./include/ -o ./lib/MainNode.o -c ./src/MainNode.cpp
	g++ -I ./include/ -o ./lib/MainList.o -c ./src/MainList.cpp
	g++ -I ./include/ -o ./lib/Screen.o -c ./src/Screen.cpp
	g++ -I ./include/ -o ./lib/Manager.o -c ./src/Manager.cpp
	g++ -I ./include/ -o ./lib/main.o -c ./src/main.cpp

link:
	g++ ./lib/*.o -o ./bin/program.exe

run:
	./bin/program.exe

clean:
	del lib\*.o
	del bin\*.exe