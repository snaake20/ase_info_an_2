#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define LINE_SIZE 128
#define HT_SIZE 30

typedef struct Gradinita
{
  char *nume;
  char *oras;
  int capacitate;
  bool areProgramPrelungit;
} Gradinita;

Gradinita *createGradinita(char *nume, char *oras, int capacitate, bool areProgramPrelungit)
{
  Gradinita *g = (Gradinita *)malloc(sizeof(Gradinita));
  if (g)
  {
    g->nume = strdup(nume);
    g->oras = strdup(oras);
    g->capacitate = capacitate;
    g->areProgramPrelungit = areProgramPrelungit;
  }
  return g;
}

typedef struct NodeLS
{
  Gradinita *info;
  struct NodeLS *next;
} NodeLS;

NodeLS *createNodeLS(Gradinita *g)
{
  NodeLS *n = (NodeLS *)malloc(sizeof(NodeLS));
  if (n)
  {
    n->info = g;
    n->next = NULL;
  }
  return n;
}

typedef struct HashTable
{
  NodeLS **el;
  int size;
} HashTable;

HashTable *initHashTable()
{
  HashTable *t = (HashTable *)malloc(sizeof(HashTable));
  if (t)
  {
    t->el = (NodeLS **)calloc(HT_SIZE, sizeof(NodeLS *));
    t->size = HT_SIZE;
  }
  return t;
}

typedef struct NodeLD
{
  Gradinita *info;
  struct NodeLD *prev, *next;
} NodeLD;

NodeLD *createNodeLD(Gradinita *g)
{
  NodeLD *n = (NodeLD *)malloc(sizeof(NodeLD));
  if (n)
  {
    n->info = g;
    n->prev = n->next = NULL;
  }
  return n;
}

// ---------------------------------------------

int hash(char *str, int size)
{
  int v = 0;
  for (int i = 0; i < strlen(str); i++)
  {
    v += str[i];
  }
  return v % size;
}

void insertHashTable(HashTable *t, NodeLS *n)
{
  int pos = hash(n->info->oras, t->size);
  if (!t->el[pos])
  {
    t->el[pos] = n;
    return;
  }
  NodeLS *aux = t->el[pos];
  while (aux->next)
  {
    aux = aux->next;
  }
  aux->next = n;
}

void parseFile(HashTable *t, char *fileName)
{
  FILE *f = fopen(fileName, "r");
  if (!f)
    exit(-1);
  char buf[LINE_SIZE];
  while (fgets(buf, LINE_SIZE, f))
  {
    char *nume = strtok(buf, ","), *oras = strtok(NULL, ","), *capacitate = strtok(NULL, ","), *areProgramPrelungit = strtok(NULL, "\n");
    insertHashTable(t, createNodeLS(createGradinita(nume, oras, atoi(capacitate), atoi(areProgramPrelungit))));
  }
  fclose(f);
}

void printGradinita(Gradinita *g)
{
  if (!g)
    return;
  printf("Nume: %s, oras: %s, capacitate: %d, are program prelungit: %s\n", g->nume, g->oras, g->capacitate, (g->areProgramPrelungit ? "da" : "nu"));
}

void printListS(NodeLS *n)
{
  if (!n)
    return;
  printGradinita(n->info);
  printListS(n->next);
}

void printHashTable(HashTable *t)
{
  if (!t || !t->el || !t->size)
    return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i])
    {
      printf("Pozitie: %d\n", i);
      printListS(t->el[i]);
    }
  }
}

// ---------------------------------------------

bool doesKeyExist(HashTable *t, char *v)
{
  if (!t || !v)
    return false;
  if (t->el[hash(v, t->size)])
    return true;
  return false;
}

void modificaOras(HashTable *t, char *v, char *n)
{
  if (!doesKeyExist(t, v))
    return;
  // link list to other hash
  NodeLS *aux = t->el[hash(v, t->size)];
  while (aux)
  {
    if (!strcmp(v, aux->info->oras))
    {
      free(aux->info->oras);
      aux->info->oras = strdup(n);
    }
    aux = aux->next;
  }
  if (!t->el[hash(n, t->size)])
  {
    t->el[hash(n, t->size)] = t->el[hash(v, t->size)];
  }
  else
  {
    NodeLS *aux = t->el[hash(n, t->size)];
    while (aux->next)
    {
      aux = aux->next;
    }
    aux->next = t->el[hash(v, t->size)];
  }
  // invalidate old hash
  t->el[hash(v, t->size)] = NULL;
}

// ---------------------------------------------

Gradinita *deepCloneGradinita(Gradinita *g)
{
  if (!g)
    return NULL;
  return createGradinita(g->nume, g->oras, g->capacitate, g->areProgramPrelungit);
}

void insertListD(NodeLD **h, NodeLD *n)
{
  if (!*h)
  {
    *h = n;
    return;
  }
  NodeLD *temp = *h;
  while (temp->next)
  {
    temp = temp->next;
  }
  n->prev = temp;
  temp->next = n;
}

void convertHTLD(HashTable *t, NodeLD **h)
{
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i])
    {
      NodeLS *aux = t->el[i];
      while (aux)
      {
        if (aux->info->areProgramPrelungit == true)
          insertListD(h, createNodeLD(deepCloneGradinita(aux->info)));
        aux = aux->next;
      }
    }
  }
}

void printListD(NodeLD *h)
{
  if (!h)
    return;
  printGradinita(h->info);
  printListD(h->next);
}

// ---------------------------------------------

void spargeIn2Liste(NodeLD **h, NodeLD **l, char* n) {
  NodeLD *aux = *h;
  while (strcmp(aux->info->nume, n) != 0)
  {
    aux = aux->next;
  }
  aux->next->prev = NULL;
  *l = aux->next;
  aux->next = NULL;
}

// ---------------------------------------------

void deleteGradinita(Gradinita **g)
{
  if (!*g)
    return;
  free((*g)->nume);
  free((*g)->oras);
  free((*g));
  *g = NULL;
}

void deleteNodeLS(NodeLS **n)
{
  if (!*n)
    return;
  deleteGradinita(&((*n)->info));
  free(*n);
  *n = NULL;
}

void deallocateListS(NodeLS **h)
{
  if (!*h)
    return;
  deallocateListS(&((*h)->next));
  deleteNodeLS(h);
}

void deallocateHashTable(HashTable **t) {
  if (!*t) return;
  for (int i = 0; i < (*t)->size; i++)
  {
    if ((*t)->el[i]) {
      deallocateListS(&((*t)->el[i]));
    }
  }
  free((*t)->el);
  free((*t));
  *t = NULL;
}

void deleteNodeLD(NodeLD **h) {
  deleteGradinita(&((*h)->info));
  free((*h));
  *h = NULL;
}

void deallocateListD(NodeLD **h) {
  if (!*h) return;
  deallocateListD(&((*h)->next));
  deleteNodeLD(h);
}

void main()
{
  HashTable *t = initHashTable();
  parseFile(t, "data.txt");
  printHashTable(t);
  printf("Modificare oras\n");
  modificaOras(t, "Iasi", "Bucuresti");
  printHashTable(t);
  NodeLD *h = NULL;
  printf("Conversie Hash Table la Lista Dubla\n");
  convertHTLD(t, &h);
  printListD(h);
  NodeLD *l = NULL;
  printf("Spargem listele\n");
  spargeIn2Liste(&h, &l, "Gradinita7");
  printf("Lista 1\n");
  printListD(h);
  printf("Lista 2\n");
  printListD(l);
  deallocateHashTable(&t);
  deallocateListD(&h);
  deallocateListD(&l);
}