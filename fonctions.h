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
int degre_positif(int s, mat_graphe *p_graphe);
void load_file(char * filename);
void chemin_le_plus_court(station * s_depart);

#endif