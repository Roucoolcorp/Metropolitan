struct Station //test
{
        float lon;
	float lat;
        char * nom;
        int suivant_aller;
        int suivant_retour;
};

typedef struct Station station;

struct Ligne
{
        int nb_station_aller;
        int nb_station_retour;
	char * nom;
        char * couleur;
        station * stat;
};

typedef struct Ligne ligne;






struct Reseau
{
        int nb_ligne;
        ligne * line;
};

typedef struct Reseau reseau;

int main()
{
        return 0;
}
