/*! \file FilePrioriteSimplexe.h
* \author A Chemier, R Lhomme
* \date 2014
*/

#ifndef FILE_PRIORITE_SIMPLEXE_H
#define FILE_PRIORITE_SIMPLEXE_H

#include <stdlib.h>
#include <stdio.h>
#include "simplexe.h"

/*!
*	\struct FileSimplexe
*	\brief une file priorité de Simplexe
*
*/
typedef struct {
   Simplexe ** file; 	/*gestion dynamique de la mémoire occupée*/
   int nbElements;	/*nombre d'éléments maximum dans la file*/
   int nbElementsCourant;
} FileSimplexe;


/*! initialise la file par defaut*/
FileSimplexe * creerFileSimplexe(const int nb_elements);

/*! libere la place mémoire occupé par la file*/
void freeFileSimplexe(FileSimplexe * f);

/*! retourne la valeur du fils gauche de la case i*/
double getGauche(const FileSimplexe *f, const int i);

/*! retourne la valeur du fils droit de la case i*/
double getDroite(const FileSimplexe *f, const int i);

/*! insere l'élément n dans la file, celle ci est retriée automatiquement*/
void insererFileSimplexe(FileSimplexe * f, Simplexe * s);	

/* retourne la valeur de la première case de la file de priorité*/
double getValeurPremier(FileSimplexe * f);

/*! récupère et enleve le premier élément de la file, celle ci est réorganisée*/
Simplexe* extremierFileSimplexe(FileSimplexe * f);

/*! échange le contenu des cases i et j de la file*/
void echangeCaseSimplexe(FileSimplexe * f, const int i, const int j);

/*! retri la file de priorité*/
void retriFileSimplexe(FileSimplexe * f);

void afficheFile(FileSimplexe *f);

#endif
