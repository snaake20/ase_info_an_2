#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#define LINE_SIZE 128

typedef struct Rezervare
{
  unsigned id_rezervare;
  char *denumire_hotel;
  unsigned char nr_camere_rezervate;
  char *nume_client;
  float suma_plata;
} Rezervare;

Rezervare *createRezervare(unsigned id_rezervare, char *denumire_hotel, unsigned char nr_camere_rezervate, char *nume_client, float suma_plata)
{
  Rezervare *r = (Rezervare *)malloc(sizeof(Rezervare));
  if (r)
  {
    r->id_rezervare = id_rezervare;
    r->denumire_hotel = strdup(denumire_hotel);
    r->nr_camere_rezervate = nr_camere_rezervate;
    r->nume_client = strdup(nume_client);
    r->suma_plata = suma_plata;
  }
  return r;
}

typedef struct NodeT
{
  Rezervare *info;
  struct NodeT *left, *right;
} NodeT;

NodeT *createNodeT(Rezervare *rez, NodeT *l, NodeT *r)
{
  NodeT *n = (NodeT *)malloc(sizeof(NodeT));
  if (n)
  {
    n->info = rez;
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
  if (n->info->id_rezervare < (*r)->info->id_rezervare)
  {
    insertBST(&(*r)->left, n);
  }
  else if (n->info->id_rezervare > (*r)->info->id_rezervare)
  {
    insertBST(&(*r)->right, n);
  }
}

void parseFile(NodeT **r, char *fileName)
{
  FILE *f = fopen(fileName, "r");
  if (!f)
    exit(-1);
  char b[LINE_SIZE];
  while (fgets(b, LINE_SIZE, f))
  {
    char *id = strtok(b, ","), *denumire_hotel = strtok(NULL, ","), *nr = strtok(NULL, ","), *nume_client = strtok(NULL, ","), *suma_plata = strtok(NULL, "\n");
    unsigned id_rezervare;
    unsigned char nr_camere_rezervate;
    sscanf(id, "%u", &id_rezervare);
    sscanf(nr, "%hhu", &nr_camere_rezervate);
    insertBST(r, createNodeT(createRezervare(id_rezervare, denumire_hotel, nr_camere_rezervate, nume_client, atof(suma_plata)), NULL, NULL));
  }
  fclose(f);
}

void printRezervare(Rezervare *r)
{
  if (!r)
    return;
  printf("id: %u, denumire hotel: %s, numar camere rezervate: %hhu, nume client: %s, suma de plata: %.2f\n", r->id_rezervare, r->denumire_hotel, r->nr_camere_rezervate, r->nume_client, r->suma_plata);
}

void inordine(NodeT *r)
{
  if (!r)
    return;
  inordine(r->left);
  printRezervare(r->info);
  inordine(r->right);
}

void nrCamereRezervateNoduriFrunza(NodeT *r, unsigned *n)
{
  if (!r)
    return;
  if (!r->left && !r->right)
  {
    *n += r->info->nr_camere_rezervate;
  }
  nrCamereRezervateNoduriFrunza(r->left, n);
  nrCamereRezervateNoduriFrunza(r->right, n);
}

int maxim(int a, int b)
{
  return a > b ? a : b;
}

int nrNiveluri(NodeT *r)
{
  if (!r)
    return 0;
  return 1 + maxim(nrNiveluri(r->left), nrNiveluri(r->right));
}

void deleteRezervare(Rezervare **r)
{
  if (!*r)
    return;
  free((*r)->denumire_hotel);
  free((*r)->nume_client);
  free(*r);
  *r = NULL;
}

void deleteNodeT(NodeT **r)
{
  if (!*r)
    return;
  deleteRezervare(&((*r)->info));
  free(*r);
  *r = NULL;
}

void deleteRad(NodeT **r)
{
  if (!*r)
    return;
  NodeT *aux = *r;
  if (aux->left)
  {
    *r = aux->left;
    if (aux->right)
    {
      NodeT *tmp = aux->left;
      while (tmp->right)
      {
        tmp = tmp->right;
      }
      tmp->right = aux->right;
    }
  }
  else
  {
    *r = aux->right;
  }
  deleteNodeT(&aux);
}

typedef struct Vector
{
  int *el;
  int length;
} Vector;

Vector *initVector()
{
  Vector *v = (Vector *)malloc(sizeof(Vector));
  if (v)
  {
    v->el = NULL;
    v->length = 0;
  }
  return v;
}

void insertVector(Vector *v, int n)
{
  v->el = (int *)realloc(v->el, sizeof(int) * (v->length + 1));
  v->el[v->length++] = n;
}

int doesKeyExist(NodeT *r, int n)
{
  if (!r)
    return 0;
  return (r->info->id_rezervare == n ? 1 : 0) + (r->left ? doesKeyExist(r->left, n) : 0) + (r->right ? doesKeyExist(r->right, n) : 0);
}

void getPath(NodeT *r, Vector *v, int n)
{
  if (!doesKeyExist(r, n))
    return;
  insertVector(v, r->info->id_rezervare);
  getPath(r->left, v, n);
  getPath(r->right, v, n);
}

void printVector(Vector *v)
{
  if (!v)
    return;
  for (int i = 0; i < v->length; i++)
  {
    printf("Pas: %d, id: %u\n", i + 1, v->el[i]);
  }
}

void deallocateBST(NodeT **r)
{
  if (!*r)
    return;
  deallocateBST(&((*r)->left));
  deallocateBST(&((*r)->right));
  deleteNodeT(r);
}

void deallocateVector(Vector **v)
{
  if (!*v)
    return;
  free((*v)->el);
  free((*v));
  *v = NULL;
}

void printNivel(NodeT *r, int level) {
    if (!r || level < 0) {
        return;
    }
    if (!level) {
        printRezervare(r->info);
    } else {
        printNivel(r->left, level - 1);
        printNivel(r->right, level - 1);
    }
}

void printNivele(NodeT *r) {
    int treeHeight = nrNiveluri(r);
    for (int i = 0; i < treeHeight; i++) {
        printf("Nivelul: %d\n", i + 1);
        printNivel(r, i);
        printf("\n");
    }
}


void main()
{
  NodeT *r = NULL;
  parseFile(&r, "data.txt");
  inordine(r);
  printNivele(r);
  unsigned nr = 0;
  nrCamereRezervateNoduriFrunza(r, &nr);
  printf("Nr de camere rezervate din nodurile frunza este: %u\n", nr);
  printf("Nr de niveluri al structurii arborescente este: %d\n", nrNiveluri(r));
  deleteRad(&r);
  inordine(r);
  Vector *v = initVector();
  getPath(r, v, 5);
  printNivele(r);
  printVector(v);
  deallocateBST(&r);
  deallocateVector(&v);
}