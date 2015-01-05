/** 
 *	@file main.c
 *  @author Aurélien Chemier
 *  @author Romane Lhomme
 * 	@date 2014
 */

#include "fenetre.h"
#include "delaunay.h"
#include "filePrioriteSimplexe.h"

#include <assert.h>  
#include <math.h>  
#include <stdio.h>
#include <stdlib.h>

/** variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/** bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	int c;
	int nbPoints = 50;
	int nbFacette = -1;
	int affiche = 0;
	int triangle = 0;
	int delaunay = 1;
	double distance = 0.f;
	Delaunay *d = NULL;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "abdf:hn:s:t")) != EOF)
	{
		switch (c)
		{
			case 'a':
				affiche = 1;
				break;
			case 'b':
				delaunay = 0;
				break;
			case 'f': 
				if ((sscanf(optarg, "%d", &nbFacette) != 1) || nbFacette <= 0)
					nbFacette = -1; /* un nombre négatif indique que toutes les facettes seront créées*/
				break;
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 's':
				if ((sscanf(optarg, "%lf", &distance) != 1) || (distance < 0.f && distance > 1.f) )
					distance = 0.f;
				break;
			case 't': 
				affiche = 1;
				triangle = 1;
				break;
			case 'h':  
			default :
				printf("-a l'affichage en squelette\n");
				printf("-b la triangulation est de base (Delaunay par défaut)\n");
				printf("-f le nombre de facettes maximum crées par la triangulation (toutes par default)\n");
				printf("-h l'aide d'utilisation\n");
				printf("-s le seuil de distance minimale (pourcentage de la distance maximum entre 0 et 1)\n");
				printf("-t l'affichage en triangles pleins\n");
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
		definitionFenetre(0, 700, 0, 700);
	}

	winInit();
	d = initialisation(nbPoints, nbFacette, distance * H_MAX);
	
	if(delaunay) triangulationDelaunay(d);
	else triangulation(d);	

	if(affiche){
		if(triangle == 0) displaySimplexeLigne(d);
		else displaySimplexeTriangle(d);
		glutMainLoop();
	}

	clearFenetre();
	destruction(d);

	return EXIT_SUCCESS;  
}  
