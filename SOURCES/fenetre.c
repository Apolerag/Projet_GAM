/*! \file Fenetre.c
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

void clearFenetre()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void winInit()
{
	gluOrtho2D(f.minX, f.maxX, f.minY, f.maxY);
}

void displayPoints(const Vertex *v, const int nbVertex)
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
	for (i = 0; i < nbVertex; ++i)
	{
		glVertex2f(v[i].coords[0]*echelleX + 5, f.maxY - v[i].coords[1]*echelleY - 5);
	}
	glEnd();
}

void displaySimplexe(Delaunay *d)
{
	Simplexe *s;
	Vertex *v;
	int i,j;
	int echelleX = f.maxX - 10;
	int echelleY = f.maxY - 10;
	int c = 0;

	glColor3f(0.0, 0.0, 0.0);
  	glClear(GL_COLOR_BUFFER_BIT);
	
	for (j = 1; j < d->filePrioriteSimplexe->nbElementsCourant+1; ++j)
	{
		s = &d->filePrioriteSimplexe->file[j];

		//tracage du triangle
		glBegin(GL_TRIANGLES);
		double r = RAND(0, 1);
		double g = RAND(0, 1);
		double b = RAND(0, 1);
		glColor3f(r, g, b);
		for (i = 0; i < 3; ++i)
		{
			glVertex2f(s->sommets[i]->coords[0]*echelleX + 5, 
				f.maxY - s->sommets[i]->coords[1]*echelleY - 5);
			c++;
		}
		glEnd();

		v = s->listeVertex;
		//tracage des vertices contenus dans le simplexe
		glBegin(GL_POINTS);
		glColor3f(1-r, 1-g, 1-b);


		while(v != NULL)
		{
			glVertex2f(v->coords[0]*echelleX + 5, 
				f.maxY - v->coords[1]*echelleY - 5);
			v = v->suivant;
			c++;
		}
		glEnd();
	}
	glFlush();
}

