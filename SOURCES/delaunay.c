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

Delaunay *initialisation(const int nbVertex, const int nombreFacette)
{
	Delaunay *d;
	ALLOUER(d, 1);
	ALLOUER(d->tableauVertices, nbVertex);
	d->nbVertices = nbVertex;
	d->nombreFacetteMax = nombreFacette;
	d->filePrioriteSimplexe = creerFileSimplexe(2 * nbVertex);
	int n;
	int i;
	Simplexe *s1, *s2;

	/*creation du carré initial */ 
	d->tableauVertices[0].coords[0] = 0; d->tableauVertices[0].coords[1] = 0; d->tableauVertices[0].coords[2] = 0;	
	d->tableauVertices[1].coords[0] = 1; d->tableauVertices[1].coords[1] = 0; d->tableauVertices[1].coords[2] = 0;
	d->tableauVertices[2].coords[0] = 1; d->tableauVertices[2].coords[1] = 1; d->tableauVertices[2].coords[2] = 0;
	d->tableauVertices[3].coords[0] = 0; d->tableauVertices[3].coords[1] = 1; d->tableauVertices[3].coords[2] = 0;

	for(n = 4; n < nbVertex; n++) {
		d->tableauVertices[n].coords[0] = RAND(0, 1);
		d->tableauVertices[n].coords[1] = RAND(0, 1);
		d->tableauVertices[n].coords[2] = RAND(0, H_MAX); //a modifier
	}

	s1 = creationSimplexe(&d->tableauVertices[0], &d->tableauVertices[1], &d->tableauVertices[2]);
	s2 = creationSimplexe(&d->tableauVertices[0], &d->tableauVertices[2], &d->tableauVertices[3]);

	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s1, &d->tableauVertices[n]) == DEDANS)
			ajouteVertex(s1, &d->tableauVertices[n]);
		else ajouteVertex(s2, &d->tableauVertices[n]);		
	}

	printf("s1: \n");
	for (i = 0; i < 3; ++i)
	{
		printf("%f %f\n", s1->sommets[i]->coords[0],s1->sommets[i]->coords[1]);
	}
	printf("s2: \n");
	for (i = 0; i < 3; ++i)
	{
		printf("%f %f\n", s2->sommets[i]->coords[0],s2->sommets[i]->coords[1]);
	}

	/*ajouteVoisin(s1, Simplexe *v0, Simplexe *v1, Simplexe *v2)
	ajouteVoisin(Simplexe *s, Simplexe *v0, Simplexe *v1, Simplexe *v2)
	*/
	insererFileSimplexe(d->filePrioriteSimplexe, s1);
	insererFileSimplexe(d->filePrioriteSimplexe, s2);

	free(s1); 
	free(s2);
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
	Simplexe *s;
	Simplexe *s1, *s2, *s3;
	Vertex *v,*c;

	while(getValeurPremier(d->filePrioriteSimplexe) >= 0) {
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		v = s->listeVertex;
		s1 = creationSimplexe(s->sommets[0], s->sommets[1], v);
		s2 = creationSimplexe(s->sommets[1], s->sommets[2], v);
		s3 = creationSimplexe(s->sommets[2], s->sommets[0], v);

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
		free(s1); free(s2); free(s3);
	}
}
