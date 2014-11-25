/*! \file base.h
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

/*! Generation d'un nombre aleatoire entre deux bornes.
* \arg a : borne inferieure
* \arg b : borne superieure.
* \warning verifier que random() retourne bien un entier long entre 0 et RAND_MAX inclus.
*/
#define RAND(A,B) ( rand()/(double)RAND_MAX ) * (B - A) + A;

/*! ALLOUER permet d'allouer à X un emplacement mémoire de taille NB*/
#define ALLOUER(X,NB) X = malloc(sizeof(*(X)) * (NB))

/*! MAX retourne le max de A et B*/
#define MAX(A,B) ( (A)>=(B) ? (A) : (B) )

/*! MIN retourne le min de A et B*/
#define MIN(A,B) ( (A)<=(B) ? (A) : (B) )

/*! Calcule la taille du tableau T*/
#define TAILLE(T) ( sizeof(T) / sizeof(T[0]))

#define FWD 1
#define BWD 0
