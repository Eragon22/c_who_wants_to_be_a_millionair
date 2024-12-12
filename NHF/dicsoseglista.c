#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fajlkezeles.h"
#include "dicsoseglista.h"

Jatekos bejatekos(char* sor, int hossz) {
	Jatekos jatekos = { 0 };
	char* bufferido = (char*)malloc(sizeof(char) * hossz);
	if (bufferido == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	char* buffernyeremeny = (char*)malloc(sizeof(char) * hossz);
	if (buffernyeremeny == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(bufferido);
		exit(0);
	}

	jatekos.nev = (char*)malloc(sizeof(char) * hossz);
	if (jatekos.nev == NULL) {
		printf("\nMemóriafoglalási hiba!");
		free(bufferido);
		free(buffernyeremeny);
		exit(0);
	}


	szetvalaszt(sor, ';', hossz, jatekos.nev, buffernyeremeny, bufferido);
	sscanf_s(bufferido, "%d", &jatekos.ido);
	sscanf_s(buffernyeremeny, "%d", &jatekos.nyeremeny);
	free(bufferido);
	free(buffernyeremeny);

	return jatekos;
}
Dicsoseglista bedicsoseglista(char* fajlnev, int hossz)
{
	FILE* fp;
	errno_t hiba = fopen_s(&fp, fajlnev, "r");
	Dicsoseglista dicsoseglista = { NULL };

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
		dicsoseglista.jatekosok = malloc(sizeof(Jatekos) * db);
		dicsoseglista.darab = db;
		if (dicsoseglista.jatekosok == NULL) {
			printf("\nMemóriafoglalási hiba!");
			free(sor);
			exit(0);
		}

		fseek(fp, 0, 0);
		for (int i = 0; fgets(sor, hossz, fp) != NULL; i++) {
			dicsoseglista.jatekosok[i] = bejatekos(sor, hossz);
		}
		free(sor);
	}

	fclose(fp);
	return dicsoseglista;
}
void freedicsoseglista(Dicsoseglista dicsoseglista) {
	for (int i = 0; i < dicsoseglista.darab; i++) {
		free(dicsoseglista.jatekosok[i].nev);
	}
	free(dicsoseglista.jatekosok);
}
void dicsoseglistabeszuras(char* fajlnev, Dicsoseglista dicsoseglista, Jatekos jatekos, int helyezes, char elvalaszto) {
	FILE* fp;
	errno_t hiba = fopen_s(&fp, fajlnev, "w");
	int voltehelyezes = helyezes;
	if (fp != NULL) {
		for (int i = 0; i < dicsoseglista.darab - 1; i++) {
			if (i == voltehelyezes - 1) {
				fprintf_s(fp, "%s%c%d%c%d\n", jatekos.nev, elvalaszto, jatekos.nyeremeny, elvalaszto, jatekos.ido);
				voltehelyezes = -1;
				i--;
			}
			else {
				fprintf_s(fp, "%s%c%d%c%d\n", dicsoseglista.jatekosok[i].nev, elvalaszto, dicsoseglista.jatekosok[i].nyeremeny, elvalaszto, dicsoseglista.jatekosok[i].ido);
			}
		}
	}

	fclose(fp);
}

int dicsoseglistase(Dicsoseglista dicsoseglista, int nyeremeny, int idomasodpercben) {
	for (int i = 0; i < dicsoseglista.darab; i++) {
		if (dicsoseglista.jatekosok[i].nyeremeny < nyeremeny)
			return i + 1;
		else
		if (dicsoseglista.jatekosok[i].nyeremeny == nyeremeny && dicsoseglista.jatekosok[i].ido < idomasodpercben)
			return i + 1;
	}
	return 0;
}