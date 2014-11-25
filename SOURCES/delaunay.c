/*! \file delaunay.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "delaunay.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

void creationPoints (vertex *v, const int nb, FileSimplexe *f)
{
	assert(nb >= 4);

	int n = 4;
	int i;
	simplexe *s1, *s2;
	vertex *c1 = NULL, *c2 = NULL;

	/*creation du carré initial */ 
	v[0].coords[0] = 0; v[0].coords[1] = 0;
	v[1].coords[0] = 1; v[1].coords[1] = 0;
	v[2].coords[0] = 1; v[2].coords[1] = 1;
	v[3].coords[0] = 0; v[3].coords[1] = 1;

	for(n = 4; n < nb; n++)
		for (i = 0; i < DIM; ++i)
			v[n].coords[i] = RAND(0, 1);

	s1 = creationSimplexe(&v[0], &v[1], &v[2]);
	s2 = creationSimplexe(&v[0], &v[2], &v[3]);

	
	
	for(n = 4; n < nb; n++) {
		if(positionPointSimplexe(s1, &v[n]) == DEDANS) {
			if(c1 == NULL)
			{
				s1->inclus = &v[n];
				c1 = s1->inclus;
			}
			else {
				c1->suivant = &v[n];
				c1 = c1->suivant;
			}
			s1->nb++;
		}
		else
		{
			if(c2 == NULL)
			{
				s2->inclus = &v[n];
				c2 = s2->inclus;
			}
			else {
				c2->suivant = &v[n];
				c2 = c2->suivant;
			}
			s2->nb++;	
		}
	}

	insererFileSimplexe(f, s1);
	insererFileSimplexe(f, s2);
}

void separationSimplexe(FileSimplexe *f, simplexe *s)
{
	//simplexe *s1 = creationSimplexe();
}
