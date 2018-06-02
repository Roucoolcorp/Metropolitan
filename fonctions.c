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

    printf("\n--- Reading the database file ---\n");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("An error occured while loading the database.\n");
        return;
    }

    //while ((read = getline(&line, &len, fp)) != -1) {
    //    printf("Retrieved line of length %zu :\n", read);
    //    printf("%s", line);
    //}


    // Reading the number of stations
    if((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &(RESEAU.nb_station));
        printf("There are %d stations\n", RESEAU.nb_station);
    } else {
        printf("An error occured while reading the number of stations.\n");
        return;
    }

    // Loading the station name and its coords
    int i = 0;
    free(RESEAU.stations);
    RESEAU.stations = malloc(sizeof(station) * RESEAU.nb_station);
    for(i = 1; i <= RESEAU.nb_station; i++) {
        if((read = getline(&line, &len, fp)) != -1) {
            station * st = malloc(sizeof(station));
            st->id = i;
            sscanf(line, "%s:%f:%f", (st->name), &(st->lng), &(st->lat));
            *(RESEAU.stations + i) = *st;
        }
    }
    printf("%d stations loaded\n", i-1);

    // Loading the number of lines
    if((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &(RESEAU.nb_ligne));
        printf("There are %d lignes\n", RESEAU.nb_ligne);
    } else {
        printf("An error occured while reading the number of lines.\n");
        return;
    }

    // Loading the lines
    i = 0;
    free(RESEAU.lignes);
    RESEAU.lignes = malloc(sizeof(ligne) * RESEAU.nb_ligne);
    for(i = 1; i <= RESEAU.nb_ligne; i++) {
        if((read = getline(&line, &len, fp)) != -1) {
            ligne * li = malloc(sizeof(ligne));
            li->id = i;
            sscanf(line, "%s:%s:%d", (li->name), &(li->couleur));
            *(RESEAU.lignes + i) = *li;

            // Read the number of stations
            read = getline(&line, &len, fp);
            int nbr_station_aller = 0;
            sscanf(line, "%d", &nbr_station_aller);
            // Read the line data
            int j;
            for(j = 0; j < nbr_station_aller; j++) {
                
            }
        }
    }
    printf("%d lines loaded\n", i-1);

    free(line);
    free(fp);
}


void chemin_le_plus_court(station * s_depart)
{
	station *tab_stat = (station*) malloc(RESEAU.nb_station*sizeof(station));
    //Initialisation




}