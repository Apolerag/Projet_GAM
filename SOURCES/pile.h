#ifndef PILE_H
#define PILE_H

#include "simplexe.h"

/*!	
*	\Struct Pile
*	\brief Pile de simplexe
*	
*	(utilisé par Delaunay)
*/
typedef struct 
{
	Simplexe *dernierPile;
} Pile;

/*! 
*	\brief ajoute un élément dans la pile
*/
void insererPile(Pile *p, Simplexe *s, const time_t t);

/*! 
*	\brief récupère le dernier élément de la pile
*	\return le premier élément de la Pile p
*/
Simplexe* getSommetPile(Pile *p);

/*!	
*	\brief controle si la pile est vide
*	\return 1 si la pile est vide, 0 sinon
*/
int estVide(const Pile *p);

#endif
