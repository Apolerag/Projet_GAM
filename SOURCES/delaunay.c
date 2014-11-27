/*! \file delaunay.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "delaunay.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

void initialisation(Vertex *v, const int nbVertex, FileSimplexe *f)
{
	int n = 4;
	int i;
	simplexe *s1, *s2;
	Vertex *c1 = NULL, *c2 = NULL;

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

	
	
	for(n = 4; n < nbVertex; n++) {
		if(positionPointSimplexe(s1, &v[n]) == DEDANS) {
			//calcul distance par rapport à s1 + 
			//inserer dans fdp Vertex s1
		}
		else
		{
			//calcul distance par rapport à s2 + 
			//inserer dans fdp Vertex s2
				
		}
	}

	insererFileSimplexe(f, s1);
	insererFileSimplexe(f, s2);
}

void separationSimplexe(FileSimplexe *f, simplexe *s)
{
	//simplexe *s1 = creationSimplexe();
}
