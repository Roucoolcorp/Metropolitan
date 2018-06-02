#include "graph.h"

mat_graphe * allouer_matrice(int nb_lig, int nb_col){

	mat_graphe *nouveau;
	nouveau = (mat_graphe *)  malloc(sizeof(mat_graphe));
	nouveau->nb_lignes = nb_lig;
	nouveau->nb_colonnes = nb_col;
	nouveau ->contenu = (double *) malloc(nb_lig*nb_col*sizeof(double));

	return nouveau;	
}

void positionner_element(double valeur, mat_graphe * p_graphe, int ligne, int colonne){

	int position = ligne * p_graphe->nb_colonnes+colonne;
	p_graphe->contenu[position] = valeur;

}

double recuperer_element(mat_graphe * p_graphe, int ligne, int colonne){

	int position = ligne * p_graphe->nb_colonnes+colonne;
	int valeur = p_graphe->contenu[position];
	return valeur;
}

void afficher_graphe(mat_graphe* p_graphe){

	int compteur = 0;
	int repetition;

	for(repetition = 0; repetition < p_graphe->nb_colonnes*p_graphe->nb_lignes;repetition++){
		if(compteur == p_graphe->nb_colonnes){
			compteur = 0;
			printf("\n");
		}
		printf("%6.1f ",p_graphe->contenu[repetition]);
		compteur++;
	}
	printf("\n");
}
mat_graphe* Add_s(mat_graphe * p_graphe ){
	
	double *nouveau;
	int repetition;
	int repetition2 = 0;
	nouveau = (double*) malloc((p_graphe->nb_lignes+1)*(p_graphe->nb_colonnes+1)*sizeof(double));
	
	p_graphe->nb_colonnes = p_graphe->nb_colonnes+1;
	p_graphe->nb_lignes = p_graphe->nb_lignes+1;

	for(repetition = 0; repetition <p_graphe->nb_colonnes*p_graphe->nb_lignes;repetition++){
		if((repetition+1)%p_graphe->nb_colonnes==0){
			nouveau[repetition]=0;
		}
		else if(repetition < (p_graphe->nb_lignes)*(p_graphe->nb_colonnes+1)){
			nouveau[repetition] = p_graphe->contenu[repetition2];
			repetition2++;
		}
		else{
			nouveau[repetition]=0;
		}
	} 
	free(p_graphe->contenu);
	p_graphe->contenu = nouveau;
	return p_graphe;
}
mat_graphe* Supp_s(mat_graphe * p_graphe, int sommet){

	double *nouveau;
	int compteur = 0;
	int repetition2 = 0;
	int repetition;
	int compteur2 = 0;
	nouveau = (double *) malloc((p_graphe->nb_lignes-1)*(p_graphe->nb_colonnes-1)*sizeof(double));

	for(repetition = 0;repetition < ((p_graphe->nb_lignes-1)*(p_graphe->nb_colonnes-1));repetition++){

		if(compteur2==sommet){
			repetition2+=p_graphe->nb_colonnes;
			compteur2++;
		}
		if(compteur==sommet){
			repetition2+=1;
			compteur++;
		}
		printf("repetition2 = %d\n",repetition2);
		nouveau[repetition]=p_graphe->contenu[repetition2];
		repetition2++;
		compteur = (compteur+1)%(p_graphe->nb_colonnes);
		printf("compteur1 = %d\n",compteur);
		if(compteur==0){
			compteur2++;
			printf("compteur2 = %d\n",compteur2);
		}

	}
	free(p_graphe->contenu);
	p_graphe->contenu = nouveau;
	p_graphe->nb_colonnes = p_graphe->nb_colonnes-1;
	p_graphe->nb_lignes = p_graphe->nb_lignes-1;
	return p_graphe;
}
void Add_arc(mat_graphe * p_graphe, int sommet1 , int sommet2,double valeur){
	
	int position = sommet1*(p_graphe->nb_colonnes)+sommet2;
	p_graphe->contenu[position]=valeur;

}
void Supp_a(mat_graphe * p_graphe, int sommet1 , int sommet2){

	int position = sommet1*(p_graphe->nb_colonnes)+sommet2;
	p_graphe->contenu[position]=0;

}
_Bool exists(mat_graphe * p_graphe, int sommet){

	_Bool existence = 0;
	if(sommet < p_graphe->nb_colonnes){
		existence = 1;
	}
	return existence;
	
}
_Bool exa(mat_graphe * p_graphe, int sommet1 , int sommet2){

	_Bool existence = 0;
	int position = sommet1*(p_graphe->nb_colonnes)+sommet2;
	if(p_graphe->contenu[position]==1){
		existence = 1;
	}
	return existence;

}

int di(mat_graphe *p_graphe, int sommet){
	if(exists(p_graphe,sommet)==1){

	
	int repetition;
	int position;
	int arc_entrant = 0;
	for(repetition = 0; repetition < p_graphe->nb_lignes;repetition++){
		position = repetition*(p_graphe->nb_colonnes)+sommet;
		if(p_graphe->contenu[position]==1){
			arc_entrant++;
		}
	}
	return arc_entrant;
	}
	else{
		printf("Erreur");
		exit(-1);
	}
}
int de(mat_graphe *p_graphe,int sommet){
	int repetition;
	int position;
	int arc_sortant = 0;
	for(repetition = 0; repetition < p_graphe->nb_lignes;repetition++){
		position = sommet*(p_graphe->nb_colonnes)+repetition;
		if(p_graphe->contenu[position]==1){
			arc_sortant++;
		}
	}
	return arc_sortant;
}
int degree(mat_graphe *p_graphe, int sommet){
	return (de(p_graphe,sommet)+di(p_graphe,sommet));
}

/*void chemin(mat_graphe *p_graphe,int sommet1, int sommet2){
	int booleen;
	int tab[p_graphe->nb_col];
	tab[0]=sommet1;
	int compteur = 0;
	

}*/