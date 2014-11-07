#include "enveloppe.h"
#include "fenetre.h"
#include "FilePrioriteVertex.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void initialiseEnveloppe(enveloppe *e)
{
	e->premier = NULL;
	e->dernier = NULL;
	e->nb = 0;
}

void ajouteFin(enveloppe *e, vertex *v)
{
	if(e->nb == 0)
	{
		v->precedent = v->suivant = v;
		e->premier = e->dernier = v;
	}
	else
	{
		e->dernier->suivant = v;

		v->suivant = e->premier;
		v->precedent = e->dernier;
		e->dernier = v;
	}
	e->nb++;
}

void ajouteDebut(enveloppe *e, vertex *v)
{
	if(e->nb == 0)
	{
		v->precedent = v->suivant = v;
		e->premier = e->dernier = v;
	}
	else
	{
		e->premier->precedent = v;

		v->suivant = e->premier;
		v->precedent = e->dernier;
		e->premier = v;
	}
	e->nb++;
}

void enlevePremierElement(enveloppe *e)
{	
	if(e->nb == 1 || e->nb == 0)
	{
		e->premier = e->dernier = NULL;
		e->nb = 0;
	}
	else
	{
		vertex *t = e->premier->suivant;
		t->precedent = e->dernier;
		e->premier->suivant = e->premier->precedent = NULL;
		e->premier = t;

		e->nb --;
	}
}

void enleveDernierElement(enveloppe *e)
{
	if(e->nb == 1 || e->nb == 0)
	{
		e->premier = e->dernier = NULL;
		e->nb = 0;
	}
	else
	{
		vertex *t = e->dernier->precedent;
		t->suivant = e->premier;
		e->dernier->precedent = e->dernier->suivant = NULL;
		e->dernier = t;

		e->nb --;
	}
}

vertex *minEnveloppe(enveloppe *e)
{
	if(e->nb == 0) return NULL;
	if(e->nb == 1) return e->premier;

	vertex * min = e->premier;
	vertex *courant = e->premier;

	do
	{
		if(ordreLexicographiqueVertex(courant, min) == INFERIEUR)
		{
			min = courant;
		}
		courant = courant->suivant;
	}
	while(courant != e->premier);

	return min;
}

vertex *maxEnveloppe(enveloppe *e)
{
	if(e->nb == 0) return NULL;
	if(e->nb == 1) return e->premier;

	vertex * max = e->premier;
	vertex *courant = e->premier;

	do	
	{
		if(ordreLexicographiqueVertex(courant, max) == SUPERIEUR)
		{
			max = courant;
		}
		courant = courant->suivant;
	}
	while(courant != e->premier);

	return max;
}

void enveloppeConvexeBrut(vertex *v, enveloppe *e, const int nb)
{
	/* calcul le temps d'execution*/
	double temps;
    clock_t t1, t2;

    initialiseEnveloppe(e);
	assert(v != NULL);
	assert(nb > 0);

	int min = minLexicographique(v, nb);
	int i = min, j, k;
	int surEnveloppe;

 	/*demarrage du chrono*/
	t1 = clock();
	
	/*calcul de l'enveloppe convexe*/
	do
	{
		ajouteFin(e,&v[i]);

		surEnveloppe = 0;
		j = 0;
		while( j < nb && !surEnveloppe)
		{
			if(i != j)
			{
				
				k = 0;
				while(k < nb && orientationPolaire(&v[i],&v[j],&v[k]) == GAUCHE)
				{
					k++;
					while(k == j || k== i)
					{
						k++;
					}
					
				}
				if(k == nb)
				{
					i = j; //j devient la valeur suivante
					surEnveloppe = 1;
				}
			}
			j++;
		}
	} while (i != min);	

	/*calcul du temps d'execution*/
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée brute : %lf\n", temps);

    /*affichage de l'enveloppe*/
    effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);
	glFlush();
}

void jarvis(vertex *v, enveloppe *e, const int nb)
{
	double temps;
    clock_t t1, t2;

    initialiseEnveloppe(e);
	assert(v != NULL);
	assert(nb > 0);

	int min = minLexicographique(v, nb);
	int courant = min, suivant, i;

 	/*demarrage du chrono*/
	t1 = clock();
	do
	{
		ajouteFin(e,&v[courant]);
		suivant = (courant + 1)%nb;
		for (i = 0; i < nb; ++i)
		{
			if(i != courant && i != suivant)
			{
				if(orientationPolaire(&v[courant], &v[suivant], &v[i]) == DROITE)
					suivant = i;	
			}
		}
		courant = suivant;
	} while (courant != min);	

	/*calcul du temps d'execution*/
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée jarvis : %lf\n", temps);

    /*affichage de l'enveloppe*/
    effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);
	glFlush();
}

void graham(vertex *v, enveloppe *e, const int nb)
{
	double temps;
	clock_t t1, t2;
	initialiseEnveloppe(e);
	int i;
	vertex *liste = NULL;
	vertex *courant = NULL, *suivant = NULL, *precedent = NULL;

	/*demarrage du chrono*/
	t1 = clock();

	int min = minLexicographique(v, nb);
	ajouteFin(e, &v[min]);

	/* creation de la liste de vertices*/
	for (i = 0; i < nb; ++i)
	{
		if(i != min)
		{
			v[i].suivant = liste;
			liste = &v[i];
		}
	}

	liste = trier(liste, &v[min]);
	precedent = liste;
	courant = precedent->suivant;
	suivant = courant->suivant;
	ajouteFin(e,precedent);

	while (courant != NULL)
	{
		while((e->premier != e->dernier) && (orientationPolaire(e->dernier->precedent,e->dernier,courant) == DROITE))
		{
			enleveDernierElement(e);
		}
		suivant = courant->suivant;
		ajouteFin(e,courant);
		courant = suivant;
	}
	t2 = clock();
	temps = (double)(t2-t1)/CLOCKS_PER_SEC;
	printf("durée graham : %lf\n", temps);
	effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);
	glFlush();
}

void insertionLexicographique(vertex *v, enveloppe *e, const int nb)
{
	double temps;
    clock_t t1, t2;
    initialiseEnveloppe(e);
    vertex **bas, **haut;
    ALLOUER(bas,nb);
    ALLOUER(haut,nb);

     /*demarrage du chrono*/
	t1 = clock();

	int i,h,b;
	triPartition(v, nb);

	printf("creation triangle de base\n");
	
	bas[0] = &v[0];
	haut[0] = &v[0];

	bas[1] = &v[1];
	haut[1] = &v[1];;

	h = b = 1;
	i = 2;
	printf("insertion des points\n");
	for(i = 2; i < nb; i++)
	{
		b++;h++;
		//afficherVertex(t);
		bas[b] = &v[i];
		haut[h] = &v[i];
		/* enveloppe basse*/
		while(b > 1 && 
		 	orientationPolaire(bas[b],bas[b-2],bas[b-1])
			== GAUCHE)
			{ 
				bas[b-1] = bas[b];
				b--;
			} 
		
		/* enveloppe haute*/
			while(h > 1 && 
		 	orientationPolaire(haut[h],haut[h-2],haut[h-1])
			== DROITE)
			{ 
				haut[h-1] = haut[h];
				h--;
			} 
	}

	printf("b %d, h %d\n",b,h );
	for (i = 0; i < b; ++i)
	{
		ajouteFin(e,bas[i]);
	}
	for (i = h; i > 0; --i)
	{
		ajouteFin(e,haut[i]);
	}
	t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;
    printf("durée insertionLexicographique : %lf\n", temps);

    effaceFenetre();
    printf("displayEnveloppe\n");
	displayEnveloppe(e);
	printf("displayPoints\n");
	displayPoints(v, nb);
	glFlush();

	free(haut);
	free(bas);
}

void divideAndConquer(vertex *v, enveloppe *e, const int nb)
{
	double temps;
	clock_t t1, t2;
	/*demarrage du chrono*/
	t1 = clock();

	triPartition(v, nb);
	*e = fusionEnveloppe(diviser(v, 0, nb/2), diviser(v, nb/2, nb));

	t2 = clock();
	temps = (double)(t2-t1)/CLOCKS_PER_SEC;

	printf("durée divideAndConquer : %lf\n", temps);
	effaceFenetre();
	displayEnveloppe(e);
	displayPoints(v, nb);
	glFlush();
}

enveloppe diviser(vertex *v, int deb, int fin)
{
	assert(deb <= fin);
	enveloppe e;
	int i;
	if( fin - deb <= 3)
	{
		printf("cas d'arret\n");
		initialiseEnveloppe(&e);
		for (i = deb; i < fin; ++i)
		{
			ajouteFin(&e, &v[i]);
		}
	}
	else e = fusionEnveloppe(diviser(v, deb, (fin+deb)/2), diviser(v, (fin+deb)/2, fin));
	return e;
}

enveloppe fusionEnveloppe(enveloppe g, enveloppe d)
{
	printf("debut fusion\n");
	enveloppe e;
	initialiseEnveloppe(&e);
	vertex *courant, *suivant;
	printf("calcul g,d\n");
	vertex *gd = maxEnveloppe(&g);
	vertex *gg = minEnveloppe(&g);
	printf("min\n");
	vertex *dg = minEnveloppe(&d); 
	vertex *dd = maxEnveloppe(&d);
	
	vertex *hg = NULL, *bg = NULL, *hd = NULL, *bd = NULL; 

	/*fusion haute*/
	printf("fusion haute\n");
	vertex *courantG = gd;
	vertex *courantD = dg;
	vertex *suivantG = courantG->suivant;
	vertex *suivantD = courantD->precedent;

	courant = g.premier;
	printf("g->nb %d\n", g.nb);
	do
	{
		afficherVertex(courant);
		courant = courant->suivant;	
	}
	while(courant != g.premier);
	courant = d.premier;
	printf("g->nb %d\n", d.nb);
	do
	{
		afficherVertex(courant);
		courant = courant->suivant;	
	}
	while(courant != d.premier);
	printf("\n");
	afficherVertex(dd);
	afficherVertex(dg);
	afficherVertex(gd);
	afficherVertex(gg);

	printf("while 1\n");
	while( ( (orientationPolaire(courantG,courantD, suivantD) == GAUCHE)||
		     (orientationPolaire(suivantG,courantG, courantD) == GAUCHE) ) 
		    && (courantD != dd)   && (courantG != gg) )
	{
		printf("while 1.1 \n");
		while(orientationPolaire(courantG,courantD, suivantD) == GAUCHE && courantD != dd)
		{
			//afficherVertex(courantD);
			courantD = suivantD;
			suivantD = suivantD->precedent;
		}
		printf("while 1.2 \n");
		while(orientationPolaire(suivantG,courantG, courantD) == GAUCHE && courantG != gg)
		{
			courantG = suivantG;
			suivantG = suivantG->suivant;
		}
	}
	hg = courantG; hd = courantD;

	/*fusion basse*/
	courantG = gd;
	courantD = dg;
	suivantG = courantG->precedent;
	suivantD = courantD->suivant;

	while( ( (orientationPolaire(courantG,courantD, suivantD) == DROITE)||
		     (orientationPolaire(suivantG,courantG, courantD) == DROITE) ) 
		    && (courantD != dd)   && (courantG != gg) )	
	{
		printf("while 2.1 \n");
		while(orientationPolaire(courantG,courantD, suivantD) == DROITE  && courantD != dd)
		{
			courantD = suivantD;
			suivantD = suivantD->suivant;
		}
		printf("while 2.2\n");
		while(orientationPolaire(suivantG,courantG, courantD) == DROITE  && courantG != gg)
		{
			courantG = suivantG;
			suivantG = suivantG->precedent;
		}
	}
	printf("fin while 2 \n");
	bg = courantG; bd = courantD;

	/*on recolle les morceaux*/

	bg->suivant = bd;
	hd->suivant = hg;

	courant = g.premier;

	printf("recolle\n");
	printf("g->nb %d\n", g.nb);
	do
	{
		if(courant == g.dernier) printf("dernier\n");
		suivant = courant->suivant;
		ajouteFin(&e, courant);
		courant = suivant;	
	}
	while(courant != g.premier);
	printf(" return\n");

	return e;
}
