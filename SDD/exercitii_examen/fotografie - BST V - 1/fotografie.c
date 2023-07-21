#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define LINE_SIZE 128

typedef struct Fotografie {
  unsigned idFotografie;
  char *oras;
  char *dataRealizare;
  float rezolutie;
} Fotografie;

Fotografie *createFotografie(unsigned idFotografie,char *oras,char *dataRealizare,float rezolutie) {
  Fotografie *f = (Fotografie *)malloc(sizeof(Fotografie));
  if (f) {
    f->idFotografie = idFotografie;
    f->oras = strdup(oras);
    f->dataRealizare = strdup(dataRealizare);
    if (rezolutie < 120) rezolutie = 120;
    if (rezolutie > 600) rezolutie = 600;
    f->rezolutie = rezolutie;
  }
  return f;
}

typedef struct NodeBST {
  Fotografie *info;
  struct NodeBST *left, *right;
} NodeBST;

NodeBST *createNodeBST(Fotografie *f) {
  NodeBST *n = (NodeBST *)malloc(sizeof(NodeBST));
  if (n) {
    n->info = f;
    n->left = n->right = NULL;
  }
  return n;
}

void insertBST(NodeBST **r, NodeBST *n) {
  if (!*r) {
    *r = n;
    return;
  }
  if (n->info->idFotografie < (*r)->info->idFotografie) {
    insertBST(&((*r)->left), n);
  } else if (n->info->idFotografie > (*r)->info->idFotografie) {
    insertBST(&((*r)->right), n);
  }
}

void parseFile(NodeBST **r, char *fileName) {
  FILE *f = fopen(fileName, "r");
  if (!f) return;
  char buf[LINE_SIZE];
  while (fgets(buf, LINE_SIZE, f))
  {
    char *id = strtok(buf, ","), *oras = strtok(NULL, ","), *dataRealizare = strtok(NULL, ","), *rezolutie = strtok(NULL, "\n");
    unsigned idFotografie;
    sscanf(id, "%u", &idFotografie);
    insertBST(r, createNodeBST(createFotografie(idFotografie, oras, dataRealizare, atof(rezolutie))));
  }
  fclose(f);
}

void printFotografie(Fotografie *f) {
  if (!f) return;
  printf("Id: %u, oras: %s, data realizare: %s, rezolutia: %.0f\n", f->idFotografie, f->oras, f->dataRealizare, f->rezolutie);
}

void inordine(NodeBST *r) {
  if (!r) return;
  printFotografie(r->info);
  inordine(r->left);
  inordine(r->right);
}

int nrFotografiiOras(NodeBST *r, char *n) {
  if (!r) return 0;
  return (!strcmp(r->info->oras, n) ? 1 : 0) + (r->left ? nrFotografiiOras(r->left, n) : 0) + (r->right ? nrFotografiiOras(r->right, n) : 0);
}

void modificaData(NodeBST *r, int id, char *d) {
  if (!r) return;
  if (r->info->idFotografie == id) {
    free(r->info->dataRealizare);
    r->info->dataRealizare = strdup(d);
  }
  modificaData(r->left, id, d);
  modificaData(r->right, id, d);
}

void deleteFotografie(Fotografie **f) {
  if (!*f) return;
  free((*f)->oras);
  free((*f)->dataRealizare);
  free(*f);
  *f = NULL;
}

void deleteRad(NodeBST **r) {
  if (!r) return;
  NodeBST *aux = *r;
  if (aux->left) {
    *r = aux->left;
    NodeBST *temp = aux->left;
    while (temp->right)
    {
      temp = temp->right;
    }
    temp->right = aux->right;
  } else if (aux->right) {
    *r = aux->right;
  }
  deleteFotografie(&aux->info);
  free(aux);
  aux = NULL;
}

typedef struct Vector {
  Fotografie **el;
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

Fotografie *deepCloneFotografie(Fotografie *f) {
  if (!f) return NULL;
  return createFotografie(f->idFotografie, f->oras, f->dataRealizare, f->rezolutie);
}

void insertVector(Vector *v, Fotografie *f) {
  if (!v || !f) return;
  v->el = (Fotografie **)realloc(v->el, sizeof(Fotografie *) * (v->length + 1));
  v->el[v->length] = f;
  v->length++;
}

void convertBSTV(NodeBST *r, Vector *v, float rez) {
  if (!r) return;
  if (r->info->rezolutie > rez) {
    insertVector(v, deepCloneFotografie(r->info));
  }
  convertBSTV(r->left, v, rez);
  convertBSTV(r->right, v, rez);
}

void printVector(Vector *v) {
  if (!v || !v->el || !v->length) return;
  for (int i = 0; i < v->length; i++)
  {
    printFotografie(v->el[i]);
  }
}

void main() {
  NodeBST *r = NULL;
  parseFile(&r, "data.txt");
  inordine(r);
  char *oras = "Bucuresti";
  int nrFotografii = nrFotografiiOras(r, oras);
  printf("Nr de fotografii din orasul %s este %d\n", oras, nrFotografii);
  modificaData(r, 10, "21.03.2023");
  printf("Dupa modificarea datei\n");
  inordine(r);
  deleteRad(&r);
  printf("Dupa stergerea radacinii\n");
  inordine(r);
  Vector *v = initVector();
  convertBSTV(r, v, 300);
  printf("Vector\n");
  printVector(v);
}