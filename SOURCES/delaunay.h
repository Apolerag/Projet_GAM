/*! \file delaunay.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "base.h"
#include "filePrioriteSimplexe.h"
#include "vertex.h"	

#define H_MAX 1000

typedef struct 
{
	FileSimplexe *filePrioriteSimplexe;
	vertex *tableauVertices;
	int nbVertices;
} Delaunay;

/*! Générations des vertices dans le carré unité
* la fonction génère aléatoirement nb vertices et crée les deux premiers simplexes de la triangulation 
* \arg v un tableau vide de vertices de taille nbVertex
* \arg f la file de priorité contenant les simplexes
*/

//à remplacer par struct delaunay
void initialisation(vertex *v, const int nbVertex, FileSimplexe *f);

//à remplacer par struct delaunay
void separationSimplexe(FileSimplexe *f, simplexe *s);

#endif
