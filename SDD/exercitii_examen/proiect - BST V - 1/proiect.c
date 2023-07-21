#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <crtdbg.h>
#define LINE_SIZE 128

typedef struct Proiect {
  unsigned cod_proiect;
  char *titlu_proiect;
  char *beneficiar;
  unsigned short durata_planificata;
  float buget_alocat;
} Proiect;

Proiect *createProiect(unsigned cod_proiect,char *titlu_proiect,char *beneficiar,unsigned short durata_planificata,float buget_alocat)
{
  Proiect *p = (Proiect *)malloc(sizeof(Proiect));
  if (p) {
    p->cod_proiect = cod_proiect;
    p->titlu_proiect = strdup(titlu_proiect);
    p->beneficiar = strdup(beneficiar);
    p->durata_planificata = durata_planificata;
    p->buget_alocat = buget_alocat;
  }
  return p;
}

Proiect *deepCopy(Proiect *p)
{
  if (!p) return NULL;
  return createProiect(p->cod_proiect, p->titlu_proiect, p->beneficiar, p->durata_planificata, p->buget_alocat);
}

typedef struct NodeT {
  Proiect *info;
  struct NodeT *left, *right;
} NodeT;

NodeT *createNodeT(Proiect *p, NodeT *l, NodeT *r) {
  NodeT *n = (NodeT *)malloc(sizeof(NodeT));
  if (n) {
    n->info = p;
    n->left = l;
    n->right = r;
  }
  return n;
}

typedef struct Vector {
  Proiect **el;
  int length;
} Vector;

Vector *initVector() {
  Vector *v = (Vector*)malloc(sizeof(Vector));
  if (v) {
    v->el = NULL;
    v->length = 0;
  }
  return v;
}

// ------------------------------------------------------

void insertBST(NodeT **r, NodeT *n) {
  if (!*r) {
    *r = n;
    return;
  }
  if (n->info->cod_proiect < (*r)->info->cod_proiect) {
    insertBST(&((*r)->left), n);
  } else if (n->info->cod_proiect > (*r)->info->cod_proiect) {
    insertBST(&((*r)->right), n);
  }
}

void parseFile(NodeT **r, char *fileName) {
  FILE *f = fopen(fileName, "r");
  if (!f) exit(-1);
  char b[LINE_SIZE];
  while (fgets(b, LINE_SIZE, f))
  {
    char *cod = strtok(b, ","), *titlu_proiect = strtok(NULL, ","), *beneficiar = strtok(NULL, ","), *durata = strtok(NULL, ","), *buget_alocat = strtok(NULL, "\n");
    unsigned cod_proiect;
    sscanf(cod, "%u", &cod_proiect);
    unsigned short durata_planificata;
    sscanf(durata, "%hu", &durata_planificata);
    insertBST(r, createNodeT(createProiect(cod_proiect, titlu_proiect, beneficiar, durata_planificata, atof(buget_alocat)),NULL,NULL));
  }
  fclose(f);
}

void printProiect(Proiect *p) {
  if (!p) return;
  printf("cod proiect: %u, titlu: %s, beneficiar: %s, durata planificata: %hu, buget: %.2f\n", p->cod_proiect, p->titlu_proiect, p->beneficiar, p->durata_planificata, p->buget_alocat);
}

void inordine(NodeT *r) {
  if (!r) return;
  inordine(r->left);
  printProiect(r->info);
  inordine(r->right);
}

unsigned nrProiecteBeneficiar(char *b, NodeT *r) {
  if (!r) return 0;
  return (!strcmp(b, r->info->beneficiar) ? 1 : 0) + (r->left ? nrProiecteBeneficiar(b, r->left) : 0) + (r->right ? nrProiecteBeneficiar(b, r->right) : 0);
}

void modificaBugetProiect(unsigned short id, float procent, NodeT *r) {
  if (!r) return;
  if (id == r->info->cod_proiect) {
    r->info->buget_alocat *= (1 + procent);
    return;
  }
  modificaBugetProiect(id, procent, r->left);
  modificaBugetProiect(id, procent, r->right);
}

unsigned getNrNoduriFrunza(NodeT *r) {
  if (!r) return 0;
  return (!r->left && !r->right ? 1 : 0) + (r->left ? getNrNoduriFrunza(r->left) : 0) + (r->right ? getNrNoduriFrunza(r->right) : 0);
}

void deleteProiect(Proiect **p) {
  if(!*p) return;
  free((*p)->titlu_proiect);
  free((*p)->beneficiar);
  free(*p);
  *p = NULL;
}

void deleteNodeT(NodeT **r) {
  if (!*r) return;
  deleteProiect(&((*r)->info));
  free(*r);
  *r = NULL;
}

void deallocateBST(NodeT **r) {
  if (!*r) return;
  deallocateBST(&((*r)->left));
  deallocateBST(&((*r)->right));
  deleteNodeT(r);
}

void insertVector(Vector *v, Proiect *p) {
  v->el = (Proiect **)realloc(v->el, sizeof(Proiect *) * (v->length + 1));
  v->el[v->length++] = p;
}

void proiecteCuDurataPeste(unsigned short prag, Vector *v, NodeT *r) {
  if (!r) return;
  if (r->info->durata_planificata > prag) {
    insertVector(v, deepCopy(r->info));
  }
  proiecteCuDurataPeste(prag, v ,r->left);
  proiecteCuDurataPeste(prag, v, r->right);
}

void printVector(Vector *v) {
  if(!v) return;
  for (int i = 0; i < v->length; i++)
  {
    printProiect(v->el[i]);
  }
}

void deallocateVector(Vector **v) {
  if (!*v) return;
  for (int i = 0; i < (*v)->length; i++)
  {
    deleteProiect(&((*v)->el[i]));
  }
  free((*v)->el);
  free((*v));
  *v = NULL;
}

void main() {
  NodeT *r = NULL;
  parseFile(&r, "data.txt");
  inordine(r);
  char *beneficiar = "alex";
  unsigned nrProiecte = nrProiecteBeneficiar(beneficiar, r);
  printf("nr de proiecte al beneficiarului %s este: %u\n", beneficiar, nrProiecte);
  unsigned short id = 3;
  float procent = 0.2;
  modificaBugetProiect(id, procent, r);
  printf("dupa modificarea cu %.2f a bugetului proiectului cu codul %hu\n", procent * 100, id);
  inordine(r);
  unsigned nrNoduriFrunza = getNrNoduriFrunza(r);
  printf("nr de noduri frunza este de: %u\n", nrNoduriFrunza);
  Vector *v = initVector();
  unsigned short prag = 4;
  printf("vectorul de proiecte cu durata planificata peste %hu\n", prag);
  proiecteCuDurataPeste(prag, v, r);
  printVector(v);
  deallocateVector(&v);
  deallocateBST(&r);
  _CrtDumpMemoryLeaks();
}