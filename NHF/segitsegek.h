#pragma once
#include <stdbool.h>

#include "kerdesek.h"

typedef struct Segitsegek {
	bool kozonseg;
	bool felezes;
	bool telefon;
}Segitsegek;

Kerdes* kozonsegkerdessegitseg(Kerdes* kerdes, int nehezseg);
Kerdes* kerdesfelezessegitseg(Kerdes* kerdes);
Kerdes* telefonsegitseg(Kerdes* kerdes, int nehezseg);