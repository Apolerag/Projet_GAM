/*! \file delaunay.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "base.h"
#include "FilePrioriteSimplexe.h"
#include "vertex.h"	

/*! Generations des vertices dans le carré unité
* la fonction génère aléatoirement nb vertices et crée les deux premiers simplexes de la triangulation 
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg f la file de priorité contenant les simplexes
*/
void creationPoints (vertex *v, const int nb, FileSimplexe *f);

void separationSimplexe(FileSimplexe *f, simplexe *s);

#endif
