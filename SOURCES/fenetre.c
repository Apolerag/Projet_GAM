/*! \file fenetre.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include <assert.h>
#include "fenetre.h"

void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin)
{
	f.minX = X_min;
	f.maxX = X_max;
	f.minY = Y_min;
	f.maxY = Y_max;
	f.margin = margin;
}

void clearFenetre(vertex *v, int nb)
{
	free(v);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void winInit()
{
	gluOrtho2D(f.minX, f.maxX, f.minY, f.maxY);
}

double myRandom (double a, double b)
{
	double tmp = random(); /* long int in [0, RAND_MAX] */

	return a+tmp*((b-a)/RAND_MAX);
}

void selectPoints (vertex *v, const int nb)
{
	int n = nb;
	while (--n >= 0)
	{	
		v[n].coords[0] = myRandom(f.minX , f.maxX);
		v[n].coords[1] = myRandom(f.minY, f.maxY);
	}
		
//	displayPoint(v,nb);
}

void effaceFenetre()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void displayEnveloppe(const enveloppe *e)
{

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 1.0);

	vertex *j = e->premier;

	while(j != e->dernier)
	{
		glVertex2f(j->coords[0],f.maxY - j->coords[1]);
		j = j->suivant;
	}
	glEnd();

}

void displayPoints(const vertex *v, const int nb)
{
	int i;
	int min = minLexicographique(v, nb);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	for (i = 0; i < nb; ++i)
	{
		if(i == min) glColor3f(1.0, 0.0, 0.0);
		else glColor3f(0.0, 1.0, 0.0);
		glVertex2f(v[i].coords[0], f.maxY - v[i].coords[1]);
	}
	glEnd();
}
