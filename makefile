all : clean comp run clean

comp : main.o fonctions.o graph.o stations.o
	gcc -o exec main.o fonctions.o graph.o stations.o -Wall -lm `sdl-config --cflags --libs` -lSDL_ttf

main.o : main.c
	gcc -o main.o -c main.c -Wall -lm `sdl-config --cflags --libs` -lSDL_ttf

fonctions.o : fonctions.c
	gcc -o fonctions.o -c fonctions.c -Wall -lm

graph.o : graph.c
	gcc -o graph.o -c graph.c -Wall -lm

stations.o : stations.c
	gcc -o stations.o -c stations.c -Wall -lm

clean : 
	rm -rf *.o

clear :
	clear
	
run :
	./exec