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

typedef struct Node {
	AngajatInfo* info;
	struct Node* next;
} ListNode;

//typdef struct Node ListNode;

//typedef struct Angajat AngajatInfo;

//management info utila stocata in HEAP
AngajatInfo* creareAngajat(char*, double, unsigned short);
//void dezalocareAngajat(AngajatInfo* angajat); // seminar

ListNode* createNode(AngajatInfo*);
ListNode* copyNode(ListNode*);

ListNode* insertNodeToEnd(ListNode*, ListNode*);

void insertNodeToHead(ListNode**, ListNode*);

// insert node to the middle either ListNode* or void as return type

// insert node after a specific name (every criteria is welcome)

void printList(ListNode*);

void dezalocareAngajat(AngajatInfo**);

void displayAngajat(AngajatInfo*);

void afisareAngajati(AngajatInfo**, short);


void main() {
	AngajatInfo a; // sau struct Angajat
	a.nume = NULL;
	a.salariu = 100.4;

	AngajatInfo* agenda[10];

	ListNode* simpleLinkedList1 = NULL;
	ListNode* simpleLinkedList2 = NULL;

	memset(agenda, 0, sizeof(AngajatInfo*) * 10);

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

			ListNode* node = createNode(ang);

			simpleLinkedList1 = insertNodeToEnd(simpleLinkedList1, node);
			insertNodeToHead(&simpleLinkedList2, node);
			// adaugare in masiv
			agenda[idx++] = ang;
		}
		//dezalocareAngajat(&ang);
		fclose(pFile);
	}
	//afisareAngajati(agenda, sizeof(agenda) / sizeof(AngajatInfo*));
	printList(simpleLinkedList1); // verifica de ce nu apare nimic in consola
	printList(simpleLinkedList2);
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
		displayAngajat(agenda[i]);
	}
}

void displayAngajat(AngajatInfo* ang) {
	if (ang) {
		printf("Nume: %s, Salariu: %.2f\n", ang->nume, ang->salariu);
		if (ang->referinta.ref_externa >> 15 == 1) {
			printf("Contractor: %d ", ang->referinta.ref_externa >> 8);
		}
		printf("Referinta: %d\n", ang->referinta.ref_externa & 255);
	}
}

ListNode* createNode(AngajatInfo* ang) {
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	if (node != NULL) {
		node->info = ang;
		node->next = NULL;
	}
	return node;
}

ListNode* copyNode(ListNode* nodeToCopy) {
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	if (node != NULL) {
		node->info = nodeToCopy->info;
		node->next = nodeToCopy->next;
	}
	return node;
}

ListNode* insertNodeToEnd(ListNode* list, ListNode* node) {
	ListNode* copy = copyNode(node);
	if (!list) {
		return copy;
	}

	ListNode* aux = list;
	while (aux->next)
		aux = aux->next;
	aux->next = copy;
	return list;
}

void printList(ListNode* list) {
	while (list) {
		displayAngajat(list->info);
		list = list->next;
	}
}

void insertNodeToHead(ListNode** list, ListNode* node) {
	ListNode* copy = copyNode(node);
	copy->next = *list;
	*list = copy;
}


// transcript seminar
// 1. alocare 2. initializare 3. return
// Tema: inserare dupa Golescu (dupa anumite criterii if node->info->nume == "Golescu ...") si inserare la mijloc