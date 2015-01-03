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

Delaunay *initialisationTest(const int nbVertex, const int nombreFacette)
{
	Delaunay *d;
	ALLOUER(d, 1);
	ALLOUER(d->tableauVertex, 5);
	d->filePrioriteSimplexe = creerFileSimplexe(2 * 5);
	d->nbVertex = 5;
	if(nombreFacette == -1) d->nombreFacetteMax = d->filePrioriteSimplexe->nbElements;
	else d->nombreFacetteMax = nombreFacette;
	//int n;
	Simplexe *s0, *s1;

	srand(time(NULL)); 
	/*creation du carré initial */ 
	d->tableauVertex[0].coords[0] = 0; d->tableauVertex[0].coords[1] = 0; d->tableauVertex[0].coords[2] = 0;	
	d->tableauVertex[1].coords[0] = 1; d->tableauVertex[1].coords[1] = 0; d->tableauVertex[1].coords[2] = 0;
	d->tableauVertex[2].coords[0] = 1; d->tableauVertex[2].coords[1] = 1; d->tableauVertex[2].coords[2] = 0;
	d->tableauVertex[3].coords[0] = 0; d->tableauVertex[3].coords[1] = 1; d->tableauVertex[3].coords[2] = 0;

	d->tableauVertex[4].coords[0] = 0.25;
	d->tableauVertex[4].coords[1] = 0.75;
	d->tableauVertex[4].coords[2] = 0; //à modifier

	s0 = creationSimplexe(&d->tableauVertex[0], &d->tableauVertex[1], &d->tableauVertex[2]);
	s1 = creationSimplexe(&d->tableauVertex[0], &d->tableauVertex[2], &d->tableauVertex[3]);

	if(positionPointSimplexe(s0, &d->tableauVertex[4]) == DEDANS)
		ajouteVertex(s0, &d->tableauVertex[4]);
	else ajouteVertex(s1, &d->tableauVertex[4]);		

	ajouteVoisin(s0, NULL, s1, NULL);
	ajouteVoisin(s1, NULL, NULL, s0);
	
	insererFileSimplexe(d->filePrioriteSimplexe, s0);
	insererFileSimplexe(d->filePrioriteSimplexe, s1);
	return d;
}


Delaunay *initialisation(const int nbVertex, const int nombreFacette)
{
	Delaunay *d;
	ALLOUER(d, 1);
	ALLOUER(d->tableauVertex, nbVertex);
	d->filePrioriteSimplexe = creerFileSimplexe(2 * nbVertex);
	d->nbVertex = nbVertex;
	if(nombreFacette == -1) d->nombreFacetteMax = d->filePrioriteSimplexe->nbElements;
	else d->nombreFacetteMax = nombreFacette;
	int n;
	Simplexe *s0, *s1;

	srand(time(NULL)); 
	/*creation du carré initial */ 
	d->tableauVertex[0].coords[0] = 0; d->tableauVertex[0].coords[1] = 0; d->tableauVertex[0].coords[2] = 0;	
	d->tableauVertex[1].coords[0] = 1; d->tableauVertex[1].coords[1] = 0; d->tableauVertex[1].coords[2] = 0;
	d->tableauVertex[2].coords[0] = 1; d->tableauVertex[2].coords[1] = 1; d->tableauVertex[2].coords[2] = 0;
	d->tableauVertex[3].coords[0] = 0; d->tableauVertex[3].coords[1] = 1; d->tableauVertex[3].coords[2] = 0;

	for(n = 4; n < nbVertex; n++) {
		d->tableauVertex[n].coords[0] = RAND(0, 1);
		d->tableauVertex[n].coords[1] = RAND(0, 1);
		d->tableauVertex[n].coords[2] = RAND(0, H_MAX); //à modifier
	}

	s0 = creationSimplexe(&d->tableauVertex[0], &d->tableauVertex[1], &d->tableauVertex[2]);
	s1 = creationSimplexe(&d->tableauVertex[0], &d->tableauVertex[2], &d->tableauVertex[3]);

	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s0, &d->tableauVertex[n]) == DEDANS)
			ajouteVertex(s0, &d->tableauVertex[n]);
		else ajouteVertex(s1, &d->tableauVertex[n]);		
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

	free(d->tableauVertex);
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
	Simplexe *s;
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
	}
}

void triangulationDelaunay(Delaunay *d)
{
	Simplexe *s, *t;
	Simplexe *s0, *s1, *s2;
	//Simplexe *nouveau1 = NULL, *nouveau2 = NULL;
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
		printf("premier Simplexe\n");
		afficheSimplexe(s);
		printf("\n");
		printf("nouveau Vertex\n");
		afficheVertex(v);
		printf("\n");
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
			printf("Simplexe à controler\n");
			afficheSimplexe(s);
			printf("\n");
			for (i = 0; i < 3; ++i)
			{
				t = s->voisins[i];
				/*printf("voisin %d\n",i);
				afficheSimplexe(t);
				printf("\n");*/
				if(t != NULL ) {
					sommetOppose = getSommetOppose(s, t);
					/*printf("sommetOppose\n");
					afficheVertex(sommetOppose);
					printf("\n");
					//printf("%d ", sommetOppose != NULL);
					printf("orientationPolaire ");
					orientationPolaire(s->sommets[0], s->sommets[1], s->sommets[2]) == GAUCHE ? printf("GAUCHE\n") : printf("DROITE\n");
					*/

					/*if(sommetOppose != NULL) printf("%d", InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEDANS);
					printf("\n");*/
					/*	if(sommetOppose != NULL)
							InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEHORS? printf("DEHORS\n"): printf("DEDANS\n");*/
					if(sommetOppose != NULL) {
						if(orientationPolaire(s->sommets[0], s->sommets[1], s->sommets[2]) == GAUCHE &&
							InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEDANS) {
							printf("cacacacacacacacacacacacacacacacacacacacacacacacacacacacacacacaca\n");
							
							echangeSimplexe(s, t, sommetOppose);
							/*printf("nouveau Simplexe \n");
							afficheSimplexe(s);
							afficheSimplexe(t);
							printf("\n");*/
							insererPile(pile, t, t0);
							insererPile(pile, s, t0);
						}
					}
				}
				
			}
		}
		/*printf("file après liste vide\n");
		afficheFile(d->filePrioriteSimplexe);
		printf("\n");*/
		retriFileSimplexe(d->filePrioriteSimplexe);
		/*printf("file retriée\n");
		afficheFile(d->filePrioriteSimplexe);
		printf("\n");*/
		printf("fin boucle\n");
	}
	free(pile);
	//printf("fin triangulation\n");
}
