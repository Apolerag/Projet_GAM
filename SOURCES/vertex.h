/**
 * @file vertex.h
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * @date 2014
 */

#ifndef _VERTEX_H
#define _VERTEX_H

#include "base.h"

/**
 * @brief Dimension de l'espace
 */
#define DIM 3

/**
 * @brief permet de gérer l'orientation des angles polaires  
 */
typedef enum
{
	GAUCHE,	/**< -1*/ 
	ALIGNES,/**< 0*/ 
	DROITE	/**< 1*/ 
} Orientation;

/**
 * @brief enum pour la position du point par rapport à un polygone
 */ 
typedef enum
{
	DEDANS, /**< -1*/ 
	DESSUS, /**< 0*/ 
	DEHORS /**< 1*/ 
} Position;

/**
 *	@struct Vertex 
 *	@brief permet de représenter un point
 *	
 *	@param coords les coordonnées du Vertex
 *	@param suivant le pointeur sur le Vertex suivant dans une liste de Vertex
 */
typedef struct _Vertex
{
	double coords[DIM];	
	struct _Vertex *suivant;
} Vertex;


void afficheVertex(const Vertex *v);

/**
 * @brief Calcul le determinant de la matrice 3*3 
 * @details la matrice est de la forme:
 * \f[
    \left |
	  \begin{array}{ccc}
	   a & b & c  \\
	   d & e & f \\
	   g & h & i \\
	  \end{array}
	\right |
 *  \f]
 * 
 * @param a, b, c, d, e, f, g, h et i les valeurs des cases de la matrices 
 * @return le determinant de la matrice 
 */
double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i);

/**
 * @brief Calcul l'orientation polaire des Vertex A, B et C
 * @details pour cela la fonction calcule le determinant de la matrice formé par les coordonnées des Vertex.
 * le signe du determinant permet de connaitre l'orientation
 * -  < 0 DROITE
 * -  = 0 ALIGNES
 * -  > 0 GAUCHE
 * 
 * 
 * @param A, B et C trois Vertex
 * @return GAUCHE, ALIGNES ou DROITE selon le signe du determminant
 */
Orientation orientationPolaire(const Vertex *A, const Vertex *B, const Vertex *C);

/** 
*	@brief Calcul la position d'un vertices par rapport à un triangle
*	@param A,B,C le triangle
*	@param N le point 
*	@return la position
*/
Position positionPointTriangle(const Vertex *A, const Vertex *B, 
										const Vertex *C, const Vertex *N);

/** 
*	@param A the first Vertex determining the circle
*	@param B the second Vertex determining the circle
*	@param C the last Vertex determining the circle
*	@param Z the Vertex to be tested against the circle \f$\Gamma(A,B,C)\f$.
*	@brief determines wether Vertex \a Z lies ouside, on, or inside
*	the circle passing through \a A, \a B and \a C.
*
*	@details Let \f$\Gamma(ABC)\f$ be the circle around vertices \f$A, B, C\f$.
*	Guibas and Stolfi have shown that the relative position of \f$Z\f$
*	and \f$\Gamma(A,B,C)\f$ is equivalent to computing the sign 
*	of determinant:
*	\f[
	\left |
	\begin{array}{cccc}
	x_A     & y_A     & x_A^2+y_A^2  & 1 \\
	x_B     & y_B     & x_B^2+y_B^2  & 1 \\
	x_C     & y_C     & x_C^2+y_C^2  & 1 \\
	x_Z     & y_Z     & x_Z^2+y_Z^2  & 1 \\
	\end{array}
	\right |
*	\f]
*
*	corresponding to the relative position of Vertex \f$Z\f$ and
*	the plane through the projections of vertices \f$A,B,C\f$
*	on the paraboloid of revolution with equation
*	\f[ z = x^2+y^2. \f]
*	According to Guibas & Stolfi's result, the current routine should return:
*	-  -1 (DEHORS) if Vertex \f$Z\f$ is outside circle \f$\Gamma(A,B,C)\f$,
*	-  0 (DESSUS)  if Vertex \f$Z\f$ lies on circle \f$\Gamma(A,B,C)\f$, and
*	-  1 (DEDANS)  if Vertex \f$Z\f$ lies inside circle \f$\Gamma(A,B,C)\f$.             
*
*	For convenience, as the only disturbing case is 
*	\f$D\f$ lies inside \f$\Gamma(A,B,C)\f$,
*	@returns 1 (DEDANS) if Vertex \f$Z\f$ strictly lies inside circle \f$\Gamma(A,B,C)\f$, -1 (DEHORS) otherwise.
*
*	@warning Vertices \f$A,B,C\f$ are ASSUMED neither to be aligned or equal.
*	Overflow might arise otherwise. User must check this condition
*	with function Angle() before calling present function.
*/
Position InCircle (const Vertex *A, const Vertex *B, const Vertex *C, const Vertex *Z);

#endif
