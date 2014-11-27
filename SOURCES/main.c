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
#include <time.h>

/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	//printf("\E[34;1mhel\E[mlo\n");
	int c;
	int nbPoints = 50;
	unsigned int nbFacette = 50;
	Vertex *v = NULL;
	FileSimplexe *f;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "hn:f:")) != EOF)
	{
		switch (c)
		{
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'f': 
				if ((sscanf(optarg, "%d", &nbFacette) != 1) || nbFacette <= 0)
					nbFacette = -1;
					printf("%u\n", nbFacette);
				break;
			case 'h':  
			default :
				printf("-n le nombre de Vertex (50 par défaut)\n");
				printf("-f le nombre de facette crée dans la triangulation\n");
				printf("un nombre négatif indique que toutes les facettes seront créés\n");
				printf("-h l'aide d'utilisation\n");
				return EXIT_SUCCESS;  
				break;
		}
	}
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
	glutInitWindowPosition(5,5);  
	glutInitWindowSize(500,500);

	glutCreateWindow("fenêtre"); 
	definitionFenetre(0, 50, 0, 50, 10);

	winInit();
	ALLOUER(v,nbPoints);
	f = creerFileSimplexe(2 * nbPoints);
	initialisation(v, nbPoints, f);

	displaySimplexe(f);
	glFlush();

	glutMainLoop(); 
	clearFenetre(v,nbPoints);
	return EXIT_SUCCESS;  


}  	
	
