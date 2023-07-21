#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define LINE_SIZE 128
#define HT_SIZE 31
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

typedef struct ContBancar
{
  char *nume_client;
  float sold;
  char *valuta_cont;
} ContBancar;

ContBancar *createContBancar(char *nume_client, float sold, char *valuta_cont)
{
  ContBancar *c = (ContBancar *)malloc(sizeof(ContBancar));
  if (c)
  {
    c->nume_client = strdup(nume_client);
    c->sold = sold;
    c->valuta_cont = strdup(valuta_cont);
  }
  return c;
}

typedef struct NodeLS
{
  ContBancar *info;
  struct NodeLS *next;
} NodeLS;

NodeLS *createNodeLS(ContBancar *c)
{
  NodeLS *n = (NodeLS *)malloc(sizeof(NodeLS));
  if (n)
  {
    n->info = c;
    n->next = NULL;
  }
  return n;
}

typedef struct HashTable
{
  NodeLS **el;
  int size;
} HashTable;

HashTable *initHashT()
{
  HashTable *t = (HashTable *)malloc(sizeof(HashTable));
  if (t)
  {
    t->el = (NodeLS **)calloc(HT_SIZE, sizeof(NodeLS *));
    t->size = HT_SIZE;
  }
  return t;
}

int hash(char *n, int s)
{
  int val = 0;
  for (int i = 0; i < strlen(n); i++)
  {
    val += n[i];
  }
  return val % s;
}

void insertHashT(HashTable *t, NodeLS *n)
{
  if (!t)
    return;
  int pos = hash(n->info->nume_client, t->size);
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
  char b[LINE_SIZE];
  while (fgets(b, LINE_SIZE, f))
  {
    char *nume_client = strtok(b, ","), *sold = strtok(NULL, ","), *valuta_cont = strtok(NULL, "\n");
    insertHashT(t, createNodeLS(createContBancar(nume_client, atof(sold), valuta_cont)));
  }
  fclose(f);
}

void printContBancar(ContBancar *c)
{
  if (!c)
    return;
  printf("nume client: %s, sold: %.2f, valuta_cont: %s\n", c->nume_client, c->sold, c->valuta_cont);
}

void printList(NodeLS *h)
{
  if (!h)
    return;
  printContBancar(h->info);
  printList(h->next);
}

void printHashT(HashTable *t)
{
  if (!t)
    return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i])
    {
      printf("Pozitie: %d\n", i);
      printList(t->el[i]);
    }
  }
}

typedef struct Vector
{
  ContBancar **el;
  int length;
} Vector;

Vector *initVector()
{
  Vector *t = (Vector *)malloc(sizeof(Vector));
  if (t)
  {
    t->el = NULL;
    t->length = 0;
  }
  return t;
}

void insertVector(Vector *v, ContBancar *c)
{
  v->el = (ContBancar **)realloc(v->el, sizeof(ContBancar *) * (v->length + 1));
  v->el[v->length++] = c;
}

ContBancar *deepClone(ContBancar *c)
{
  return createContBancar(c->nume_client, c->sold, c->valuta_cont);
}

void conturiCuValuta(char *val, HashTable *t, Vector *v)
{
  if (!t)
    return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i])
    {
      NodeLS *aux = t->el[i];
      while (aux)
      {
        if (!strcmp(aux->info->valuta_cont, val))
          insertVector(v, deepClone(aux->info));
        aux = aux->next;
      }
    }
  }
}

void printVector(Vector *v) {
  if (!v) return;
  for (int i = 0; i < v->length; i++)
  {
    printContBancar(v->el[i]);
  }
}

typedef struct Cluster {
  int dimensiune_cluster;
  int index_tabela;
} Cluster;

Cluster *createCluster(int dim, int idx) {
  Cluster *c = (Cluster *)malloc(sizeof(Cluster));
  if (c) {
    c->dimensiune_cluster = dim;
    c->index_tabela = idx;
  }
  return c;
}

void insertCluster(Cluster***c, int*n, Cluster * p) {
  (*c) = (Cluster **)realloc(*c, sizeof(Cluster *) * (*n + 1));
  (*c)[(*n)++] = p;
}

void getClusters(HashTable *t, Cluster ***c, int *n) {
  if (!t)
    return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i])
    {
      NodeLS *aux = t->el[i];
      if (!aux->next) continue;
      int nr=0;
      while (aux)
      {
        nr++;
        aux = aux->next;
      }
      insertCluster(c, n, createCluster(nr, i));
    }
  }
}

void printClusters(Cluster**c, int dim) {
  if (!c) return;
  for (int i = 0; i < dim; i++)
  {
    printf("index tabela: %d, dimensiune cluster %d\n", c[i]->index_tabela, c[i]->dimensiune_cluster);
  }
}

typedef struct SoldTotal {
  char *nume_client;
  float sold_total;
} SoldTotal;

SoldTotal *createSoldTotal(char *n, float s) {
  SoldTotal *c = (SoldTotal *)malloc(sizeof(SoldTotal));
  if (c) {
    c->nume_client = strdup(n);
    c->sold_total = s;
  }
  return c;
}

void insertSoldTotal(SoldTotal***c, int*n, SoldTotal * p) {
  (*c) = (SoldTotal **)realloc(*c, sizeof(SoldTotal *) * (*n + 1));
  (*c)[(*n)++] = p;
}

int isKeyIn(SoldTotal **v, int dim, char *n) {
  if (!v) return -1;
  for (int i = 0; i < dim; i++)
  {
    if (!strcmp(v[i]->nume_client, n)) return i;
  }
  return -1;
}

void getSoldTotal(Vector *v, SoldTotal***s, int*n) {
  if (!v) return;
  for (int i = 0; i < v->length; i++)
  {
    int pos = isKeyIn(*s, *n, v->el[i]->nume_client);
    if (pos == -1) {
      insertSoldTotal(s,n,createSoldTotal(v->el[i]->nume_client, v->el[i]->sold));
    } else {
      (*s)[pos]->sold_total += v->el[i]->sold;
    }
  }
  
}

void printSoldTotal(SoldTotal**c, int dim) {
  if (!c) return;
  for (int i = 0; i < dim; i++)
  {
    printf("nume client: %s, sold total %.2f\n", c[i]->nume_client, c[i]->sold_total);
  }
}

void deleteContBancar(ContBancar **c) {
  free((*c)->nume_client);
  free((*c)->valuta_cont);
  free((*c));
  *c = NULL;
}

void deallocateVector(Vector **v) {
  if (!*v) return;
  for (int i = 0; i < (*v)->length; i++)
  {
    deleteContBancar(&((*v)->el[i]));
  }
  free((*v)->el);
  free(*v);
  *v = NULL;
}

void deleteCluster(Cluster **c) {
  if (!*c) return;
  free((*c));
  *c = NULL;
}

void deallocateClusters(Cluster ***c, int* dim) {
  if (!*c) return;
  for (int i = 0; i < *dim; i++)
  {
    deleteCluster(&((*c)[i]));
  }
  free(*c);
  *c = NULL;
  *dim = 0;
}

void deleteNodeLS(NodeLS **n) {
  deleteContBancar(&((*n)->info));
  free(*n);
  *n = NULL;
}

void deallocateList(NodeLS **h) {
  if (!*h) return;
  deallocateList(&((*h)->next));
  deleteNodeLS(h);
}

void deallocateHashT(HashTable **t) {
  if (!*t) return;
  for (int i = 0; i < (*t)->size; i++)
  {
    deallocateList(&((*t)->el[i]));
  }
  free((*t)->el);
  free((*t));
  *t = NULL;
}

void deleteSoldTotal(SoldTotal **s) {
  if (!*s) return;
  free((*s)->nume_client);
  free((*s));
  *s = NULL;
}

void deallocateSoldTotal(SoldTotal ***s, int* dim) {
  if (!*s) return;
  for (int i = 0; i < *dim; i++)
  {
    deleteSoldTotal(&((*s)[i]));
  }
  free(*s);
  *s = NULL;
  *dim = 0;
}

void main()
{
  HashTable *t = initHashT();
  parseFile(t, "data.txt");
  printHashT(t);
  Vector *v = initVector();
  conturiCuValuta("RON", t, v);
  printf("Vector\n");
  printVector(v);
  Cluster **clustere = NULL;
  int dim = 0;
  getClusters(t, &clustere, &dim);
  printf("Clustere\n");
  printClusters(clustere, dim);
  deallocateHashT(&t);
  deallocateClusters(&clustere, &dim);
  SoldTotal**s = NULL;
  int n= 0;
  getSoldTotal(v, &s, &n);
  deallocateVector(&v);
  printf("Solduri Totale\n");
  printSoldTotal(s, n);
  deallocateSoldTotal(&s, &n);
  _CrtDumpMemoryLeaks();
}