/*! \file main.c
* \author A Chemier, R Lhomme
* \date 2014
*/

/*
1 millions de points
algo "naïf": 10.886148 s
algo jarvis : 1.216959 s
algo grahon : 1.858054 s

10 millions de points
algo "naïf": 169.494484 s
algo jarvis : 13.946895 s

*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <math.h>  
#include <time.h>

#include "fenetre.h"
#include "enveloppe.h"


/*! variable externe permettant de lire les parametres sur le ligne de commande.*/
extern char *optarg;

/*! bascule pour autoriser ou interdire (0) les messages d'erreurs envoyes par getopt. */
extern int opterr;

int main(int argc, char **argv)  
{  
	//printf("\E[34;1mhel\E[mlo\n");
	int c;
	int nbPoints = 50;
	vertex *v = NULL;
	enveloppe e1,e2,e3,e4,e5;
	initialiseEnveloppe(&e1);
	initialiseEnveloppe(&e2);
	initialiseEnveloppe(&e3);
	initialiseEnveloppe(&e4);
	initialiseEnveloppe(&e5);
	int jar = 0, lex = 0, gra = 0, di = 0, bru = 0;
	
	opterr = 0;
	while ((c = getopt(argc, argv, "bBjJgGlLdDn:")) != EOF)
	{
		switch (c)
		{
			case 'b': 
			case 'B': 
				bru = 1;
				break;
			case 'j': 
			case 'J': 
				jar = 1;
				break;
			case 'g': 
			case 'G': 
				gra = 1;
				break;
			case 'L': 
			case 'l': 
				lex = 1;
				break;
			case 'd': 
			case 'D': 
				di = 1;
				break;
			case 'n': 
				if ((sscanf(optarg, "%d", &nbPoints) != 1) || nbPoints <= 0)
					nbPoints = 50;
				break;
			case 'h':  
			default :
				printf("-b ou -B Brute\n");
				printf("-j ou -J jarvis\n");
				printf("-g ou -G Graham\n");
				printf("-l ou -L lexico\n");
				printf("-d ou -D divideAndConquer\n");
				printf("-n le nombre de vertex (50 par défaut)\n");
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
	selectPoints (v, nbPoints);

	if(jar) jarvis(v, &e1,nbPoints);
	if(bru)enveloppeConvexeBrut(v, &e2,nbPoints);
	if(gra)graham(v, &e3,nbPoints);
	if(lex)insertionLexicographique( v, &e4, nbPoints);
	if(di)/*printf("ne fonctionne pas\n"); */divideAndConquer( v, &e5, nbPoints);

	glutMainLoop(); 
	clearFenetre(v,nbPoints);
	return EXIT_SUCCESS;  


}  	
	
