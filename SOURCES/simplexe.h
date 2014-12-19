/*! \file Simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef SIMPLEXE_H
#define SIMPLEXE_H

#include <time.h>
#include "vertex.h"

/*! paramètred de l'équation d'un plan de la forme:
*
*	\f$
*	a*x + b*y + c*z + d = 0
*	\f$
*/
typedef struct 
{
	double a;
	double b;
	double c;
	double d;
} Equation;

/*! Structure pour representer un triangle
*	\arg sommets les sommets du simplexe
*	\arg listeVertex la liste des vertex qui sont contenus dans le simplexe
*	\arg nbListe le nombre d'éléments dans la liste
*	\arg voisins les simplexes voisins du simplexe courant
*	\arg distanceMax la distance en le plan formé par le simplexe et le premier vertex de la liste
*/
typedef struct _Simplexe
{
	const Vertex *sommets[3];
	Vertex *listeVertex; //liste de vertices 
	// avec le vertex le plus loin du plan formé par le simplexe
	// en première position
	int nbListe;
	Equation e;
	struct _Simplexe *voisins[3];
	double distanceMax;

	/*gestion de la pile*/
	struct _Simplexe *precedentPile;
	time_t marqueurTemps; //

} Simplexe;

/*!	Pile de simplexe
* (utilisé par Delaunay)
*/
typedef struct 
{
	Simplexe *dernierPile;
} Pile;

/*! crée le Simplexe ABC*/
Simplexe* creationSimplexe(const Vertex *A, const Vertex *B, const Vertex *C);

/*! supprime les éléments occupés en mémoire par le Simplexe*/
void destructionSimplexe(Simplexe *s);

/*! retourne la position du Vertex N par rapport au Simplexe s
* DEDANS, DESSUS ou DEHORS 
*/
Position positionPointSimplexe(const Simplexe *s, const Vertex *N);

/*! ajoute un voisin au Simplexe*/
void ajouteVoisin(Simplexe *s, Simplexe *v0, Simplexe *v1, Simplexe *v2);

/*! ajoute un vertex dans la liste de vertices du Simplexe s
* 	si la distance est supérieur à la distance max courante du simplexe,
*	le vertex est ajouté en tête et la distance est mise à jour
*	sinon le vertex est inséré en position deux dans la liste
*	\arg s le simplexe où se situe le vertex
*	\arg v le vertex à insérer dans le simplexe
*   \arg distance la distance minimal entre le plan formé par s et v
*/
void ajouteVertex(Simplexe *s, Vertex *v);

/*! calcul l'équation du plan formé par s :
*
*	\f$
*	a*x + b*y + c*z + d = 0
*	\f$
*	
*	A la fin equation contient a,b,c et d.
*	\warning les trois vertices du simplexe ne sont pas alignés
*/
Equation equationPlan(const Simplexe *s);

/*! calcul la distance entre le simplexe s et le vertex v
*	abs(a*x+b*y+c*z+d)/sqrt(a2 +b2+ c2)
*/
double distanceVertexSimplexe(Simplexe *s, Vertex *v);		

const Vertex * getSommetOppose(Simplexe *s, Simplexe *Voisin);

/****************************************************************/
/*Pile*/

/*! ajoute un élément dans la pile
*
*/
void insererPile(Pile *p, Simplexe *s, const time_t t);

/*! récupère le dernier élément de la pile
*/
Simplexe* getSommetPile(Pile *p);

/*!	controle si la pile est vide
*	\return 1 si la pile est vide, 0 sinon
*/
int estVide(const Pile *p);

#endif
