/*! \file fenetre.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "fenetre.h"

void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin)
{
	f.minX = X_min;
	f.maxX = X_max;
	f.minY = Y_min;
	f.maxY = Y_max;
	f.margin = margin;
}

void clearFenetre(vertex *v, const int nb)
{
	free(v);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void winInit()
{
	gluOrtho2D(f.minX, f.maxX, f.minY, f.maxY);
}

double myRandom (const double a, const double b)
{
	return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

void selectPoints (vertex *v, const int nb)
{
	assert(nb >= 4);
	assert(f.maxX - f.minX > 10 && f.maxX > f.minX);
	assert(f.maxY - f.minY > 10 && f.maxY > f.minY);

	int n = 4;
	int i;

	v[0].coords[0] = 0; v[0].coords[1] = 0;
	v[1].coords[0] = 1; v[1].coords[1] = 0;
	v[2].coords[0] = 1; v[2].coords[1] = 1;
	v[3].coords[0] = 0; v[3].coords[1] = 1;

	for(n = 4; n < nb; n++)
		for (i = 0; i < DIM; ++i)
			v[n].coords[i] = myRandom(0, 1);

}

void effaceFenetre()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void displayPoints(const vertex *v, const int nb)
{	
	glColor3f(0.0, 0.0, 0.0);
  	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	int echelleX = f.maxX - 10;
	int echelleY = f.maxY - 10;

	/*tracer carrée initial*/
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);
	for (i = 0; i < 4; ++i)
	{
		glVertex2f(v[i].coords[0]*echelleX + 5, f.maxY - v[i].coords[1]*echelleY - 5);
	}
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	for (i = 0; i < nb; ++i)
	{
		glVertex2f(v[i].coords[0]*echelleX + 5, f.maxY - v[i].coords[1]*echelleY - 5);
	}
	glEnd();
}
