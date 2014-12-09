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
	Simplexe *s1, *s2;

	/*creation du carré initial */ 
	d->tableauVertices[0].coords[0] = 0; d->tableauVertices[0].coords[1] = 0;
	d->tableauVertices[1].coords[0] = 1; d->tableauVertices[1].coords[1] = 0;
	d->tableauVertices[2].coords[0] = 1; d->tableauVertices[2].coords[1] = 1;
	d->tableauVertices[3].coords[0] = 0; d->tableauVertices[3].coords[1] = 1;

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

void triangulation(Delaunay *d)
{
	Simplexe *s;
	Simplexe *s1, *s2, *s3;
	Vertex *v,*c;
	int i;

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

		for (i = 1; i < d->filePrioriteSimplexe->nbElementsCourant; ++i)
		{
			printf("%f ", d->filePrioriteSimplexe->file[i].distanceMax);
		}
		printf("\n");
	}
}
