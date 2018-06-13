#include "stations.h"
#include <stdio.h>
#include <string.h>

extern reseau RESEAU;

int tab_contains_station(int id, int tab[]) {
  int i;
  for(i = 0; i < 100; i++) {
    if(tab[i] == -1) {
      return 0;
    }

    if(tab[i] == id) {
      return 1;
    }
  }
  return 0;
}

int tab_contains(ligne * l, ligne ** lines) {
  int i = 0;
  while(1) {
    if(lines[i] == NULL) {
      break;
    }
    if(sizeof(l) - sizeof(ligne*) * i <= 0) {
      break;
    }
    if(lines[i]->id == l->id) {
      return 1;
    }
    i++;
  }
  return 0;
}

int is_on_same_line(station * st1, station * st2) {
  printf("    same line?\n");
  
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
    printf("l1 %lu ligne*i %lu\n", sizeof(l1), sizeof(ligne*) * i);
    if(sizeof(l1) - sizeof(ligne*) * i <= 0) {
      break;
    }
    if(l1[i] == NULL) {
      break;
    }
    j = 0;
    while(1) {
      if(l2[j] == NULL) {
        break;
      }

      printf("l2 %lu ligne*j %lu\n", sizeof(l2), sizeof(ligne*) * j);
      if(sizeof(l2) - sizeof(ligne*) * j <= 0) {
        break;
      }

      if(l2[j]->id == l1[i]->id) {
        printf("  (is on same line)\n");
        return 1;
      }
      j++;
    }
    i++;
  }
  printf("  (is not on same line)\n");
  return 0;
}

ligne * get_common_line(station * st1, station * st2) {
  printf("      (common lines)\n");
  ligne ** l1 = get_line_from_station(st1);
  ligne ** l2 = get_line_from_station(st2);
  int i = 0;
  int j = 0;
  /*while(1) {
    if(l1[i] == NULL) {
      break;
    }
    j = 0;
    while(1) {
      if(l2[j] == NULL) {
        break;
      }
      printf("l1[%d] = %s | l2[%d] = %s\n", i, l1[i]->nom, j, l2[j]->nom);
      if(l2[j]->id == l1[i]->id) {
        printf("      Common line : %s\n", l1[i]->nom);
        return l1[i];
      }
      j++;
    }
    i++;
  }*/
  for(i = 0; i < number_of_lines_in_station(st1); i++) {
    for(j = 0; j < number_of_lines_in_station(st2); j++) {
      if(l2[j]->id == l1[i]->id) {
        printf("      Common line : %s\n", l1[i]->nom);
        return l1[i];
      }
    }
  }
  printf("      --no common line--\n");
  return NULL;
}

int number_of_lines_in_station(station * st) {
  int i;
  int j;
  int index = 0;
  for(i = 0; i < RESEAU.nb_ligne; i++){
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
        if(((RESEAU.lignes + i)->stations + j)->name == NULL) {
            break;
          }
          if(st->id == ((RESEAU.lignes + i)->stations + j)->id) {
              index++;
          } 
      }
  }
  return index;
}

ligne ** get_line_from_station_name(char * name) {
  int i;
  int j;
  int index = 0;
  ligne ** lines = malloc(10 * sizeof(ligne *));
  for(i = 0; i < RESEAU.nb_ligne; i++){
      printf("i = %d", i);
      printf(" %s\n", (RESEAU.lignes + i)->nom);
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
          printf("%d/%d %s\n", j, (RESEAU.lignes + i)->nb_station_aller, ((RESEAU.lignes + i)->stations + j)->name);
          if(((RESEAU.lignes + i)->stations + j)->name == NULL) {
            break;
          }
          if(strcmp(name, ((RESEAU.lignes + i)->stations + j)->name) == 0) {
              lines[index] = (RESEAU.lignes + i);
              index++;
          } 
      }
  }
  printf("      %d lines found for station %s\n", index, name);
  return lines;
}

ligne ** get_line_from_station(station * st) {
  int i;
  int j;
  int index = 0;
  ligne ** lines = malloc(sizeof(ligne *) * 10);
  for(i = 0; i < RESEAU.nb_ligne; i++){
      for(j = 0; j < (RESEAU.lignes + i)->nb_station_aller; j++) {
        if(((RESEAU.lignes + i)->stations + j)->name == NULL) {
            break;
          }
          if(st->id == ((RESEAU.lignes + i)->stations + j)->id) {
              lines[index] = (RESEAU.lignes + i);
              index++;
          } 
      }
  }

  printf("      %d lines found for station %s\n", index, st->name);
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
            return (RESEAU.stations + i);
        }
    }
    return NULL;
}
