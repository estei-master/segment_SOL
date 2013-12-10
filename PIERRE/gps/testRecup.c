#include <stdio.h>
#include <stdlib.h>

int main ()
{
	const char bufferGPS[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	int longueur = 15;
	int position = 0;
	char *donnees = malloc((longueur+1)*sizeof(char));

	snprintf(donnees, longueur+1, "%s", bufferGPS + position);
	printf("Données reçues : %s\n", donnees);
	free(donnee);
	
	return 0;
}
