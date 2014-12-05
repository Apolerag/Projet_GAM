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
	d->nombreFacetteMax = nombreFacette;
	d->filePrioriteSimplexe = creerFileSimplexe(2 * nbVertex);
	int n = 4;
	Simplexe *s1, *s2;
	double *equationS1, *equationS2;
	double dist;

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
	
	equationS1 = equationPlan(s1);
	equationS2 = equationPlan(s2);

	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s1, &d->tableauVertices[n]) == DEDANS) {
			dist = abs(equationS1[0] * d->tableauVertices[n].coords[0] + 
					   equationS1[1] * d->tableauVertices[n].coords[1] + 
					   equationS1[2] * d->tableauVertices[n].coords[2] + equationS1[3]) /
				    sqrt(pow(equationS1[0],2) + 
				    	 pow(equationS1[1],2) + 
				    	 pow(equationS1[2],2));

			ajouteVertex(s1, &d->tableauVertices[n], dist);
		}
		else
		{
			dist = abs(equationS2[0] * d->tableauVertices[n].coords[0] + 
					   equationS2[1] * d->tableauVertices[n].coords[1] + 
					   equationS2[2] * d->tableauVertices[n].coords[2] + equationS2[3]) /
				    sqrt(pow(equationS2[0],2) + 
				    	 pow(equationS2[1],2) + 
				    	 pow(equationS2[2],2));
				    
			ajouteVertex(s2, &d->tableauVertices[n], dist);
				
		}
	}

	insererFileSimplexe(d->filePrioriteSimplexe, s1);
	insererFileSimplexe(d->filePrioriteSimplexe, s2);
	free(equationS1);
	free(equationS2);
	return d;
}

void destruction(Delaunay *d)
{
	Simplexe *s;
	//nettoyage de la file
	while(d->filePrioriteSimplexe->nbElementsCourant > 0)
	{
		s = extremierFileSimplexe(d->filePrioriteSimplexe);
		free(s);
	}
	free(d->filePrioriteSimplexe);

	free(d->tableauVertices);

	free(d);
}

void separationSimplexe(FileSimplexe *f, Simplexe *s)
{
	//Simplexe *s1 = creationSimplexe();
}
