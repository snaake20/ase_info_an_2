#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct CursaFeroviara
{
  unsigned nrCursa;
  char *dataCursa;
  unsigned char nrVagoane;
  unsigned short nrBileteCumparate[2];
  float pretBilet[2];
} CursaFeroviara;

typedef struct NodT
{
  CursaFeroviara *info;
  struct NodT *left, *right;
} NodT;

CursaFeroviara *createCursa(unsigned nrCursa, char *dataCursa, unsigned char nrVagoane, unsigned short *nrBileteCumparate, float *pretBilet)
{
  CursaFeroviara *c = (CursaFeroviara *)malloc(sizeof(CursaFeroviara));
  if (c)
  {
    c->nrCursa = nrCursa;
    c->dataCursa = strdup(dataCursa);
    c->nrVagoane = nrVagoane;
    c->nrBileteCumparate[0] = nrBileteCumparate[0];
    c->nrBileteCumparate[1] = nrBileteCumparate[1];
    c->pretBilet[0] = pretBilet[0];
    c->pretBilet[1] = pretBilet[1];
  }
  return c;
}

void insertT(NodT **r, NodT *n)
{
  if (!*r)
  {
    *r = n;
    return;
  }
  if (n->info->nrCursa < (*r)->info->nrCursa)
  {
    insertT(&((*r)->left), n);
  }
  else if (n->info->nrCursa > (*r)->info->nrCursa)
  {
    insertT(&((*r)->right), n);
  }
}

NodT *createNode(CursaFeroviara *c, NodT *l, NodT *r)
{
  NodT *n = (NodT *)malloc(sizeof(NodT));
  if (n)
  {
    n->info = c;
    n->left = l;
    n->right = r;
  }
  return n;
}

void parseFile(NodT **r)
{
  FILE *f = fopen("data.txt", "r");
  if (!f)
    return;
  char buffer[128];
  while (fgets(buffer, 128, f))
  {
    char *nrCursa = strtok(buffer, ","), *dataCursa = strtok(NULL, ","), *nrVagoane = strtok(NULL, ","), *nrBileteCumparateS = strtok(NULL, ","), *pretBileteS = strtok(NULL, "\n");
    unsigned short nrBileteCumparate[2];
    nrBileteCumparate[0] = atoi(strtok(nrBileteCumparateS, ";"));
    nrBileteCumparate[1] = atoi(strtok(NULL, "\n"));
    float pretBilete[2];
    pretBilete[0] = atof(strtok(pretBileteS, ";"));
    pretBilete[1] = atof(strtok(NULL, "\n"));
    insertT(r, createNode(createCursa(atoi(nrCursa), dataCursa, atoi(nrVagoane), nrBileteCumparate, pretBilete), NULL, NULL));
  }
  fclose(f);
}

float incasariCursa(CursaFeroviara *c)
{
  return (c->nrBileteCumparate[0] * c->pretBilet[0]) + (c->nrBileteCumparate[1] * c->pretBilet[1]);
}

void printCursa(CursaFeroviara *c)
{
  if (!c)
  {
    printf("Cursa inexistenta\n");
    return;
  }
  printf("Nr. cursa: %u, data cursa: %s, nr. vagoane: %d, nr. bilete ach cls I: %hu, nr. bilete ach cls II: %hu, pret clasa I: %.2f, pret clasa II: %.2f, incasare: %.2f\n", c->nrCursa, c->dataCursa, c->nrVagoane, c->nrBileteCumparate[0], c->nrBileteCumparate[1], c->pretBilet[0], c->pretBilet[1], incasariCursa(c));
}

void printPreordine(NodT *r)
{
  if (!r)
    return;
  printCursa(r->info);
  printPreordine(r->left);
  printPreordine(r->right);
}

unsigned short nrBileteCls2(NodT *r)
{
  return (r ? r->info->nrBileteCumparate[1] : 0) + (r->left ? nrBileteCls2(r->left) : 0) + (r->right ? nrBileteCls2(r->right) : 0);
}

void modificaPretCls1(NodT *r, char *d, float p)
{
  if (!r)
    return;
  if (!strcmp(r->info->dataCursa, d))
  {
    r->info->pretBilet[0] *= (p + 1);
  }
  modificaPretCls1(r->left, d, p);
  modificaPretCls1(r->right, d, p);
}

typedef struct AuxV
{
  float *el;
  int n;
} AuxV;

void insertAuxV(AuxV **v, float i)
{
  (*v)->el = (float *)realloc(((*v)->el), sizeof(float) * ((*v)->n + 1));
  (*v)->el[(*v)->n] = i;
  (*v)->n++;
}

void vectorIncasari(AuxV **v, NodT *r)
{
  if (!r)
    return;
  insertAuxV(v, incasariCursa(r->info));
  vectorIncasari(v, r->left);
  vectorIncasari(v, r->right);
}

float maxIncasari(AuxV *v)
{
  if (!v)
    return 0;
  float max = 0;

  for (int i = 0; i < v->n; i++)
  {
    if (v->el[i] > max)
      max = v->el[i];
  }

  return max;
}

CursaFeroviara *cursaIncasariMaxime(NodT *r, float max)
{
  if (r == NULL) {
    return NULL;
  }

  if (incasariCursa(r->info) == max) {
    return r->info;
  }

  CursaFeroviara *result = cursaIncasariMaxime(r->left, max);
  if (result != NULL) {
    return result;
  }

  return cursaIncasariMaxime(r->right, max);
}

typedef struct Vector
{
  char **el;
  int n;
} Vector;

void insertV(Vector **v, char *n)
{
  (*v)->el = (char **)realloc(((*v)->el), sizeof(char *) * ((*v)->n + 1));
  (*v)->el[(*v)->n] = strdup(n);
  (*v)->n++;
}

void convertToV(NodT *r, Vector **v)
{
  if (!r)
    return;
  if (!r->left && !r->right)
  {
    char buf[128];
    itoa(r->info->nrCursa, buf, 10);
    insertV(v, strcat(strcat(buf, " "), r->info->dataCursa));
  }
  convertToV(r->left, v);
  convertToV(r->right, v);
}

void printV(Vector *v)
{
  if (!v || !v->el || !v->n)
    return;
  for (int i = 0; i < v->n; i++)
  {
    printf("Cursa: %s\n", v->el[i]);
  }
}

void main()
{
  NodT *r = NULL;
  parseFile(&r);
  printPreordine(r);
  printf("Nr bilete cls 2: %hu\n", nrBileteCls2(r));
  modificaPretCls1(r, "20.06.2023", 0.5f);
  printPreordine(r);
  AuxV *aux = (AuxV *)malloc(sizeof(AuxV));
  aux->el = NULL;
  aux->n = 0;
  vectorIncasari(&aux, r);
  float max = maxIncasari(aux);
  CursaFeroviara *c = cursaIncasariMaxime(r, max);
  printCursa(c);
  Vector *v = (Vector *)malloc(sizeof(Vector));
  v->el = NULL;
  v->n = 0;
  convertToV(r, &v);
  printV(v);
}