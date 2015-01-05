/**
 * @file simplexe.h
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * @date 2014
 */

#ifndef Simplexe_H
#define Simplexe_H

#include <time.h>
#include "vertex.h"

/** 
 *	@struct Equation
 *	@brief paramètres de l'équation d'un plan :
 *	@details l'équation est de la forme :
 *	\f$
 *	a*x + b*y + c*z + d = 0
 *	\f$
 *	
 *	@param a, b, c, d les coefficients de l'équation.
 */
typedef struct 
{
	double a;
	double b;
	double c;
	double d;
} Equation;

/** 
 *	@struct Simplexe
 *	@brief Structure pour representer un triangle
 *	
 *	@param sommets les sommets du Simplexe
 *	@param listeVertex la liste des Vertex qui sont contenus dans le Simplexe, 
 *	le premier de la liste est également le plus éloigné du Simplexe
 *	@param nbListe le nombre d'éléments dans la liste
 *	@param voisins les Simplexes voisins du Simplexe courant
 *	@param distanceMax la distance en le plan formé par le Simplexe et le premier Vertex de la liste
 *  @param indiceDansFile l'indice du simplexe dans la file de priorité
*/
typedef struct _Simplexe
{
	const Vertex *sommets[3];
	Vertex *listeVertex;
	Equation e;
	struct _Simplexe *voisins[3];
	double distanceMax;

	/*gestion de la pile*/
	struct _Simplexe *precedentPile;
	time_t marqueurTemps;
	/* gestion de la file */
	int indiceDansFile;

} Simplexe;

/**
 * @brief crée le Simplexe ABC
 * 
 * @param A, B, C les trois sommet du Simplexe à créer
 * @return un Simplexe initialisé
 */
Simplexe* creationSimplexe(const Vertex *A, const Vertex *B, const Vertex *C);

/**
 * @brief retourne la position du Vertex N par rapport au Simplexe s
 * @details [long description]
 * 
 * @param s un Simplexe
 * @param N un Vertex
 * 
 * @return DEDANS, DESSUS ou DEHORS  en fonction de la position du Vertex par rapport au Simplexe
 */
Position positionPointSimplexe(const Simplexe *s, const Vertex *N);

/**
 * @brief ajoute ses voisin à un Simplexe
 * 
 * @param s un Simplexe
 * @param v0, v1, v2 trois Simplexe, les voisins de s
 */
void ajouteVoisin(Simplexe *s, Simplexe *v0, Simplexe *v1, Simplexe *v2);

/**
 * @brief ajoute un Vertex dans la liste de vertices du Simplexe s
 * @details si la distance est supérieur à la distanceMmax courante du Simplexe,
 * le Vertex est ajouté en tête et la distance est mise à jour
 * sinon le Vertex est inséré en position deux dans la liste
 * 
 * @param s le Simplexe où se situe le Vertex
 * @param v le Vertex à insérer dans le Simplexe
 */
void ajouteVertex(Simplexe *s, Vertex *v);

/**
 * @brief calcule l'équation du plan formé par s
 * @details A la fin equation contient a,b,c et d.
 * 
 * @warning les trois vertices du Simplexe ne sont pas alignés
 * @param s un Simplexe
 * @return l'équation de s
 */
Equation equationPlan(const Simplexe *s);

/**
 * @brief calcul la distance entre le Simplexe s et le Vertex v
 * @details la formule utilisé est \f$ | |-\frac{a * v.x + b*v.y + d}{c}| - |v.z| |  \f$
 * 
 * @param s un Simplexe
 * @param v un Vertex appartenant au Simplexe s
 * 
 * @return la distance entre v et son projeté orthogonal sur le plan formé par s
 */
double distanceVertexSimplexe(const Simplexe *s, const Vertex *v);		

/**
 * @brief retrouve le Vertex Sommet de voisin qui n'est pas Sommet de s
 * 
 * @param s un Simplexe
 * @param Voisin un Simplexe voisin de s
 * 
 * @return Le Vertex de Voisin n'etant pas un Sommet de s
 */
const Vertex * getSommetOppose(const Simplexe *s, Simplexe *Voisin);

/**
 * @brief modifie un voisin de s
 * 
 * @param s un Simplexe
 * @param ancienVoisin un voisin de s
 * @param nouveauVoisin le Simplexe qui remplace ancienVoisin en voisin de s
 */
void controleNouveauVoisin(Simplexe *s, Simplexe *ancienVoisin, Simplexe *nouveauVoisin);

/**
 * @brief réoganise s1 et s2 quand InCircle retourne DEDANS
 * 
 * @param s1 un Simplexe 
 * @param s2 un Voisin de s1 dont le sommet opposé appartient au cercle formé par les sommet de s1
 * @param v le resultat de getSommetOppose(const Simplexe *s, Simplexe *Voisin) pour s1 et s2
 * 
 *  @warning s1 et s2 sont voisins
 */
void echangeSimplexe(Simplexe *s1, Simplexe *s2, const Vertex *v);

/**
 * @brief affiche les valeurs du simplexe sur la sortie standard
 * 
 * @param s un Simplexe
 */
void afficheSimplexe(const Simplexe *s);

#endif
