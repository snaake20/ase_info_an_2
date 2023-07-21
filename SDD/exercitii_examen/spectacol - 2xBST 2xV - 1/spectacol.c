#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <crtdbg.h>
#define LINE_SIZE 128

typedef struct Spectacol
{
  int id_spectacol;
  float pret_bilet;
  char* nume_client;
  char* data_sustinere;
} Spectacol;

Spectacol* createSpectacol(int id_spectacol, float pret_bilet, char* nume_client, char* data_sustinere)
{
  Spectacol* s = (Spectacol*)malloc(sizeof(Spectacol));
  if (s)
  {
    s->id_spectacol = id_spectacol;
    s->pret_bilet = pret_bilet;
    s->nume_client = strdup(nume_client);
    s->data_sustinere = strdup(data_sustinere);
  }
  return s;
}

typedef struct NodeT
{
  Spectacol* info;
  struct NodeT* left, * right;
} NodeT;

NodeT* createNodeT(Spectacol* s, NodeT* l, NodeT* r)
{
  NodeT* n = (NodeT*)malloc(sizeof(NodeT));
  if (n)
  {
    n->info = s;
    n->left = l;
    n->right = r;
  }
  return n;
}

void insertNodeBST(NodeT** r, NodeT* n)
{
  if (!*r)
  {
    *r = n;
    return;
  }
  if (n->info->id_spectacol < (*r)->info->id_spectacol)
  {
    insertNodeBST(&((*r)->left), n);
  }
  else if (n->info->id_spectacol > (*r)->info->id_spectacol)
  {
    insertNodeBST(&((*r)->right), n);
  }
}

void parseFile(NodeT** r, char* fileName)
{
  FILE* f = fopen(fileName, "r");
  if (!f)
    exit(-1);
  char b[LINE_SIZE];
  while (fgets(b, LINE_SIZE, f))
  {
    char* id_spectacol = strtok(b, ","), * pret_bilet = strtok(NULL, ","), * nume_client = strtok(NULL, ","), * data_sustinere = strtok(NULL, "\n");
    insertNodeBST(r, createNodeT(createSpectacol(atoi(id_spectacol), atof(pret_bilet), nume_client, data_sustinere), NULL, NULL));
  }
  fclose(f);
}

void printSpectacol(Spectacol* s)
{
  if (!s)
    return;
  printf("id: %d, pret: %.2f, nume: %s, data: %s\n", s->id_spectacol, s->pret_bilet, s->nume_client, s->data_sustinere);
}

void inordine(NodeT* r)
{
  if (!r)
    return;
  inordine(r->left);
  printSpectacol(r->info);
  inordine(r->right);
}

typedef struct Vector
{
  Spectacol** el;
  int length;
} Vector;

Vector* initVector()
{
  Vector* v = (Vector*)malloc(sizeof(Vector));
  if (v)
  {
    v->el = NULL;
    v->length = 0;
  }
  return v;
}

void insertVector(Vector* v, Spectacol* s)
{
  v->el = (Spectacol**)realloc(v->el, sizeof(Spectacol*) * (v->length + 1));
  v->el[v->length++] = s;
}

Spectacol* deepClone(Spectacol* s)
{
  if (!s)
    return NULL;
  return createSpectacol(s->id_spectacol, s->pret_bilet, s->nume_client, s->data_sustinere);
}

void spectacoleDinData(char* d, NodeT* r, Vector* v)
{
  if (!r)
    return;
  if (!strcmp(r->info->data_sustinere, d))
  {
    insertVector(v, deepClone(r->info));
  }
  spectacoleDinData(d, r->left, v);
  spectacoleDinData(d, r->right, v);
}

void printVector(Vector* v)
{
  if (!v)
    return;
  for (int i = 0; i < v->length; i++)
  {
    printSpectacol(v->el[i]);
  }
}

void deleteSpectacol(Spectacol** s)
{
  if (!*s)
    return;
  free((*s)->nume_client);
  free((*s)->data_sustinere);
  free((*s));
  *s = NULL;
}

void deallocateVector(Vector** v)
{
  if (!*v)
    return;
  for (int i = 0; i < (*v)->length; i++)
  {
    deleteSpectacol(&((*v)->el[i]));
  }
  free((*v)->el);
  free(*v);
  *v = NULL;
}

typedef struct AggrClient
{
  char* nume_client;
  float cost_total;
} AggrClient;

void insertAuxVector(AggrClient** v, int* n, AggrClient a)
{
  (*v) = (AggrClient*)realloc((*v), sizeof(AggrClient) * ((*n) + 1));
  (*v)[(*n)++] = a;
}

int isKeyIn(AggrClient* v, int n, char* c)
{
  if (!v || !c)
    return -1;
  for (int i = 0; i < n; i++)
  {
    if (!strcmp(c, v[i].nume_client))
      return i;
  }
  return -1;
}

void aggregateClients(NodeT* r, AggrClient** v, int* n)
{
  if (!r)
    return;
  int pos = isKeyIn(*v, *n, r->info->nume_client);
  if (pos == -1)
  {
    AggrClient a = { .nume_client = strdup(r->info->nume_client), .cost_total = r->info->pret_bilet };
    insertAuxVector(v, n, a);
  }
  else
  {
    (*v)[pos].cost_total += r->info->pret_bilet;
  }
  aggregateClients(r->left, v, n);
  aggregateClients(r->right, v, n);
}

void printAuxVector(AggrClient* v, int n)
{
  if (!v)
    return;
  for (int i = 0; i < n; i++)
  {
    printf("nume client: %s, cost total: %.2f\n", v[i].nume_client, v[i].cost_total);
  }
}

void deallocateAuxVector(AggrClient** v, int* n)
{
  if (!*v)
    return;
  for (int i = 0; i < *n; i++)
  {
    free((*v)[i].nume_client);
  }
  free((*v));
  *v = NULL;
  *n = 0;
}

void deleteNodeT(NodeT** r)
{
  if (!*r)
    return;
  deleteSpectacol(&((*r)->info));
  free((*r));
  *r = NULL;
}

void deallocateBST(NodeT** r)
{
  if (!*r)
    return;
  deallocateBST(&((*r)->left));
  deallocateBST(&((*r)->right));
  deleteNodeT(r);
}

void insertNodeBSTAux(NodeT** r, NodeT* n)
{
  if (!*r)
  {
    *r = n;
    return;
  }
  if (n->info->pret_bilet < (*r)->info->pret_bilet)
  {
    insertNodeBSTAux(&((*r)->left), n);
  }
  else if (n->info->pret_bilet > (*r)->info->pret_bilet)
  {
    insertNodeBSTAux(&((*r)->right), n);
  } else  {
    deleteNodeT(&n);
  }
}

void splitIn2Trees(NodeT* r, NodeT** s, NodeT** t, float p)
{
  if (!r)
    return;
  if (r->info->pret_bilet < p)
  {
    insertNodeBSTAux(s, createNodeT(deepClone(r->info), NULL, NULL));
  }
  else
  {
    insertNodeBSTAux(t, createNodeT(deepClone(r->info), NULL, NULL));
  }
  splitIn2Trees(r->left, s, t, p);
  splitIn2Trees(r->right, s, t, p);
}

void main()
{
  NodeT* r = NULL;
  parseFile(&r, "data.txt");
  inordine(r);
  Vector* v = initVector();
  printf("Spectacolele din data\n");
  spectacoleDinData("20.03.2023", r, v);
  printVector(v);
  deallocateVector(&v);
  AggrClient* a = NULL;
  int n = 0;
  aggregateClients(r, &a, &n);
  printf("Clients aggregated\n");
  printAuxVector(a, n);
  deallocateAuxVector(&a, &n);
  NodeT* s = NULL, * t = NULL;
  splitIn2Trees(r, &s, &t, 23);
  deallocateBST(&r);
  printf("Arbore cu pret sub\n");
  inordine(s);
  printf("Arbore cu pret peste\n");
  inordine(t);
  deallocateBST(&s);
  deallocateBST(&t);
  _CrtDumpMemoryLeaks();
}