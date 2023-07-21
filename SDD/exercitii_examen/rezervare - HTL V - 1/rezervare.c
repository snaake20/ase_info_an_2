#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Rezervare
{
  unsigned idRezervare;
  char *denumire;
  unsigned char nrCamereHotel;
  unsigned char nrCamereRezervate;
  char *numeClient;
  char *perioadaRezervarii;
  float pretCamera;
} Rezervare;

typedef struct HashT
{
  Rezervare **r;
  int size;
} HashT;

Rezervare *createRezervare(unsigned idRezervare, char *denumire, unsigned char nrCamereHotel, unsigned char nrCamereRezervate, char *numeClient, char *perioadaRezervarii, float pretCamera)
{
  Rezervare *r = (Rezervare *)malloc(sizeof(Rezervare));
  if (r)
  {
    r->idRezervare = idRezervare;
    r->denumire = (char *)malloc(strlen(denumire) + 1);
    if (r->denumire)
    {
      strcpy_s(r->denumire, strlen(denumire) + 1, denumire);
    }
    r->nrCamereHotel = nrCamereHotel;
    r->nrCamereRezervate = nrCamereRezervate;
    r->numeClient = (char *)malloc(strlen(numeClient) + 1);
    if (r->numeClient)
    {
      strcpy_s(r->numeClient, strlen(numeClient) + 1, numeClient);
    }
    r->perioadaRezervarii = (char *)malloc(strlen(perioadaRezervarii) + 1);
    if (r->perioadaRezervarii)
    {
      strcpy_s(r->perioadaRezervarii, strlen(perioadaRezervarii) + 1, perioadaRezervarii);
    }
    r->pretCamera = pretCamera;
  }
  return r;
}

int hash(char *den, int s)
{
  return den[0] % s;
}

void initHashT(HashT **t, int n)
{
  if (!(*t))
  {
    (*t) = (HashT *)malloc(sizeof(HashT));
    (*t)->r = (Rezervare **)malloc(sizeof(Rezervare *) * n);
    for (int i = 0; i < n; i++)
    {
      (*t)->r[i] = NULL;
    }

    (*t)->size = n;
  }
}

void insertTable(HashT **t, Rezervare *r)
{
  if (!(*t)->r)
    return;
  int poz = hash(r->denumire, (*t)->size);
  if ((*t)->r[poz] != NULL)
  {
    int gasit = 0;
    while (poz + 1 < (*t)->size)
    {
      if ((*t)->r[poz + 1] == NULL)
      {
        (*t)->r[poz + 1] = r;
        gasit = 1;
        break;
      }
      poz++;
    }
    if (gasit == 0)
    {
      while (poz - 1 >= 0)
      {
        if ((*t)->r[poz - 1] == NULL)
        {
          (*t)->r[poz - 1] = r;
          break;
        }
        poz--;
      }
    }
  }
  else
  {
    (*t)->r[poz] = r;
  }
}

void parseFile(HashT **t)
{
  FILE *f = fopen("data.txt", "r");
  if (f)
  {
    char buffer[128];
    int gasitNrInreg = 0;
    while (fgets(buffer, 128, f))
    {
      if (gasitNrInreg == 0)
      {
        char *nrInreg = strtok(buffer, "\n");
        gasitNrInreg = 1;
        initHashT(t, atoi(nrInreg));
      }
      else
      {
        char *id = strtok(buffer, ","), *denumireHotel = strtok(NULL, ","), *nrCam = strtok(NULL, ","), *nrCamR = strtok(NULL, ","), *numeClient = strtok(NULL, ","), *perioadaRezervarii = strtok(NULL, ","), *pret = strtok(NULL, "\n");

        insertTable(t, createRezervare(atoi(id), denumireHotel, atoi(nrCam), atoi(nrCamR), numeClient, perioadaRezervarii, atof(pret)));
      }
    }
    fclose(f);
  }
}

void printRezervare(Rezervare *r)
{
  printf("id rez: %u, denumire hotel: %s, nr camere: %d, din care rezervate: %d, nume client: %s, perioada: %s, pret %.2f\n", r->idRezervare, r->denumire, r->nrCamereHotel, r->nrCamereRezervate, r->numeClient, r->perioadaRezervarii, r->pretCamera);
}

void printHashT(HashT *t)
{
  if (t)
  {
    for (int i = 0; i < t->size; i++)
    {
      if (t->r[i])
        printRezervare(t->r[i]);
    }
  }
}

void printGradDeOcupare(HashT *t, char *d, char *p)
{
  float res = 0.0f, c;
  int total = 0;
  for (int i = 0; i < t->size; i++)
  {
    if (t->r[i]){
      if (strcmp(d, t->r[i]->denumire) == 0 && strcmp(p, t->r[i]->perioadaRezervarii) == 0) {
        total += t->r[i]->nrCamereRezervate;
        c = t->r[i]->nrCamereHotel;
      }
    }
  }
  printf("Gradul de ocupare al hotelului %s in perioada %s este %.2f%%\n", d, p,total/c * 100);
}

typedef struct Vector {
  Rezervare** v;
  int n;
} Vector;

Rezervare* deepCloneRezervare(Rezervare *r)
{
  return createRezervare(r->idRezervare, r->denumire, r->nrCamereHotel, r->nrCamereRezervate, r->numeClient, r->perioadaRezervarii, r->pretCamera);
}

void convertToVector(HashT* t, Vector** v, char*c) {
  *v = (Vector*)malloc(sizeof(Vector));
  (*v)->v = NULL;
  (*v)->n = 0;
  for (int i = 0; i < t->size; i++)
  {
    if (t->r[i] && strcmp(c, t->r[i]->numeClient) == 0) {
      (*v)->v = (Rezervare**)realloc((*v)->v, ((*v)->n + 1) * sizeof(Rezervare*));
      (*v)->v[(*v)->n] = deepCloneRezervare(t->r[i]);
      (*v)->n++;
    }
  }
}

void printVector(Vector* v) {
  if (v) {
    for (int i = 0; i < v->n; i++)
    {
      printRezervare(v->v[i]);
    }
  }
}

void printIncasari(Vector*v, char* p) {
  float res = 0.0f;
  for (int i = 0; i < v->n; i++)
  {
    if (strcmp(v->v[i]->perioadaRezervarii, p) == 0) {

      char * dI = strtok(v->v[i]->perioadaRezervarii, "-"), * dS = strtok(NULL, ".");

      int dataI = atoi(dI), dataS = atoi(dS);
      res += (dataS - dataI + 1) * v->v[i]->pretCamera * v->v[i]->nrCamereRezervate;
    }
  }
  printf("Pt perioada %s incasarile sunt: %.2f\n", p,res);
}

void printCamereRezervate(HashT* t, char* n) {
  int res = 0;
  for (int i = 0; i < t->size; i++)
  {
    if (t->r[i]) {
      if (strcmp(n, t->r[i]->numeClient) == 0)
        res+=t->r[i]->nrCamereRezervate;
    }
  }
  printf("Nr de camere rezervate de %s este %d\n", n, res);
}

void deleteRezervare(Rezervare **r) {
  free((*r)->denumire);
  free((*r)->numeClient);
  free((*r)->perioadaRezervarii);
  free((*r));
  (*r) = NULL;
}

void deallocateHashT(HashT** t) {
  for (int i = 0; i < (*t)->size; i++)
  {
    deleteRezervare(&((*t)->r[i]));
  }
  free((*t)->r);
  free((*t));
  *t = NULL;
}

void deallocateVector(Vector **v) {
  for (int i = 0; i < (*v)->n; i++)
  {
    deleteRezervare(&((*v)->v[i]));
  }
  free((*v)->v);
  free((*v));
  *v = NULL;
}

void main()
{
  HashT *t = NULL;
  parseFile(&t);
  printHashT(t);
  printGradDeOcupare(t, "Transilvania", "20-22.06.2023");
  Vector* rc = NULL;
  convertToVector(t, &rc, "Alex");
  printVector(rc);
  printIncasari(rc, "20-22.06.2023");
  printCamereRezervate(t, "Alex");
  deallocateHashT(&t);
  deallocateVector(&rc);
}