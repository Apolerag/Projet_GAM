/**
 * @file filePrioriteSimplexe.c
 * @author Aurélien Chemier
 * @author Romane Lhomme
 * @date 2014
 */

#include "filePrioriteSimplexe.h"

FileSimplexe * creerFileSimplexe(const int nb_elements)
{ 
	FileSimplexe * file_retour;
	ALLOUER(file_retour, 1);
	ALLOUER(file_retour->file, nb_elements + 1);
	file_retour->nbElements = nb_elements;
	file_retour->nbElementsCourant = 0;
	return file_retour;
}

void freeFileSimplexe(FileSimplexe * f)
{
	int i;
	
	for (i = 1; i <= f->nbElementsCourant; ++i)
	{
		free(f->file[i]);
	}
	free(f->file);
	free(f);
}

double getGauche(const FileSimplexe *f, const int i)
{
	if(2*i <=  f->nbElementsCourant){
		return f->file[2*i]->distanceMax;
	}
	return -1;
}

double getDroite(const FileSimplexe *f, const int i)
{
	if((2*i)+1 <=  f->nbElementsCourant){
		return f->file[(2*i)+1]->distanceMax;
	}
	return -1;
}

void insererFileSimplexe(FileSimplexe * f, Simplexe * s)
{
	int i;
	if(f->nbElements == f->nbElementsCourant) {
		printf("La file est pleine, on ne peut pas insérer.\n"); 
		return;
	}

	f->nbElementsCourant++;
	f->file[f->nbElementsCourant] = s;
	
	i = f->nbElementsCourant ;
	s->indiceDansFile = i;
	while((i > 1) && (f->file[i]->distanceMax > f->file[i/2]->distanceMax)) {
		echangeCaseSimplexe(f, i, i/2);
		i /= 2;
	}
}

double getValeurPremier(FileSimplexe * f)
{
	if(f->nbElementsCourant > 0)
		return f->file[1]->distanceMax;
	else return -1;
}

Simplexe* extremierFileSimplexe(FileSimplexe * f)
{
	int i;
	double gauche, droite, courant;

	echangeCaseSimplexe(f, 1, f->nbElementsCourant);
	f->nbElementsCourant--;

	i = 1;
	while(2*i < f->nbElementsCourant)
	{
		gauche = getGauche(f,i);
		droite = getDroite(f,i);
		courant = f->file[i]->distanceMax;

		if(gauche > courant && gauche > droite) {
			echangeCaseSimplexe(f, i, 2*i);
			i *= 2 ; 
		}
		else if(droite > courant){
			echangeCaseSimplexe(f, i, (2*i)+1);
			i *= 2 ; i += 1 ;
		}	
		else
			break;
	}
	/* Cas spécial quand il n'y a plus que deux éléments */
	if(f->nbElementsCourant == 2) {
		if(f->file[1]->distanceMax < f->file[2]->distanceMax)
			echangeCaseSimplexe(f, 1, 2);
	}

	return f->file[f->nbElementsCourant+1];
}

void echangeCaseSimplexe(FileSimplexe * f, const int i, const int j)
{
	Simplexe* temp;

	f->file[i]->indiceDansFile = j;
	f->file[j]->indiceDansFile = i;

	temp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = temp;
}

void triFileSimplexe(FileSimplexe * f, Simplexe * s)
{
	int indice;
	indice = s->indiceDansFile;

	while(indice > 1 && f->file[indice]->distanceMax > f->file[indice/2]->distanceMax) {
		
		echangeCaseSimplexe(f, indice, indice/2);
		indice /= 2;
	}
	while( 2*indice < f->nbElementsCourant &&
			(f->file[indice]->distanceMax < getGauche(f, indice) || 
				f->file[indice]->distanceMax < getDroite(f, indice) ) ) {

		double gauche = getGauche(f,indice);
		double droite = getDroite(f,indice);
		double courant = f->file[indice]->distanceMax;

		if(gauche > courant && gauche > droite) {
			echangeCaseSimplexe(f, indice, 2*indice);
			indice *= 2 ; 
		}
		else if(droite > courant){
			echangeCaseSimplexe(f, indice, (2*indice)+1);
			indice = 2*indice + 1 ;
		}	
		else
			break;
	}
}
