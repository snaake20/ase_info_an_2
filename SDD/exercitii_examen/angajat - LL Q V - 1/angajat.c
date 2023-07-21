#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define LINE_SIZE 128

typedef struct Angajat {
  unsigned cod_departament;
  char* nume;
  float salariu;
} Angajat;

typedef struct NodeLS {
  Angajat *info;
  struct NodeLS *next;
} NodeLS;

typedef struct NodeLP {
  NodeLS *hs;
  struct NodeLP *next;
} NodeLP;

Angajat *createAngajat(unsigned cod_departament,char* nume,float salariu) {
  Angajat *a = (Angajat *)malloc(sizeof(Angajat));
  if (a) {
    a->cod_departament = cod_departament;
    a->nume = strdup(nume);
    a->salariu = salariu;
  }
  return a;
}

NodeLS *createNodeLS(Angajat *a) {
  NodeLS *n = (NodeLS*)malloc(sizeof(NodeLS));
  if (n) {
    n->info = a;
    n->next = NULL;
  }
  return n;
}

NodeLP *createNodeLP(NodeLS *h) {
  NodeLP *n = (NodeLP *)malloc(sizeof(NodeLP));
  if (n) {
    n->hs = h;
    n->next = NULL;
  }
  return n;
}

void insertListP(NodeLP **h, NodeLS *s) {
  if (!*h) {
    *h = createNodeLP(s);
    return;
  }
  NodeLP* aux = *h;
  while (aux->next)
  {
    if (aux->hs->info->cod_departament == s->info->cod_departament) {
      NodeLS *auxs = aux->hs;
      while (auxs->next)
      {
        auxs = auxs->next;
      }
      auxs->next = s;
      return;
    }
    aux = aux->next;
  }
  aux->next = createNodeLP(s);
}

void parseFile(NodeLP **h, char *fileName) {
  FILE *f = fopen(fileName, "r");
  if (!f) return;
  char buf[LINE_SIZE];
  while (fgets(buf, LINE_SIZE, f))
  {
    char *cod_departament = strtok(buf, ","), *nume = strtok(NULL, ","), *salariu = strtok(NULL, "\n");
    unsigned cod;
    sscanf(cod_departament, "%u", &cod);
    insertListP(h, createNodeLS(createAngajat(cod, nume, atof(salariu))));
  }
  fclose(f);
}

void printAngajat(Angajat *a) {
  if (!a) return;
  printf("Id dep: %u, nume: %s, salariu: %.2f\n", a->cod_departament, a->nume, a->salariu);
}

void printList(NodeLP *h) {
  if (!h) return;
  while (h)
  {
    NodeLS* aux = h->hs;
    while (aux)
    {
      printAngajat(aux->info);
      aux = aux->next;
    }
    h = h->next;
  }
}

typedef struct Vector {
  Angajat **el;
  int length;
} Vector;

Angajat *deepCloneAngajat(Angajat *a) {
  return createAngajat(a->cod_departament, a->nume, a->salariu);
}

Vector *initVector() {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  if (v) {
    v->el = NULL;
    v->length = 0;
  }
  return v;
}

void insertVector(Vector *v, Angajat *a) {
  if (!v || !a) return;
  v->el = (Angajat **)realloc(v->el, sizeof(Angajat *) * (v->length + 1));
  v->el[v->length] = a;
  v->length++;
}

void convertLLV(NodeLP *h, Vector *v, float p) {
  if (!h || !v) return;
  while (h)
  {
    NodeLS *aux = h->hs;
    while (aux)
    {
      if (aux->info->salariu > p) insertVector(v, deepCloneAngajat(aux->info));
      aux = aux->next;
    }
    h = h->next;
  }
}

void printVector(Vector *v) {
  if (!v || !v->el || !v->length) return;
  for (int i = 0; i < v->length; i++)
  {
    printAngajat(v->el[i]);
  }
}

typedef struct NodeQ {
  Angajat *info;
  struct NodeQ *next;
} NodeQ;

NodeQ *createNodeQ(Angajat *a) {
  NodeQ *n = (NodeQ *)malloc(sizeof(NodeQ));
  if (n) {
    n->info = a;
    n->next = NULL;
  }
  return n;
}

void put(NodeQ **h, NodeQ *n) {
  if (!*h) {
    *h = n;
    return;
  }
  NodeQ *aux = *h;
  while (aux->next)
  {
    aux = aux->next;
  }
  aux->next = n;
}

void convertLLQ(NodeLP *h, NodeQ **q, int c) {
  if (!h || !q) return;
  while (h)
  {
    NodeLS *aux = h->hs;
    while (aux)
    {
      if (aux->info->cod_departament == c) put(q, createNodeQ(deepCloneAngajat(aux->info)));
      aux = aux->next;
    }
    h = h->next;
  } 
}

void printQueue(NodeQ *q) {
  if (!q) return;
  printAngajat(q->info);
  printQueue(q->next);
}

Vector *initFinalVector() {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  if (v) {
    v->el = (Angajat **)malloc(sizeof(Angajat *) * 3);
    v->length = 3;
  }
  return v;
}

void swapAngajat(Angajat **v1, Angajat **v2) {
  Angajat *temp = *v1;
  *v1 = *v2;
  *v2 = temp;
}

void sortVector(Vector *v) {
  for (int i = 0; i < v->length - 1; i++)
  {
    for (int j = 0; j < v->length - i -1; j++)
    {
      if (v->el[j]->salariu > v->el[j+1]->salariu) swapAngajat(&(v->el[j]), &(v->el[j+1]));
    }
  }
}

void deleteAngajat(Angajat **a) {
  if (!*a) return;
  free((*a)->nume);
  free((*a));
  *a = NULL;
}

void convertQV(NodeQ *q, Vector* v) {
  int idx = 0;
  while (q)
  {
    if (idx < 3) {
      v->el[idx] = deepCloneAngajat(q->info);
      idx++;
    } else {
      sortVector(v);
      if (q->info->salariu < v->el[2]->salariu) {
        deleteAngajat(&(v->el[2]));
        v->el[2] = deepCloneAngajat(q->info);
      }
    }
    q = q->next;
  }
}

void deallocateLP(NodeLP **h) {
  if (!*h) return;
  NodeLP *next = (*h)->next;
  NodeLS *aux = (*h)->hs;
  while (aux) {
    NodeLS *nexts = aux->next;
    deleteAngajat(&(aux->info));
    free(aux);
    aux = NULL;
    aux = nexts;
  }
  free(*h);
  *h = NULL;
  deallocateLP(&next);
}

void deallocateQ(NodeQ **q) {
  if (!*q) return;
  NodeQ *next = (*q)->next;
  deleteAngajat(&((*q)->info));
  free(*q);
  *q = NULL;
  deallocateQ(&next);
}

void deallocateVector(Vector **v) {
  if (!*v) return;
  for (int i = 0; i < (*v)->length; i++)
  {
    deleteAngajat(&((*v)->el[i]));
  }
  free((*v)->el);
  free(*v);
  *v = NULL;
}

void main() {
  NodeLP* h = NULL;
  parseFile(&h, "data.txt");
  printf("Lista de liste\n");
  printList(h);
  Vector *v = initVector();
  convertLLV(h, v, 2300.0f);
  printf("Vector\n");
  printVector(v);
  NodeQ *q = NULL;
  convertLLQ(h, &q, 1);
  printf("Coada\n");
  printQueue(q);
  Vector *minSal = initFinalVector();
  convertQV(q, minSal);
  printf("Vector cu 3 sal min din coada\n");
  printVector(minSal);
  deallocateLP(&h);
  deallocateVector(&v);
  deallocateQ(&q);
  deallocateVector(&minSal);
}