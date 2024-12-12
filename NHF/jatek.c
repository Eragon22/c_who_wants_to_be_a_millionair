#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <time.h>


#include "debugmalloc.h"
#include "econio.h"
#include "dicsoseglista.h"
#include "jatek.h"

//nehézségválasztó menü
void nehezsegvalasztoszoveg() {
	econio_gotoxy(13, 1);
	econio_textcolor(COL_LIGHTYELLOW);
	econio_textbackground(COL_BLUE);
	printf("  %20s%30s  ", "Válasszon nehézséget", "Legyen Ön Is Millimos!");

	econio_textcolor(COL_BLACK);
	econio_textbackground(COL_WHITE);

	econio_gotoxy(13, 2);
	printf("  %50s  ", " ");
	econio_gotoxy(13, 3);
	printf("  [1]%17s %29s  ", "Könnyû", "(Max nyeremény: 25 000 000ft)");
	econio_gotoxy(13, 4);
	printf("  [2]%17s %29s  ", "Közepes", "(Max nyeremény: 40 000 000ft)");
	econio_gotoxy(13, 5);
	printf("  [3]%17s %29s  ", "Nehéz", "(Max nyeremény: 50 000 000ft)");
	econio_gotoxy(13, 6);
	printf("  %50s  ", " ");

	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
	econio_gotoxy(13, 7);
}
int nehezsegvalaszto() {
	char* input = (char*)malloc(sizeof(char) * 1000);
	if (input == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	do {
		econio_clrscr();
		nehezsegvalasztoszoveg();
		scanf_s("%s", input, 1000);
	} while (strcmp(input, "1") != 0 &&
		strcmp(input, "2") != 0 &&
		strcmp(input, "3") != 0);

	int nehezseg = 0;
	sscanf_s(input, "%d", &nehezseg);
	free(input);
	return nehezseg;
}

//játék segédfüggvények
Kerdes* randomkerdes(Kerdesek kerdesek, int nehezseg) {
	int* indexek = (int*)malloc(kerdesek.darab * sizeof(int));
	if (indexek == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}
	int j = 0;
	for (int i = 0; i < kerdesek.darab; i++) {
		if (kerdesek.kerdesek[i].nehezseg == nehezseg && !kerdesek.kerdesek[i].volte) {
			indexek[j] = i;
			j++;
		}
	}
	int randomindex = indexek[rand() % j];
	free(indexek);

	kerdesek.kerdesek[randomindex].volte = 1;
	return &kerdesek.kerdesek[randomindex];
}
Kerdes* kerdesvalaszto(Kerdesek kerdesek, int kerdesszam, int nehezseg, int maxhossz) {
	Kerdes* kerdes = (Kerdes*)malloc(sizeof(Kerdes) * maxhossz);
	if (kerdes == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	switch (nehezseg) {
	case 1: {
		memcpy(kerdes, randomkerdes(kerdesek, kerdesszam * (2 / 5) + 1), sizeof(Kerdes));
		break;
	}
	case 2: {
		memcpy(kerdes, randomkerdes(kerdesek, kerdesszam * (1 / 2) + 3), sizeof(Kerdes));
		break;
	}
	case 3: {
		memcpy(kerdes, randomkerdes(kerdesek, kerdesszam * (2 / 3) + 5), sizeof(Kerdes));
		break;
	}
	default:
		break;
	};
	return kerdes;
}
int aktualisnyeremeny(int aktualiskerdes, int nehezseg) {
	int* nyeremenyek = (int[15]){ 0 };
	switch (nehezseg) {
	case 1: {
		nyeremenyek = (int[15]){ 1000,3000,6000,12000,25000,
								50000,10000,200000,400000,800000,
								1500000,3000000,6000000,12500000,25000000 };
		break;
	}
	case 2: {
		nyeremenyek = (int[15]){ 5000,10000,25000,50000,100000,
								200000,300000,500000,8000000,1500000,
								3000000,5000000,10000000,20000000,40000000 };
		break;
	}
	case 3: {
		nyeremenyek = (int[15]){ 10000,20000,50000,100000,250000,
								500000,750000,1000000,1500000,2000000,
								5000000,10000000,15000000,25000000,50000000 };
		break;
	}
	default:
		break;
	}
	return nyeremenyek[aktualiskerdes];
}
void kerdessortores(char* szoveg, int sorhossz) {
	int szoveghossz = strlen(szoveg);
	int szovegveg = 1;
	for (int i = 0; szovegveg; i++) {
		econio_textbackground(COL_BLUE);
		econio_gotoxy(2, i + 2);
		printf("  ");
		econio_textbackground(COL_WHITE);
		econio_textcolor(COL_BLACK);

		char* sor = (char*)malloc(sizeof(char) * sorhossz + 2);
		if (sor == NULL) {
			printf("\nMemóriafoglalási hiba!");
			exit(0);
		}

		if (strlen(szoveg) / sorhossz > 0) {
			int utolsoszokoz = 0;
			for (int i = 0; i < sorhossz; i++)
				if (szoveg[i] == ' ')
					utolsoszokoz = i;

			strncpy_s(sor, sizeof(char) * utolsoszokoz + 1, szoveg, utolsoszokoz);
			strcpy_s(szoveg, sizeof(char) * strlen(szoveg), szoveg + utolsoszokoz + 1);
		}
		else {
			strcpy_s(sor, sizeof(char) * sorhossz, szoveg);
			szovegveg = 0;
		}
		printf(" %50s ", sor);
		econio_textbackground(COL_BLUE);
		printf("  ");

		free(sor);
	}
}
void helyezettkezeles(int nyeremeny, int ido, int maxhossz) {
	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 1);
	printf("%56s", "");

	econio_gotoxy(2, 2);
	printf("  ");
	econio_textbackground(COL_WHITE);
	econio_textcolor(COL_BLACK);

	int helyezes = dicsoseglistase(bedicsoseglista("dicsoseglista.csv", 1000), nyeremeny, ido);
	if (helyezes > 0) {
		printf(" %37s %2d %9s ", "Gratulálok! Felkerült a dicsõséglisa ", helyezes, " helyére!");
		econio_textbackground(COL_BLUE);
		printf("  ");

		econio_gotoxy(2, 3);
		printf("  ");
		econio_textbackground(COL_WHITE);

		printf(" %50s ", "Kérem adja meg a nevét.");
		econio_textbackground(COL_BLUE);
		printf("  ");
		econio_gotoxy(2, 4);
		printf("%56s", "");
	}
	else {
		printf(" %35s %12dft ", "Játék vége! Nyereménye: ", nyeremeny);
		econio_textbackground(COL_BLUE);
		printf("  ");
		econio_gotoxy(2, 3);
		printf("%56s", "");
	}

	bemenetszoveg();
	char* sor = (char*)malloc(sizeof(char) * maxhossz);
	if (sor == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}
	scanf_s("%s", sor);
	if (helyezes > 0) {
		Dicsoseglista dicsoseglista = bedicsoseglista("dicsoseglista.csv", maxhossz);
		Jatekos tjatekos = { sor,nyeremeny,(clock() - ido) / CLOCKS_PER_SEC };
		dicsoseglistabeszuras("dicsoseglista.csv", dicsoseglista, tjatekos, helyezes, ';');
		freedicsoseglista(dicsoseglista);
	}
	free(sor);

	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}

//játék menü
void oraszoveg(clock_t idostart) {
	int ora = (clock() - idostart) / CLOCKS_PER_SEC / 60 / 60;
	int perc = (clock() - idostart) / CLOCKS_PER_SEC / 60 % 60;
	int masodperc = (clock() - idostart) / CLOCKS_PER_SEC % 60;

	econio_gotoxy(60, 19);
	econio_textbackground(COL_BLUE);
	printf("%18s", "");

	econio_gotoxy(60, 20);
	printf("  ");
	econio_textbackground(COL_WHITE);
	econio_textcolor(COL_BLACK);
	printf("   %02d:%02d:%02d   ", ora, perc, masodperc);
	econio_textcolor(COL_RESET);
	econio_textbackground(COL_BLUE);
	printf("  ");

	econio_gotoxy(60, 21);
	printf("%18s", " ");
	econio_textbackground(COL_RESET);
}
void nyeremenyszoveg(int aktualiskerdes, int nehezseg) {
	econio_textbackground(COL_BLUE);
	econio_gotoxy(60, 1);
	printf("%18s", " ");
	econio_textcolor(COL_BLACK);
	for (int i = 0; i < 15; i++) {
		econio_gotoxy(60, i + 2);
		econio_textbackground(COL_BLUE);
		printf("  ");

		if (i == 4 || i == 9 || i == 14) {
			econio_textcolor(COL_YELLOW);
		}
		if (i == aktualiskerdes) {
			econio_textbackground(COL_LIGHTYELLOW);
			printf(" %02d•%9d ", i + 1, aktualisnyeremeny(i, nehezseg));
		}
		else
		{
			econio_textbackground(COL_WHITE);
			printf(" %02d %9d ", i + 1, aktualisnyeremeny(i, nehezseg));
		}
		econio_textcolor(COL_BLACK);


		econio_textbackground(COL_BLUE);
		printf("  ");
	}
	econio_textcolor(COL_RESET);
	econio_textbackground(COL_BLUE);
	econio_gotoxy(60, 17);
	printf("%18s", " ");
	econio_textbackground(COL_RESET);
}
void kerdesszoveg(Kerdes* kerdes) {
	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 1);
	printf("%56s", "");

	char* szoveg = (char*)malloc(sizeof(char) * strlen(kerdes->kerdes) + 1);
	if (szoveg == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}
	strcpy_s(szoveg, sizeof(char) * strlen(kerdes->kerdes) + 1, kerdes->kerdes);

	kerdessortores(szoveg, 50);
	free(szoveg);

	econio_gotoxy(2, (strlen(kerdes->kerdes) / 50) + 3);
	printf("%56s", "");
	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}
void valaszszoveg(Kerdes* kerdes) {
	econio_textcolor(COL_BLACK);

	econio_textbackground(COL_BLUE);
	econio_gotoxy(18, 12);
	printf("%40s", "");
	econio_textbackground(COL_BLUE);
	econio_gotoxy(18, 13);
	printf("  ");
	econio_textbackground(COL_WHITE);
	printf(" [A] %30s ", kerdes->avalasz);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_gotoxy(18, 14);
	printf("  ");
	econio_textbackground(COL_WHITE);
	printf(" [B] %30s ", kerdes->bvalasz);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_textbackground(COL_BLUE);
	econio_gotoxy(18, 15);
	printf("  ");
	econio_textbackground(COL_WHITE);
	printf(" [C] %30s ", kerdes->cvalasz);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_textbackground(COL_BLUE);
	econio_gotoxy(18, 16);
	printf("  ");
	econio_textbackground(COL_WHITE);
	printf(" [D] %30s ", kerdes->dvalasz);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_textbackground(COL_BLUE);

	econio_gotoxy(18, 17);
	printf("%40s", "");

	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}
void segitsegszoveg(Segitsegek segitsegek) {
	econio_textcolor(COL_BLACK);

	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 12);
	printf("%18s", "");
	econio_gotoxy(2, 13);
	printf("  ");
	econio_textbackground(COL_WHITE);
	printf(" Segítségek:  ");
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_gotoxy(2, 14);
	printf("  ");
	econio_textbackground(COL_WHITE);
	if (!segitsegek.kozonseg)
		econio_textcolor(COL_LIGHTGRAY);
	printf(" [K] %8s ", "Közönség");
	econio_textcolor(COL_BLACK);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_gotoxy(2, 15);
	printf("  ");
	econio_textbackground(COL_WHITE);
	if (!segitsegek.felezes)
		econio_textcolor(COL_LIGHTGRAY);
	printf(" [F] %8s ", "Felezés");
	econio_textcolor(COL_BLACK);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_gotoxy(2, 16);
	printf("  ");
	econio_textbackground(COL_WHITE);
	if (!segitsegek.telefon)
		econio_textcolor(COL_LIGHTGRAY);
	printf(" [T] %8s ", "Telefon");
	econio_textcolor(COL_BLACK);
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_gotoxy(2, 17);
	printf("%18s", "");

	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}
void bemenetszoveg() {
	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 19);
	printf("%56s", "");
	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 20);
	printf("  ");
	econio_textbackground(COL_WHITE);
	printf("%52s", "");
	econio_textbackground(COL_BLUE);
	printf("  ");
	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 21);
	printf("%56s", "");
	econio_textbackground(COL_WHITE);
	econio_textcolor(COL_BLACK);
	econio_gotoxy(5, 20);
}
void jatekfolytatasszoveg() {
	econio_textbackground(COL_BLUE);
	econio_gotoxy(2, 1);
	printf("%56s", "");

	econio_gotoxy(2, 2);
	printf("  ");
	econio_textbackground(COL_WHITE);
	econio_textcolor(COL_BLACK);
	printf(" [I/N]%45s ", "Folytatja a játékot?");
	econio_textbackground(COL_BLUE);
	printf("  ");

	econio_gotoxy(2, 3);
	printf("%56s", "");
	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}

//játék vége
void jatekvege(Kerdes* kerdes, int kerdessorszam, int nehezseg, int ido, int maxhossz) {
	int nyeremeny = 0;
	if (kerdessorszam >= 4) {
		nyeremeny = aktualisnyeremeny(4, nehezseg);
	}
	if (kerdessorszam >= 9) {
		nyeremeny = aktualisnyeremeny(9, nehezseg);
	}
	helyezettkezeles(nyeremeny, ido, maxhossz);
	econio_textbackground(COL_RESET);
	econio_textcolor(COL_RESET);
}
void hibasvalasz(Kerdes* kerdes, int kerdessorszam, int nehezseg, clock_t idostart) {
	econio_clrscr();

	oraszoveg(idostart);
	nyeremenyszoveg(kerdessorszam, nehezseg);
	jatekvege(kerdes, kerdessorszam - 1, nehezseg, clock() - idostart, 1000);
}
bool helyesvalasz(Kerdesek *kerdesek, Kerdes* kerdes, int kerdessorszam, int nehezseg, clock_t idostart) {
	char* input = (char*)malloc(sizeof(char) * 1000);
	if (input == NULL) {
		printf("\nMemóriafoglalási hiba!");
		freekerdesek(*kerdesek);
		exit(0);
	}
	
	do {
		econio_clrscr();

		oraszoveg(idostart);
		nyeremenyszoveg(kerdessorszam, nehezseg);
		jatekfolytatasszoveg();
		bemenetszoveg();

		scanf_s("%s", input, 1000);
		econio_textcolor(COL_RESET);
		econio_textbackground(COL_RESET);
	} while (strcmp(input, "I") != 0 && strcmp(input, "N") != 0);
	if (!strcmp(input, "N")) {
		char* buffer = (char*)malloc(sizeof(char) * 51);
		if (buffer == NULL) {
			printf("\nMemóriafoglalási hiba!");
			free(input);
			freekerdesek(*kerdesek);
			exit(0);
		}

		sprintf_s(buffer, sizeof(char) * 50, "%s%d", "Játék vége! Nyereménye: ", aktualisnyeremeny(kerdessorszam, nehezseg));
		helyezettkezeles(aktualisnyeremeny(kerdessorszam, nehezseg), clock() - idostart, 1000, buffer);
		free(buffer);
		free(input);
		return false;
	}
	free(input);
	return true;
}

char kerdesfeltetel(Kerdes* kerdes, clock_t idostart, int aktualiskerdes, int nehezseg, Segitsegek *segitsegek) {
	char* input = (char*)malloc(sizeof(char) * 1000);
	if (input == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	int voltesegitseg = false;
	do {
		econio_clrscr();
		oraszoveg(idostart);
		nyeremenyszoveg(aktualiskerdes, nehezseg);
		kerdesszoveg(kerdes);
		valaszszoveg(kerdes);
		segitsegszoveg(*segitsegek);
		bemenetszoveg();

		scanf_s("%s", input, 1000);
		econio_textcolor(COL_RESET);
		econio_textbackground(COL_RESET);

		if ((segitsegek->kozonseg == 1 ? !strcmp(input, "K") : 0) && !voltesegitseg) {
			kozonsegkerdessegitseg(kerdes, nehezseg);
			voltesegitseg = true;
			segitsegek->kozonseg = false;
		}
		if ((segitsegek->felezes == 1 ? !strcmp(input, "F") : 0) && !voltesegitseg) {
			kerdesfelezessegitseg(kerdes);
			voltesegitseg = true;
			segitsegek->felezes = false;
		}
		if ((segitsegek->telefon == 1 ? !strcmp(input, "T") : 0) && !voltesegitseg) {
			telefonsegitseg(kerdes, nehezseg);
			voltesegitseg = true;
			segitsegek->telefon = false;
		}
	} while (strcmp(input, "A") != 0 &&
			 strcmp(input, "B") != 0 &&
			 strcmp(input, "C") != 0 &&
			 strcmp(input, "D") != 0);

	int valasz = input[0];
	free(input);
	return valasz;
}
void jatek() {
	int nehezseg = nehezsegvalaszto();
	Kerdesek kerdesek = bekerkerdesek("kerdesek.csv", 1000);
	srand(time(NULL));
	clock_t idostart = clock();
	Segitsegek segitsegek = { 1,1,1 };

	for (int i = 0; i < 15; i++) {
		Kerdes* kerdes = kerdesvalaszto(kerdesek, i, nehezseg, 1000);

		char valasz = kerdesfeltetel(kerdes, idostart, i, nehezseg, &segitsegek);

		if (kerdes->valasz[0] != valasz) {
			free(kerdes);
			hibasvalasz(kerdes, i, nehezseg, idostart);
			break;
		}
		else {
			free(kerdes);
			if (!helyesvalasz(&kerdesek, kerdes, i, nehezseg, idostart)) {
				break;
			}
		}
	}
	freekerdesek(kerdesek);
}