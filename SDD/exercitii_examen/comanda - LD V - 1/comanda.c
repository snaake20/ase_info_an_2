#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <crtdbg.h>
#define LINE_SIZE 128

typedef struct Comanda {
  unsigned numar_comanda;
  char* data_livrare_programata;
  char* data_livrare_efectuata;
  char* nume_client;
  float suma_plata;
} Comanda;

Comanda* createComanda(unsigned numar_comanda, char* data_livrare_programata, char* data_livrare_efectuata, char* nume_client, float suma_plata) {
  Comanda* c = (Comanda*)malloc(sizeof(Comanda));
  if (c) {
    c->numar_comanda = numar_comanda;
    c->data_livrare_programata = strdup(data_livrare_programata);
    c->data_livrare_efectuata = strdup(data_livrare_efectuata);
    c->nume_client = strdup(nume_client);
    c->suma_plata = suma_plata;
  }
  return c;
}

typedef struct NodeLD {
  Comanda* info;
  struct NodeLD* prev, * next;
} NodeLD;

NodeLD* createNodeLD(Comanda* c) {
  NodeLD* n = (NodeLD*)malloc(sizeof(NodeLD));
  if (n) {
    n->info = c;
    n->prev = n->next = NULL;
  }
  return n;
}

void insertListD(NodeLD** h, NodeLD* n) {
  if (!*h) {
    *h = n;
    return;
  }
  NodeLD* temp = *h;
  while (temp->next)
  {
    temp = temp->next;
  }
  n->prev = temp;
  temp->next = n;
}

typedef struct Vector {
  unsigned* el;
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

void insertVector(Vector* v, unsigned n) {
  v->el = (unsigned*)realloc(v->el, sizeof(unsigned) * (v->length + 1));
  v->el[v->length++] = n;
}

// ----

void parseFile(NodeLD** h, char* fileName) {
  FILE* f = fopen(fileName, "r");
  if (!f) exit(-1);
  char b[LINE_SIZE];
  while (fgets(b, LINE_SIZE, f))
  {
    char* numar = strtok(b, ","), * data_livrare_programata = strtok(NULL, ","), * data_livrare_efectuata = strtok(NULL, ","), * nume_client = strtok(NULL, ","), * suma_plata = strtok(NULL, "\n");
    unsigned numar_comanda;
    sscanf(numar, "%u", &numar_comanda);
    insertListD(h, createNodeLD(createComanda(numar_comanda, data_livrare_programata, data_livrare_efectuata, nume_client, atof(suma_plata))));
  }
  fclose(f);
}

void printComanda(Comanda* c) {
  if (!c) return;
  printf("numar comanda: %u, data livrare programata: %s, data livrare efectuata: %s, nume client: %s, suma plata: %.2f.\n", c->numar_comanda, c->data_livrare_programata, c->data_livrare_efectuata, c->nume_client, c->suma_plata);
}

NodeLD* getTail(NodeLD* h) {
  if (!h) return NULL;
  if (!h->next) return h;
  return getTail(h->next);
}

void printListD(NodeLD* n) {
  if (!n->prev) {
    printf("Lista de la cap\n");
    while (n)
    {
      printComanda(n->info);
      n = n->next;
    }
  }
  else {
    printf("Lista de la coada\n");
    while (n)
    {
      printComanda(n->info);
      n = n->prev;
    }
  }
}

int diferentaDate(char* p, char* e) {
  int zi_p = atoi(strtok(p, ".")), luna_p = atoi(strtok(NULL, ".")), an_p = atoi(strtok(NULL, "\n"));
  int zi_e = atoi(strtok(e, ".")), luna_e = atoi(strtok(NULL, ".")), an_e = atoi(strtok(NULL, "\n"));
  return (an_e - an_p) * 365 + (luna_e - luna_p) * 30 + (zi_e - zi_p);
}

void getDiferenta(NodeLD* h, int* max) {
  if (!h) return;
  char* p = strdup(h->info->data_livrare_programata), * e = strdup(h->info->data_livrare_efectuata);
  int dif = diferentaDate(p, e);
  free(p);
  free(e);
  if (*max < dif) *max = dif;
  getDiferenta(h->next, max);
}

Comanda* getComandaDifMax(NodeLD* h, int max) {
  if (!h) return NULL;
  char* p = strdup(h->info->data_livrare_programata), * e = strdup(h->info->data_livrare_efectuata);
  int dif = diferentaDate(p, e);
  free(p);
  free(e);
  if (dif == max) return h->info;
  return getComandaDifMax(h->next, max);
}

float maxVal(NodeLD* h) {
  if (!h) return 0;
  float max = 0;
  while (h)
  {
    if (max < h->info->suma_plata) max = h->info->suma_plata;
    h = h->next;
  }
  return max;
}

void modificaValComMax(NodeLD* h, float disc) {
  if (!h) return;
  float max = maxVal(h);
  while (h)
  {
    if (max == h->info->suma_plata) {
      h->info->suma_plata *= (1 - disc);
    }
    h = h->next;
  }
}

typedef struct Aux {
  char* nume_client;
  unsigned nrComenzi;
} Aux;

void insertAuxV(Aux** v, int* dim, Aux a) {
  (*v) = (Aux*)realloc((*v), ((*dim) + 1) * sizeof(Aux));
  (*v)[(*dim)++] = a;
}

int isKeyIn(Aux* v, int dim, char* k) {
  if (!v) return -1;
  for (int i = 0; i < dim; i++)
  {
    if (!strcmp(v[i].nume_client, k)) return i;
  }
  return -1;
}

char* numeClientNrComMax(NodeLD* h) {
  if (!h) return NULL;
  Aux* aggr = NULL;
  int dim = 0;
  while (h)
  {
    int pos = isKeyIn(aggr, dim, h->info->nume_client);
    if (pos == -1) {
      Aux a = {.nume_client = strdup(h->info->nume_client), .nrComenzi = 1};
      insertAuxV(&aggr, &dim, a);
    }
    else {
      aggr[pos].nrComenzi++;
    }
    h = h->next;
  }
  unsigned max = 0, pos = 0;
  char* client = NULL;
  for (int i = 0; i < dim; i++)
  {
    if (max < aggr[i].nrComenzi) {
      max = aggr[i].nrComenzi;
      pos = i;
    }
  }
  client = strdup(aggr[pos].nume_client);
  for (int i = 0; i < dim; i++)
  {
    free(aggr[i].nume_client);
  }
  free(aggr);
  return client;
}

void convertLDV(NodeLD *h, Vector *v, int l) {
  if (!h) return;
  while (h)
  {
    char* t = strdup(h->info->data_livrare_programata);
    char * zi =strtok(t, "."); // ignore day
    int luna = atoi(strtok(NULL, "."));
    free(t);
    if (luna == l) {
      insertVector(v, h->info->numar_comanda);
    }
    h = h->next;
  }
}

void printVector(Vector *v) {
  if (!v) return;
  for (int i = 0; i < v->length; i++)
  {
    printf("%d ", v->el[i]);
  }
}

void deleteComanda(Comanda** c) {
  if (!*c) return;
  free((*c)->data_livrare_programata);
  free((*c)->data_livrare_efectuata);
  free((*c)->nume_client);
  free(*c);
  *c = NULL;
}

void deleteNodeLD(NodeLD** n) {
  if (!*n) return;
  deleteComanda(&((*n)->info));
  free(*n);
  *n = NULL;
}

void deallocateListD(NodeLD **h)
{
  if (!*h) return;
  deallocateListD(&((*h)->next));
  deleteNodeLD(h);
}

void deallocateVector(Vector** v) {
  if (!*v) return;
  free((*v)->el);
  free((*v));
  *v = NULL;
}

void main() {
  NodeLD* h = NULL;
  parseFile(&h, "data.txt");
  printListD(h);
  printListD(getTail(h));
  int diferentaMaxima = 0;
  getDiferenta(h, &diferentaMaxima);
  Comanda* c = getComandaDifMax(h, diferentaMaxima);
  char* p = strdup(c->data_livrare_programata), * e = strdup(c->data_livrare_efectuata);
  printf("Diferenta maxima in numar de zile este: %d\n", diferentaDate(p,e));
  free(p); free(e);
  printComanda(c);
  printf("Lista dupa discount\n");
  modificaValComMax(h, 0.2);
  printListD(h);
  printListD(getTail(h));
  char* clientComandos = numeClientNrComMax(h);
  printf("Clientul cu cel mai mare numar de comenzi este: %s\n",clientComandos);
  free(clientComandos);
  clientComandos = NULL;
  Vector* v = createVector();
  convertLDV(h, v, 3);
  printVector(v);
  deallocateListD(&h);
  deallocateVector(&v);
  _CrtDumpMemoryLeaks();
}