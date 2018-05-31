typedef struct Station station;
typedef struct Ligne ligne;
//typedef struct Sous_stat sous_stat;

struct Station
{
        float lon;
        float lat;
        char * nom;
        int id;
        int nb_stat_adj;
        station ** stat_adj; 
};

//struct Ligne
//{
 //       int nb_station_aller;
  //      int nb_station_retour;
//      char * nom;
 //       char * couleur;
  //      station * stat;
//};

struct _mat_graphe
{
int nb_lignes ;
int nb_colonnes ;
double * contenu ;
};

typedef struct _mat_graphe mat_graphe;

struct Reseau
{
        int nb_station;
        station ** stat;
};

typedef struct Reseau reseau;

int main()
{
        return 0;
}
