#include "stations.h"
#include <stdio.h>
#include <string.h>

extern reseau RESEAU;

int is_on_same_line(station * st1, station * st2) {
  if(get_line_from_station(st1) == get_line_from_station(st2)) {
    return 1;
  } else {
    return 0;
  }
}

ligne * get_line_from_station_name(char * name) {
  int i,j;
  for(i = 0; i < RESEAU.nb_ligne; i++){
      //printf("i = %d\n", i);
      //printf("%s\n", (RESEAU.lignes + i)->nom);
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
          //printf("%d/%d %s\n", j, (RESEAU.lignes + i)->nb_station_aller, ((RESEAU.lignes + i)->stations + j)->name);
          if(strcmp(name, ((RESEAU.lignes + i)->stations + j)->name) == 0) {
              return (RESEAU.lignes + i);
          } 
      }
  }
  return NULL;
}

ligne * get_line_from_station(station * st) {
  int i,j;
  for(i = 0; i < RESEAU.nb_ligne; i++){
      //printf("i = %d\n", i);
      //printf("%s\n", (RESEAU.lignes + i)->nom);
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
          //printf("%d/%d %s\n", j, (RESEAU.lignes + i)->nb_station_aller, ((RESEAU.lignes + i)->stations + j)->name);
          if(strcmp(st->name, ((RESEAU.lignes + i)->stations + j)->name) == 0) {
              return (RESEAU.lignes + i);
          } 
      }
  }
  return NULL; 
}

int get_id_from_name(char * name) {
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
        if(strcmp((char *)name, (char *)(RESEAU.stations + i)->name) == 0) {
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
        if(strcmp((char *)name, (char *)(RESEAU.stations + i)->name) == 0) {
            //printf("Found %s!\n", (RESEAU.stations + i)->name);
            return (RESEAU.stations + i);
        }
    }
    //printf("Not found!\n");
    return NULL;
}
