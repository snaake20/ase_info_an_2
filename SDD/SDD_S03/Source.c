#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define LINE_BUFFER 128

typedef union Referinta {
	char ref_interna;
	unsigned short ref_externa; // ->0000 0000 contractor <=|=> id_angajat 0000 0000
} RefInfo;

//typdef union Referinta RefInfo;

typedef struct Angajat {
	char* nume;
	double salariu;
	RefInfo referinta;
} AngajatInfo;

//typedef struct Angajat AngajatInfo;

//management info utila stocata in HEAP
AngajatInfo* creareAngajat(char*, double, unsigned short);
//void dezalocareAngajat(AngajatInfo* angajat); // seminar
void dezalocareAngajat(AngajatInfo**);
void afisareAngajati(AngajatInfo**, short);

void main() {
	AngajatInfo a; // sau struct Angajat
	a.nume = NULL;
	a.salariu = 100.4;

	AngajatInfo* agenda[10];
	memset(agenda, NULL, sizeof(AngajatInfo*) * 10);

	char fileLineBuffer[LINE_BUFFER];

	FILE* pFile = fopen("Data.txt", "r");

	char* token;
	unsigned short referinta;
	double salariu;
	char nume[LINE_BUFFER];
	if (pFile) {
		int idx = 0;
		while (fgets(fileLineBuffer, sizeof(fileLineBuffer), pFile)) {
			// citire nume
			token = strtok(fileLineBuffer, ",");
			strcpy(nume, token);
			// citire salariu
			token = strtok(NULL, ",");
			salariu = atof(token);
			// citire referinta
			token = strtok(NULL, "\n");
			referinta = atoi(token);
			// creare pointe la angajat
			AngajatInfo* ang = creareAngajat(nume, salariu, referinta);
			// adaugare in masiv
			agenda[idx++] = ang;
		}
		//dezalocareAngajat(&ang);
		fclose(pFile);
		afisareAngajati(agenda, sizeof(agenda) / sizeof(AngajatInfo*));
	}
}

AngajatInfo* creareAngajat(char* nume, double salariu, unsigned short referinta) {
	AngajatInfo* res = NULL;
	res = (AngajatInfo*)malloc(sizeof(AngajatInfo) * 1);
	if (res != NULL) {
		res->nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
		if (res->nume != NULL) {
			strcpy_s(res->nume, strlen(nume) + 1, nume);
		}
		res->salariu = salariu;
		res->referinta.ref_externa = referinta;
	}
	return res;
}

void dezalocareAngajat(AngajatInfo** angajat) {
	if (*angajat != NULL) {
		free((*angajat)->nume);
		free(*angajat);
	}
	*angajat = NULL; // eliminare dangling pointer
}

void afisareAngajati(AngajatInfo** agenda, short nr_angajati) {
	for (int i = 0; i < nr_angajati; i++)
	{
		if (agenda[i]) {
			printf("Nume: %s, Salariu: %.2f\n", agenda[i]->nume, agenda[i]->salariu);
			if (agenda[i]->referinta.ref_externa >> 15 == 1) {
				printf("Contractor: %d ", agenda[i]->referinta.ref_externa >> 8);
			}
			printf("Referinta: %d\n", agenda[i]->referinta.ref_externa & 255);
		}
	}
}