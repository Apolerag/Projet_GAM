/*! \file delaunay.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "delaunay.h"

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
	Simplexe *s1, *s2;

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

	s1 = creationSimplexe(&d->tableauVertices[0], &d->tableauVertices[1], &d->tableauVertices[2]);
	s2 = creationSimplexe(&d->tableauVertices[0], &d->tableauVertices[2], &d->tableauVertices[3]);

	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s1, &d->tableauVertices[n]) == DEDANS)
			ajouteVertex(s1, &d->tableauVertices[n]);
		else ajouteVertex(s2, &d->tableauVertices[n]);		
	}
	
	ajouteVoisin(s1, NULL, s2, NULL);
	ajouteVoisin(s2, NULL, NULL, s1);
	
	insererFileSimplexe(d->filePrioriteSimplexe, s1);
	insererFileSimplexe(d->filePrioriteSimplexe, s2);

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
	Simplexe *s1, *s2, *s3;
	Vertex *v,*c;
	while(getValeurPremier(d->filePrioriteSimplexe) >= 0
		&& d->nombreFacetteMax > d->filePrioriteSimplexe->nbElementsCourant) {
		
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		v = s->listeVertex;
		s1 = creationSimplexe(s->sommets[0], s->sommets[1], v);
		s2 = creationSimplexe(s->sommets[1], s->sommets[2], v);
		s3 = creationSimplexe(s->sommets[2], s->sommets[0], v);
		ajouteVoisin(s1, s2, s3, s->voisins[2]);
		ajouteVoisin(s2, s3, s1, s->voisins[0]);
		ajouteVoisin(s3, s1, s2, s->voisins[1]);


		t = s->voisins[0];
		if(t != NULL)  
		{
			if(t->voisins[0] == s) t->voisins[0] = s2;
			else if(t->voisins[1] == s) t->voisins[1] = s2;
			else if(t->voisins[2] == s) t->voisins[2] = s2;
		}

		t = s->voisins[1]; 
		if(t != NULL)
		{
			if(t->voisins[0] == s) t->voisins[0] = s3;
			else if(t->voisins[1] == s) t->voisins[1] = s3;
			else if(t->voisins[2] == s) t->voisins[2] = s3;
		}

		t = s->voisins[2]; 
		if(t != NULL)
		{
			if(t->voisins[0] == s) t->voisins[0] = s1;
			else if(t->voisins[1] == s) t->voisins[1] = s1;
			else if(t->voisins[2] == s) t->voisins[2] = s1;

		}

		v = v->suivant;
		while(v != NULL) {
			c = v->suivant;
			if(positionPointSimplexe(s1, v) == DEDANS)
				ajouteVertex(s1, v);
			else if(positionPointSimplexe(s2, v) == DEDANS)
				ajouteVertex(s2, v);
			else ajouteVertex(s3, v);

			v = c;
		}
		insererFileSimplexe(d->filePrioriteSimplexe, s1);
		insererFileSimplexe(d->filePrioriteSimplexe, s2);
		insererFileSimplexe(d->filePrioriteSimplexe, s3);
		free(s);
	}
}

void triangulationDelaunay(Delaunay *d)
{
	Simplexe *s;
	Simplexe *s1, *s2, *s3;
	Vertex *v,*c;

	while(getValeurPremier(d->filePrioriteSimplexe) >= 0) {
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		v = s->listeVertex;
		s1 = creationSimplexe(s->sommets[0], s->sommets[1], v);
		s2 = creationSimplexe(s->sommets[1], s->sommets[2], v);
		s3 = creationSimplexe(s->sommets[2], s->sommets[0], v);
		
		ajouteVoisin(s1, s2, s3, s->voisins[2]);
		ajouteVoisin(s2, s2, s1, s->voisins[0]);
		ajouteVoisin(s3, s1, s2, s->voisins[1]);
		
		/*ajout vertex, on va voir le voisin et on modifie la valeur du voisin avec la valeur dans la file

		*/

		v = v->suivant;
		while(v != NULL) {
			c = v->suivant;
			if(positionPointSimplexe(s1, v) == DEDANS)
				ajouteVertex(s1, v);
			else if(positionPointSimplexe(s2, v) == DEDANS)
				ajouteVertex(s2, v);
			else ajouteVertex(s3, v);

			v = c;
		}
		insererFileSimplexe(d->filePrioriteSimplexe, s1);
		insererFileSimplexe(d->filePrioriteSimplexe, s2);
		insererFileSimplexe(d->filePrioriteSimplexe, s3);
		free(s);
	}
}
