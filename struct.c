typedef struct Station station;
typedef struct Ligne ligne;

struct Station
{
        float lon;
	float lat;
        char * nom;
        int suivant_aller;
        int suivant_retour;
	station ** suivant;
	station ** precedent;
	ligne ** lignes;
        int distance;
        int id;
};


struct Ligne
{
        int nb_station_aller;
        int nb_station_retour;
	char * nom;
        char * couleur;
        station * stat;
};

struct Reseau
{
        int nb_station;
        int nb_ligne;
        ligne * line;
};

typedef struct Reseau reseau;

int main()
{
        return 0;
}
