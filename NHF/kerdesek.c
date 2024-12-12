#include <stdio.h>
#include <stdlib.h>

#include "fajlkezeles.h"
#include "kerdesek.h"

Kerdes bekerdes(char* sor, int hossz) {
	Kerdes kerdes = { 0 };
	char* buffer = (char*)malloc(sizeof(char) * hossz);
	if (buffer == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	kerdes.kerdes = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.kerdes == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		exit(0);
	}

	kerdes.avalasz = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.avalasz == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		free(kerdes.kerdes);
		exit(0);
	}

	kerdes.bvalasz = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.bvalasz == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		free(kerdes.kerdes);
		free(kerdes.avalasz);
		exit(0);
	}

	kerdes.cvalasz = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.cvalasz == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		free(kerdes.kerdes);
		free(kerdes.avalasz);
		free(kerdes.bvalasz);
		exit(0);
	}

	kerdes.dvalasz = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.dvalasz == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		free(kerdes.kerdes);
		free(kerdes.avalasz);
		free(kerdes.bvalasz);
		free(kerdes.cvalasz);
		exit(0);
	}

	kerdes.valasz = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.valasz == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		free(kerdes.kerdes);
		free(kerdes.avalasz);
		free(kerdes.bvalasz);
		free(kerdes.cvalasz);
		free(kerdes.dvalasz);
		exit(0);
	}

	kerdes.kategoria = (char*)malloc(sizeof(char) * hossz);
	if (kerdes.kategoria == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(buffer);
		free(kerdes.kerdes);
		free(kerdes.avalasz);
		free(kerdes.bvalasz);
		free(kerdes.cvalasz);
		free(kerdes.dvalasz);
		free(kerdes.valasz);
		exit(0);
	}
	
	szetvalaszt(sor, ';', hossz, buffer, kerdes.kerdes, kerdes.avalasz, kerdes.bvalasz, kerdes.cvalasz, kerdes.dvalasz, kerdes.valasz, kerdes.kategoria);
	sscanf_s(buffer, "%d", &kerdes.nehezseg);
	free(buffer);

	kerdes.volte = false;
	return kerdes;
}
Kerdesek bekerkerdesek(char* fajlnev, int hossz) {
	FILE* fp;
	errno_t hiba = fopen_s(&fp, fajlnev, "r");
	Kerdesek kerdesek = { NULL, 0 };

	if (fp != NULL) {
		char* sor = (char*)malloc(hossz * sizeof(char));
		if (sor == NULL) {
			printf("\nMemóriafoglalási hiba!");
			exit(0);
		}
		int db = 0;

		for (int i = 0; fgets(sor, hossz, fp) != NULL; i++) {
			db++;
		}
		kerdesek.kerdesek = malloc(sizeof(Kerdes) * db);
		kerdesek.darab = db;
		if (kerdesek.kerdesek == NULL) {
			printf("\nMemóriafoglalási hiba!");
			free(sor);
			exit(0);
		}

		fseek(fp, 0, 0);
		for (int i = 0; fgets(sor, hossz, fp) != NULL; i++) {
			kerdesek.kerdesek[i] = bekerdes(sor, hossz);
		}

		free(sor);
		fclose(fp);
	}
	else {
		printf("Hiba! Forrásfájl nem található!");
		exit(0);
	}

	return kerdesek;
}
void freekerdesek(Kerdesek kerdesek) {
	if (kerdesek.kerdesek != NULL) {
		for (int i = 0; i < kerdesek.darab; i++) {
			free(kerdesek.kerdesek[i].avalasz);
			free(kerdesek.kerdesek[i].bvalasz);
			free(kerdesek.kerdesek[i].cvalasz);
			free(kerdesek.kerdesek[i].dvalasz);
			free(kerdesek.kerdesek[i].valasz);
			free(kerdesek.kerdesek[i].kerdes);
			free(kerdesek.kerdesek[i].kategoria);
		}
		free(kerdesek.kerdesek);
	}
}