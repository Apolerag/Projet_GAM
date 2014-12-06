/*! \file delaunay.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "base.h"
#include "filePrioriteSimplexe.h"
#include "vertex.h"	

#define H_MAX 1000

/*!
* 	\arg filePrioriteSimplexe: les simplexes créés par la triangulation
*	\arg tableauVertices: le tableau de vertices à trianguler
*	\arg nbVertices: le nombre de vertices dans le tableau
*	\arg nombreFacetteMax: le nombre maximal de simplexe créés (défini par l'utilisateur)
*/
typedef struct 
{
	FileSimplexe *filePrioriteSimplexe;
	Vertex *tableauVertices;
	int nbVertices;
	int nombreFacetteMax;
} Delaunay;

/*! Générations des vertices dans le carré unité
* la fonction génère aléatoirement nb vertices et crée les deux premiers Simplexes de la triangulation 
* \arg v un tableau vide de vertices de taille nbVertex
* \arg f la file de priorité vide qui contiendra les simplexes
*/
Delaunay *initialisation(const int nbVertex, const int nombreFacette);

/*! libere la place occupé en mémoire par d et ses composants
*
*/
void destruction(Delaunay *d);

/*! Triangule les vertex contenu dans d selon la methode de Delaunay
*
*/
void triangulation(Delaunay *d);

#endif
