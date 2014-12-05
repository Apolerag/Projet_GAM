/*! \file Simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef SIMPLEXE_H
#define SIMPLEXE_H

#include "vertex.h"

typedef struct _Simplexe
{
	const Vertex *sommets[3];
	Vertex *fileVertex; //liste de vertices 
	// avec le vertex le plus loin du plan formé par le simplexe
	// en première position
	int nbFile;
	struct _Simplexe *voisins[3];
	double distanceMax;
} Simplexe;

/*! crée le Simplexe ABC*/
Simplexe* creationSimplexe(const Vertex *A, const Vertex *B, const Vertex *C);

/*! retourne la position du Vertex N par rapport au Simplexe s
* DEDANS, DESSUS ou DEHORS 
*/
Position positionPointSimplexe(const Simplexe *s, const Vertex *N);

/*! ajoute un voisin au Simplexe*/
void ajouteVoisin(Simplexe *s, Simplexe *v);

/*! calcul la distance max entre les Vertices v appartenant au Simplexe s 
*	le plan formé par s a pour équation :
*
*	\f$
*	a*x + b*y + c*z + d = 0
*	\f$
*/
void distanceMax(Simplexe *s);

/*! ajoute un vertex dans la liste de vertices du Simplexe s
* 	si la distance est supérieur à la distance max courante du simplexe,
*	le vertex est ajouté en tête et la distance est mise à jour
*	sinon le vertex est inséré en position deux dans la liste
*	\arg s le simplexe où se situe le vertex
*	\arg v le vertex à insérer dans le simplexe
*   \arg distance la distance minimal entre le plan formé par s et v
*/
void ajouteVertex(Simplexe *s, Vertex *v, const int distance);

double *equationPlan(const Simplexe *s);

#endif
