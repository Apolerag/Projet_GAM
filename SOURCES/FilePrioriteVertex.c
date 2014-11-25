/*! \file file_priorite_int.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include "FilePrioriteVertex.h"
#define ALLOUER(X,NB) X = malloc(sizeof(*(X)) * (NB))

FileVertex * creerFileVertex(const int nb_elements)
{ 
	FileVertex * file_retour;
	ALLOUER(file_retour, 1);
	ALLOUER(file_retour->file, nb_elements + 1);
	file_retour->nbElements = nb_elements;
	file_retour->nbElementsCourant = 0;

	return file_retour;
}

void freeFileVertex(FileVertex * f)
{
	free(f->file);
	f->nbElements = 0;
}

void insererFileVertex(FileVertex * f, vertex * v)
{
	if(f->nbElements == f->nbElementsCourant) {
		printf("La file est pleine, on ne peut pas insérer.\n"); 
		return;
	}

	f->nbElementsCourant++;
	f->file[f->nbElementsCourant] = *v;

	int i ;
	i = f->nbElementsCourant ;
	while((ordreLexicographiqueVertex(&(f->file[i/2]), &(f->file[i])) == SUPERIEUR) 
		&& (i > 1)) {

		echangeCaseVertex(f, i, i/2);
		i /= 2;
	}
}

void afficherFileVertex(FileVertex * f)
{
	int i;

	for(i = 1; i < f->nbElements + 1; i++) {
		printf("%d ", i);
		afficherVertex(&(f->file[i]));
	}
}

vertex* extremierFileVertex(FileVertex * f)
{
	echangeCaseVertex(f, 1, f->nbElementsCourant);
	f->nbElementsCourant--;
	Ordre gauche, droite;

	int i = 1;
	while(2*i < f->nbElementsCourant)
	{
		gauche = ordreLexicographiqueVertex(&f->file[i], &f->file[2*i]);
		droite = ordreLexicographiqueVertex(&f->file[i], &f->file[(2*i)+1]);
		if((gauche == SUPERIEUR) && (droite == SUPERIEUR)) {
			if(ordreLexicographiqueVertex(&f->file[2*i], &f->file[(2*i)+1]) == INFERIEUR) {
				echangeCaseVertex(f, i, 2*i);
				i *= 2 ; 
			}
			else {
				echangeCaseVertex(f, i, (2*i)+1);
				i *= 2 ; i += 1 ;
			}	
		}
		else if(gauche == SUPERIEUR) {
			echangeCaseVertex(f, i, 2*i);
			i *= 2 ; 
		}
		else if(droite == SUPERIEUR) {
			echangeCaseVertex(f, i, (2*i)+1);
			i *= 2 ; i += 1 ;
		}
		else
			break;
	}
	/* Cas spécial quand il n'y a plus que deux éléments */
	if(f->nbElementsCourant == 2) {
		if(ordreLexicographiqueVertex(&f->file[1], &f->file[2]) == SUPERIEUR)
			echangeCaseVertex(f, 1, 2);
	}

	return &f->file[f->nbElementsCourant+1];
}

void echangeCaseVertex(FileVertex * f, const int i, const int j)
{
	vertex temp;
	temp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = temp;
}
