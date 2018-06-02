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
    int degre_positif;
};
typedef struct _Sommet Sommet;

struct _mat_graphe
{
int nb_lignes ;
int nb_colonnes ;
double * contenu ;
};

typedef struct _mat_graphe mat_graphe;

mat_graphe * allouer_matrice(int nb_lig, int nb_col);
void positionner_element(double valeur, mat_graphe * p_graphe, int ligne, int colonne);
double recuperer_element(mat_graphe * p_graphe, int ligne, int colonne);
void afficher_graphe(mat_graphe* p_graphe);
mat_graphe* Add_s(mat_graphe * p_graphe );
mat_graphe* Supp_s(mat_graphe * p_graphe, int sommet);
void Add_arc(mat_graphe * p_graphe, int sommet1 , int sommet2,double valeur);
void Supp_a(mat_graphe * p_graphe, int sommet1 , int sommet2);
_Bool exists(mat_graphe * p_graphe, int sommet);
_Bool exa(mat_graphe * p_graphe, int sommet1 , int sommet2);
int di(mat_graphe *p_graphe, int sommet);
int de(mat_graphe *p_graphe,int sommet);
int degree(mat_graphe *p_graphe, int sommet);
#endif
