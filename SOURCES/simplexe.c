/*! \file simplexe.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/
#include "simplexe.h"
#include "vertex.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

simplexe * creationSimplexe(const vertex *A, const vertex *B, const vertex *C)
{
	simplexe *s;
	ALLOUER(s,1);
	s->t[0] = A;
	s->t[1] = B;
	s->t[2] = C;
	s->inclus = NULL;
	s->nb = 0;
	s->nbVoisin = 0;
	return s;
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

void ajouteVoisin(simplexe *s, simplexe *v)
{
	assert(s->nbVoisin < 3);

	s->voisin[s->nbVoisin] = v;
	s->nbVoisin++;
}

void distanceMax(simplexe *s)
{
	assert(s != NULL);

	int i;
	const vertex *A = s->t[0];
	const vertex *B = s->t[1];
	const vertex *C = s->t[2];
	double dist;

	double n[3]; //vecteur normal au plan ABC

	n[0] = (B->coords[1] - A->coords[1])*(C->coords[2] - A->coords[2]) -
			(B->coords[2] - A->coords[2])*(C->coords[1] - A->coords[1]);

	n[1] = (B->coords[2] - A->coords[2])*(C->coords[0] - A->coords[0]) -
			(B->coords[0] - A->coords[0])*(C->coords[2] - A->coords[2]);

	n[2] = (B->coords[0] - A->coords[0])*(C->coords[1] - A->coords[1]) -
			(B->coords[1] - A->coords[1])*(C->coords[0] - A->coords[0]);

	/* calcul des coefficients a,b,c,d de l'équation de plan ax + by + cz + d = 0*/
	double a = n[0];
	double b = n[1];
	double c = n[2];
	double d = -a * A->coords[0] - b * A->coords[1] - c * A->coords[2];

	s->distanceMax = 0.0;
	for (i = 0; i < s->nb; ++i) {
		dist = abs(a * s->t[i]->coords[0] + b * s->t[i]->coords[1] + c * s->t[i]->coords[2] + d) /
			sqrt(pow(a,2) + pow(b,2) + pow(c,2) );
		s->distanceMax = MAX(s->distanceMax, dist);
	}
}
