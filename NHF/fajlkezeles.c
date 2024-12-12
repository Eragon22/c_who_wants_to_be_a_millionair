#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "fajlkezeles.h"

void szetvalaszt(char* szoveg, char elvalaszto, int maxhossz, ...) {
	va_list valist;
	va_start(valist, maxhossz);

	int k = 0;
	char* buffer = (char*)malloc(sizeof(char) * maxhossz);
	if (buffer == NULL) {
		printf("\nMemóriafoglalási hiba!");
		exit(0);
	}

	int kesz = 0;
	for (int i = 0; kesz == 0; i++) {
		if (szoveg[i] == elvalaszto || szoveg[i] == '\0') {
			buffer[k] = '\0';
			strcpy_s(va_arg(valist, char*), maxhossz, buffer);
			k = 0;
		}
		else {
			buffer[k] = szoveg[i];
			k++;
		}

		if (szoveg[i] == '\0') {
			kesz = 1;
		}
	}
	free(buffer);
	va_end(valist);
}
