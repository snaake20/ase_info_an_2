#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Angajat {
	char* nume;
	double salariu;
} AngajatInfo;

//typedef struct Angajat AngajatInfo;

//management info utila stocata in HEAP
AngajatInfo* creareAngajat(char*, double);
//void dezalocareAngajat(AngajatInfo* angajat); // seminar
void dezalocareAngajat(AngajatInfo** angajat);

void main() {
	AngajatInfo a; // sau struct Angajat
	a.nume = NULL;
	a.salariu = 100.4;

	AngajatInfo* agenda[10];

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile) {

		AngajatInfo* ang = creareAngajat("Popescu Maria", 1200.0);
		dezalocareAngajat(&ang);


		fclose(pFile);
	}
}

AngajatInfo* creareAngajat(char* nume, double salariu) {
	AngajatInfo* res = NULL;
	res = (AngajatInfo*)malloc(sizeof(AngajatInfo) * 1);
	if (res != NULL) {
		res->nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
		if (res->nume != NULL) {
			strcpy_s(res->nume, strlen(nume) + 1, nume);
		}
		res->salariu = salariu;
	}
	return res;
}

//void dezalocareAngajat(AngajatInfo* angajat) { 
//	if (angajat != NULL) {
//		free(angajat->nume);
//		free(angajat);
//	}
//}

//AngajatInfo* dezalocareAngajat(AngajatInfo* angajat) { 
//	if (angajat != NULL) {
//		free(angajat->nume);
//		free(angajat);
//	}
//	return NULL;
//}

void dezalocareAngajat(AngajatInfo** angajat) { 
	if (*angajat != NULL) {
		free((*angajat)->nume);
		free(*angajat);
	}
	*angajat = NULL; // eliminare dangling pointer
}

// transcript ora
// stiva creste de la adresa mari la adrese mici
// daca stiva creste prea mult ajunge in CS (code segment) => stack overflow
// aliniamentul de memorie are loc si pe heap
// 