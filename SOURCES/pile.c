/**
 *	@file pile.c
 * @author Aurélien Chemier
 * @author Romane Lhomme
 *	@date 2014
 */

#include "pile.h"

void insererPile(Pile *p, Simplexe *s, const time_t t)
{
	if(s->marqueurTemps != t){
		s->marqueurTemps = t;
		s->precedentPile = p->dernierPile;
		p->dernierPile = s;
	}
}

Simplexe* getSommetPile(Pile *p)
{
	Simplexe *s = p->dernierPile;
	if(s != NULL) 
		p->dernierPile = s->precedentPile;
	return s;
}

int estVide(const Pile *p)
{
	if(p->dernierPile == NULL) return 1;
	return 0;
}
