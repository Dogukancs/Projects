all: compile link

compile:
	g++ -I ./include/ -o ./lib/SayiDugumu.o -c ./src/SayiDugumu.cpp
	g++ -I ./include/ -o ./lib/SatirDugumu.o -c ./src/SatirDugumu.cpp
	g++ -I ./include/ -o ./lib/Matris.o -c ./src/Matris.cpp
	g++ -I ./include/ -o ./lib/MatrisDugumu.o -c ./src/MatrisDugumu.cpp
	g++ -I ./include/ -o ./lib/BagliListe.o -c ./src/BagliListe.cpp
	g++ -I ./include/ -o ./lib/KonsolArayuz.o -c ./src/KonsolArayuz.cpp
	g++ -I ./include/ -o ./lib/main.o -c ./src/main.cpp

link:
	g++ -static ./lib/*.o -o ./bin/program.exe

run:
	./bin/program.exe

clean:
	del lib\*.o
	del bin\*.exe

	