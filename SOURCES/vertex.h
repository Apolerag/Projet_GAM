/*! \file vertex.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#ifndef _VERTEX_H
#define _VERTEX_H

#include "base.h"

/*! Dimension de l'espace */
#define DIM 3

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
	DEHORS = 1
} Position;

/*! Structure pour representer un point. 
* \arg coords les coordonnées du vertex.
* \arg le vertex suivant dans une liste de vertices.
*/
typedef struct _Vertex
{
	double coords[DIM];	
	struct _Vertex *suivant;
} Vertex;

/*! Calcul le determinant de la matrice 3*3 
\f[
    \left |
	  \begin{array}{ccc}
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
* \return l'orientation du Vertex C par rapport x
*/
Orientation orientationPolaire(const Vertex *A, const Vertex *B, const Vertex *C);

/*! Retourne l'indice du min lexicographique des points du fichier
* \arg const Vertex *v un tableau de Vertex
* \arg const int taile la taille du tableau
*/
int minLexicographique(const Vertex *v, const int taille);

/*! Calcul la position d'un vertices par rapport à un triangle
* \arg A,B,C le triangle
* \arg N le point 
* \return la position
*/
Position positionPointTriangle(const Vertex *A, const Vertex *B, 
										const Vertex *C, const Vertex *N);


/*! \fn  InCircle (Vertex *A, Vertex *B, Vertex *C, Vertex *Z)
 *  \param A the first Vertex determining the circle
 *  \param B the second Vertex determining the circle
 *  \param C the last Vertex determining the circle
 *  \param Z the Vertex to be tested against the circle \f$\Gamma(A,B,C)\f$.
 *  \brief determines wether Vertex \a Z lies ouside, on, or inside
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
 *  corresponding to the relative position of Vertex \f$Z\f$ and
 *  the plane through the projections of vertices \f$A,B,C\f$
 *  on the paraboloid of revolution with equation
 *  \f[ z = x^2+y^2. \f]
 *  According to Guibas & Stolfi's result, the current routine should return:
 *   -  -1 (DEHORS) if Vertex \f$Z\f$ is outside circle \f$\Gamma(A,B,C)\f$,
 *   -  0 (DESSUS)  if Vertex \f$Z\f$ lies on circle \f$\Gamma(A,B,C)\f$, and
 *   -  1 (DEDANS)  if Vertex \f$Z\f$ lies inside circle \f$\Gamma(A,B,C)\f$.             
 *
 *  For convenience, as the only disturbing case is 
 *  \f$D\f$ lies inside \f$\Gamma(A,B,C)\f$,
 *  the routine actually returns: 
 *     1 (DEDANS)  if Vertex \f$Z\f$ strictly lies inside circle \f$\Gamma(A,B,C)\f$,
 *     0       otherwise.
 *
 *  \warning Vertices \f$A,B,C\f$ are ASSUMED neither to be aligned or equal.
 *           Overflow might arise otherwise. User must check this condition
 *           with function Angle() before calling present function.
 */
Position InCircle (Vertex *A, Vertex *B, Vertex *C, Vertex *Z);

#endif
