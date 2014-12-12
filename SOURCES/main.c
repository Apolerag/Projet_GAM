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
	int affiche = 1;
	Delaunay *d = NULL;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "a:f:hn:")) != EOF)
	{
		switch (c)
		{
			case 'a':
				if ((sscanf(optarg, "%d", &affiche) != 1) || (affiche != 0 && affiche != 1))
					affiche = 1;
				break;
			case 'f': 
				if ((sscanf(optarg, "%d", &nbFacette) != 1) || nbFacette <= 0)
					nbFacette = -1; // un nombre négatif indique que toutes les facettes seront créés
					printf("%u\n", nbFacette);
				break;
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'h':  
			default :
				printf("-a l'affichage du résultat (1 affiche, 0 n'affiche pas) (par defaut 1)\n");
				printf("-f le nombre de facettes crée par la triangulation (toutes par default)\n");
				printf("-h l'aide d'utilisation\n");
				printf("-n le nombre de Vertex (50 par défaut)\n");
				return EXIT_SUCCESS;  
				break;
		}
	}
	if(affiche) {
		glutInit(&argc, argv);  
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  
		glutInitWindowPosition(5,5);  
		glutInitWindowSize(500,500);
		glutCreateWindow("fenêtre"); 
		definitionFenetre(0, 50, 0, 50, 10);
	}

	winInit();
	d = initialisation(nbPoints, nbFacette);
	triangulation(d);

	if(affiche){
		displaySimplexe(d);
		glutMainLoop();
	}
	 
	clearFenetre();
	destruction(d);

	return EXIT_SUCCESS;  

}  

/*
int main(int argc, char **argv)  
{ 
	Vertex v1, v2, v3, v4;
	Simplexe *s;

	
	v1.coords[0] = 0; v1.coords[1] = 0, v1.coords[2] = 0;
	v2.coords[0] = 2; v2.coords[1] = 0, v2.coords[2] = 0;
	v3.coords[0] = 2; v3.coords[1] = 2, v3.coords[2] = 0;
	v4.coords[0] = 1; v4.coords[1] = 1, v4.coords[2] = 0;


	s = creationSimplexe(&v1,&v2,&v3);
	printf("%f\n",distanceVertexSimplexe(s, &v4));
	free(s);
	return EXIT_SUCCESS;
}*/
