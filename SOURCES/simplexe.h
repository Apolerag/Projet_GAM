/*! \file Simplexe.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef Simplexe_H
#define Simplexe_H

#include <time.h>
#include "vertex.h"

/*! 
*	\struct Equation
*	\brief paramètre de l'équation d'un plan de la forme:
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

/*! 
*	\struct Simplexe
*	\brief Structure pour representer un triangle
*	\arg sommets les sommets du Simplexe
*	\arg listeVertex la liste des Vertex qui sont contenus dans le Simplexe
*	\arg nbListe le nombre d'éléments dans la liste
*	\arg voisins les Simplexes voisins du Simplexe courant
*	\arg distanceMax la distance en le plan formé par le Simplexe et le premier Vertex de la liste
*/
typedef struct _Simplexe
{
	const Vertex *sommets[3];
	Vertex *listeVertex; //liste de vertices 
	// avec le Vertex le plus loin du plan formé par le Simplexe
	// en première position
	int nbListe;
	Equation e;
	struct _Simplexe *voisins[3];
	double distanceMax;

	/*gestion de la pile*/
	struct _Simplexe *precedentPile;
	time_t marqueurTemps; //

} Simplexe;

/*! crée le Simplexe ABC*/
Simplexe* creationSimplexe(const Vertex *A, const Vertex *B, const Vertex *C);

/*! supprime les éléments occupés en mémoire par le Simplexe*/
//void destructionSimplexe(Simplexe *s);

/*! retourne la position du Vertex N par rapport au Simplexe s
* DEDANS, DESSUS ou DEHORS 
*/
Position positionPointSimplexe(const Simplexe *s, const Vertex *N);

/*! ajoute un voisin au Simplexe*/
void ajouteVoisin(Simplexe *s, Simplexe *v0, Simplexe *v1, Simplexe *v2);

/*! ajoute un Vertex dans la liste de vertices du Simplexe s
* 	si la distance est supérieur à la distance max courante du Simplexe,
*	le Vertex est ajouté en tête et la distance est mise à jour
*	sinon le Vertex est inséré en position deux dans la liste
*	\arg s le Simplexe où se situe le Vertex
*	\arg v le Vertex à insérer dans le Simplexe
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
*	\warning les trois vertices du Simplexe ne sont pas alignés
*/
Equation equationPlan(const Simplexe *s);

/*! calcul la distance entre le Simplexe s et le Vertex v
*	abs(a*x+b*y+c*z+d)/sqrt(a2 +b2+ c2)
*/
double distanceVertexSimplexe(const Simplexe *s, const Vertex *v);		

/*!	s et voisin sont deux Simplexes voisins
*	la fonction retourne le vetex sommet de Voisin qui n'est pas un sommet de s
*/
const Vertex * getSommetOppose(const Simplexe *s, Simplexe *Voisin);

/*!	Controle les voisins de s et remplace ancienVoisin par nouveauVoisin
*
*/
void controleNouveauVoisin(Simplexe *s, Simplexe *ancienVoisin, Simplexe *nouveauVoisin);

/*!
*	\fn void echangeSimplexe(Simplexe *s1, Simplexe *s2, const int i);
*	\brief échange les Simplexe s1 et s2 quand s2->sommet[i] est dans le cercle formé par les sommets de s1
*
*	\param s1 et s2 deux Simplexe voisin
*	\param i le Vertex de s2 non sommet de s1
*
*	\warning s1 et s2 sont voisins
*/
void echangeSimplexe(Simplexe *s1, Simplexe *s2, const Vertex *v);

void afficheSimplexe(const Simplexe *s);

#endif
