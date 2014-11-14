/*! \file simplexe.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/
#include "simplexe.h"
#include "vertex.h"

void creationSimplexe(simplexe *s, const vertex *A, const vertex *B, const vertex *C)
{
	//TODO
}

void positionTableauSimplexe(const simplexe *s, const vertex *N, const int nb)
{
	//TODO
}

Position positionPointSimplexe(const simplexe *s, const vertex *N)
{
	Position position;
	Orientation O1 = orientationPolaire(s->t[0], s->t[1], N) ;
	Orientation O2 = orientationPolaire(s->t[1], s->t[2], N) ;
	Orientation O3 = orientationPolaire(s->t[2], s->t[0], N) ;
	if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
		position = DEHORS; 
	else if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
		position = DESSUS; 
	else position = DEDANS; 
	
	return position;
}
