/** 
 *	@file base.h
 *  @author Aurélien Chemier
 *  @author Romane Lhomme
 *	@date 2014
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
 
/**
 * @brief Génération d'un nombre aléatoire entre borné entre A et B.
 * 
 * @param A  borne inferieure
 * @param B  borne superieure
 * @return un double entre A et B
 */
#define RAND(A,B) ( rand()/(double)RAND_MAX ) * (B - A) + A;

/*! 
*	@brief ALLOUER permet d'allouer à X un emplacement mémoire de taille NB
*	@param X le type qui doit être allouer
*	@param NB la taille à allouer
*/
#define ALLOUER(X,NB) X = malloc(sizeof(*(X)) * (NB))
