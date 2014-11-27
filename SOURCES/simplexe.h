/*! \file Simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef SIMPLEXE_H
#define SIMPLEXE_H

#include "filePrioriteVertex.h"
#include "vertex.h"

typedef struct _Simplexe
{
	const Vertex *sommets[3];
	FileVertex *fileVertex; //liste avec en premier le plus loin
	struct _Simplexe *voisins[3];
	double distanceMax;
} Simplexe;

/*! crée le Simplexe ABC*/
Simplexe* creationSimplexe(const Vertex *A, const Vertex *B, const Vertex *C);

/*! retourne la position du Vertex N par rapport au Simplexe s*/
Position positionPointSimplexe(const Simplexe *s, const Vertex *N);

/*! ajoute un voisin au Simplexe*/
void ajouteVoisin(Simplexe *s, Simplexe *v);

/*! calcul la distance max entre les Vertex v appartenant au Simplexe s 
*	le plan formé par s a pour équation :
*
*	\f$
*	a*x + b*y + c*z + d = 0
*	\f$
*/
void distanceMax(Simplexe *s);

#endif
