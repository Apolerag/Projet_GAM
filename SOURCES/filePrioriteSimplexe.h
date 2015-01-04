/** 
 *	@file filePrioriteSimplexe.h
 *  @author Aurélien Chemier
 *  @author Romane Lhomme
 * 	@date 2014
 */

#ifndef FILE_PRIORITE_SIMPLEXE_H
#define FILE_PRIORITE_SIMPLEXE_H

#include <stdlib.h>
#include <stdio.h>
#include "simplexe.h"

/**
*	@struct FileSimplexe
*	@brief une file priorité de Simplexe
*	@details les Simplexe sont triés en fonction de leurs distanceMax, 
*	plus celle ci est grand, plus le Simplexe est prioritaire
*	
*	@param file un tableau de pointeurs sur Simplexe
*	@param nbElements la taille du tableau
*	@param nbElementsCourant le nombre de case occupé dans le tableau
*/

typedef struct {
   Simplexe ** file; 
   int nbElements;	
   int nbElementsCourant;
} FileSimplexe;

/**
 * @brief initialise une file de priorité 
 * @details alloue une file de taille nb_elements + 1 , nbElement égale nb_element et nbElementcourant égale 0
 * 
 * @param nb_elements la taille de la FileSimplexe à allouer
 * @return une FilePriorité initialisée
 */
FileSimplexe * creerFileSimplexe(const int nb_elements);

/**
 * @brief libère la place occupé en mémoire par f
 * @details vide la liste, libère les Simplexe, libère le tableau et finalement libere la file
 * 
 * @param f une FileSimplexe initialisée
 */
void freeFileSimplexe(FileSimplexe * f);

/**
 * @brief retourne la distance du fils gauche de la case i
 * @details controle si le fils gauche existe (2*i <=  f->nbElementsCourant)
 * et renvoie la distance max de la case 2*i
 * 
 * @param f une FileSimplexe initialisée
 * @param i la case dont on veut le fils gauche
 * 
 * @return la distance max du Simplexe en position 2*i, -1 si celui çi n'existe pas 
 */
double getGauche(const FileSimplexe *f, const int i);

/**
 * @brief retourne la distance du fils droit de la case i
 * @details controle si le fils gauche existe (2*i+1 <=  f->nbElementsCourant)
 * et renvoie la distance max de la case 2*i+1
 * 
 * @param f une FileSimplexe initialisée
 * @param i la case dont on veut le fils droit
 * 
 * @return la distance max du Simplexe en position 2*i+1, -1 si celui çi n'existe pas 
 */
double getDroite(const FileSimplexe *f, const int i);

/**
 * @brief insere un Simplexe dans la FileSimplexe
 * @details Après avoir controlé si une place est disponible dans le tableau,
 * le Simplexe s est inseré en queue de file.
 * Il est ensuite remonté dans la file tant que sa priorité est supérieur à celle de son parent ou 
 * qu'il est en première position de la file.
 * 
 * @param f une FileSimplexe initialisée
 * @param s un Simmplexe à insérer dans la file
 */
void insererFileSimplexe(FileSimplexe * f, Simplexe * s);	

/**
 * @brief retourne la distance de la première case de la file de priorité
 * @details la distance permet de savoir s'il reste des Vertex à trianguler.
 * Si la valeur retournée est -1, celà signifie que tous les Simplexe de la file ne contiennent pas de Vertex
 * 
 * @param f une FileSimplexe initialisée
 * @return la distanceMax du premier Simplexe de la file
 */
double getValeurPremier(FileSimplexe * f);

/*! récupère et enleve le premier élément de la file, celle ci est réorganisée*/
/**
 * @brief récupère le premier élément de la file
 * @details la file est ensuite réorganisé pour garder les Simplexe prioritaire en haut de file
 * 
 * @param f une FileSimplexe initialisée
 * @return le premier Simplexe de la file
 */
Simplexe* extremierFileSimplexe(FileSimplexe * f);

/**
 * @brief échange le contenu des cases i et j de la file
 * 
 * @param f une FileSimplexe initialisée
 * @param i la première case à échanger 
 * @param j la deuxième case à échanger 
 */
void echangeCaseSimplexe(FileSimplexe * f, const int i, const int j);

/**
 * @brief retrie la file
 * @details La file est réorganisé en fonction de la priorité de ses Simplexe
 * 
 * @param f une FileSimplexe initialisée
 */
void retriFileSimplexe(FileSimplexe * f);

/**
 * @brief replace le simplexe s au bon endroit dans la file de priorité
 * 
 * @param f une FileSimplexe initialisée contenant au moins un pointeur sur 
 * le simplexe s
 * @param s le simplexe qui doit être rangé a la bonne place dans la file
 */
void triFileSimplexe(FileSimplexe * f, Simplexe * s);

#endif
