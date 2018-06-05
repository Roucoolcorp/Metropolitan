#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonctions.h"
#include "graph.h"
#include "stations.h"

reseau RESEAU;
mat_graph * MAT_RESEAU;
station ** stations_list;
int tab_id[4];
int index_tab = 0;
int tab_optimal_way[4];
int* tab_succ = NULL;
int tab_succ_size;
int * tab_chemin;
int tab_chemin_size;

/*int main() {
	load_file("bdd.txt");

	//printf("%s\n", get_line_from_station_name("Pierre et Marie Curie")->nom);

	//if(is_on_same_line(get_station_from_name("Pierre et Marie Curie"), get_station_from_name("Vavin"))) {
	//	printf("Oui\n");
	//} else {
	//	printf("Non\n");
	//}

	int id_station_start, id_station_end;
	id_station_start = get_station_start();
	id_station_end = get_station_end();
	//debut commentaire char * name_start = malloc(100);
    printf("Where are you ?\n");
    scanf("%[^\n]", name_start);
    char * name_end = malloc(100);
    printf("Where are you going?\n");
    printf("a\n");
    scanf("%[^\n]", name_end);
    printf("b\n");
    id_station_start = get_id_from_name(name_start);
    id_station_end = get_id_from_name(name_end);
    free(name_end);
	free(name_start);//fin du commentaire
	shortest_way(id_station_start, id_station_end, MAT_RESEAU);
	return 0;
}*/

// Arduino's map() function
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (float) (((float)x - (float)in_min) * ((float)out_max - (float)out_min) / ((float)in_max - (float)in_min) + (float)out_min);
}

void FillRect(SDL_Surface * ecran, int x, int y, int w, int h, int color) {
	SDL_Rect rect = {x,y,w,h};
	SDL_FillRect(ecran, &rect, color);
}

void display_station(SDL_Surface * ecran, station * st, int selected) {
	float x, y;
	x = map(st->lat, 2.222997, 2.474476, 0, 1120);
	y = map(st->lng, 48.794310, 48.926113, 812, 0);
	if(y > 812) {
		return;
	}
	if(selected) {
		FillRect(ecran, (int)x, (int)y, 10, 10, 0xAA2211);
	} else {
		FillRect(ecran, (int)x, (int)y, 10, 10, 0x888888);
	}
	SDL_Flip(ecran);
}

void display_picture(SDL_Surface * ecran, SDL_Surface * image, int x, int y) {
	SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(image, NULL, ecran, &position);
}

void display_way(SDL_Surface * ecran) {
	TTF_Font * police = TTF_OpenFont("Ubuntu-L.ttf", 25);
	SDL_Color couleurNoire = {0, 0, 0};
	SDL_Surface * texte = TTF_RenderUTF8_Blended(police, "Trajet à suivre :", couleurNoire);
	SDL_Surface * instruction = NULL;
	display_picture(ecran, texte, 50, 833);
	SDL_Flip(ecran);
	int i;
	int mini_index = 0;
	for(i = tab_chemin_size - 1; i >= 0; i--) {
		if(i < tab_chemin_size - 1 && i > 0) {
			printf("Inf\n");
			if(is_on_same_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1])) || is_on_same_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i + 1]))) {
				printf("Same line\n");
				continue;
			} else {
				printf("Not same line\n");
			}
		} else {
			printf("First or last\n");
		}
		printf("%d\n", tab_chemin[i]);
		char * tmp = malloc(1000);
		if(i == 0) {
			strcat(tmp, "Arrivé à ");
			strcat(tmp, get_station_from_id(tab_chemin[i])->name);
		} else {
			strcat(tmp, "Prendre le métro à ");
			strcat(tmp, get_station_from_id(tab_chemin[i])->name);
			//if(is_on_same_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1]))) {
			if(get_common_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1])) != NULL) {
				strcat(tmp, " (");
				strcat(tmp, get_common_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1]))->nom);
				strcat(tmp, ")");
			} else {
				strcat(tmp, " (");
				strcat(tmp, (get_line_from_station(get_station_from_id(tab_chemin[i - 1])))[0]->nom);
				strcat(tmp, ")");
			}
			/*} else {
				if(is_on_same_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i + 1]))) {
					strcat(tmp, " (");
					strcat(tmp, get_common_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i + 1]))->nom);
					strcat(tmp, ")");
				}
			}*/
		}
		instruction = TTF_RenderUTF8_Blended(police, tmp, couleurNoire);
		display_picture(ecran, instruction, 50, 860 + mini_index * 30);
		mini_index++;
		SDL_Flip(ecran);
	}
	TTF_CloseFont(police);
}

void handle_click(int x, int y, SDL_Surface * ecran) {
	if(x >= 900 && x <= 900 + 180 && y >= 850 && y <= 850 + 50){
		printf("Bouton\n");
		shortest_way(tab_id[0], tab_id[1], MAT_RESEAU);
		display_way(ecran);
		return;
	} else if(y > 812) {
		printf("Clear\n");
		draw_base_screen(ecran);
		return;
	}

	int i;
	for(i = 0; i < RESEAU.nb_station; i++){
		station * st = RESEAU.stations + i;
		int station_x, station_y;
		station_x = map(st->lat, 2.222997, 2.474476, 0, 1120);
		station_y = map(st->lng, 48.794310, 48.926113, 812, 0);
		if(x <= station_x + 10 && x >= station_x - 10 && y <= station_y + 10 && y >= station_y - 10) {
			printf("Found : %s\n", st->name);
			display_station(ecran, st, 1);
			tab_id[index_tab] = st->id;
			index_tab++;
			index_tab%=4;
			if(index_tab == 0) {
				optimal_way(tab_id);
				display_way(ecran);
			}
			return;
		}
	}
	printf("Not found\n");
}

void draw_base_screen(SDL_Surface * ecran) {
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	SDL_Surface * paris = SDL_LoadBMP("carte_paris.bmp");
    display_picture(ecran, paris, 0, 0);
    SDL_Surface * calculer = SDL_LoadBMP("calculer_distance.bmp");
    display_picture(ecran, calculer, 900, 850);
    SDL_Flip(ecran);
    
    // Draw all stations
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
    	display_station(ecran, RESEAU.stations + i, 0);
    }

    SDL_FreeSurface(paris);
}

void ui() {
	SDL_WM_SetCaption("Metropolitan", NULL);
    SDL_Surface *ecran = SDL_SetVideoMode(1120, 1200, 32, SDL_HWSURFACE);
    SDL_Surface * paris = SDL_LoadBMP("carte_paris.bmp");
    draw_base_screen(ecran);
	int continuer = 1;
	SDL_Event event;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;

			case SDL_MOUSEBUTTONUP:
				handle_click(event.motion.x, event.motion.y, ecran);
				break;
		}
	}
}

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	load_file("bdd.txt");
	//printf("%s\n", get_line_from_station_name("Pierre et Marie Curie")->nom);
	int id_station_start, id_station_end;
	id_station_start = 1;//get_station_start();
	//id_station_end = get_station_end();
	//shortest_way(id_station_start, id_station_end, MAT_RESEAU);
    tab_id[0] = 1;//id_station_start;
    tab_id[1] = 2;//get_next_station();
    tab_id[2] = 3;//get_next_station();
    tab_id[3] = 4;//get_next_station();

    optimal_way(tab_id);

    ui();

    TTF_Quit();
    SDL_Quit();
    return 0;
}