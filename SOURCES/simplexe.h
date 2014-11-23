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
	vertex *inclus;
	unsigned int nb;
	struct _simplexe *voisin[3];
	unsigned int nbVoisin;
	double distanceMax;
	unsigned int posDistanceMax;
} simplexe;

/*! créé le vertex ABC*/
simplexe* creationSimplexe(const vertex *A, const vertex *B, const vertex *C);

/*! retourne la position du vertex N par rapport au simplexe s*/
Position positionPointSimplexe(const simplexe *s, const vertex *N);

/*! ajoute un voisin au simplexe*/
void ajouteVoisin(simplexe *s, simplexe *v);

/*! calcul la distance max entre les vertex v appartenant au simplexe s 
*	le plan formé par s a pour équation :
*
*	\f$
*	a*x + b*y + c*z + d = 0
*	\f$
*/
void distanceMax(simplexe *s);

#endif
