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

	glutMainLoop(); 
	clearFenetre(v,nbPoints);
	return EXIT_SUCCESS;  


}  
/*

int main(int argc, char **argv)  
{ 
	Simplexe *s;
	Vertex *A, *B, *C;
	ALLOUER(A,1); ALLOUER(B,1);	ALLOUER(C,1);

	double *tab;
	A->coords[0] = 0; A->coords[1] = 0; A->coords[2] = 0; 
	B->coords[0] = 3; B->coords[1] = 0; B->coords[2] = 0; 
	C->coords[0] = 2; C->coords[1] = 3; C->coords[2] = 0; 

	s = creationSimplexe(A,B,C);
	tab = equationPlan(s);

	fprintf(stderr, "%f %f %f %f\n", tab[0], tab[1], tab[2], tab[3]);

	free(A); free(B); free(C);
	free(s);
	free(tab);
}
*/
