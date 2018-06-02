#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern reseau RESEAU;


int get_id_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU->nb_station; i++) {
        if(strcmp(name, *(RESEAU + i)->name)) {
            return *(RESEAU+i)->id;
        }
    }
    return -1;
}

station * get_station_from_id(int id) {
    int i;
    for(i = 0; i < RESEAU->nb_station; i++) {
        if(id == *(RESEAU + i)->id) {
            return (RESEAU+i);
        }
    }
    return NULL;
}

station * get_station_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU->nb_station; i++) {
        if(strcmp(name, *(RESEAU + i)->name)) {
            return (RESEAU+i);
        }
    }
    return NULL;
}

int degre_positif(int s, mat_graphe *p_graphe)
{
    int degre=0;
    int i;
    for(i=0; i< p_graphe->nb_colonnes;i++)
    {
        if(recuperer_element(p_graphe,s,i)!=-1)
	{
            degre++;
        }
    }
    return degre;
}


void chemin_le_plus_court(station * s_depart, reseau * R)
{
	station *tab_stat = (station*) malloc(R->nb_station*sizeof(station));
    //Initialisation




}