#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



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

int main()
{
	return 0;
}
