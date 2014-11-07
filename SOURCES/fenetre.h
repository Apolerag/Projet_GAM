/*! \file fenetre.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef _FENETRE_H
#define _FENETRE_H

#include "vertex.h"
#include "base.h"
#include "enveloppe.h"

#include <unistd.h>  
#include <GL/glut.h> 
#include <stdio.h>
#include <stdlib.h>
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
void clearFenetre(vertex *v,int nb);

/*! Incantation d'ouverture de fenetre OpenGL */
void winInit();

/*! Generation d'un nombre aleatoire entre deux bornes.
* \arg a : borne inferieure
* \arg b : borne superieure.
* \warning verifier que random() retourne bien un entier long entre 0 et RAND_MAX inclus.
*/
double myRandom (double a, double b);

/*! Generations des sites 
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
*/
void selectPoints (vertex *v, const int nb);

void effaceFenetre();

void displayEnveloppe(const enveloppe *e);

void displayPoints(const vertex *v, const int nb);

#endif
