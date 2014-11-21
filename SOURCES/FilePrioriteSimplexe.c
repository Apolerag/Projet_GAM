/*! \file file_priorite_int.c
* \author A Chemier, R Lhomme
* \date 2014
*/

#include "FilePrioriteSimplexe.h"
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

void insererVertexFile(File_Priorite * f, simplexe * s)
{
	if(f->nbElements == f->nbElementsCourant) {
		printf("La file est pleine, on ne peut pas insérer.\n"); 
		return;
	}

	f->nbElementsCourant++;
	f->file[f->nbElementsCourant] = *s;

	int i ;
	i = f->nbElementsCourant ;
	while( (f->file[i/2].distanceMax > f->file[i/2].distanceMax) 
		&& (i > 1)) {
		echangeCase(f, i, i/2);
		i /= 2;
	}
}

simplexe* extremierFile(File_Priorite * f)
{
	echangeCase(f, 1, f->nbElementsCourant);
	f->nbElementsCourant--;
	double gauche, droite;

	int i = 1;
	while(2*i < f->nbElementsCourant)
	{
		gauche = f->file[2*i].distanceMax -  f->file[i].distanceMax;
		droite = f->file[(2*i)+1].distanceMax -  f->file[i].distanceMax;
		if((gauche > 0) && (droite > 0)) {
			//if(ordreLexicographiqueVertex(&f->file[2*i], &f->file[(2*i)+1]) == INFERIEUR) {
			if(f->file[2*i].distanceMax <  f->file[(2*i)+1].distanceMax) {
				echangeCase(f, i, 2*i);
				i *= 2 ; 
			}
			else {
				echangeCase(f, i, (2*i)+1);
				i *= 2 ; i += 1 ;
			}	
		}
		else if(gauche > 0) {
			echangeCase(f, i, 2*i);
			i *= 2 ; 
		}
		else if(droite > 0) {
			echangeCase(f, i, (2*i)+1);
			i *= 2 ; i += 1 ;
		}
		else
			break;
	}
	/* Cas spécial quand il n'y a plus que deux éléments */
	if(f->nbElementsCourant == 2) {
		if(f->file[1].distanceMax > f->file[2].distanceMax)
			echangeCase(f, 1, 2);
	}

	return &f->file[f->nbElementsCourant+1];
}

void echangeCase(File_Priorite * f, const int i, const int j)
{
	simplexe temp;
	temp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = temp;
}
