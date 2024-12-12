#pragma once

typedef struct Jatekos {
	char* nev;
	int nyeremeny;
	int ido;
}Jatekos;
typedef struct Dicsoseglista {
	Jatekos* jatekosok;
	int darab;
}Dicsoseglista;

Jatekos bejatekos(char* sor, int hossz);
Dicsoseglista bedicsoseglista(char* fajlnev, int hossz);
void freedicsoseglista(Dicsoseglista dicsoseglista);
void dicsoseglistabeszuras(char* fajlnev, Dicsoseglista dicsoseglista, Jatekos jatekos, int helyezes, char elvalaszto);

int dicsoseglistase(Dicsoseglista dicsoseglista, int nyeremeny, int idomasodpercben);
void kidocsiseglista(char* fajlnev, Dicsoseglista dicsoseglista, int maxhossz, char elvalaszto);