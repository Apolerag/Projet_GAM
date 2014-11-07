/*! \file vertex.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef _VERTEX_H
#define _VERTEX_H

#include "base.h"

/*! Dimension de l'espace */
#define DIM 2

/*! enum pour representer l'orientation de trois points*/
typedef enum
{
	GAUCHE = -1, 
	ALIGNES = 0, 
	DROITE = 1
} Orientation;

/*! enum pour la position du point par rapport a un polygone*/
typedef enum
{
	DEDANS = -1,
	DESSUS = 0,
	DEHORS = 1,
	POLYGONE = 2
} Position;

typedef enum {
	INFERIEUR = -1,
	EGAUX = 0,
	SUPERIEUR = 1
} Ordre;

/*! Structure pour representer un point. */
typedef struct _vertex
{
	double coords[DIM];	
	Position position;
	struct _vertex *precedent;
	struct _vertex *suivant;
} vertex;

/*! Calcul le determinant de la matrice 3*3 abcdefghi
* \arg a, b, c la premiere ligne de la matrice
* \arg c, d, e la deuxieme ligne de la matrice
* \arg g, h, i la troisieme ligne de la matrice
*/
double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i);


/*! Calcul l'orientation polaire des Vertex A, B et C
* \arg A, B et C les trois Vertices dont on veut calculer l'angle
* \return l'orientation du vertex C par rapport x
*/
Orientation orientationPolaire(const vertex *A, const vertex *B, const vertex *C);

/*! Retourne l'indice du min lexicographique des points du fichier
* \arg const vertex *v un tableau de vertex
* \arg const int taile la taille du tableau
*/
int minLexicographique(const vertex *v, const int taille);

/*! Calcul la position d'un vertices par rapport à un triangle
* \arg A,B,C le triangle
* \arg N le point 
* \return la position
*/
Position positionPointTriangle(const vertex *A, const vertex *B, 
										const vertex *C, const vertex *N);


/*! affiche les informations d'un vertex*/
void afficherVertex(const vertex * v);

/*! compare lexicographiquement deux vertex - retourne INFERIEUR si le premier est 
	inférieur lexicographiquement au deuxième, EGAUX si les deux vertexs sont 
	confondus, SUPERIEUR sinon */
Ordre ordreLexicographiqueVertex(const vertex * v1, const vertex * v2);

/* tir par fusion*/
vertex* Separer(vertex *liste);

vertex* fusion(vertex *lg,vertex *ld, const vertex* origin);

void afficherListe(vertex *v);

vertex* trier(vertex* l, const vertex* origin);

void echanger(vertex *v ,const int i,const int j);

int partition(vertex *v, const int deb, const int fin);

void triPartitionBis(vertex *v,const int debut,const int fin);

void triPartition(vertex *v, const int n);

#endif
