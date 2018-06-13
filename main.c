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

void display_way(SDL_Surface * ecran, int distance) {
	TTF_Font * police = TTF_OpenFont("Ubuntu-L.ttf", 25);
	SDL_Color couleurNoire = {0, 0, 0};
	SDL_Color couleurLigne = {0, 0, 0};
	char * titre = malloc(500);
	titre[0] = '\0';
	printf("Jusqu'à là ça marche\n");
	strcat(titre, "Trajet à suivre : (");
	printf("Enfin je crois\n");
	char * str = malloc(100);
	sprintf(str, "%d", distance);
	strcat(titre, str);
	strcat(titre, " minutes)");
	SDL_Surface * texte = TTF_RenderUTF8_Blended(police, titre, couleurNoire);
	SDL_Surface * instruction = NULL;
	//SDL_Color couleurLigne;
	int r, g, b;
	display_picture(ecran, texte, 50, 833);
	SDL_Flip(ecran);
	int i;
	int mini_index = 0;
	free(str);
	free(titre);

	printf("\n");
	ligne * current_line = NULL;
	//SDL_Renderer * renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	for(i = tab_chemin_size - 1; i >= 0; i--) {
		char * tmp = malloc(500);
		tmp[0] = '\0';
		printf("Station à traiter : %s (i = %d)\n", get_station_from_id(tab_chemin[i])->name, i);
		if(i == tab_chemin_size - 1) {
			printf("   C'est la première station\n");
			printf("   La suivante est : %s\n", get_station_from_id(tab_chemin[i - 1])->name);
			current_line = get_common_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1]));
			printf("   Nous entrons sur la %s\n", current_line->nom);

			strcat(tmp, "Prenre le metro à ");
			strcat(tmp, get_station_from_id(tab_chemin[i])->name);
			strcat(tmp, ", ");
			strcat(tmp, current_line->nom);
			
			sscanf(current_line->couleur, "#%2d%2d%2d", &r, &g, &b);
			couleurLigne.r = r;
			couleurLigne.g = g;
			couleurLigne.b = b;
			
			instruction = TTF_RenderUTF8_Blended(police, tmp, couleurLigne);
			display_picture(ecran, instruction, 50, 860 + mini_index * 30);
			SDL_Flip(ecran);
			mini_index++;
		} else if(i == 0) {
			printf("   Nous sommes arrivés\n");

			strcat(tmp, "Vous êtes arrivé à ");
			strcat(tmp, get_station_from_id(tab_chemin[i])->name);
			
			instruction = TTF_RenderUTF8_Blended(police, tmp, couleurNoire);
			display_picture(ecran, instruction, 50, 860 + mini_index * 30);
			SDL_Flip(ecran);
			mini_index++;
		} else {
			printf("   La suivante est : %s\n", get_station_from_id(tab_chemin[i - 1])->name);
			if(tab_contains(current_line, get_line_from_station(get_station_from_id(tab_chemin[i - 1])))) {
				printf("   Nous restons sur la même ligne (%s)\n", current_line->nom);
			} else {
				if(current_line != get_common_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1]))) {
					current_line = get_common_line(get_station_from_id(tab_chemin[i]), get_station_from_id(tab_chemin[i - 1]));
					printf("   Nous changeons de ligne : %s\n", current_line->nom);

					strcat(tmp, "Changement à ");
					strcat(tmp, get_station_from_id(tab_chemin[i])->name);
					strcat(tmp, ", prendre la ");
					strcat(tmp, current_line->nom);
					
					sscanf(current_line->couleur, "#%2d%2d%2d", &r, &g, &b);
					couleurLigne.r = r;
					couleurLigne.g = g;
					couleurLigne.b = b;
					
					instruction = TTF_RenderUTF8_Blended(police, tmp, couleurLigne);
					display_picture(ecran, instruction, 50, 860 + mini_index * 30);
					SDL_Flip(ecran);
					mini_index++;
				} else {
					printf("   On reste sur la même ligne\n");
				}
			}
		}

		//if(i != tab_chemin_size - 1) {
		//	SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		//	SDL_RenderDrawLine(renderer, map(get_station_from_id(tab_chemin[i])->lat, 2.222997, 2.474476, 0, 1120), map(tab_chemin[i]->lng, 48.794310, 48.926113, 812, 0), get_station_from_id(tab_chemin[i+1])->lat, 2.222997, 2.474476, 0, 1120), map(tab_chemin[i+1]->lng, 48.794310, 48.926113, 812, 0);
		//	SDL_RenderPresent(renderer);
		//	SDL_Flip(ecran);
		//}

		free(tmp);
		printf("\n");
	}
	TTF_CloseFont(police);
	//printf("10\n");
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

void handle_click(int x, int y, SDL_Surface * ecran) {
	if(x >= 900 && x <= 900 + 180 && y >= 850 && y <= 850 + 50){
		printf("Bouton\n");
		int d = shortest_way(tab_id[0], tab_id[1], MAT_RESEAU);
		display_way(ecran, d);
		index_tab = 0;
		return;
	} else if(y > 812) {
		printf("Clear\n");
		draw_base_screen(ecran);
		index_tab = 0;
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
			//if(index_tab == 0) {
			//	optimal_way(tab_id);
			//	display_way(ecran);
			//}
			return;
		}
	}
	printf("Not found\n");
}

void ui() {
	SDL_WM_SetCaption("Metropolitan", NULL);
    SDL_Surface *ecran = SDL_SetVideoMode(1120, 1200, 32, SDL_HWSURFACE);
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

	/*printf("\n-------------------------\n");
	int i;
	for(i = 0; i < RESEAU.nb_station; i++) {
		get_line_from_station(RESEAU.stations + i);
	}
	printf("----------------------------\n\n");*/

	printf("%d\n", is_on_same_line(get_station_from_name("Concorde"), get_station_from_name("Champs-Élysées - Clémenceau")));

	get_line_from_station_name("Châtillon - Montrouge");

	//printf("%s\n", get_line_from_station_name("Pierre et Marie Curie")->nom);
	//int id_station_start, id_station_end;
	//id_station_start = 1;//get_station_start();
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