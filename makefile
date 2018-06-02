all : clean comp clear run clean

comp : main.o fonctions.o graph.o struct.o
	gcc -o exec main.o fonctions.o graph.o struct.o -Wall -lm

main.o : main.c
	gcc -o main.o -c main.c -Wall -lm

fonctions.o : fonctions.c
	gcc -o fonctions.o -c fonctions.c -Wall -lm

graph.o : graph.c
	gcc -o graph.o -c graph.c -Wall -lm

struct.o : struct.c
	gcc -o struct.o -c struct.c -Wall -lm

clean : 
	rm -rf *.o

clear :
	clear
	
run :
	./exec