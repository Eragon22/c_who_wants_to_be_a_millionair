#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "segitsegek.h"

Kerdes* kozonsegkerdessegitseg(Kerdes* kerdes, int nehezseg) {
	int szazalek = 0;
	switch (nehezseg) {
	case(1): {
		szazalek = 85;
		break;
	}
	case(2): {
		szazalek = 70;
		break;
	}
	case(3): {
		szazalek = 40;
		break;
	}
	default:
		break;
	}

	int szavazatok[4] = { 0 };
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		if (rand() % 100 < szazalek) {
			szavazatok[0]++;
		}
		else {
			szavazatok[rand() % 3 + 1]++;
		}
	}

	int helyessorszam = kerdes->valasz[0] - 'A';
	int temp = szavazatok[0];
	szavazatok[0] = szavazatok[helyessorszam];
	szavazatok[helyessorszam] = temp;

	char* buffer = malloc(8 * sizeof(char));
	if (buffer == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	sprintf_s(buffer, sizeof(buffer), " %02ddb", szavazatok[0]);
	strcat_s(kerdes->avalasz, sizeof(char) * (strlen(kerdes->avalasz) + strlen(buffer)) + 1, buffer);
	sprintf_s(buffer, sizeof(buffer), " %02ddb", szavazatok[1]);
	strcat_s(kerdes->bvalasz, sizeof(char) * (strlen(kerdes->bvalasz) + strlen(buffer)) + 1, buffer);
	sprintf_s(buffer, sizeof(buffer), " %02ddb", szavazatok[2]);
	strcat_s(kerdes->cvalasz, sizeof(char) * (strlen(kerdes->cvalasz) + strlen(buffer)) + 1, buffer);
	sprintf_s(buffer, sizeof(buffer), " %02ddb", szavazatok[3]);
	strcat_s(kerdes->dvalasz, sizeof(char) * (strlen(kerdes->dvalasz) + strlen(buffer)) + 1, buffer);
	free(buffer);

	return kerdes;
}
Kerdes* kerdesfelezessegitseg(Kerdes* kerdes) {
	int helyessorszam = kerdes->valasz[0] - 'A';
	int torol[4] = { 1,1,1,1 };

	torol[helyessorszam] = 0;
	srand(time(NULL));

	int hibas = 1;
	while (hibas) {
		int random = rand() % 4;
		if (random != helyessorszam) {
			torol[random] = 0;
			hibas = 0;
		}
	}

	if (torol[0])
		strcpy_s(kerdes->avalasz, sizeof(char) * strlen(kerdes->avalasz) + 1, "");
	if (torol[1])
		strcpy_s(kerdes->bvalasz, sizeof(char) * strlen(kerdes->bvalasz) + 1, "");
	if (torol[2])
		strcpy_s(kerdes->cvalasz, sizeof(char) * strlen(kerdes->cvalasz) + 1, "");
	if (torol[3])
		strcpy_s(kerdes->dvalasz, sizeof(char) * strlen(kerdes->dvalasz) + 1, "");
	return kerdes;
}
Kerdes* telefonsegitseg(Kerdes* kerdes, int nehezseg) {
	int szazalek = 0;
	switch (nehezseg) {
	case(1): {
		szazalek = 95;
		break;
	}
	case(2): {
		szazalek = 90;
		break;
	}
	case(3): {
		szazalek = 80;
		break;
	}
	default:
		break;
	}

	int helyessorszam = kerdes->valasz[0] - 'A';
	int helyese = rand() % 100 < szazalek;

	if (!helyese) {
		int temp = 0;
		do {
			temp = rand() % 4;
		} while (helyessorszam == temp);
		helyessorszam = temp;
	}

	if (helyessorszam == 0)
		strcat_s(kerdes->avalasz, sizeof(char) * (strlen(kerdes->avalasz) + 5), " •");
	else
		strcat_s(kerdes->avalasz, sizeof(char) * (strlen(kerdes->avalasz) + 5), "  ");

	if (helyessorszam == 1)
		strcat_s(kerdes->bvalasz, sizeof(char) * (strlen(kerdes->bvalasz) + 5), " •");
	else
		strcat_s(kerdes->bvalasz, sizeof(char) * (strlen(kerdes->bvalasz) + 5), "  ");

	if (helyessorszam == 2)
		strcat_s(kerdes->cvalasz, sizeof(char) * (strlen(kerdes->cvalasz) + 5), " •");
	else
		strcat_s(kerdes->cvalasz, sizeof(char) * (strlen(kerdes->cvalasz) + 5), "  ");

	if (helyessorszam == 3)
		strcat_s(kerdes->dvalasz, sizeof(char) * (strlen(kerdes->dvalasz) + 5), " •");
	else
		strcat_s(kerdes->dvalasz, sizeof(char) * (strlen(kerdes->dvalasz) + 5), "  ");

	return kerdes;
}
