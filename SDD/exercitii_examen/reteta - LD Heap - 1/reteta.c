#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define LINE_SIZE 128

typedef struct Reteta
{
  unsigned nr_reteta;
  char *nume_pacient;
  char *nume_medic;
  char *data_emitere;
  float valoare;
} Reteta;

Reteta *createReteta(unsigned nr_reteta, char *nume_pacient, char *nume_medic, char *data_emitere, float valoare)
{
  Reteta *r = (Reteta *)malloc(sizeof(Reteta));
  if (r)
  {
    r->nr_reteta = nr_reteta;
    r->nume_pacient = strdup(nume_pacient);
    r->nume_medic = strdup(nume_medic);
    r->data_emitere = strdup(data_emitere);
    r->valoare = valoare;
  }
  return r;
}

void deleteReteta(Reteta **r) {
  if (!*r) return;
  free((*r)->nume_pacient);
  free((*r)->nume_medic);
  free((*r)->data_emitere);
  free(*r);
  *r = NULL;
}

typedef struct NodeLD
{
  Reteta *info;
  struct NodeLD *prev, *next;
} NodeLD;

NodeLD *createNodeLD(Reteta *r)
{
  NodeLD *n = (NodeLD *)malloc(sizeof(NodeLD));
  if (n)
  {
    n->info = r;
    n->prev = n->next = NULL;
  }
  return n;
}

void insertNodeLD(NodeLD **h, NodeLD *n)
{
  if (!*h)
  {
    *h = n;
    return;
  }
  NodeLD *aux = *h;
  while (aux->next)
  {
    aux = aux->next;
  }
  n->prev = aux;
  aux->next = n;
}

void parseFile(NodeLD **h, char *fileName)
{
  FILE *f = fopen(fileName, "r");
  if (!f)
    return;
  char buf[LINE_SIZE];
  while (fgets(buf, LINE_SIZE, f))
  {
    char *nr = strtok(buf, ","), *nume_pacient = strtok(NULL, ","), *nume_medic = strtok(NULL, ","), *data_emitere = strtok(NULL, ","), *valoare = strtok(NULL, "\n");
    unsigned nr_reteta;
    sscanf(nr, "%u", &nr_reteta);
    insertNodeLD(h, createNodeLD(createReteta(nr_reteta, nume_pacient, nume_medic, data_emitere, atof(valoare))));
  }
  fclose(f);
}

void printReteta(Reteta *r)
{
  if (!r)
    return;
  printf("Numar reteta: %u, nume pacient: %s, nume medic: %s, data emitere: %s, valoare %.2f\n", r->nr_reteta, r->nume_pacient, r->nume_medic, r->data_emitere, r->valoare);
}

void printList(NodeLD *h)
{
  if (!h)
    return;
  printReteta(h->info);
  printList(h->next);
}

float getValMax(NodeLD *h)
{
  float res = 0;
  NodeLD *aux = h;
  while (aux)
  {
    if (aux->info->valoare > res)
      res = aux->info->valoare;
    aux = aux->next;
  }
  return res;
}

Reteta *getRetetaValMax(NodeLD *h)
{
  if (!h)
    return NULL;
  float max = getValMax(h);
  NodeLD *aux = h;
  while (aux)
  {
    if (aux->info->valoare == max)
    {
      return aux->info;
    }
    aux = aux->next;
  }
}

void actualizareValoare(NodeLD *h, char *n, float p) {
  NodeLD *aux = h;
  while (aux)
  {
    if (!strcmp(n, aux->info->nume_pacient))
    {
      aux->info->valoare *= (1 + p);
    }
    aux = aux->next;
  }
}

NodeLD *getTail(NodeLD *h) {
  NodeLD *aux = h;
  while (aux->next)
  {
    aux = aux->next;
  }
  return aux;
}

void printListReverse(NodeLD *c) {
  if(!c) return;
  printReteta(c->info);
  printListReverse(c->prev);
}

typedef struct Aux {
  char *nume;
  int nr;
} Aux;

int inVector(Aux* v, int n, char *nume) {
  if (!v || !n || !nume) return -1;
  for (int i = 0; i < n; i++)
  {
    if (!strcmp(nume,v[i].nume)) {
      return i;
    }
  }
  return -1;
}

char *getMaxMedic(Aux *v, int n) {
  if (!v || !n) return NULL;
  int max = 0;
  for (int i = 0; i < n; i++)
  {
    if (v[i].nr > max) max = v[i].nr;
  }
  for (int i = 0; i < n; i++)
  {
    if (v[i].nr == max) return v[i].nume;
  }
}

char *numeMedicMaxNrRetete(NodeLD *h) {
  if (!h) return NULL;
  Aux* mediciNrFacturi = NULL;
  int n = 0;
  NodeLD *aux = h;
  while (aux)
  {
    int pos = inVector(mediciNrFacturi, n, aux->info->nume_medic);
    if (pos == -1) {
      mediciNrFacturi = (Aux *)realloc(mediciNrFacturi, sizeof(Aux) * (n+1));
      mediciNrFacturi[n].nr = 1;
      mediciNrFacturi[n].nume = aux->info->nume_medic;
      n++;
    } else {
      mediciNrFacturi[pos].nr++;
    }
    aux = aux->next;
  }
  char *medic = getMaxMedic(mediciNrFacturi, n);
  free(mediciNrFacturi);
  mediciNrFacturi = NULL;
  return medic;
}

typedef struct Heap {
  unsigned* el;
  int size;
} Heap;

Heap *initHeap() {
  Heap *h = (Heap *)malloc(sizeof(Heap));
  if (h) {
    h->el = NULL;
    h->size = 0;
  }
  return h;
}

void swap(unsigned *a, unsigned *b) {
  unsigned temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(Heap *h, int i) {
  int p = i;
  int s = (2*i) + 1;
  int d = (2*i) + 2;

  if (s < h->size && h->el[s] > h->el[p]) {
    p = s;
  }
  if (d < h->size && h->el[d] > h->el[p]) {
    p = d;
  }

  if (p != i) {
    swap(&(h->el[i]), &(h->el[p]));
    heapify(h, p);
  }
}

void insertHeap(Heap *h, unsigned n) {
  h->el = (unsigned*)realloc(h->el, sizeof(unsigned) * (h->size + 1));
  h->el[h->size] = n;
  h->size++;

  for (int i = (h->size - 1)/2; i >= 0; i--)
  {
    heapify(h, i);
  }
  
}

void convertLDH(NodeLD *head, Heap *h, char* d) {
  if (!head || !h || !d) return;
  NodeLD *aux = head;
  while (aux)
  {
    if (!strcmp(aux->info->data_emitere, d)) insertHeap(h, aux->info->nr_reteta);
    aux = aux->next;
  }
}

void printHeap(Heap *h) {
  if (!h) return;
  for (int i = 0; i < h->size; i++)
  {
    printf("Reteta cu nr-ul: %u\n", h->el[i]);
  }
}

void deallocateList(NodeLD **h) {
  if (!*h) return;
  NodeLD *next = (*h)->next;
  deleteReteta(&((*h)->info));
  free(*h);
  *h = NULL;
  deallocateList(&(next));
}

void deallocateHeap(Heap **h) {
  free((*h)->el);
  free(*h);
  *h = NULL;
}

void main()
{
  NodeLD *h = NULL;
  parseFile(&h, "data.txt");
  printList(h);
  Reteta *r = getRetetaValMax(h);
  printf("Reteta cu val maxima\n");
  printReteta(r);
  actualizareValoare(h, "Alex", -0.2);
  printf("Dupa actualizare\n");
  printList(h);
  printListReverse(getTail(h));
  char *medicNrMaxRetete = numeMedicMaxNrRetete(h);
  printf("Medicul cu nr de retete maxim este: %s\n", medicNrMaxRetete);
  Heap* heap = initHeap();
  convertLDH(h, heap, "20.03.2023");
  printf("Heap\n");
  printHeap(heap);
  deallocateList(&h);
  deallocateHeap(&heap);
}
