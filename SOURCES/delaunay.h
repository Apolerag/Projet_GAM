/*! \file delaunay.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "base.h"
#include "FilePrioriteSimplexe.h"
#include "vertex.h"	

#include <assert.h>

/*! Generation d'un nombre aleatoire entre deux bornes.
* \arg a : borne inferieure
* \arg b : borne superieure.
* \warning verifier que random() retourne bien un entier long entre 0 et RAND_MAX inclus.
*/
double myRandom (const double a, const double b);

/*! Generations des sites 
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
*/
void creationPoints (vertex *v, const int nb, File_Priorite *f);

#endif
