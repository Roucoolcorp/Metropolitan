#include "fonctions.h"

extern reseau RESEAU;
extern mat_graph * MAT_RESEAU;

int get_id_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
        if(strcmp((char *)name, (char *)(RESEAU.stations + i)->name) == 0) {
            return (RESEAU.stations + i)->id;
        }
    }
    printf("Not found!\n");
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

int positive_degrees(int s, mat_graph *p_graphe)
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
    printf("\n");

    //displayGraph(MAT_RESEAU);

    free(line);
    free(fp);
}


void shortest_way(int id_start, int id_end, mat_graph *p_graphe)
{
	 Sommet *tab_sommet = (Sommet*) malloc(p_graphe->nbrCols*sizeof(Sommet));
    //Initialisation
    int i;
    if(id_start == id_end)
    {
        printf("Ŷou already are at this station\n");
    }
    for(i= 0; i<p_graphe->nbrCols;i++)
    {
        if(i==id_start)
        {
            tab_sommet[i].distance=0;
        }
        else
        {
            tab_sommet[i].distance=INT_MAX;
        }
        tab_sommet[i].pred=-1;//il n'y pas de sommet pour chaque prédécésseur
        tab_sommet[i].marque=false;//pas de sommet marqué
        tab_sommet[i].degrePositif=positive_degrees(i,p_graphe); //calculer des degrés positifs
    }
    int min = 0;
    int x1;
    //Affichage de la premiere ligne
    //printf("               | d(0)      | d(1)      | d(2)      | d(3)      | d(4)      | d(5)      ||| P(0)      | P(1)      | P(2)      | P(3)      | P(4)      | P(5)      \n");
  //  printf("Initialisation | %10d| %0d| %10d| %10d| %10d| %10d||| %10d| %10d| %10d| %10d| %10d| %10d|\n", tab_sommet[0].distance,tab_sommet[1].distance,tab_sommet[2].distance,tab_sommet[3].distance,tab_sommet[4].distance,tab_sommet[5].distance,tab_sommet[0].pred,tab_sommet[1].pred,tab_sommet[2].pred,tab_sommet[3].pred,tab_sommet[4].pred,tab_sommet[5].pred);
    //Loop: shortest way
    while(min != INT_MAX)
    {

        //d(x) = min for a marked node
        bool trouv = false;
        i=0;
        x1=0;
        while((i<p_graphe->nbrCols) && (!trouv))
        {
            if((tab_sommet[i].distance==min)&&(tab_sommet[i].marque==false))
            {
                x1=i;
                tab_sommet[i].marque=true;
                trouv = true;
            }
            i++;
        }
        int* tab_succ = (int*) malloc(sizeof(int)*tab_sommet[x1].degrePositif);
        int j = 0;
        for(i=0;i<p_graphe->nbrCols;i++)
        {
            if(getElement(p_graphe,x1,i)!=-1)
            {
                tab_succ[j]=i;
                j++;
            }
        }
        //new distances
        int y;
        for(y=0;y<tab_sommet[x1].degrePositif;y++)
        {
            if(tab_sommet[x1].distance+getElement(p_graphe,x1,tab_succ[y])<tab_sommet[tab_succ[y]].distance)
            {
                tab_sommet[tab_succ[y]].distance=tab_sommet[x1].distance+getElement(p_graphe,x1,tab_succ[y]);
                tab_sommet[tab_succ[y]].pred = x1;
            }
        }
    free(tab_succ);
     //   printf("               | %10d| %10d| %10d| %10d| %10d| %10d||| %10d| %10d| %10d| %10d| %10d| %10d|\n", tab_sommet[0].distance,tab_sommet[1].distance,tab_sommet[2].distance,tab_sommet[3].distance,tab_sommet[4].distance,tab_sommet[5].distance,tab_sommet[0].pred,tab_sommet[1].pred,tab_sommet[2].pred,tab_sommet[3].pred,tab_sommet[4].pred,tab_sommet[5].pred);

        //x successors
        min = INT_MAX;
        for(i = 0; i<p_graphe->nbrCols;i++)
        {
            if(tab_sommet[i].marque ==false)
            {
                if(tab_sommet[i].distance<min && tab_sommet[i].marque==false)
                {
                    min = tab_sommet[i].distance;
                }
            }
        }
    }
    station station_start;
    station station_end;
    station_end.name = get_station_from_id(id_end)->name;
    station_end.id = get_station_from_id(id_end)->id;  
    station_start.name = get_station_from_id(id_start)->name;
    station_start.id = get_station_from_id(id_start)->id;      
    printf("You need %d minutes to go to %s from %s\n", tab_sommet[id_end].distance, station_end.name, station_start.name);
}

int get_station_start()
{
    char * name_start = malloc(100);
    printf("Where are you ?\n");
    scanf("%[^\n]", name_start);
    return get_id_from_name(name_start);
    free(name_start);
    //return 0;
} 

int get_station_end()
{
    char * name_end = malloc(100);
    printf("Where are you going?\n");
    scanf("\n%[^\n]", name_end);
    return get_id_from_name(name_end);
    free(name_end);
    //return 0;
}


