/*! \file delaunay.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "delaunay.h"
#include "pile.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

static void afficheFile(FileSimplexe *f)
{
	int i = 1;
	Simplexe *s, *t;
	for(; i <= f->nbElementsCourant; i++)
	{
		s = f->file[i];
		printf("%d ", i);

		t = s->voisins[0]; 
		if(t != NULL)  
		{
			if(t->voisins[0] == s) { printf("0 ");}
			else if(t->voisins[1] == s) { printf("1 ");}
			else if(t->voisins[2] == s) { printf("2 ");}
			else printf("caca ");
		}
		else printf("N ");

		t = s->voisins[1];
		if(t != NULL)
		{
			if(t->voisins[0] == s) { printf("0 ");}
			else if(t->voisins[1] == s) { printf("1 ");}
			else if(t->voisins[2] == s) { printf("2 ");}
			else printf("caca ");

		}
		else printf("N ");

		t = s->voisins[2]; 
		if(t != NULL)
		{
			if(t->voisins[0] == s) { printf("0 ");}
			else if(t->voisins[1] == s) { printf("1 ");}
			else if(t->voisins[2] == s) { printf("2 ");}
			else printf("caca ");
		}
		else printf("N ");
		printf("\n");
		//printf("%lf\n", s->distanceMax);
	}
}

Delaunay *initialisation(const int nbVertex, const int nombreFacette)
{
	Delaunay *d;
	ALLOUER(d, 1);
	ALLOUER(d->tableauVertices, nbVertex);
	d->filePrioriteSimplexe = creerFileSimplexe(2 * nbVertex);
	d->nbVertices = nbVertex;
	if(nombreFacette == -1) d->nombreFacetteMax = d->filePrioriteSimplexe->nbElements;
	else d->nombreFacetteMax = nombreFacette;
	int n;
	Simplexe *s0, *s1;

	srand(time(NULL)); 
	/*creation du carré initial */ 
	d->tableauVertices[0].coords[0] = 0; d->tableauVertices[0].coords[1] = 0; d->tableauVertices[0].coords[2] = 0;	
	d->tableauVertices[1].coords[0] = 1; d->tableauVertices[1].coords[1] = 0; d->tableauVertices[1].coords[2] = 0;
	d->tableauVertices[2].coords[0] = 1; d->tableauVertices[2].coords[1] = 1; d->tableauVertices[2].coords[2] = 0;
	d->tableauVertices[3].coords[0] = 0; d->tableauVertices[3].coords[1] = 1; d->tableauVertices[3].coords[2] = 0;

	for(n = 4; n < nbVertex; n++) {
		d->tableauVertices[n].coords[0] = RAND(0, 1);
		d->tableauVertices[n].coords[1] = RAND(0, 1);
		d->tableauVertices[n].coords[2] = RAND(0, H_MAX); //à modifier
	}

	s0 = creationSimplexe(&d->tableauVertices[0], &d->tableauVertices[1], &d->tableauVertices[2]);
	s1 = creationSimplexe(&d->tableauVertices[0], &d->tableauVertices[2], &d->tableauVertices[3]);

	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s0, &d->tableauVertices[n]) == DEDANS)
			ajouteVertex(s0, &d->tableauVertices[n]);
		else ajouteVertex(s1, &d->tableauVertices[n]);		
	}
	
	ajouteVoisin(s0, NULL, s1, NULL);
	ajouteVoisin(s1, NULL, NULL, s0);
	
	insererFileSimplexe(d->filePrioriteSimplexe, s0);
	insererFileSimplexe(d->filePrioriteSimplexe, s1);

	return d;
}

void destruction(Delaunay *d)
{
	freeFileSimplexe(d->filePrioriteSimplexe);
	free(d->tableauVertices);
	free(d);
}


/*
durée de la triangulation (simple a = 0)
n = 10000 	0m0.044s
n = 100000 	0m0.424s
n = 1000000	0m5.020s
*/
void triangulation(Delaunay *d)
{
	Simplexe *s, *t;
	Simplexe *s0, *s1, *s2;
	Vertex *v,*c;
	while(getValeurPremier(d->filePrioriteSimplexe) >= 0
		&& d->nombreFacetteMax > d->filePrioriteSimplexe->nbElementsCourant) {
		
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		v = s->listeVertex;
		s0 = creationSimplexe(s->sommets[0], s->sommets[1], v);
		s1 = creationSimplexe(s->sommets[1], s->sommets[2], v);
		s2 = creationSimplexe(s->sommets[2], s->sommets[0], v);
		ajouteVoisin(s0, s1, s2, s->voisins[2]);
		ajouteVoisin(s1, s2, s0, s->voisins[0]);
		ajouteVoisin(s2, s0, s1, s->voisins[1]);


		t = s->voisins[0];
		if(t != NULL)  
		{
			if(t->voisins[0] == s) t->voisins[0] = s1;
			else if(t->voisins[1] == s) t->voisins[1] = s1;
			else if(t->voisins[2] == s) t->voisins[2] = s1;
		}

		t = s->voisins[1]; 
		if(t != NULL)
		{
			if(t->voisins[0] == s) t->voisins[0] = s2;
			else if(t->voisins[1] == s) t->voisins[1] = s2;
			else if(t->voisins[2] == s) t->voisins[2] = s2;
		}

		t = s->voisins[2]; 
		if(t != NULL)
		{
			if(t->voisins[0] == s) t->voisins[0] = s0;
			else if(t->voisins[1] == s) t->voisins[1] = s0;
			else if(t->voisins[2] == s) t->voisins[2] = s0;

		}

		v = v->suivant;
		while(v != NULL) {
			c = v->suivant;
			if(positionPointSimplexe(s0, v) == DEDANS)
				ajouteVertex(s0, v);
			else if(positionPointSimplexe(s1, v) == DEDANS)
				ajouteVertex(s1, v);
			else ajouteVertex(s2, v);

			v = c;
		}
		insererFileSimplexe(d->filePrioriteSimplexe, s0);
		insererFileSimplexe(d->filePrioriteSimplexe, s1);
		insererFileSimplexe(d->filePrioriteSimplexe, s2);
		free(s);
	}
}

void triangulationDelaunay(Delaunay *d)
{
	Simplexe *s, *t;
	Simplexe *s0, *s1, *s2;
	Vertex *v,*c;
	const Vertex *sommetOppose;
	int i;
	time_t t0;
	Pile *pile;
	ALLOUER(pile,1);

	while(getValeurPremier(d->filePrioriteSimplexe) >= 0
		&& d->nombreFacetteMax > d->filePrioriteSimplexe->nbElementsCourant) {
		
		t0 = time(NULL);
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		v = s->listeVertex;
		s0 = creationSimplexe(s->sommets[0], s->sommets[1], v);
		s1 = creationSimplexe(s->sommets[1], s->sommets[2], v);
		s2 = creationSimplexe(s->sommets[2], s->sommets[0], v);
		ajouteVoisin(s0, s1, s2, s->voisins[2]);
		ajouteVoisin(s1, s2, s0, s->voisins[0]);
		ajouteVoisin(s2, s0, s1, s->voisins[1]);

		controleNouveauVoisin(s->voisins[0], s, s1);
		controleNouveauVoisin(s->voisins[1], s, s2);
		controleNouveauVoisin(s->voisins[2], s, s0);
		
		v = v->suivant;
		while(v != NULL) {
			c = v->suivant;
			if(positionPointSimplexe(s0, v) == DEDANS)
				ajouteVertex(s0, v);
			else if(positionPointSimplexe(s1, v) == DEDANS)
				ajouteVertex(s1, v);
			else ajouteVertex(s2, v);

			v = c;
		}
		insererFileSimplexe(d->filePrioriteSimplexe, s0);
		insererFileSimplexe(d->filePrioriteSimplexe, s1);
		insererFileSimplexe(d->filePrioriteSimplexe, s2);
		free(s);

		insererPile(pile, s0, t0);
		insererPile(pile, s1, t0);
		insererPile(pile, s2, t0);

		while(! estVide(pile)) {
			s = getSommetPile(pile);

			for (i = 0; i < 3; ++i)
			{
				t = s->voisins[i];
				sommetOppose = getSommetOppose(s, t);

				printf("%d ", sommetOppose != NULL);
				printf("%d ", orientationPolaire(s->sommets[0], s->sommets[1], s->sommets[2]) == GAUCHE);
				if(sommetOppose != NULL) printf("%d", InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEDANS);
				printf("\n");
				/*	if(sommetOppose != NULL)
						InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEHORS? printf("DEHORS\n"): printf("DEDANS\n");*/
				if(sommetOppose != NULL &&
					orientationPolaire(s->sommets[0], s->sommets[1], s->sommets[2]) == GAUCHE &&
					InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEDANS) {
					echangeSimplexe(s, t, i);

					insererPile(s, t, t0);
					printf("caca\n");
				}
			}
		}
		retriFileSimplexe(d->filePrioriteSimplexe);
	}
	free(pile);
}
