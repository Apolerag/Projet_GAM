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

void initialisation(Vertex *v, const int nbVertex, FileSimplexe *f)
{
	int n = 4;
	Simplexe *s1, *s2;
	double *equationS1, *equationS2;
	double dist;

	/*creation du carré initial */ 
	v[0].coords[0] = 0; v[0].coords[1] = 0;
	v[1].coords[0] = 1; v[1].coords[1] = 0;
	v[2].coords[0] = 1; v[2].coords[1] = 1;
	v[3].coords[0] = 0; v[3].coords[1] = 1;

	for(n = 4; n < nbVertex; n++) {
		v[n].coords[0] = RAND(0, 1);
		v[n].coords[1] = RAND(0, 1);
		v[n].coords[2] = RAND(0, H_MAX); //a modifier
	}

	s1 = creationSimplexe(&v[0], &v[1], &v[2]);
	s2 = creationSimplexe(&v[0], &v[2], &v[3]);
	
	equationS1 = equationPlan(s1);
	equationS2 = equationPlan(s2);

	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s1, &v[n]) == DEDANS) {
			dist = abs(equationS1[0] * v[n].coords[0] + 
					   equationS1[1] * v[n].coords[1] + 
					   equationS1[2] * v[n].coords[2] + equationS1[3]) /
				    sqrt(pow(equationS1[0],2) + 
				    	 pow(equationS1[1],2) + 
				    	 pow(equationS1[2],2));

			ajouteVertex(s1, &v[n], dist);
		}
		else
		{
			dist = abs(equationS2[0] * v[n].coords[0] + 
					   equationS2[1] * v[n].coords[1] + 
					   equationS2[2] * v[n].coords[2] + equationS2[3]) /
				    sqrt(pow(equationS2[0],2) + 
				    	 pow(equationS2[1],2) + 
				    	 pow(equationS2[2],2));
				    
			ajouteVertex(s2, &v[n], dist);
				
		}
	}

	insererFileSimplexe(f, s1);
	insererFileSimplexe(f, s2);
	free(equationS1);
	free(equationS2);
}

void separationSimplexe(FileSimplexe *f, Simplexe *s)
{
	//Simplexe *s1 = creationSimplexe();
}
