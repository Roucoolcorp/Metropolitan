#ifndef STATIONS
#define STATIONS

typedef struct Station station;
typedef struct Ligne ligne;
//typedef struct Sous_stat sous_stat;

struct Station
{
  float lng;
  float lat;
  char * name;
  int id;
  int nb_stat_adj;
  station * stat_adj; 
};

struct Ligne
{
  int id;
  int nb_station_aller;
  int nb_station_retour;
  char * nom;
  char * couleur;
  station * stat;
};

struct Reseau
{
  int nb_station;
  station * stations;
  int nb_ligne;
  ligne * lignes;
};

typedef struct Reseau reseau;



#endif