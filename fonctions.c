#include "fonctions.h"

extern reseau RESEAU;
extern mat_graph * MAT_RESEAU;

int get_id_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
        if(strcmp(name, (RESEAU.stations + i)->name) == 0) {
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
        if(strcmp(name, (RESEAU.stations + i)->name) == 0) {
            return (RESEAU.stations + i);
        }
    }
    return NULL;
}

int degre_positif(int s, mat_graph *p_graphe)
{
    int degre=0;
    int i;
    for(i=0; i< p_graphe->nbrCols;i++)
    {
        if(getElement(p_graphe,s,i)!=-1)
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

    // Cleaning the mat graphe
    free(MAT_RESEAU);

    // Opening the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("An error occured while loading the database.\n");
        return;
    }


    // Reading the number of stations
    if((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &(RESEAU.nb_station));
        printf("There are %d stations\n", RESEAU.nb_station);
    } else {
        printf("An error occured while reading the number of stations.\n");
        return;
    }

    // Allocating mat graph
    MAT_RESEAU = allocateMatrix(RESEAU.nb_station, RESEAU.nb_station); 

    // Loading the station name and its coords
    int i;
    free(RESEAU.stations);
    RESEAU.stations = malloc(sizeof(station) * RESEAU.nb_station);
    for(i = 0; i < RESEAU.nb_station; i++) {
        if((read = getline(&line, &len, fp)) != -1) {
            //station * st = malloc(sizeof(station));
            station st;
            st.name = malloc(100);
            st.id = i;
            sscanf(line, "%[^:]:%f:%f", (st.name), &(st.lng), &(st.lat));
            *(RESEAU.stations + i) = st;
        }
    }
    printf("%d stations loaded\n", i);

    // Feeding the first mat graph data
    feedMatrix(MAT_RESEAU, INT_MAX); // Set the maximum distance between all stations by default
    for(i = 0; i < RESEAU.nb_station; i++) { // Set the minimum distance between a station and itself
        setElement(0, MAT_RESEAU, i, i);
    }

    // Loading the number of lines
    if((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%d", &(RESEAU.nb_ligne));
        printf("There are %d lignes\n", RESEAU.nb_ligne);
    } else {
        printf("An error occured while reading the number of lines.\n");
        return;
    }

    // Loading the lines
    free(RESEAU.lignes);
    RESEAU.lignes = malloc(sizeof(ligne) * RESEAU.nb_ligne);
    for(i = 0; i < RESEAU.nb_ligne; i++) {
        if((read = getline(&line, &len, fp)) != -1) {
            ligne li;
            li.id = i;
            li.nom = malloc(100);
            li.couleur = malloc(10);
            sscanf(line, "%[^:]:%[^:]:%d", (li.nom), (li.couleur), &(li.truc_ou_on_sait_pas_ce_que_cest));
            *(RESEAU.lignes + i) = li;

            printf("%s (%s)\n", li.nom, li.couleur);

            // Read the number of stations for way #1
            read = getline(&line, &len, fp);
            int nbr_station_aller = 0;
            sscanf(line, "%d", &nbr_station_aller);
            // Read the line data for way #1
            int j;
            for(j = 0; j < nbr_station_aller; j++) {
                read = getline(&line, &len, fp);
                char * station1 = malloc(100);
                char * station2 = malloc(100);
                int distance = -2;
                sscanf(line, "%[^:]:%[^:]:%d", station1, station2, &distance);
                setElement(distance, MAT_RESEAU, get_id_from_name(station1), get_id_from_name(station2));
            }

            // Read the number of stations for way #2
            read = getline(&line, &len, fp);
            int nbr_station_retour = 0;
            sscanf(line, "%d", &nbr_station_retour);
            // Read the line data for way #2
            for(j = 0; j < nbr_station_retour; j++) {
                read = getline(&line, &len, fp);
                char * station1 = malloc(100);
                char * station2 = malloc(100);
                int distance = -2;
                sscanf(line, "%[^:]:%[^:]:%d", station1, station2, &distance);
                setElement(distance, MAT_RESEAU, get_id_from_name(station1), get_id_from_name(station2));
            }

            printf("  %d connexions for way #1 and %d connexions for way #2\n", nbr_station_aller, nbr_station_retour);
        }
    }
    printf("%d lines loaded\n", i);

    //displayGraph(MAT_RESEAU);

    free(line);
    free(fp);
}


void chemin_le_plus_court(station * s_depart)
{
	station *tab_stat = (station*) malloc(RESEAU.nb_station*sizeof(station));
    //Initialisation




}