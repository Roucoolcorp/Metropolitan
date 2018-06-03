#ifndef GRAPH
#define GRAPH

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct _Sommet
{
	int distance;
	int pred;
	bool marque;
	int degrePositif;
};
typedef struct _Sommet Sommet;

struct _mat_graph
{
	int nbrLines ;
	int nbrCols ;
	double * contenu ;
};

typedef struct _mat_graph mat_graph;

mat_graph * allocateMatrix(int nb_lig, int nb_col);
void setElement(double valeur, mat_graph * p_graph, int ligne, int colonne);
double getElement(mat_graph * p_graph, int ligne, int colonne);
void displayGraph(mat_graph* p_graph);
mat_graph* addSommet(mat_graph * p_graph );
mat_graph* delSommet(mat_graph * p_graph, int sommet);
void addArc(mat_graph * p_graph, int sommet1 , int sommet2,double valeur);
void delArc(mat_graph * p_graph, int sommet1 , int sommet2);
_Bool sommetExists(mat_graph * p_graph, int sommet);
int arcsEntrants(mat_graph *p_graph, int sommet);
int arcsSortants(mat_graph *p_graph,int sommet);
int deg(mat_graph *p_graph, int sommet);
void feedMatrix(mat_graph *p_graph, long value);
#endif
