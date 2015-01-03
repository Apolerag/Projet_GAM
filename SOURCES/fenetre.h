/**
 *	@file fenetre.h
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * 	@date 2014
*/

#ifndef _FENETRE_H
#define _FENETRE_H

#include "base.h"
#include "delaunay.h"
#include "vertex.h"

#include <assert.h>
#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

/**
*	@struct Fenetre
*	@brief Tailles diverses du systeme de fenêtrage .
*/
typedef struct {
	double minX;
	double maxX;
	double minY;
	double maxY;
} Fenetre;

/**
*	@brief la fenêtre qui est affichée
*/
Fenetre f;

/**
*	@brief modifie les dimensions de la Fenetre
* 	@param X_min, X_max, Y_min, Y_max les nouvelles dimensions de la Fenetre
*/

void definitionFenetre(const double X_min, const double X_max, const double Y_min, const double Y_max);

/**
*	@brief vide la Fenetre.
*/
void clearFenetre();

/**
*	@brief Incantation d'ouverture de Fenetre OpenGL. 
*/
void winInit();

/**
*	@brief dessine les arêtes des Simplexe
*	@details Les Simplexe ont été créés par triangulationDelaunay(Delaunay *d) ou triangulation(Delaunay *d).
*	Les Vertex qui non pas été inséré dans la triangulation sont également affichés.
*/
void displaySimplexeLigne(Delaunay *d);

/**
*	@brief dessine les Simplexe
*	@details Les Simplexe ont été créés par triangulationDelaunay(Delaunay *d) ou triangulation(Delaunay *d).
*	Les Vertex qui non pas été inséré dans la triangulation sont également affichés.
*/
void displaySimplexeTriangle(Delaunay *d);

#endif
