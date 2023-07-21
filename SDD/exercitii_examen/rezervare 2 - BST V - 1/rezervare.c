#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <crtdbg.h>
#define LINE_SIZE 128

typedef struct Rezervare {
	unsigned numar_rezervare;
	char* denumire_hotel;
	unsigned char numar_camere_rezervate;
	char* nume_client;
	char* data_rezervare;
} Rezervare;

Rezervare* createRezervare(unsigned numar_rezervare, char* denumire_hotel, unsigned char numar_camere_rezervate, char* nume_client, char* data_rezervare)
{
	Rezervare* r = (Rezervare*)malloc(sizeof(Rezervare));
	if (r) {
		r->numar_rezervare = numar_rezervare;
		r->denumire_hotel = strdup(denumire_hotel);
		r->numar_camere_rezervate = numar_camere_rezervate;
		r->nume_client = strdup(nume_client);
		r->data_rezervare = strdup(data_rezervare);
	}
	return r;
}

Rezervare* deepCopyRezervare(Rezervare* r) {
	return createRezervare(r->numar_rezervare, r->denumire_hotel, r->numar_camere_rezervate, r->nume_client, r->data_rezervare);
}

void deleteRezervare(Rezervare** r) {
	if (!*r) return;
	free((*r)->denumire_hotel);
	free((*r)->nume_client);
	free((*r)->data_rezervare);
	free(*r);
	*r = NULL;
}

typedef struct NodeT {
	Rezervare* info;
	struct NodeT* left, * right;
} NodeT;

NodeT* createNodeT(Rezervare* rez, NodeT* l, NodeT* r) {
	NodeT* t = (NodeT*)malloc(sizeof(NodeT));
	if (t) {
		t->info = rez;
		t->left = l;
		t->right = r;
	}
	return t;
}

void deleteNodeT(NodeT** n) {
	if (!*n) return;
	deleteRezervare(&((*n)->info));
	free(*n);
	*n = NULL;
}

void insertBST(NodeT** r, NodeT* n) {
	if (!*r) {
		*r = n;
		return;
	}
	if (n->info->numar_rezervare < (*r)->info->numar_rezervare) {
		insertBST(&((*r)->left), n);
	}
	else if (n->info->numar_rezervare > (*r)->info->numar_rezervare) {
		insertBST(&((*r)->right), n);
	}
}

void parseFile(NodeT** r, char* fileName) {
	FILE* f = fopen(fileName, "r");
	if (!f) exit(-1);
	char b[LINE_SIZE];
	while (fgets(b, LINE_SIZE, f))
	{
		char* numar = strtok(b, ","), * denumire_hotel = strtok(NULL, ","), * numar_camere = strtok(NULL, ","), * nume_client = strtok(NULL, ","), * data_rezervare = strtok(NULL, "\n");
		unsigned numar_rezervare;
		sscanf(numar, "%u", &numar_rezervare);
		unsigned char numar_camere_rezervate;
		sscanf(numar_camere, "%hhu", &numar_camere_rezervate);
		insertBST(r, createNodeT(createRezervare(numar_rezervare, denumire_hotel, numar_camere_rezervate, nume_client, data_rezervare), NULL, NULL));
	}
	fclose(f);
}

void printRezervare(Rezervare* r) {
	if (!r) return;
	printf("numar rezervare: %u, denumire hotel: %s, numar camere rezervate: %hhu, nume client: %s, data rezervare: %s.\n", r->numar_rezervare, r->denumire_hotel, r->numar_camere_rezervate, r->nume_client, r->data_rezervare);
}

void inordine(NodeT* r) {
	if (!r) return;
	inordine(r->left);
	printRezervare(r->info);
	inordine(r->right);
}

void deallocateBST(NodeT** r) {
	if (!*r) return;
	deallocateBST(&((*r)->left));
	deallocateBST(&((*r)->right));
	deleteNodeT(r);
}

void getNrMaxCamere(NodeT* r, unsigned* n) {
	if (!r) return;
	if (*n < r->info->numar_camere_rezervate) *n = r->info->numar_camere_rezervate;
	getNrMaxCamere(r->left, n);
	getNrMaxCamere(r->right, n);
}

Rezervare* gasesteRezervareNrMaxCamere(NodeT* r, unsigned n) {
	if (!r) return NULL;
	if (r->info->numar_camere_rezervate == n) {
		return r->info;
	}
	Rezervare* l = gasesteRezervareNrMaxCamere(r->left, n);
	if (l) {
		return l;
	}
	return gasesteRezervareNrMaxCamere(r->right, n);
}

Rezervare* gasesteRezervare(NodeT* r, unsigned n) {
	if (!r) return NULL;
	if (r->info->numar_rezervare == n) {
		return r->info;
	}
	Rezervare* l = gasesteRezervare(r->left, n);
	if (l) {
		return l;
	}
	return gasesteRezervare(r->right, n);
}

void modificaNrCamereRezervate(NodeT* r, unsigned nr_rezervare, unsigned char nr_camere)
{
	if (!r) return;
	Rezervare* rez = gasesteRezervare(r, nr_rezervare);
	if (!rez) return;
	rez->numar_camere_rezervate = nr_camere;
}

unsigned getNrNoduriBST(NodeT* r) {
	if (!r) return 0;
	return 1 + (r->left ? getNrNoduriBST(r->left) : 0) + (r->right ? getNrNoduriBST(r->right) : 0);
}

typedef struct Vector {
	Rezervare** el;
	int length;
} Vector;

Vector* createVector() {
	Vector* v = (Vector*)malloc(sizeof(Vector));
	if (v) {
		v->el = NULL;
		v->length = 0;
	}
	return v;
}

void insertVector(Vector* v, Rezervare* r) {
	v->el = (Rezervare**)realloc(v->el, sizeof(Rezervare*) * (v->length + 1));
	v->el[v->length++] = r;
}

int doesNodeExist(NodeT* r, unsigned n) {
	if (!r) return 0;
	return (r->info->numar_rezervare == n ? 1 : 0) + (r->left ? doesNodeExist(r->left, n) : 0) + (r->right ? doesNodeExist(r->right, n) : 0);
}

void getPathTo(unsigned nr, NodeT* r, Vector* v) {
	if (!doesNodeExist(r, nr)) return;
	insertVector(v, deepCopyRezervare(r->info));
	getPathTo(nr, r->left, v);
	getPathTo(nr, r->right, v);
}

void printVector(Vector* v) {
	if (!v) return;
	for (int i = 0; i < v->length; i++)
	{
		printRezervare(v->el[i]);
	}
}

void deallocateVector(Vector** v) {
	if (!*v) return;
	for (int i = 0; i < (*v)->length; i++)
	{
		deleteRezervare(&((*v)->el[i]));
	}
	free((*v)->el);
	free(*v);
	*v = NULL;
}

void main() {
	NodeT* r = NULL;
	parseFile(&r, "data.txt");
	inordine(r);
	unsigned nrNoduriBST = getNrNoduriBST(r);
	printf("Nr de noduri din arbore este %u\n", nrNoduriBST);
	unsigned nr_max_camere = 0;
	getNrMaxCamere(r, &nr_max_camere);
	Rezervare* rez = gasesteRezervareNrMaxCamere(r, nr_max_camere);
	printf("Rezervarea cu nr max de camere\n");
	printRezervare(rez);
	unsigned nr_rezervare = 3;
	modificaNrCamereRezervate(r, nr_rezervare, 0);
	rez = gasesteRezervare(r, nr_rezervare);
	printf("Rezervarea modificata\n");
	printRezervare(rez);
	rez = NULL;
	Vector* v = createVector();
	getPathTo(3, r, v);
	printf("Vector cu calea catre rezervarea cu numarul 3\n");
	printVector(v);
	deallocateBST(&r);
	deallocateVector(&v);
	_CrtDumpMemoryLeaks();
}