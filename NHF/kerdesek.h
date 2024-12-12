#pragma once
#include <stdbool.h>

typedef struct Kerdes {
	int nehezseg;
	char* kerdes;
	char* avalasz, * bvalasz, * cvalasz, * dvalasz;
	char* valasz;
	char* kategoria;
	bool volte;
}Kerdes;
typedef struct Kerdesek {
	Kerdes* kerdesek;
	int darab;
}Kerdesek;

Kerdes bekerdes(char* sor, int hossz);
Kerdesek bekerkerdesek(char* fajlnev, int hossz);
void freekerdesek(Kerdesek kerdesek);