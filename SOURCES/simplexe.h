/*! \file simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"

typedef struct _simplexe
{
	const vertex* t[3];
	const vertex *inclus;
	unsigned int nb;
	struct _simplexe *voisin[3];
	unsigned int nbVoisin;
	double distanceMax;
} simplexe;

typedef struct 
{
	simplexe *liste;
	unsigned int nb;
} liste_simplexe;

/*!*/
void creationSimplexe(simplexe *s, const vertex *A, const vertex *B, const vertex *C);

/*! retourne la position du vertex N par rapport au simplexe s*/
Position positionPointSimplexe(const simplexe *s, const vertex *N);

/*! ajoute un voisin au simplexe*/
void ajouteVoisin(simplexe *s, simplexe *v);

/*! calcul la distance entre le vertex v et son projeté sur le plan 
*	formé par le simplexe s d'équation :
*
*	\f$
*	a*x + b*y + c*z + d = 0
*	\f$
*/
double distancePlan(simplexe *s);

#endif
