#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define LINE_SIZE 128

typedef struct Comanda
{
  unsigned idComanda;
  char *dataLansare;
  char *dataLivrare;
  char *numeClient;
  float sumaPlata;
} Comanda;

Comanda *createComanda(unsigned idComanda, char *dataLansare, char *dataLivrare, char *numeClient, float sumaPlata)
{
  Comanda *c = (Comanda *)malloc(sizeof(Comanda));
  if (c)
  {
    c->idComanda = idComanda;
    c->dataLansare = strdup(dataLansare);
    c->dataLivrare = strdup(dataLivrare);
    c->numeClient = strdup(numeClient);
    c->sumaPlata = sumaPlata;
  }
  return c;
}

typedef struct HashTable
{
  Comanda **el;
  int size;
} HashTable;

void initHashTable(HashTable **t, int s)
{
  *t = (HashTable *)malloc(sizeof(HashTable));
  if (*t)
  {
    (*t)->el = (Comanda **)calloc(s, sizeof(Comanda *));
    (*t)->size = s;
  }
}

int hash(char *n, int s)
{
  if (n)
  {
    int res = 0;
    for (int i = 0; i < strlen(n); i++)
    {
      res += n[i];
    }
    return res % s;
  }
}

void insertHashTable(HashTable *t, Comanda *c)
{
  if (!t)
    return;
  int pos = hash(c->numeClient, t->size);
  if (t->el[pos] == NULL)
  {
    t->el[pos] = c;
    return;
  }
  int index = 1;
  while (pos + index < t->size)
  {
    if (t->el[pos + index] == NULL)
    {
      t->el[pos + index] = c;
      return;
    }
    index++;
  }
  index = 1;
  while (pos - index >= 0)
  {
    if (t->el[pos - index] == NULL)
    {
      t->el[pos - index] = c;
      return;
    }
    index++;
  }
}

void parseFile(HashTable **t, char *fileName)
{
  FILE *f = fopen(fileName, "r");
  if (!f)
    return;
  char buffer[LINE_SIZE];
  bool didHTInit = false;
  while (fgets(buffer, LINE_SIZE, f))
  {
    if (!didHTInit)
    {
      char *nrInreg = strtok(buffer, "\n");
      initHashTable(t, atoi(nrInreg));
      didHTInit = true;
      continue;
    }
    char *idComanda = strtok(buffer, ","), *dataLansare = strtok(NULL, ","), *dataLivrare = strtok(NULL, ","), *numeClient = strtok(NULL, ","), *sumaPlata = strtok(NULL, "\n");
    unsigned id;
    sscanf(idComanda, "%u", &id);
    insertHashTable(*t, createComanda(id, dataLansare, dataLivrare, numeClient, atof(sumaPlata)));
  }
  fclose(f);
}

void printComanda(Comanda *c)
{
  if (!c)
    return;
  printf("Id: %u, data lansare: %s, livrare %s, nume client: %s, suma plata %.2f\n", c->idComanda, c->dataLansare, c->dataLivrare, c->numeClient, c->sumaPlata);
}

void printHT(HashTable *t)
{
  if (!t)
    return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i])
      printComanda(t->el[i]);
  }
}

void comenziDateDe(char *c, HashTable *t) {
  if (!t) return;
  int res = 0;
  // if (t->el[hash(c, t->size)] && !strcmp(t->el[hash(c, t->size)]->numeClient, c)) {
  //   res++;
  // }
  for (int i = 0; i < t->size; i++)
  {
    if(!strcmp(t->el[i]->numeClient, c)) res++;
  }
  printf("Nr de comenzi al clientului %s este de: %d\n", c, res);
}

void modificaDataDeLivrare(HashTable *t, unsigned id, char *d) {
  if (!t) return;
  for (int i = 0; i < t->size; i++)
  {
    if (id == t->el[i]->idComanda) {
      free(t->el[i]->dataLivrare);
      t->el[i]->dataLivrare = strdup(d);
    }
  }
}

void deleteComanda(Comanda** c) {
  if (!*c) return;
  free((*c)->dataLansare);
  free((*c)->dataLivrare);
  free((*c)->numeClient);
  free(*c);
  *c = NULL;
}

void deleteComenziLivrate(HashTable *t, char *d) {
  if (!t) return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i] && strcmp(d, t->el[i]->dataLivrare) == 1) deleteComanda(&(t->el[i]));
  }
}

typedef struct ListNode {
  Comanda* info;
  struct ListNode *next;
} ListNode;

Comanda *deepCloneComanda(Comanda *c) {
  return createComanda(c->idComanda, c->dataLansare, c->dataLivrare, c->numeClient, c->sumaPlata);
}

ListNode *createListNode(Comanda *c) {
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  if (n) {
    n->info = c;
    n->next = NULL;
  }
  return n;
}

void insertList(ListNode **h, ListNode *n) {
  if (!*h) {
    *h = n;
    return;
  }
  ListNode *aux = *h;
  while (aux->next)
  {
    aux = aux->next;
  }
  aux->next = n;
}

void convertHTList(HashTable *t, ListNode **h, float s) {
  if (!t) return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i] && t->el[i]->sumaPlata > s) insertList(h, createListNode(deepCloneComanda(t->el[i])));
  }
}

void printList(ListNode *h) {
  if (!h) return;
  printComanda(h->info);
  printList(h->next);
}

void main()
{
  HashTable *t = NULL;
  parseFile(&t, "data.txt");
  printHT(t);
  comenziDateDe("Liviu", t);
  modificaDataDeLivrare(t, 3, "28.03.2023");
  printHT(t);
  deleteComenziLivrate(t, "27.03.2023");
  printf("\n");
  printHT(t);
  ListNode *h = NULL;
  convertHTList(t, &h, 300.5);
  printf("\n");
  printList(h);
}