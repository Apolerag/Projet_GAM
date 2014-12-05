/*! \file Simplexe.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/
#include "simplexe.h"
#include "vertex.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Simplexe * creationSimplexe(const Vertex *A, const Vertex *B, const Vertex *C)
{
	Simplexe *s;
	ALLOUER(s,1);
	s->sommets[0] = A;
	s->sommets[1] = B;
	s->sommets[2] = C;
	s->fileVertex = NULL;
	s->nbFile = 0;
	s->distanceMax = -1;
	return s;
}

Position positionPointSimplexe(const Simplexe *s, const Vertex *N)
{
	Orientation O1 = orientationPolaire(s->sommets[0], s->sommets[1], N) ;
	Orientation O2 = orientationPolaire(s->sommets[1], s->sommets[2], N) ;
	Orientation O3 = orientationPolaire(s->sommets[2], s->sommets[0], N) ;
	
	if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
		return DEHORS; 
	if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
		return DESSUS; 
	return DEDANS; 
}

void ajouteVoisin(Simplexe *s, Simplexe *v)
{

}

void ajouteVertex(Simplexe *s, Vertex *v, const double distance)
{
	if(s->fileVertex == NULL || distance > s->distanceMax) { 
		// liste vide ou vertex plus loin que le premier 
		// -> premiere position dans la liste
		s->distanceMax = distance;
		v->suivant = s->fileVertex;
		s->fileVertex = v;
	}
	else {
		//vertex moins loin que le premier -> deuxieme position de la liste
		v->suivant = s->fileVertex->suivant;
		s->fileVertex->suivant = v;
	}
	s->nbFile ++;	
}

double *equationPlan(const Simplexe *s)
{
	assert(s != NULL);
	double *equation;
	ALLOUER(equation, 4);

	const Vertex *A = s->sommets[0];
	const Vertex *B = s->sommets[1];
	const Vertex *C = s->sommets[2];
	//double dist;

	double a = (B->coords[1] - A->coords[1]) * (C->coords[2] - A->coords[2]) -
			(B->coords[2] - A->coords[2]) * (C->coords[1] - A->coords[1]);

	double b = (B->coords[2] - A->coords[2]) * (C->coords[0] - A->coords[0]) -
			(B->coords[0] - A->coords[0]) * (C->coords[2] - A->coords[2]);

	double c = (B->coords[0] - A->coords[0]) * (C->coords[1] - A->coords[1]) -
			(B->coords[1] - A->coords[1]) * (C->coords[0] - A->coords[0]);

	equation[0] = a;
	equation[1] = b;
	equation[2] = c;
	equation[3] = -a * A->coords[0] - b * A->coords[1] - c * A->coords[2];

	return equation;
}
