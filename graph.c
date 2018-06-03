#include "graph.h"

mat_graph * allocateMatrix(int nb_lig, int nb_col){
	mat_graph *mat;
	mat = (mat_graph *)  malloc(sizeof(mat_graph));
	mat->nbrLines = nb_lig;
	mat->nbrCols = nb_col;
	mat ->contenu = (double *) malloc(nb_lig*nb_col*sizeof(double));

	return mat;	
}

void setElement(double valeur, mat_graph * p_graph, int ligne, int colonne){
	int position = ligne * p_graph->nbrCols+colonne;
	p_graph->contenu[position] = valeur;

}

double getElement(mat_graph * p_graph, int ligne, int colonne){
	int position = ligne * p_graph->nbrCols+colonne;
	int valeur = p_graph->contenu[position];
	return valeur;
}

void displayGraph(mat_graph* p_graph){
	int cmp = 0;
	int rep;
	for(rep = 0; rep < p_graph->nbrCols*p_graph->nbrLines;rep++){
		if(cmp == p_graph->nbrCols){
			cmp = 0;
			printf("\n");
		}
		if(p_graph->contenu[rep] == INT_MAX) {
			printf("INF");
		} else {
			printf("%3.1f ",p_graph->contenu[rep]);
		}
		cmp++;
	}
	printf("\n");
}

mat_graph* addSommet(mat_graph * p_graph ){
	double *mat;
	int rep;
	int rep2 = 0;
	mat = (double*) malloc((p_graph->nbrLines+1)*(p_graph->nbrCols+1)*sizeof(double));
	
	p_graph->nbrCols = p_graph->nbrCols+1;
	p_graph->nbrLines = p_graph->nbrLines+1;

	for(rep = 0; rep <p_graph->nbrCols*p_graph->nbrLines;rep++){
		if((rep+1)%p_graph->nbrCols==0){
			mat[rep]=0;
		} else if(rep < (p_graph->nbrLines)*(p_graph->nbrCols+1)){
			mat[rep] = p_graph->contenu[rep2];
			rep2++;
		} else{
			mat[rep]=0;
		}
	} 
	free(p_graph->contenu);
	p_graph->contenu = mat;
	return p_graph;
}

mat_graph* delSommet(mat_graph * p_graph, int sommet){
	double *mat;
	int cmp = 0;
	int rep2 = 0;
	int rep;
	int cmp2 = 0;
	mat = (double *) malloc((p_graph->nbrLines-1)*(p_graph->nbrCols-1)*sizeof(double));

	for(rep = 0;rep < ((p_graph->nbrLines-1)*(p_graph->nbrCols-1));rep++){

		if(cmp2 == sommet){
			rep2 += p_graph->nbrCols;
			cmp2++;
		}
		if(cmp == sommet){
			rep2 += 1;
			cmp++;
		}
		printf("rep2 = %d\n",rep2);
		mat[rep]=p_graph->contenu[rep2];
		rep2++;
		cmp = (cmp+1)%(p_graph->nbrCols);
		printf("cmp1 = %d\n",cmp);
		if(cmp == 0){
			cmp2++;
			printf("cmp2 = %d\n",cmp2);
		}

	}
	free(p_graph->contenu);
	p_graph->contenu = mat;
	p_graph->nbrCols = p_graph->nbrCols-1;
	p_graph->nbrLines = p_graph->nbrLines-1;
	return p_graph;
}

void addArc(mat_graph * p_graph, int sommet1 , int sommet2,double valeur){
	int position = sommet1*(p_graph->nbrCols)+sommet2;
	p_graph->contenu[position]=valeur;

}

void delArc(mat_graph * p_graph, int sommet1 , int sommet2){
	int position = sommet1*(p_graph->nbrCols)+sommet2;
	p_graph->contenu[position] = 0;

}

_Bool sommetExists(mat_graph * p_graph, int sommet){
	return (sommet < p_graph->nbrCols);
}

int arcsEntrants(mat_graph *p_graph, int sommet){
	if(sommetExists(p_graph,sommet) == 1){	
		int rep;
		int position;
		int arc_entrant = 0;
		for(rep = 0; rep < p_graph->nbrLines;rep++){
			position = rep*(p_graph->nbrCols)+sommet;
			if(p_graph->contenu[position]==1){
				arc_entrant++;
			}
		}
		return arc_entrant;
	} else{
		exit(-1);
	}
}

int arcsSortants(mat_graph *p_graph,int sommet){
	int rep;
	int position;
	int arc_sortant = 0;
	for(rep = 0; rep < p_graph->nbrLines;rep++){
		position = sommet*(p_graph->nbrCols)+rep;
		if(p_graph->contenu[position] == 1){
			arc_sortant++;
		}
	}
	return arc_sortant;
}

void feedMatrix(mat_graph *p_graph, long value){
	int rep;
	for(rep = 0; rep < p_graph->nbrCols*p_graph->nbrLines;rep++){
		p_graph->contenu[rep] = value;
	}
}