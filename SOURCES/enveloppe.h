#ifndef ENVELOPPE
#define ENVELOPPE

#include "vertex.h"

typedef struct 
{
	vertex *premier;
	vertex *dernier;
	unsigned int nb;
} enveloppe;

/*! initialise les pointeurs de l'enveloppe à NULL
* \arg e une enveloppe
*/
void initialiseEnveloppe(enveloppe *e);

/*! ajoute un vertex à la fin de la liste de vertices de l'enveloppe
* \arg e l'enveloppe
* \arg v le vertex 
*/
void ajouteFin(enveloppe *e, vertex *v);

/*! ajoute un vertexau début de la liste de vertices de l'enveloppe
* \arg e l'enveloppe
* \arg v le vertex 
*/
void ajouteDebut(enveloppe *e, vertex *v);

/*! enleve le dernier vertex de la liste de l'enveloppe
* \arg e l'enveloppe
*/
void enleveDernierElement(enveloppe *e);

/*! retourne le vertex de l'enveloppe avec le plus grand lexicographiquement
* \arg e l'enveloppe
*/
vertex *minEnveloppe(enveloppe *e);

/*! retourne le vertex de l'enveloppe avec le plus petit lexicographiquement
* \arg e l'enveloppe
*/
vertex *maxEnveloppe(enveloppe *e);

/*! calcul de l'enveloppe convexe des vertices en utilisant un algorithme "naif"
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void enveloppeConvexeBrut(vertex *v, enveloppe *e, const int nb);

/*! Calcul de l'enveloppe convexe selon la méthode de Jarvis
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void jarvis(vertex *v, enveloppe *e, const int nb);

/*! Calcul de l'enveloppe convexe selon la méthode de Graham
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void graham(vertex *v, enveloppe *e, const int nb);

/*! Calcul de l'enveloppe convexe selon la méthode d'insertion lexicographique
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void insertionLexicographique(vertex *v, enveloppe *e, const int nb);

/*! Calcul de l'enveloppe convexe selon la méthode divide and conquer
* \arg *v un tableau de vertices
* \arg nb le nombre de vertices
* \arg e l'enveloppe
*/
void divideAndConquer(vertex *v, enveloppe *e, const int nb);

enveloppe diviser(vertex *v, int deb, int fin);

/*! fusionne deux enveloppes entre elles */
enveloppe fusionEnveloppe(enveloppe e1, enveloppe e2);

#endif
