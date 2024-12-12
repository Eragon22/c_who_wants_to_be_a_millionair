#pragma once
#include <stdbool.h>

#include "kerdesek.h"
#include "segitsegek.h"

Kerdes* randomkerdes(Kerdesek kerdesek, int nehezseg);
Kerdes* kerdesvalaszto(Kerdesek kerdesek, int kerdesszam, int nehezseg, int maxhossz);
int aktualisnyeremeny(int aktualiskerdes, int nehezseg);
void kerdessortores(char* szoveg, int sorhossz);
void helyezettkezeles(int nyeremeny, int ido, int maxhossz);

void oraszoveg(clock_t idostart);
void nyeremenyszoveg(int aktualiskerdes, int nehezseg);
void kerdesszoveg(Kerdes* kerdes);
void valaszszoveg(Kerdes* kerdes);
void segitsegszoveg(int kozonseg, int felezes, int telefon);
void bemenetszoveg();
void jatekfolytatasszoveg();

void jatekvege(Kerdes* kerdes, int kerdessorszam, int nehezseg, int ido, int maxhossz);
void hibasvalasz(Kerdes* kerdes, int kerdessorszam, int nehezseg, clock_t idostart);
bool helyesvalasz(Kerdesek* kerdesek, Kerdes* kerdes, int kerdessorszam, int nehezseg, clock_t idostart);

char kerdesfeltetel(Kerdes* kerdes, clock_t idostart, int aktualiskerdes, int nehezseg, Segitsegek* segitsegek);
void jatek();