#ifndef FONCTIONS
#define FONCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "stations.h"

int positive_degrees(int s, mat_graph *p_graphe);
void load_file(char * filename);
int shortest_way(int id_start, int id_end, mat_graph *p_graphe);
int get_station_start();
int get_station_end();
int get_next_station();
int * optimal_way(int * tab_id);
#endif