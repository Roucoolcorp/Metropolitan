#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "graph.h"
#include "stations.h"

reseau RESEAU;
mat_graph * MAT_RESEAU;

int main() {
	load_file("bdd.txt");
	int id_station_start, id_station_end;
	id_station_start = get_station_start();
	id_station_end = get_station_end();
	/* char * name_start = malloc(100);
    printf("Where are you ?\n");
    scanf("%[^\n]", name_start);
    char * name_end = malloc(100);
    printf("Where are you going?\n");
    printf("a\n");
    scanf("%[^\n]", name_end);
    printf("b\n");
    id_station_start = get_id_from_name(name_start);
    id_station_end = get_id_from_name(name_end);
    free(name_end);
	free(name_start); */
	shortest_way(id_station_start, id_station_end, MAT_RESEAU);
	return 0;
}