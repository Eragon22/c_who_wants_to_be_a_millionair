#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <locale.h>
#include <time.h>

#include "kerdesek.h"
#include "dicsoseglista.h"
#include "debugmalloc.h"
#include "econio.h"
#include "jatek.h"

//dicsőséglista menü
void dicsoseglistaszoveg(Dicsoseglista dicsoseglista) {
	econio_clrscr();
	econio_gotoxy(13, 1);
	econio_textcolor(COL_LIGHTYELLOW);
	econio_textbackground(COL_BLUE);
	printf("  %13s%37s  ","Dicsõséglista", "Legyen Ön Is Millimos!");

	econio_textcolor(COL_BLACK);
	econio_textbackground(COL_WHITE);
	econio_gotoxy(13, 2);
	printf("  %50s  ", " ");
	econio_gotoxy(13, 3);
	int i = 0;
	while(i < dicsoseglista.darab) {
		int ora = dicsoseglista.jatekosok[i].ido / 60 / 60;
		int perc = dicsoseglista.jatekosok[i].ido / 60 % 60;
		int masodperc = dicsoseglista.jatekosok[i].ido % 60;

		printf("  [%02d] %20s | %9dft | %02d:%02d:%02d  ", i + 1, dicsoseglista.jatekosok[i].nev, dicsoseglista.jatekosok[i].nyeremeny, ora, perc, masodperc);
		econio_gotoxy(13, 4 + i);
		i++;
	}
	printf("  %50s  ", " ");
	econio_gotoxy(13, 4 + i);
	printf("  [K]%47s  ","Kilépés");
	econio_gotoxy(13, 5 + i);
	printf("  %50s  ", " ");
	econio_gotoxy(13, 6 + i);
	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}
void dicsoseglista() {
	Dicsoseglista dicsoseglista = bedicsoseglista("dicsoseglista.csv", 1000);
	char* input = (char*)malloc(sizeof(char) * 1000);
	if (input == NULL) {

	}

	do {
		dicsoseglistaszoveg(dicsoseglista);
		scanf_s("%s", input, 1000);
	} while (strcmp(input, "K") != 0);

	free(input);
	freedicsoseglista(dicsoseglista);
}

//főmenü
void menuszoveg() {
	econio_gotoxy(20, 1);
	econio_textcolor(COL_LIGHTYELLOW);
	econio_textbackground(COL_BLUE);
	printf("  %36s  ", "Legyen Ön Is Millimos!");

	econio_textcolor(COL_BLACK);
	econio_textbackground(COL_WHITE);

	econio_gotoxy(20, 2);
	printf("%40s", " ");
	econio_gotoxy(20, 3);
	printf("  [D]%33s  ", "Dicsõséglista");
	econio_gotoxy(20, 4);
	printf("  [U]%33s  ", "Új játék indítása");
	econio_gotoxy(20, 5);
	printf("  [K]%33s  ", "Kilépés");
	econio_gotoxy(20, 6);
	printf("%40s", " ");

	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
	econio_gotoxy(20, 7);
}
void menu() {
	char* input = (char*)malloc(sizeof(char) * 1000);
	if (input == NULL) {

	}	

	do {
		econio_clrscr();
		menuszoveg();
		scanf_s("%s", input, 1000);

		if (strcmp(input, "D") == 0) {
			dicsoseglista();
		}

		if (strcmp(input, "U") == 0) {
			jatek();
		}
	} while (strcmp(input, "K") != 0);
	free(input);
}

int main() {
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	menu();

	return 0;
}