#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define LINE_SIZE 128
#define HT_SIZE 31

typedef struct Data Data;

typedef struct Programare Programare;

typedef struct NodeLD NodeLD;

typedef struct HashT HashT;

struct Data
{
  unsigned zi, luna, an;
};

struct Programare
{
  char *cod;
  Data data_calendaristica;
  char *nume_solicitant;
};

Programare *createProgramare(char* cod, Data data, char *nume_solicitant) {
  Programare *p = (Programare *)malloc(sizeof(Programare));
  if (p) {
    p->cod = strdup(cod);
    p->data_calendaristica = data;
    p->nume_solicitant = strdup(nume_solicitant);
  }
  return p;
}

Programare *deepCloneProgramare(Programare *p) {
  if (!p) return NULL;
  return createProgramare(p->cod, p->data_calendaristica, p->nume_solicitant);
}

struct NodeLD {
  Programare *info;
  NodeLD *prev, *next;
};

NodeLD *createNodeLD(Programare *p) {
  NodeLD *n = (NodeLD *)malloc(sizeof(NodeLD));
  if (n) {
    n->info = p;
    n->prev = n->next = NULL;
  }
  return n;
}

typedef struct NodeLS {
  Programare *info;
  struct NodeLS *next;
} NodeLS;

NodeLS *createNodeLS(Programare *p) {
  NodeLS *n = (NodeLS *)malloc(sizeof(NodeLS));
  if (n) {
    n->info = p;
    n->next = NULL;
  }
  return n;
}

struct HashT {
  NodeLS **el;
  unsigned size;
};

HashT *initHashT() {
  HashT *h = (HashT *)malloc(sizeof(HashT));
  if (h) {
    h->el = (NodeLS **)calloc(HT_SIZE,sizeof(NodeLS *));
    h->size = HT_SIZE;
  }
  return h;
}

int hash(unsigned luna, unsigned size) {
  return luna % size;
}

// -------------------------------------------------------

void insertListD(NodeLD **h, NodeLD *n) {
  if (!*h) {
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

void parseFile(NodeLD **h, char *fileName) {
  FILE *f = fopen(fileName, "r");
  if (!f) exit(-1);
  char buf[LINE_SIZE];
  while (fgets(buf, LINE_SIZE, f))
  {
    char *cod = strtok(buf, ","), *data = strtok(NULL, ","), *nume_solicitant = strtok(NULL, "\n");
    char *zi = strtok(data, "."), *luna = strtok(NULL, "."), *an = strtok(NULL, "\n");
    Data d;
    sscanf(zi, "%u", &d.zi);
    sscanf(luna, "%u", &d.luna);
    sscanf(an, "%u", &d.an);
    insertListD(h, createNodeLD(createProgramare(cod, d, nume_solicitant)));
  }
  fclose(f);
}

NodeLD *getTail(NodeLD *h) {
  if (!h) return NULL;
  while (h->next)
  {
    h = h->next;
  }
  return h;
}

void printProgramare(Programare *p) {
  if (!p) return;
  printf("Cod: %s, data: %u/%u/%u, nume solicitant: %s\n", p->cod, p->data_calendaristica.zi, p->data_calendaristica.luna, p->data_calendaristica.an, p->nume_solicitant);
}

void printList(NodeLD *n) {
  if (!n) return;
  if (!n->prev) {
    printf("Lista de la cap\n");
    while (n)
    {
      printProgramare(n->info);
      n = n->next;
    }
    
  } else {
    printf("Lista de la coada\n");
    while (n)
    {
      printProgramare(n->info);
      n = n->prev;
    }
  }
}

void insertVector(Programare ***v, unsigned *n, Programare *p) {
  *v = (Programare **)realloc(*v, sizeof(Programare*) * ((*n) + 1));
  (*v)[*n] = p;
  (*n)++;
}

void convertLDV(NodeLD *h, Programare ***v, unsigned *n, unsigned luna) {
  if (!h) return;
  while (h)
  {
    if (h->info->data_calendaristica.luna == luna)
      insertVector(v, n, deepCloneProgramare(h->info));
    h = h->next;
  }
}

void printVector(Programare **v, unsigned n) {
  if (!v) return;
  for (unsigned i = 0; i < n; i++)
  {
    printProgramare(v[i]);
  }
}

void insertHashT(HashT *t, NodeLS *n) {
  if (!t) return;
  unsigned pos = hash(n->info->data_calendaristica.luna, t->size);
  if (!t->el[pos]) {
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

void convertLDHT(NodeLD *h, HashT *t) {
  if (!h || !t) return;
  while (h)
  {
    insertHashT(t, createNodeLS(deepCloneProgramare(h->info)));
    h = h->next;
  }
}

void printListS(NodeLS *h)
{
  if (!h) return;
  printProgramare(h->info);
  printListS(h->next);
}

void printHashT(HashT *t)
{
  if (!t) return;
  for (unsigned i = 0; i < t->size; i++)
  {
    if (t->el[i]) {
      printf("Pozitia: %u\n", i);
      printListS(t->el[i]);
    }
  }
}

void getNrMaxProgramari(HashT *t, unsigned *l, unsigned *n) {
  if (!t) return;
  for (int i = 0; i < t->size; i++)
  {
    if (t->el[i]) {
      unsigned nr = 0;
      NodeLS *aux = t->el[i];
      while (aux)
      {
        nr++;
        aux = aux->next;
      }
      if (nr > *n) {
        *n = nr;
        *l = t->el[i]->info->data_calendaristica.luna;
      }
    }
  }
}

void deleteProgramare(Programare **p) {
  if (!*p) return;
  free((*p)->cod);
  free((*p)->nume_solicitant);
  free((*p));
  *p = NULL;
}

void deleteNodeLD(NodeLD **h) {
  if (!*h) return;
  deleteProgramare(&((*h)->info));
  free(*h);
  *h = NULL;
}

void deallocateListD(NodeLD **h) {
  if (!*h) return;
  deallocateListD(&((*h)->next));
  deleteNodeLD(h);
}

void deallocateVector(Programare ***p, unsigned *length) {
  if (!*p) return;
  for (unsigned i = 0; i < *length; i++)
  {
    deleteProgramare(&((*p)[i]));
  }
  free(*p);
  *p = NULL;
  *length = 0;
}

void deleteNodeLS(NodeLS **h) {
  if (!*h) return;
  deleteProgramare(&((*h)->info));
  free(*h);
  *h = NULL;
}

void deallocateListS(NodeLS **h) {
  if (!*h) return;
  deallocateListS(&((*h)->next));
  deleteNodeLS(h);
}

void deallocateHashT(HashT **t) {
  for (unsigned i = 0; i < (*t)->size; i++)
  {
    if ((*t)->el[i]) {
      deallocateListS(&((*t)->el[i]));
    }
  }
  free((*t)->el);
  free((*t));
  *t = NULL;
}

void main() {
  NodeLD *h = NULL;
  parseFile(&h, "data.txt");
  printList(h);
  printList(getTail(h));
  Programare **p = NULL;
  unsigned length = 0;
  convertLDV(h, &p, &length, 8);
  printf("Print vector\n");
  printVector(p, length);
  HashT *t = initHashT();
  convertLDHT(h,t);
  printf("Print Hash Table\n");
  printHashT(t);
  unsigned luna, nrProgramari = 0;
  getNrMaxProgramari(t, &luna, &nrProgramari);
  printf("Luna %u cu nr de programari %u este max din anul curent", luna, nrProgramari);
  deallocateListD(&h);
  deallocateVector(&p, &length);
  deallocateHashT(&t);
}