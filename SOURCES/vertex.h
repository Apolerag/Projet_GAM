/*! \file vertex.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef _VERTEX_H
#define _VERTEX_H

#include "base.h"

/*! Dimension de l'espace */
#define DIM 2

/*! enum pour representer l'orientation de trois points*/
typedef enum
{
	GAUCHE = -1, 
	ALIGNES = 0, 
	DROITE = 1
} Orientation;

/*! enum pour la position du point par rapport a un polygone*/
typedef enum
{
	DEDANS = -1,
	DESSUS = 0,
	DEHORS = 1,
	POLYGONE = 2
} Position;

/*! enum pour comparer deux vertex*/
typedef enum {
	INFERIEUR = -1,
	EGAUX = 0,
	SUPERIEUR = 1
} Ordre;

/*! Structure pour representer un point. */
typedef struct _vertex
{
	double coords[DIM];	
	Position position;
	struct _vertex *precedent;
	struct _vertex *suivant;
} vertex;


/*! Calcul le determinant de la matrice 3*3 
\f[
    \left |
	  \begin{array}{cccc}
	   a & b & c  \\
	   d & e & f \\
	   g & h & i \\
	  \end{array}
	\right |
 *  \f]
*/
double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i);


/*! Calcul l'orientation polaire des Vertex A, B et C
* \arg A, B et C les trois Vertices dont on veut calculer l'angle
* \return l'orientation du vertex C par rapport x
*/
Orientation orientationPolaire(const vertex *A, const vertex *B, const vertex *C);

/*! Retourne l'indice du min lexicographique des points du fichier
* \arg const vertex *v un tableau de vertex
* \arg const int taile la taille du tableau
*/
int minLexicographique(const vertex *v, const int taille);

/*! Calcul la position d'un vertices par rapport à un triangle
* \arg A,B,C le triangle
* \arg N le point 
* \return la position
*/
Position positionPointTriangle(const vertex *A, const vertex *B, 
										const vertex *C, const vertex *N);


/*! affiche les informations d'un vertex*/
void afficherVertex(const vertex * v);

/*! compare lexicographiquement deux vertex - retourne INFERIEUR si le premier est 
	inférieur lexicographiquement au deuxième, EGAUX si les deux vertexs sont 
	confondus, SUPERIEUR sinon */
Ordre ordreLexicographiqueVertex(const vertex * v1, const vertex * v2);

/*! \fn  InCircle (vertex *A, vertex *B, vertex *C, vertex *Z)
 *  \param A the first vertex determining the circle
 *  \param B the second vertex determining the circle
 *  \param C the last vertex determining the circle
 *  \param Z the vertex to be tested against the circle \f$\Gamma(A,B,C)\f$.
 *  \brief determines wether vertex \a Z lies ouside, on, or inside
 *  the circle passing through \a A, \a B and \a C.
 *
 *  Let \f$\Gamma(ABC)\f$ be the circle around vertices \f$A, B, C\f$.
 *  Guibas and Stolfi have shown that the relative position of \f$Z\f$
 *  and \f$\Gamma(A,B,C)\f$ is equivalent to computing the sign 
 *  of determinant:
 *  \f[
        \left |
	  \begin{array}{cccc}
	   x_A     & y_A     & x_A^2+y_A^2  & 1 \\
	   x_B     & y_B     & x_B^2+y_B^2  & 1 \\
	   x_C     & y_C     & x_C^2+y_C^2  & 1 \\
	   x_Z     & y_Z     & x_Z^2+y_Z^2  & 1 \\
	  \end{array}
	\right |
 *  \f]
 *  corresponding to the relative position of vertex \f$Z\f$ and
 *  the plane through the projections of vertices \f$A,B,C\f$
 *  on the paraboloid of revolution with equation
 *  \f[ z = x^2+y^2. \f]
 *  According to Guibas & Stolfi's result, the current routine should return:
 *   -  -1 (DEHORS) if vertex \f$Z\f$ is outside circle \f$\Gamma(A,B,C)\f$,
 *   -  0 (DESSUS)  if vertex \f$Z\f$ lies on circle \f$\Gamma(A,B,C)\f$, and
 *   -  1 (DEDANS)  if vertex \f$Z\f$ lies inside circle \f$\Gamma(A,B,C)\f$.             
 *
 *  For convenience, as the only disturbing case is 
 *  "\f$D\f$ lies inside \f$\Gamma(A,B,C)\f$",
 *  the routine actually returns: 
 *     1 (DEDANS)  if vertex \f$Z\f$ strictly lies inside circle \f$\Gamma(A,B,C)\f$,
 *     0       otherwise.
 *
 *  \warning Vertices \f$A,B,C\f$ are ASSUMED neither to be aligned or equal.
 *           Overflow might arise otherwise. User must check this condition
 *           with function Angle() before calling present function.
 */
Position InCircle (vertex *A, vertex *B, vertex *C, vertex *Z);

#endif
