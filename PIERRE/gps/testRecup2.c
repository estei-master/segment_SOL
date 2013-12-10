#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_BUFFER_DONNEES	100
#define NB_CARACT_A_LIRE	    20
#define TAILLE_DONNEES_UTILES   1
#define POSITION_TRAME		    10

int main(int argc, char* argv[])
{
	FILE* fichier = NULL;
	char donneesRecues[TAILLE_BUFFER_DONNEES];
	char *donnees = malloc((TAILLE_DONNEES_UTILES+1)*sizeof(char));
	char *donnees2;
	char testDonnees[20] = {""};
	int nbCaract = NB_CARACT_A_LIRE;
	int position = POSITION_TRAME;
	int i;
	
	fichier = fopen("donnee.txt", "r");
	if(fichier != NULL)
	{
		//récupération de la trame de données écrite dans le fichier
		fgets(donneesRecues, nbCaract, fichier);
		/*récupère une partie de la trame à partir de POSITION_TRAME
		et de taille TAILLE_DONNEES_UTILES*/
		printf("Données reçues : %s\n", donneesRecues);
		//1ière méthode en utilisant la fonction snprintf 
		snprintf(donnees, TAILLE_DONNEES_UTILES+1, "%s", donneesRecues + position);
		printf("Données utiles (snprintf) : %s\n", donnees);
		//2ième méthode en utilisant la fonction strtok
		donnees2 = strtok(donneesRecues, ",");
		for(i=0;i<(POSITION_TRAME/2);i++)
			donnees2 = strtok(NULL, ",");
		strcat(testDonnees, donnees2);
		printf("Données utiles (strtok) : %s\n",testDonnees);
		fclose(fichier);
	}
	return 0;
}
