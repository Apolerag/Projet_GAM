/*! \file FilePrioriteVertex.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef FILE_PRIORITE_VERTEX_H
#define FILE_PRIORITE_VERTEX_H

#include <stdlib.h>
#include <stdio.h>
#include "vertex.h"


typedef struct {
   Vertex * file; 	/*gestion dynamique de la mémoire occupée*/
   int nbElements;	/*nombre d'éléments maximum dans la file*/
   int nbElementsCourant;
} FileVertex;


/*! initialise la file par defaut*/
FileVertex * creerFileVertex(const int nb_elements);

/*! libere la place mémoire occupé par la file*/
void freeFileVertex(FileVertex * f);

/*! insere l'élément n dans la file, celle ci est retriée automatiquement*/
void insererFileVertex(FileVertex * f, Vertex * v);

/*! affiche le contenu de la file*/
void afficherFileVertex(FileVertex * f);

/*! récupère et enleve le premier élément de la file, celle ci est réorganisée*/
Vertex* extremierFileVertex(FileVertex * f);

/*! échange le contenu des cases i et j de la file*/
void echangeCaseVertex(FileVertex * f, const int i, const int j);

#endif
