/*! \file delaunay.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "delaunay.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

double myRandom (const double a, const double b)
{
	return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

void creationPoints (vertex *v, const int nb, File_Priorite *f)
{
	assert(nb >= 4);

	int n = 4;
	int i;
	simplexe *s1, *s2;
	vertex *c1, *c2;

	/*creation du carré initial */ 
	v[0].coords[0] = 0; v[0].coords[1] = 0;
	v[1].coords[0] = 1; v[1].coords[1] = 0;
	v[2].coords[0] = 1; v[2].coords[1] = 1;
	v[3].coords[0] = 0; v[3].coords[1] = 1;

	for(n = 4; n < nb; n++)
		for (i = 0; i < DIM; ++i)
			v[n].coords[i] = myRandom(0, 1);

	s1 = creationSimplexe(&v[0], &v[1], &v[2]);
	s2 = creationSimplexe(&v[0], &v[2], &v[3]);

	c1 = s1->inclus;
	c2 = s2->inclus;
	for(n = 4; n < nb; n++) {
		if(positionPointSimplexe(s1, &v[n]) == DEDANS) {
			if(c1 == NULL)
				c1 = &v[n];
			else {
				c1->suivant = &v[n];
				c1 = c1->suivant;
			}
			s1->nb++;
		}
		else
		{
			if(c2 == NULL)
				c2 = &v[n];
			else {
				c2->suivant = &v[n];
				c2 = c2->suivant;
			}
			s2->nb++;	
		}
	}

	insererVertexFile(f, s1);
	insererVertexFile(f, s2);
}
