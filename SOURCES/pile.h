/**
 *	@file pile.h
 *  @author Aurélien Chemier
 *  @author Romane Lhomme
 *	@date 2014
 */

#ifndef PILE_H
#define PILE_H

#include "base.h"
#include "simplexe.h"

/**
 *	@struct Pile
 *	@brief une pile de Simplexe
 *	@details (utilisé par Delaunay)
 *	
 *	@param dernierPile le Simplexe en tête de Pile
 *	@param nbPile le nombre de Simplexe dans la pile
 *	@param maxPile le plus grand nombre de Simplexe que la pile ait eu
 */
typedef struct 
{
	Simplexe *dernierPile;
	int nbPile;
	int maxPile;
} Pile;

/**
 * @brief initialise une pile vide
 * @return une pile vide initialisée
 */
Pile* initialiserPile();

/**
 * @brief ajoute un élément dans la pile
 * 
 * @param p une Pile
 * @param s un Simplexe à inserer
 * @param t un marqueur pour controler si le s n'a pas déjà été empilé
 */
void insererPile(Pile *p, Simplexe *s, const time_t t);

/**
 * @brief récupère le dernier élément de la pile
 * 
 * @param p une Pile
 * @return le dernier élément de la Pile p
 */
Simplexe* getSommetPile(Pile *p);

/**
 * @brief controle si la pile est vide
 * 
 * @param p une Pile
 * @return 1 si la pile est vide, 0 sinon
 */
int estVide(const Pile *p);

#endif
