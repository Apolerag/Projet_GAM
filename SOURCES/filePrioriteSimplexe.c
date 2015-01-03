/**
 * @file FilePrioriteSimplexe.c
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
	/*while(f->nbElementsCourant > 0)
	{
		s = extremierFileSimplexe(f);
		///free(s);
		
	}*/
	printf("boucle %d\n",f->nbElementsCourant);
	for (i = 1; i <= f->nbElementsCourant; ++i)
	{
		//free(f->file[i]);
	}
	printf("fin boucle\n");
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
	if(f->nbElements == f->nbElementsCourant) {
		printf("La file est pleine, on ne peut pas insérer.\n"); 
		return;
	}

	f->nbElementsCourant++;
	f->file[f->nbElementsCourant] = s;
	
	int i ;
	i = f->nbElementsCourant ;
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
	echangeCaseSimplexe(f, 1, f->nbElementsCourant);
	f->nbElementsCourant--;
	double gauche, droite, courant;

	int i = 1;
	while(2*i < f->nbElementsCourant)
	{
		gauche = getGauche(f,i);
		droite = getDroite(f,i);
		courant = f->file[i]->distanceMax;
		//printf("gauche %lf droite %lf courant %lf\n", gauche, droite, courant);

		if(gauche > courant && gauche > droite) {
			//printf("gauche\n");
			echangeCaseSimplexe(f, i, 2*i);
			i *= 2 ; 
		}
		else if(droite > courant){
			//printf("droite\n");
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
	temp = f->file[i];
	f->file[i] = f->file[j];
	f->file[j] = temp;
}

void retriFileSimplexe(FileSimplexe * f)
{
	int i,j;
	double gauche, droite, courant;

	for ( i = f->nbElementsCourant / 2; i >= 1; --i)
	{
		j = i;
		while(j <= f->nbElementsCourant) {
			gauche = getGauche(f,j);
			droite = getDroite(f,j);
			courant = f->file[j]->distanceMax;
			if(gauche > courant && gauche > droite) {
				echangeCaseSimplexe(f, j, 2*j);
				j*=2;
			}
			else if(droite > courant){
				echangeCaseSimplexe(f, j, (2*j)+1);
				j = 2*j+1;
			}	
			else break;
		}
	}
}
