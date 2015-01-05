/**
 * @file delaunay.c
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * @date 2014
*/

#include "delaunay.h"
#include "pile.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

Delaunay *initialisation(const int nbVertex, const int nombreFacette, const double distance)
{
	int n;
	Simplexe *s0, *s1;

	Delaunay *d;
	ALLOUER(d, 1);
	ALLOUER(d->tableauVertex, nbVertex);
	d->filePrioriteSimplexe = creerFileSimplexe(2 * nbVertex - 6);
	d->nbVertex = nbVertex;

	if(nombreFacette == -1) d->nombreFacetteMax = d->filePrioriteSimplexe->nbElements;
	else d->nombreFacetteMax = nombreFacette;
	d->distanceMin = distance;	

	srand(time(NULL)); 
	/*creation du carré initial */ 
	d->tableauVertex[0].coords[0] = 0; d->tableauVertex[0].coords[1] = 0; d->tableauVertex[0].coords[2] = 0;	
	d->tableauVertex[1].coords[0] = 1; d->tableauVertex[1].coords[1] = 0; d->tableauVertex[1].coords[2] = 0;
	d->tableauVertex[2].coords[0] = 1; d->tableauVertex[2].coords[1] = 1; d->tableauVertex[2].coords[2] = 0;
	d->tableauVertex[3].coords[0] = 0; d->tableauVertex[3].coords[1] = 1; d->tableauVertex[3].coords[2] = 0;

	for(n = 4; n < nbVertex; n++) {
		d->tableauVertex[n].coords[0] = RAND(0, 1);
		d->tableauVertex[n].coords[1] = RAND(0, 1);
		d->tableauVertex[n].coords[2] = RAND(0, H_MAX);
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

void triangulation(Delaunay *d)
{
	Simplexe *s;
	Simplexe *s0, *s1, *s2;
	int compteur = 4; /* les 4 points du carré initial*/
	Vertex *v,*c;
	clock_t temps;
    srand(time(NULL));
	while(getValeurPremier(d->filePrioriteSimplexe) >= d->distanceMin && 
		d->nombreFacetteMax > d->filePrioriteSimplexe->nbElementsCourant) {

		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		compteur ++;
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
	temps=clock();
    printf("Temps de calcul: %f secondes \n", (double) temps/CLOCKS_PER_SEC);
	printf("Nombre de points inséré : %d\n", compteur);
	printf("Nombre de facette créées : %d\n", d->filePrioriteSimplexe->nbElementsCourant);
}

void triangulationDelaunay(Delaunay *d)
{
	Simplexe *s, *t;
	Simplexe *s0, *s1, *s2;
	Vertex *v,*c;
	const Vertex *sommetOppose;
	int i;
	int compteur = 4; /* les 4 points du carré initial*/
	time_t t0;
	Pile *pile = initialiserPile();
	clock_t temps;
    srand(time(NULL));

	while(getValeurPremier(d->filePrioriteSimplexe) >= d->distanceMin && 
		d->nombreFacetteMax > d->filePrioriteSimplexe->nbElementsCourant) {
		
		t0 = time(NULL);
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		v = s->listeVertex;
		compteur ++;
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
			else if(positionPointSimplexe(s2, v) == DEDANS) 
				ajouteVertex(s2, v);

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
				if(t != NULL ) {
					sommetOppose = getSommetOppose(s, t);
					if(sommetOppose != NULL) {
						if(InCircle(s->sommets[0], s->sommets[1], s->sommets[2], sommetOppose) == DEDANS) {
							echangeSimplexe(s, t, sommetOppose);
							triFileSimplexe(d->filePrioriteSimplexe, s);
							triFileSimplexe(d->filePrioriteSimplexe, t);
							insererPile(pile, t, t0);
							insererPile(pile, s, t0);
						}
					}
				}
			}
		}
	}
	temps=clock();
    printf("Temps de calcul: %f secondes \n", (double) temps/CLOCKS_PER_SEC);
	printf("Nombre de points inséré : %d\n", compteur);
	printf("Nombre de facette créées : %d\n", d->filePrioriteSimplexe->nbElementsCourant);
	printf("Taille maximale de la pile: %d\n", pile->maxPile);
	free(pile);
}
