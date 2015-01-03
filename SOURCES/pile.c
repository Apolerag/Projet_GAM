/**
 *	@file pile.c
 * @author Aurélien Chemier
 * @author Romane Lhomme
 *	@date 2014
 */

#include "pile.h"

Pile* initialiserPile()
{
	Pile *p;
	ALLOUER(p,1);
	p->dernierPile = NULL;
	p->nbPile = 0;
	p->maxPile = 0;
	return p;
}

void insererPile(Pile *p, Simplexe *s, const time_t t)
{
	if(s->marqueurTemps != t){
		s->marqueurTemps = t;
		s->precedentPile = p->dernierPile;
		p->dernierPile = s;
		p->nbPile++;
		if(p->nbPile > p->maxPile) p->maxPile++;
	}
}

Simplexe* getSommetPile(Pile *p)
{
	Simplexe *s = p->dernierPile;
	if(s != NULL) {
		p->dernierPile = s->precedentPile;
		p->nbPile--;
	}
	return s;
}

int estVide(const Pile *p)
{
	if(p->nbPile == 0) return 1;
	return 0;
}
