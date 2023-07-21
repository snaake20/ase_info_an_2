#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define LINE_SIZE 128

typedef struct Comanda
{
  int id_comanda;
  int cod_client;
  int timp_livrare;
  float valoare;
  char *adresa;
} Comanda;

Comanda *createComanda(int id_comanda, int cod_client, int timp_livrare, float valoare, char *adresa)
{
  Comanda *c = (Comanda *)malloc(sizeof(Comanda));
  if (c)
  {
    c->id_comanda = id_comanda;
    c->cod_client = cod_client;
    c->timp_livrare = timp_livrare;
    c->valoare = valoare;
    c->adresa = strdup(adresa);
  }
  return c;
}

typedef struct NodeT
{
  Comanda *info;
  struct NodeT *left, *right;
} NodeT;

NodeT *createNodeT(Comanda *c, NodeT *l, NodeT *r)
{
  NodeT *n = (NodeT *)malloc(sizeof(NodeT));
  if (n)
  {
    n->info = c;
    n->left = l;
    n->right = r;
  }
  return n;
}

void insertBST(NodeT **r, NodeT *n)
{
  if (!*r)
  {
    *r = n;
    return;
  }
  if (n->info->id_comanda < (*r)->info->id_comanda)
  {
    insertBST(&((*r)->left), n);
  }
  else if (n->info->id_comanda > (*r)->info->id_comanda)
  {
    insertBST(&((*r)->right), n);
  }
}

void parseFile(NodeT **r, char *fileName)
{
  FILE *f = fopen(fileName, "r");
  if (!f) exit(-1);
  char b[LINE_SIZE];
  while (fgets(b, LINE_SIZE, f))
  {
    char *id_comanda = strtok(b, ","), *cod_client = strtok(NULL, ","), *timp_livrare = strtok(NULL, ","), *valoare = strtok(NULL, ","), *adresa = strtok(NULL, "\n");
    insertBST(r, createNodeT(createComanda(atoi(id_comanda), atoi(cod_client), atoi(timp_livrare), atof(valoare), adresa), NULL, NULL));
  }
}

void printComanda(Comanda *c) {
  if (!c) return;
  printf("id: %d, cod client: %d, timp livrare: %d, adresa: %s\n", c->id_comanda, c->cod_client, c->timp_livrare, c->adresa);
}

void inordine(NodeT *r) {
  if (!r) return;
  inordine(r->left);
  printComanda(r->info);
  inordine(r->right);
}

typedef struct Vector {
  Comanda **el;
  int length;
} Vector;

Vector *initVector() {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  if (v) {
    v->el = NULL;
    v->length = 0;
  }
  return v;
}

void insertVector(Vector *v, Comanda *c) {
  v->el = (Comanda**)realloc(v->el, sizeof(Comanda *) * (v->length + 1));
  v->el[v->length++] = c;
}

Comanda *deepClone(Comanda *c) {
  if (!c) return NULL;
  return createComanda(c->id_comanda, c->cod_client, c->timp_livrare, c->valoare, c->adresa);
}

void comenziCuTimpLivrarePeste(NodeT *r, Vector*v, int t) {
  if (!r) return;
  if (r->info->timp_livrare > t) insertVector(v, deepClone(r->info));
  comenziCuTimpLivrarePeste(r->left, v, t);
  comenziCuTimpLivrarePeste(r->right, v, t);
}

void printVector(Vector *v) {
  if (!v) return;
  for (int i = 0; i < v->length; i++)
  {
    printComanda(v->el[i]);
  }
}

typedef struct Heap {
  Comanda **el;
  int size;
} Heap;

Heap *initHeap() {
  Heap *v = (Heap *)malloc(sizeof(Heap));
  if (v) {
    v->el = NULL;
    v->size = 0;
  }
  return v;
}

void swap(Comanda **a, Comanda **b) {
  Comanda * tmp = *a;
  *a = *b;
  *b = tmp;
}

void heapify(Heap *h, int i) {
  int p = i, s = 2*i+1, d= 2*i+2;
  if (s<h->size && h->el[s]->timp_livrare > h->el[p]->timp_livrare) {
    p = s;
  }
  if (d<h->size && h->el[d]->timp_livrare > h->el[p]->timp_livrare) {
    p = d;
  }
  if (p!=i) {
    swap(&h->el[i], &h->el[p]);
    heapify(h, p);
  }
}

void insertHeap(Heap *h, Comanda *c) {
  h->el = (Comanda**)realloc(h->el, sizeof(Comanda *) * (h->size + 1));
  h->el[h->size++] = c;
  for (int i = (h->size -1)/2; i >= 0; i--)
  {
    heapify(h, i);
  }
}

void comenziPrioritare(NodeT *r, Heap *h) {
  if (!r) return;
  insertHeap(h, deepClone(r->info));
  comenziPrioritare(r->left, h);
  comenziPrioritare(r->right, h);
}

void extragereHeap(Heap *h, Comanda **c) {
  swap(&h->el[0], &h->el[h->size-1]);
  *c = h->el[h->size-1];
  h->el = (Comanda **)realloc(h->el, sizeof(Comanda*) * (--h->size));
  for (int i = (h->size - 1)/2; i >= 0; i--)
  {
    heapify(h, i);
  }
}

void printHeap(Heap *h) {
  if (!h) return;
  for (int i = 0; i < h->size; i++)
  {
    printComanda(h->el[i]);
  }
}

typedef struct Aux {
  int cod_client;
  float suma_totala;
} Aux;

void insertVectorAux(Aux** v, int *n, Aux a) {
  *v = (Aux *)realloc(*v, sizeof(Aux) * ((*n) + 1));
  (*v)[(*n)++] = a;
}

int inVector(Aux *v, int n, int c) {
  if (!v || !n) return -1;
  for (int i = 0; i < n; i++)
  {
    if (v[i].cod_client == c) return i;
  }
  return -1;
}

void convertBSTAux(NodeT *r, Aux **v, int *n) {
  if (!r) return;
  int pos = inVector(*v, *n, r->info->cod_client);
  if (pos == -1) {
    Aux a = {r->info->cod_client, r->info->valoare};
    insertVectorAux(v, n, a);
  } else {
    (*v)[pos].suma_totala += r->info->valoare;
  }
  convertBSTAux(r->left, v, n);
  convertBSTAux(r->right, v, n);
}

void printVectorAux(Aux *v, int n) {
  if (!v) return;
  for (int i = 0; i < n; i++)
  {
    printf("Cod client: %d, suma totala: %.2f\n", v[i].cod_client, v[i].suma_totala);
  }
}

void deleteComanda(Comanda **c) {
  if (!*c) return;
  free((*c)->adresa);
  free((*c));
  *c = NULL;
}

void deleteNodeT(NodeT **r) {
  if (!*r) return;
  deleteComanda(&((*r)->info));
  free((*r));
  *r = NULL;
}

void deallocateBST(NodeT **r) {
  if (!*r) return;
  deallocateBST(&((*r)->left));
  deallocateBST(&((*r)->right));
  deleteNodeT(r);
}

void deallocateVector(Vector **v) {
  for (int i = 0; i < (*v)->length; i++)
  {
    deleteComanda(&((*v)->el[i]));
  }
  free((*v)->el);
  free((*v));
  *v = NULL;
}

void deallocateHeap(Heap **v) {
  for (int i = 0; i < (*v)->size; i++)
  {
    deleteComanda(&((*v)->el[i]));
  }
  free((*v)->el);
  free((*v));
  *v = NULL;
}

void deallocateVectorAux(Aux **v, int *n) {
  free((*v));
  *v = NULL;
  *n = 0;
}

void main() {
  NodeT *r = NULL;
  parseFile(&r, "data.txt");
  inordine(r);
  Vector *v = initVector();
  comenziCuTimpLivrarePeste(r, v, 30);
  printf("Vector cu timp livrare peste 30\n");
  printVector(v);
  Heap *h = initHeap();
  comenziPrioritare(r, h);
  printf("Heap\n");
  printHeap(h);
  Aux *a = NULL;
  int l = 0;
  convertBSTAux(r, &a, &l);
  printf("Vector aux\n");
  printVectorAux(a, l);
  deallocateBST(&r);
  deallocateVector(&v);
  deallocateHeap(&h);
  deallocateVectorAux(&a, &l);
}