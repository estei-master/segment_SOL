#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_BUFFER_DONNEES	100
#define NB_CARACT_A_LIRE	    24
#define TAILLE_DONNEES_UTILES   1
#define POSITION_TRAME		    10

int main(void)
{
	FILE* fichier = NULL;
	char donneesRecues[TAILLE_BUFFER_DONNEES];
	char *donnees;
	char latitude[20] = {""}, longitude[20] = {""}, heure[20] = {""}, niveauBatterie[5] = {""}, nbSatellites[5] = {""};
	int nbCaract = NB_CARACT_A_LIRE;
	int position = POSITION_TRAME;
	int i;
	
	while(1)
	{
		//ouverture du fichier
		fichier = fopen("donneeIHM.txt", "r");
		//si le fichier n'est pas vide
		if(fichier != NULL)
		{
			fgets(donneesRecues, nbCaract, fichier);//récupère la les données écritent dans le fichier
			printf("Données reçues : %s\n", donneesRecues);
		
			//Latitude
			donnees = strtok(donneesRecues, ",");
			strcat(latitude, donnees);
			printf("Latitude : %s\n", latitude);
			
			//Longitude
			donnees = strtok(NULL, ",");
			strcat(longitude, donnees);
			printf("Longitude : %s\n", longitude);
			
			//Heure
			donnees = strtok(NULL, ",");
			strcat(heure, donnees);
			printf("Heure (UTC) : %s\n", heure);
			
			//Niveau batterie
			/*donnees = strtok(NULL, ",");
			strcat(niveauBatterie, donnees);
			printf("Niveau de batterie : %s%\n", niveauBatterie);*/
			
			//Nombre de satellite
			donnees = strtok(NULL, ",");
			strcat(nbSatellites, donnees);
			printf("Nombre de satellites : %s\n", nbSatellites);
			printf("\n");
			
			//RàZ des buffers
			strcpy(latitude, "");
			strcpy(longitude, "");
			strcpy(heure, "");
			strcpy(niveauBatterie, "");
			strcpy(nbSatellites, "");
			//attente
			sleep(2);
			//fermeture du fichier
			fclose(fichier);
		}
	}
	
	return 0;
}
