#include "stations.h"
#include <stdio.h>
#include <string.h>

extern reseau RESEAU;

int is_on_same_line(station * st1, station * st2) {
  ligne ** l1 = get_line_from_station(st1);
  ligne ** l2 = get_line_from_station(st2);
  if(l1 == NULL) {
    return 0;
  }
  if(l2 == NULL) {
    return 0;
  }
  int i = 0;
  int j = 0;
  while(1) {
    if(l1[i] == NULL) {
      break;
    }
    while(1) {
      if(l2[j] == NULL) {
        break;
      }
      //printf("b :\n");
      //if(l1[i]->nom != NULL && l2[j]->nom != NULL) {
      //  printf("l1 = %s | l2 = %s\n", l1[i]->nom, l2[j]->nom);
      //}
      if(l2[j] == l1[i]) {
        return 1;
      }
      j++;
    }
    i++;
  }
  return 0;
}

ligne * get_common_line(station * st1, station * st2) {
  ligne ** l1 = get_line_from_station(st1);
  ligne ** l2 = get_line_from_station(st2);
  int i = 0;
  int j = 0;
  while(1) {
    if(l1[i] == NULL) {
      break;
    }
    while(1) {
      if(l2[j] == NULL) {
        break;
      }
      printf("a :\n");
      printf("l1 = %s | l2 = %s\n", l1[i]->nom, l2[j]->nom);
      if(l2[j] == l1[i]) {
        return l1[i];
      }
      j++;
    }
    i++;
  }
  return NULL;
}

ligne ** get_line_from_station_name(char * name) {
  int i,j, index = 0;
  ligne ** lines = malloc(10 * sizeof(ligne *));
  for(i = 0; i < RESEAU.nb_ligne; i++){
      //printf("i = %d\n", i);
      //printf("%s\n", (RESEAU.lignes + i)->nom);
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
          //printf("%d/%d %s\n", j, (RESEAU.lignes + i)->nb_station_aller, ((RESEAU.lignes + i)->stations + j)->name);
          if(strcmp(name, ((RESEAU.lignes + i)->stations + j)->name) == 0) {
              lines[index] = (RESEAU.lignes + i);
              index++;
          } 
      }
  }
  return lines;
}

ligne ** get_line_from_station(station * st) {
  int i,j, index = 0;
  ligne ** lines = malloc(10 * sizeof(ligne *));
  for(i = 0; i < RESEAU.nb_ligne; i++){
      //printf("i = %d\n", i);
      //printf("%s\n", (RESEAU.lignes + i)->nom);
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
          //printf("%d/%d %s\n", j, (RESEAU.lignes + i)->nb_station_aller, ((RESEAU.lignes + i)->stations + j)->name);
          if(strcmp(st->name, ((RESEAU.lignes + i)->stations + j)->name) == 0) {
              lines[index] = (RESEAU.lignes + i);
              index++;
          } 
      }
  }
  return lines;
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
