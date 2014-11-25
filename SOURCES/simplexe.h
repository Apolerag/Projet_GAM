/*! \file simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef SIMPLEXE_H
#define SIMPLEXE_H

#include "FilePrioriteVertex.h"
#include "vertex.h"

typedef struct _simplexe
{
	const vertex *sommets[3];
	FileVertex *fileVertex; //liste avec en premier le plus loin
	struct _simplexe *voisins[3];
	double distanceMax;
} simplexe;

/*! crée le simplexe ABC*/
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
