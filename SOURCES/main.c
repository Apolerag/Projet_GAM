/*! \file main.c
* \author Aurélien Chemier, Romane Lhomme
* \date 2014
*/

#include "fenetre.h"
#include "delaunay.h"
#include "filePrioriteSimplexe.h"

#include <assert.h>  
#include <math.h>  
#include <stdio.h>
#include <stdlib.h>

/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	//printf("\E[34;1mhel\E[mlo\n");
	int c;
	int nbPoints = 50;
	int nbFacette = -1;
	int affiche = 0;
	int triangle = 0;
	Delaunay *d = NULL;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "af:hn:t:")) != EOF)
	{
		switch (c)
		{
			case 'a':
					affiche = 1;
				break;
			case 'f': 
				if ((sscanf(optarg, "%d", &nbFacette) != 1) || nbFacette <= 0)
					nbFacette = -1; // un nombre négatif indique que toutes les facettes seront créées
				break;
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 't': 
				if ((sscanf(optarg, "%d", &triangle) != 1) || (triangle != 0 && triangle != 1))
					triangle = 0;
				break;
			case 'h':  
			default :
				printf("-a l'affichage du résultat\n");
				printf("-f le nombre de facettes maximum crées par la triangulation (toutes par default)\n");
				printf("-h l'aide d'utilisation\n");
				printf("-t le type de l'affichage (0 ligne, 1 triangle\n");
				printf("-n le nombre de Vertex (50 par défaut)\n");
				return EXIT_SUCCESS;  
		}
	}
	if(affiche) {
		glutInit(&argc, argv);  
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
		glutInitWindowPosition(5,5);  
		glutInitWindowSize(700,700);
		glutCreateWindow("fenêtre"); 
		definitionFenetre(0, 700, 0, 700, 10);
	}

	winInit();
	d = initialisationTest(nbPoints, nbFacette);
	triangulationDelaunay(d);
	printf("fin triangulationDelaunay\n");
	if(affiche){
		printf("%d\n", triangle);
		if(triangle == 0) displaySimplexeLigne(d);
		else displaySimplexeTriangle(d);
		glutMainLoop();
	}
	printf("Fin affiche\n");

	clearFenetre();
	destruction(d);

	printf("return\n");
	return EXIT_SUCCESS;  
}  

/*
int main(int argc, char **argv)  
{
	Simplexe *s;
	FileSimplexe *file;
	file = creerFileSimplexe(1000000);
	int i;
	srand(time(NULL)); 
	for (i = 1; i <= 1000000; ++i)
	{
		ALLOUER(s,1);
		s->distanceMax = RAND(0,100);
		file->file[i] = s;
	}
	file->nbElements = file->nbElementsCourant = 1000000;


	retriFile(file);
	while(file->nbElementsCourant > 0) {
		s = extremierFileSimplexe(file);
		free(s);
	}



	freeFileSimplexe(file);

	return EXIT_SUCCESS;
}*/
