/*! \file file_prioriteInt.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef FILE_PRIORITE_VERTEX_H
#define FILE_PRIORITE_VERTEX_H

#include <stdlib.h>
#include <stdio.h>
#include "simplexe.h"

typedef struct {
   simplexe * file; 	/*gestion dynamique de la mémoire occupée*/
   int nbElements;	/*nombre d'éléments maximum dans la file*/
   int nbElementsCourant;
} File_Priorite;


/*! initialise la file par defaut*/
File_Priorite * creerFile(const int nb_elements);

/*! libere la place mémoire occupé par la file*/
void freeFile(File_Priorite * f);

/*! insere l'élément n dans la file, celle ci est retriée automatiquement*/
void insererVertexFile(File_Priorite * f, simplexe * v);

/*! récupère et enleve le premier élément de la file, celle ci est réorganisée*/
simplexe* extremierFile(File_Priorite * f);

/*! échange le contenu des cases i et j de la file*/
void echangeCase(File_Priorite * f, const int i, const int j);

#endif
