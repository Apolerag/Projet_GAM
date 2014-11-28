/*! \file fenetre.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef _FENETRE_H
#define _FENETRE_H

#include "base.h"
#include "filePrioriteSimplexe.h"
#include "vertex.h"

#include <assert.h>
#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

/*! Tailles diverses du systeme de fenetrage .*/
typedef struct {
	double minX;
	double maxX;
	double minY;
	double maxY;
	double margin;
} Fenetre;

/*! la fenêtre qui est affichée*/
Fenetre f;

/*! modifie la dimension de la Fenetre
* \arg X_min, X_max, Y_min, Y_max, margin les nouvelles dimensions de la Fenetre
*/
void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin);

/*! vide la Fenetre
*
*/
void clearFenetre(Vertex *v, const int nbVertex);

/*! Incantation d'ouverture de Fenetre OpenGL */
void winInit();

void effaceFenetre();

void displayPoints(const Vertex *v, const int nbVertex);

void displaySimplexe(FileSimplexe *f);

#endif
