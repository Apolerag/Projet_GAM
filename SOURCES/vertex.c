#include "vertex.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double determinant(const double a, const double b, const double c,
				const double d, const double e, const double f,
				const double g, const double h, const double i)
{
	return (a*e*i + d*h*c + g*b*f) - (g*e*c + a*h*f + d*b*i);
}

Orientation orientationPolaire(const vertex *A, const vertex *B, const vertex *C)
{
	double det = determinant(1,1,1,
						   A->coords[0],B->coords[0],C->coords[0],
						   A->coords[1],B->coords[1],C->coords[1]);
	if(det < 0) return DROITE;
	else if(det > 0) return GAUCHE;
	else return ALIGNES;
}

int minLexicographique(const vertex *v, const int taille)
{
	
	vertex minL = v[0];
	int indice = 0 ;
	
	int i ;
	for(i = 1; i < taille; i++) 
	{
		if( (v[i].coords[0] < minL.coords[0]) ||
			((v[i].coords[0] == minL.coords[0]) && (v[i].coords[1] < minL.coords[1])))
		{
			minL = v[i]; 
			indice = i ;
		}
	}
	return indice ;
}

/*! Calcul la position des vertices par rapport au triangle
* 
*/
Position positionPointTriangle(const vertex *A, const vertex *B, 
										const vertex *C, const vertex *N)
{
	Position position;
	Orientation O1 = orientationPolaire(A,B,N) ;
	Orientation O2 = orientationPolaire(B,C,N) ;
	Orientation O3 = orientationPolaire(C,A,N) ;
	if(O1 == DROITE || O2 == DROITE || O3 == DROITE)
		position = DEHORS; 
	else if(O1 == ALIGNES || O2 == ALIGNES  || O3 == ALIGNES )
		position = DESSUS; 
	else position = DEDANS; 
	
	return position;
}

void afficherVertex(const vertex * v)
{
	int i;
	printf("Vertex : ");
	for(i=0; i<DIM; i++)
		printf("%lf ", v->coords[i]);
	printf("\n");
}

Ordre ordreLexicographiqueVertex(const vertex * v1, const vertex * v2)
{
	int i;
	for(i=0; i<DIM; i++)
	{
		if(v1->coords[i] < v2->coords[i])
			return INFERIEUR ;
		else if(v1->coords[i] > v2->coords[i])
			return SUPERIEUR ;
	}
	return EGAUX ;
}

void afficherListe(vertex *v)
{
	vertex *j = v;
	while (j != NULL)
	{
		printf("%lf, %lf \n",j->coords[0], j->coords[1]);
		j = j->suivant;
	}

}

/* tri fusion de la liste*/
vertex* separer(vertex *liste)
{
	vertex *m;
	if (liste == NULL || liste->suivant == NULL)
		return NULL;
	else
	{
		m = liste->suivant;
		liste->suivant = m->suivant;
		m->suivant=separer(m->suivant);
		return m;
	}
}
vertex* fusion(vertex *lg,vertex *ld, const vertex *origin)
{
	vertex *retour = NULL;
	if (lg == NULL)
	{
		return ld;
	}
	if (ld == NULL)
	{
		return lg;
	}
	if(orientationPolaire(origin, lg,ld ) == DROITE)
	{
		retour = ld;
		ld = ld->suivant;
	}
	else
	{
		retour = lg;
		lg = lg->suivant;
	}
	
	vertex *courant = retour;
	retour->suivant = NULL;
	while(lg != NULL && ld != NULL)
	{
		if(orientationPolaire(origin, lg,ld) == DROITE)
		{
			courant->suivant = ld;
			ld = ld->suivant;
		}
		else
		{
			courant->suivant = lg;
			lg = lg->suivant;
		}
		courant = courant->suivant;
	}
	if(lg != NULL) courant->suivant = lg;
	else courant->suivant = ld;
	return retour;
}

vertex* trier(vertex* l, const vertex *origin)
{
	vertex * m;
	if (l != NULL && l->suivant != NULL)
	{
		m = separer(l);
		l = trier(l,origin);
		m = trier(m,origin);
		l = fusion(l,m,origin);
	}
	return l;
}

/*tri Partition*/

void echanger(vertex *v ,const int i,const int j)
{ 
	vertex tmp;
	tmp=v[i];
	v[i]=v[j];
	v[j]=tmp;
}

int partition(vertex *v, const int deb, const int fin)
{ 
	int compt = deb; 
	vertex pivot = v[deb]; 
	int i; 
	for (i = deb+1; i <= fin; i++)
	{ 
		if (ordreLexicographiqueVertex(&v[i], &pivot) == INFERIEUR)
		{
			compt++;
			echanger(v,compt,i);
		}
	
	}
	echanger(v,compt,deb); 
	return compt;
}

void triPartitionBis(vertex *v,const int debut,const int fin)
{ 
	if (debut<fin)
	{ 
		int pivot = partition(v,debut,fin);
		triPartitionBis(v, debut, pivot-1);
		triPartitionBis(v, pivot+1, fin);
	}
}

void triPartition(vertex *v, const int nb)
{
	triPartitionBis(v, 0, nb-1); 
}
