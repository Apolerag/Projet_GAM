/**
 * @file vertex.c
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * @date 2014
 */

#include "vertex.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void afficheVertex(const Vertex *v)
{
	if(v == NULL) printf("NULL\n");
	else printf("(%.2f, %.2f) ", v->coords[0], v->coords[1]);
}

double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i)
{
	return (a*e*i + d*h*c + g*b*f) - (g*e*c + a*h*f + d*b*i);
}

Orientation orientationPolaire(const Vertex *A, const Vertex *B, const Vertex *C)
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

Position positionPointTriangle(const Vertex *A, const Vertex *B, 
										const Vertex *C, const Vertex *N)
{
	Position position;
	Orientation O1 = orientationPolaire(A,B,N);
	Orientation O2 = orientationPolaire(B,C,N);
	Orientation O3 = orientationPolaire(C,A,N);
	if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
		position = DEHORS; 
	else if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
		position = DESSUS; 
	else position = DEDANS; 
	
	return position;
}

Position InCircle (const Vertex *A, const Vertex *B, const Vertex *C, const Vertex *Z)
{
  double AZx = A->coords[0] - Z->coords[0], AZy = A->coords[1] - Z->coords[1],
         BZx = B->coords[0] - Z->coords[0], BZy = B->coords[1] - Z->coords[1],
         CZx = C->coords[0] - Z->coords[0], CZy = C->coords[1] - Z->coords[1],

  det = ((A->coords[0] + Z->coords[0])*AZx + (A->coords[1] + Z->coords[1])*AZy) * (BZx*CZy - BZy*CZx) +
        ((B->coords[0] + Z->coords[0])*BZx + (B->coords[1] + Z->coords[1])*BZy) * (CZx*AZy - CZy*AZx) +
        ((C->coords[0] + Z->coords[0])*CZx + (C->coords[1] + Z->coords[1])*CZy) * (AZx*BZy - AZy*BZx);

  /* should return (det > 0.0) ? IN : (det == 0.0) ? ON : OUT; really */
  return (det > 0.0) ? DEDANS : DEHORS;
}
