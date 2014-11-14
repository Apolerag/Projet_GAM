/*! \file simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"

typedef struct _simplexe
{
	vertex* t[3];
	vertex *inclus;
	unsigned int nb;
	struct _simplexe *suivant;
} simplexe;

typedef struct 
{
	simplexe *liste;
	unsigned int nb;
} liste_simplexe;

/*!*/
void creationSimplexe(simplexe *s, const vertex *A, const vertex *B, const vertex *C);

/*! controle si les vertex du tableau de vertex N sont contenus dans le simplexe*/
void positionTableauSimplexe(const simplexe *s, const vertex *N, const int nb);

/*! retourne la position du vertex N par rapport au simplexe s*/
Position positionPointSimplexe(const simplexe *s, const vertex *N);

#endif
