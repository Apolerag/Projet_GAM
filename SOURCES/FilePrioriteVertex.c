/*! \file file_priorite_int.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include "FilePrioriteVertex.h"
#define ALLOUER(X,NB) X = malloc(sizeof(*(X)) * (NB))

File_Priorite * creerFile(const int nb_elements)
{ 
	File_Priorite * file_retour;
	ALLOUER(file_retour, 1);
	ALLOUER(file_retour->file, nb_elements + 1);
	file_retour->nbElements = nb_elements;
	file_retour->nbElementsCourant = 0;

	return file_retour;
}

void freeFile(File_Priorite * f)
{
	free(f->file);
	f->nbElements = 0;
}

void insererVertexFile(File_Priorite * f, vertex * v)
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

		echangeCase(f, i, i/2);
		i /= 2;
	}
}

void afficherFile(File_Priorite * f)
{
	int i;

	for(i = 1; i < f->nbElements + 1; i++) {
		printf("%d ", i);
		afficherVertex(&(f->file[i]));
	}
}

vertex* extremierFile(File_Priorite * f)
{
	echangeCase(f, 1, f->nbElementsCourant);
	f->nbElementsCourant--;
	Ordre gauche, droite;

	int i = 1;
	while(2*i < f->nbElementsCourant)
	{
		gauche = ordreLexicographiqueVertex(&f->file[i], &f->file[2*i]);
		droite = ordreLexicographiqueVertex(&f->file[i], &f->file[(2*i)+1]);
		if((gauche == SUPERIEUR) && (droite == SUPERIEUR)) {
			if(ordreLexicographiqueVertex(&f->file[2*i], &f->file[(2*i)+1]) == INFERIEUR) {
				echangeCase(f, i, 2*i);
				i *= 2 ; 
			}
			else {
				echangeCase(f, i, (2*i)+1);
				i *= 2 ; i += 1 ;
			}	
		}
		else if(gauche == SUPERIEUR) {
			echangeCase(f, i, 2*i);
			i *= 2 ; 
		}
		else if(droite == SUPERIEUR) {
			echangeCase(f, i, (2*i)+1);
			i *= 2 ; i += 1 ;
		}
		else
			break;
	}
	/* Cas spécial quand il n'y a plus que deux éléments */
	if(f->nbElementsCourant == 2) {
		if(ordreLexicographiqueVertex(&f->file[1], &f->file[2]) == SUPERIEUR)
			echangeCase(f, 1, 2);
	}

	return &f->file[f->nbElementsCourant+1];
}

void echangeCase(File_Priorite * f, const int i, const int j)
{
	vertex temp;
	temp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = temp;
}
