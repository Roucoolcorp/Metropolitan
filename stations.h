#ifndef STATIONS
#define STATIONS

#include <stdlib.h>

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
  int attente_metro;
  char * nom;
  char * couleur;
  station * stations;
};

struct Reseau
{
  int nb_station;
  station * stations;
  int nb_ligne;
  ligne * lignes;
};

typedef struct Reseau reseau;

int is_on_same_line(station * st1, station * st2);
ligne * get_common_line(station * st1, station * st2);
ligne ** get_line_from_station_name(char * name);
ligne ** get_line_from_station(station * st);
int get_id_from_name(char * name);
station * get_station_from_id(int id);
station * get_station_from_name(char * name);

#endif