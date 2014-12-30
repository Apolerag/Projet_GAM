/*! \file delaunay.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "base.h"
#include "filePrioriteSimplexe.h"
#include "vertex.h"	

/*! \brief valeur max des coordonnées z des Vertex*/
#define H_MAX 1000

/*!
*	\struct Delaunay
* 	\arg filePrioriteSimplexe: les Simplexe créés par la triangulation
*	\arg tableauVertex: le tableau de Vertex à trianguler
*	\arg nbVertex: le nombre de Vertex dans le tableau
*	\arg nombreFacetteMax: le nombre maximal de Simplexe créés (défini par l'utilisateur)
*/
typedef struct 
{
	FileSimplexe *filePrioriteSimplexe;
	Vertex *tableauVertex;
	int nbVertex;
	int nombreFacetteMax;
} Delaunay;

/*! fonction de test (à enlever)*/
Delaunay *initialisationTest(const int nbVertex, const int nombreFacette);

/*! Générations des Vertex dans le carré unité
* la fonction génère aléatoirement nb Vertex et crée les deux premiers Simplexe de la triangulation 
* \arg v un tableau vide de Vertex de taille nbVertex
* \arg f la file de priorité vide qui contiendra les Simplexe
*/
Delaunay *initialisation(const int nbVertex, const int nombreFacette);

/*! libere la place occupé en mémoire par d et ses composants
*
*/
void destruction(Delaunay *d);

/*! Triangule les Vertex contenu dans d
*
*/
void triangulation(Delaunay *d);

/*! Triangule les Vertex contenu dans d selon la methode de Delaunay
*
*/
void triangulationDelaunay(Delaunay *d);

#endif
