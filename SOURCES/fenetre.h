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

/*! contient le nom du fichier à lire*/
char *in;

/*! contient le nom du fichier à écrire*/
char *out;

/*! Tailles diverses du systemes de fenetrage .*/
typedef struct {
	double minX;
	double maxX;
	double minY;
	double maxY;
	double margin;
} fenetre;

/*! la fenêtre qui est affichée*/
fenetre f;

/*! modifie la dimension de la fenetre
* \arg X_min, X_max, Y_min, Y_max, margin les nouvelles dimensions de la fenetre
*/
void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max, const double margin);

/*! vide la fenetre
*
*/
void clearFenetre(vertex *v, const int nbVertex);

/*! Incantation d'ouverture de fenetre OpenGL */
void winInit();

void effaceFenetre();

void displayPoints(const vertex *v, const int nbVertex);

void displaySimplexe(FileSimplexe *f);

#endif
