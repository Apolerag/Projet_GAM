/*! \file vertex.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "vertex.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i)
{
	return (a*e*i + d*h*c + g*b*f) - (g*e*c + a*h*f + d*b*i);
}

Orientation orientationPolaire(const vertex *A, const vertex *B, const vertex *C)
{
	double det;

	if (A == B || B == C || A == C)
    	return ALIGNES;

    det = determinant(1,1,1,
					  A->coords[0],B->coords[0],C->coords[0],
					  A->coords[1],B->coords[1],C->coords[1]);

	if(det < 0) return DROITE;
	else if(det > 0) return GAUCHE;
	else return ALIGNES;
}

int minLexicographique(const vertex *v, const int taille)
{
	
	vertex minL = v[0];
	int indice = 0 ;
	
	int i ;
	for(i = 1; i < taille; i++) 
	{
		if( (v[i].coords[0] < minL.coords[0]) ||
			((v[i].coords[0] == minL.coords[0]) && (v[i].coords[1] < minL.coords[1])))
		{
			minL = v[i]; 
			indice = i ;
		}
	}
	return indice ;
}

Position positionPointTriangle(const vertex *A, const vertex *B, 
										const vertex *C, const vertex *N)
{
	Position position;
	Orientation O1 = orientationPolaire(A,B,N) ;
	Orientation O2 = orientationPolaire(B,C,N) ;
	Orientation O3 = orientationPolaire(C,A,N) ;
	if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
		position = DEHORS; 
	else if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
		position = DESSUS; 
	else position = DEDANS; 
	
	return position;
}

void afficherVertex(const vertex * v)
{
	int i;
	printf("Vertex : ");
	for(i=0; i<DIM; i++)
		printf("%lf ", v->coords[i]);
	printf("\n");
}

Ordre ordreLexicographiqueVertex(const vertex * v1, const vertex * v2)
{
	int i;
	for(i=0; i<DIM; i++)
	{
		if(v1->coords[i] < v2->coords[i])
			return INFERIEUR ;
		else if(v1->coords[i] > v2->coords[i])
			return SUPERIEUR ;
	}
	return EGAUX ;
}

void afficherListe(vertex *v)
{
	vertex *j = v;
	while (j != NULL)
	{
		printf("%lf, %lf \n",j->coords[0], j->coords[1]);
		j = j->suivant;
	}

}

Position InCircle (vertex *A, vertex *B, vertex *C, vertex *Z)
{
  double AZx = A->coords[0] - Z->coords[0], AZy = A->coords[1] - Z->coords[1],
         BZx = B->coords[0] - Z->coords[0], BZy = B->coords[1] - Z->coords[1],
         CZx = C->coords[0] - Z->coords[0], CZy = C->coords[1] - Z->coords[1],

  det = ((A->coords[0] + Z->coords[0])*AZx + (A->coords[1] + Z->coords[1])*AZy) * (BZx*CZy - BZy*CZx) +
        ((B->coords[0] + Z->coords[0])*BZx + (B->coords[1] + Z->coords[1])*BZy) * (CZx*AZy - CZy*AZx) +
        ((C->coords[0] + Z->coords[0])*CZx + (C->coords[1] + Z->coords[1])*CZy) * (AZx*BZy - AZy*BZx);

  /* should return (det > 0.0) ? IN : (det == 0.0) ? ON : OUT; really */
  return (det > 0.0) ? DEDANS : 0;
}
