#ifndef FONCTIONS
#define FONCTIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"
#include "stations.h"

int get_id_from_name(char * name);
station * get_station_from_id(int id);
station * get_station_from_name(char * name);
ligne * get_line_from_station_name(char * name);
int positive_degrees(int s, mat_graph *p_graphe);
void load_file(char * filename);
void shortest_way(int id_start, int id_end, mat_graph *p_graphe);
int get_station_start();
int get_station_end();
#endif