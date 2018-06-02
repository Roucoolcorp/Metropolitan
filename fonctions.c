#include "fonctions.h"

extern reseau RESEAU;


int get_id_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
        if(strcmp(name, (RESEAU.stations + i)->name)) {
            return (RESEAU.stations + i)->id;
        }
    }
    return -1;
}

station * get_station_from_id(int id) {
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
        if(id == (RESEAU.stations + i)->id) {
            return (RESEAU.stations + i);
        }
    }
    return NULL;
}

station * get_station_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
        if(strcmp(name, (RESEAU.stations + i)->name)) {
            return (RESEAU.stations + i);
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

void load_file(char * filename) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/etc/motd", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //while ((read = getline(&line, &len, fp)) != -1) {
    //    printf("Retrieved line of length %zu :\n", read);
    //    printf("%s", line);
    //}

    //free(RESEAU);
    read = getline(&line, &len, fp);
    if(read != -1) {
        sscanf((char*)read, "%d", &(RESEAU.nb_station));
    } else {
        printf("An error occured while reading the number of stations.\n");
        return;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}


void chemin_le_plus_court(station * s_depart)
{
	station *tab_stat = (station*) malloc(RESEAU.nb_station*sizeof(station));
    //Initialisation




}