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
	s->listeVertex = NULL;
	s->nbListe = 0;
	s->distanceMax = -1;
	s->e = equationPlan(s);
	s->precedentPile = NULL;
	s->marqueurTemps = 0;
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

void ajouteVoisin(Simplexe *s, Simplexe *v0, Simplexe *v1, Simplexe *v2)
{
	s->voisins[0] = v0;
	s->voisins[1] = v1;
	s->voisins[2] = v2;
}

void ajouteVertex(Simplexe *s, Vertex *v)
{
	double distance = distanceVertexSimplexe(s,v);
	if(s->listeVertex == NULL || distance > s->distanceMax) { 
		// liste vide ou vertex plus loin que le premier 
		// -> premiere position dans la liste
		s->distanceMax = distance;
		v->suivant = s->listeVertex;
		s->listeVertex = v;
	}
	else {
		//vertex moins loin que le premier -> deuxieme position de la liste
		v->suivant = s->listeVertex->suivant;
		s->listeVertex->suivant = v;
	}
	s->nbListe ++;	
}

Equation equationPlan(const Simplexe *s)
{
	assert(s != NULL);
	Equation eq;

	const Vertex *A = s->sommets[0];
	const Vertex *B = s->sommets[1];
	const Vertex *C = s->sommets[2];
	//double dist;

	eq.a = (B->coords[1] - A->coords[1]) * (C->coords[2] - A->coords[2]) -
			(B->coords[2] - A->coords[2]) * (C->coords[1] - A->coords[1]);

	eq.b = (B->coords[2] - A->coords[2]) * (C->coords[0] - A->coords[0]) -
			(B->coords[0] - A->coords[0]) * (C->coords[2] - A->coords[2]);

	eq.c = (B->coords[0] - A->coords[0]) * (C->coords[1] - A->coords[1]) -
			(B->coords[1] - A->coords[1]) * (C->coords[0] - A->coords[0]);

	eq.d = -eq.a * A->coords[0] - eq.b * A->coords[1] - eq.c * A->coords[2];
	return eq;
}

double distanceVertexSimplexe(const Simplexe *s, const Vertex *v)
{
	return (double)abs(s->e.a * v->coords[0] + s->e.b * v->coords[1] + 
			   s->e.c * v->coords[2] + s->e.d) /
			   sqrt(pow(s->e.a,2) + pow(s->e.b,2) + pow(s->e.c,2));		   
}

const Vertex * getSommetOppose(const Simplexe *s, Simplexe *Voisin)
{
	const Vertex *v = NULL;

	if(Voisin != NULL) {
		if(Voisin->voisins[0] == s) v = s->sommets[0];
		else if(Voisin->voisins[1] == s) v = s->sommets[1];
		else if(Voisin->voisins[2] == s) v = s->sommets[2];
	}
	
	return v;
}

void controleNouveauVoisin(Simplexe *s, Simplexe *ancienVoisin, Simplexe *nouveauVoisin)
{
	if(s != NULL)  
	{
		if(s->voisins[0] == ancienVoisin) s->voisins[0] = nouveauVoisin;
		else if(s->voisins[1] == ancienVoisin) s->voisins[1] = nouveauVoisin;
		else if(s->voisins[2] == ancienVoisin) s->voisins[2] = nouveauVoisin;
	}

}

void echangeSimplexe(Simplexe *s1, Simplexe *s2, const int i)
{
	Simplexe *nouveau1 = NULL, *nouveau2 = NULL;
	Vertex *v = NULL, *c = NULL;

	if(orientationPolaire(s1->sommets[0], s1->sommets[1], s2->sommets[i]) == GAUCHE &&
		orientationPolaire(s2->sommets[i], s1->sommets[1], s1->sommets[2]) == GAUCHE ) {
		nouveau1 = creationSimplexe(s1->sommets[0], s1->sommets[1], s2->sommets[i]);
		nouveau2 = creationSimplexe(s2->sommets[i], s1->sommets[1], s1->sommets[2]);

		nouveau1->voisins[0] = nouveau2;
		nouveau1->voisins[1] = s2->voisins[(i+2)%3];
		nouveau1->voisins[2] = s1->voisins[2];

		nouveau2->voisins[0] = s1->voisins[0];
		nouveau2->voisins[1] = s2->voisins[(i+1)%3];
		nouveau2->voisins[2] = nouveau1;
	}
	else if(orientationPolaire(s1->sommets[0], s1->sommets[1], s2->sommets[i]) == GAUCHE &&
			orientationPolaire(s2->sommets[i], s1->sommets[2], s1->sommets[0]) == GAUCHE ) {
		nouveau1 = creationSimplexe(s1->sommets[0], s1->sommets[1], s2->sommets[i]);
		nouveau2 = creationSimplexe(s2->sommets[i], s1->sommets[2], s1->sommets[0]);

		nouveau1->voisins[0] = nouveau2;
		nouveau1->voisins[1] = s2->voisins[(i+2)%3];
		nouveau1->voisins[2] = s1->voisins[2];

		nouveau2->voisins[0] = s1->voisins[0];
		nouveau2->voisins[1] = s2->voisins[(i+1)%3];
		nouveau2->voisins[2] = nouveau1;
	}
	else if(orientationPolaire(s2->sommets[i], s1->sommets[1], s1->sommets[2]) == GAUCHE && 
			orientationPolaire(s2->sommets[i], s1->sommets[2], s1->sommets[0]) == GAUCHE ) {
		nouveau1 = creationSimplexe(s2->sommets[i], s1->sommets[1], s1->sommets[2]);
		nouveau2 = creationSimplexe(s2->sommets[i], s1->sommets[2], s1->sommets[0]);

		nouveau1->voisins[0] = nouveau2;
		nouveau1->voisins[1] = s2->voisins[(i+2)%3];
		nouveau1->voisins[2] = s1->voisins[2];

		nouveau2->voisins[0] = s1->voisins[0];
		nouveau2->voisins[1] = s2->voisins[(i+1)%3];
		nouveau2->voisins[2] = nouveau1;
	}

	v = s1->listeVertex;
	while(v != NULL) {
		c = v->suivant;
		if(positionPointSimplexe(nouveau1, v) == DEDANS)
			ajouteVertex(nouveau1, v);
		else ajouteVertex(nouveau2, v);

		v = c;
	}

	v = s2->listeVertex;
	while(v != NULL) {
		c = v->suivant;
		if(positionPointSimplexe(nouveau1, v) == DEDANS)
			ajouteVertex(nouveau1, v);
		else ajouteVertex(nouveau2, v);

		v = c;
	}

	free(s1); s1 = nouveau1;
	free(s2); s2 = nouveau2;
}

