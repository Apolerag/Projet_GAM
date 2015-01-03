/** 
 *	@file delaunay.h
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * 	@date 2014
 */

#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "base.h"
#include "filePrioriteSimplexe.h"
#include "vertex.h"	

/**
*	@brief valeur max des coordonnées z des Vertex
*/
#define H_MAX 1

/**
*	@struct Delaunay
*	@brief structure gérant la triangulation des Vertex
*	
* 	@param filePrioriteSimplexe: les Simplexe créés par la triangulation
*	@param tableauVertex: le tableau de Vertex à trianguler
*	@param nbVertex: le nombre de Vertex dans le tableau
*	@param nombreFacetteMax: le nombre maximal de Simplexe créés (défini par l'utilisateur)
*/
typedef struct 
{
	FileSimplexe *filePrioriteSimplexe;
	Vertex *tableauVertex;
	int nbVertex;
	int nombreFacetteMax;
	double distanceMin;
} Delaunay;

/**
 * @brief initialise une structure Delaunay en générant des Vertex aléatoirement dans le carré unité
 * @details la fonction génère aléatoirement nb Vertex et crée les deux premiers Simplexe de la triangulation 
 * 
 * @param nbVertex la taille du tableau de Vertex à allouer
 * @param nombreFacette le nombre maximum de Simplexe à créer
 * 
 * @return une structure Delaunay initialisée
 */
Delaunay *initialisation(const int nbVertex, const int nombreFacette, const double distance);

/**
 * @brief libère la place occupée en mémoire par d et ses composants
 * 
 * @param d un Delaunay initialisé
 */
void destruction(Delaunay *d);

/**
 * @brief Triangule les Vertex contenus dans d
 * 
 * @param d un Delaunay initialisé
 */
void triangulation(Delaunay *d);

/**
 * @brief Triangule les Vertex contenus dans d selon la methode de Delaunay
 * 
 * @param d un Delaunay initialisé
 */
void triangulationDelaunay(Delaunay *d);

#endif
