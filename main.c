#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "fonctions.h"
#include "graph.h"
#include "stations.h"

reseau RESEAU;
mat_graph * MAT_RESEAU;

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

void display_station(SDL_Surface * ecran, station * st) {
	float x, y;
	//x = (st->lat - 2.222890) * 4600;
	//y = (180 - st->lng - 48.910703)*8.1;
	//y = (180 - st->lng - 48.910703) * 1 + 812;

	//x = (1 + st->lng - 48.910703) * 1000;
	//y = (st->lat - 2.222890) * 1000;

	// Centre = 48.853327, 2.348923
	//y = ((st->lat - 2.336733) / (2.344367 - 2.336733)) * (812 - 1);
	//x = (st->lat - 2.222997) * (1120 - 0) / (2.474476 - 2.222997) + 2.222997;
	x = map(st->lat, 2.222997, 2.474476, 0, 1120);

	//En haut = 48.926113, 2.357569
	//En bas = 48.798310, 2.381936
	y = map(st->lng, 48.794310, 48.926113, 812, 0);
	//printf("truc = %f\n", ((st->lat - 2.336733) / (2.344367 - 2.336733)));
	printf("lat = %f | lng = %f | x = %d | y = %d\n", st->lat, st->lng, (int)x, (int)y);
	FillRect(ecran, (int)x, (int)y, 10, 10, 0xAA2211);
	SDL_Flip(ecran);
}

void display_picture(SDL_Surface * ecran, SDL_Surface * image, int x, int y) {
	SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_BlitSurface(image, NULL, ecran, &position);
}

void ui() {
	SDL_WM_SetCaption("Metropolitan", NULL);
    SDL_Surface *ecran = SDL_SetVideoMode(1120, 812, 32, SDL_HWSURFACE);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_Surface * paris = SDL_LoadBMP("carte_paris.bmp");
    display_picture(ecran, paris, 0, 0);
    SDL_Flip(ecran);
    //display_station(ecran, get_station_from_name("Pierre et Marie Curie"));
    //display_station(ecran, get_station_from_name("Philippe Auguste"));
    //display_station(ecran, get_station_from_name("Argentine"));
    int i;
    for(i = 0; i < RESEAU.nb_station; i++) {
    	display_station(ecran, RESEAU.stations + i);
    }
	int continuer = 1;
	SDL_Event event;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
		}
	}
}

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	load_file("bdd.txt");
	//printf("%s\n", get_line_from_station_name("Pierre et Marie Curie")->nom);
	int id_station_start, id_station_end;
	int tab_id[4];
	id_station_start = 1;//get_station_start();
	//id_station_end = get_station_end();
	//shortest_way(id_station_start, id_station_end, MAT_RESEAU);
    tab_id[0] = 1;//id_station_start;
    tab_id[1] = 2;//get_next_station();
    tab_id[2] = 3;//get_next_station();
    tab_id[3] = 4;//get_next_station();

    optimal_way(tab_id);

    ui();

    SDL_Quit();
    return 0;
}