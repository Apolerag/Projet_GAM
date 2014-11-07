/*! \file base.h
* \author A Chemier, R Lhomme
* \date 2014
*/

/*! ALLOUER permet d'allouer à X un emplacement mémoire de taille NB*/
#define ALLOUER(X,NB) X = malloc(sizeof(*(X)) * (NB))

/*! MAX retourne le max de A et B*/
#define MAX(A,B) ( (A)>=(B) ? (A) : (B) )

/*! MIN retourne le min de A et B*/
#define MIN(A,B) ( (A)<=(B) ? (A) : (B) )

#define TAILLE(T) ( sizeof(T) / sizeof(T[0]))

#define FWD 1
#define BWD 0
