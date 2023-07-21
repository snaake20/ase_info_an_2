#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Consultatie
{
  char *dataConsultatie;
  char *numeMedic;
  char *specialitate;
  char *diagnostic;
  int pretConsultatie;
} Consultatie;

typedef struct NodS
{
  Consultatie *info;
  struct NodS *next;
} NodS;

typedef struct NodP
{
  NodS *head;
  struct NodP *next;
} NodP;

void printConsultatie(Consultatie *c)
{
  printf("data consultatie: %s, nume medic: %s, specialitate: %s, diagnostic: %s, pret: %d\n", c->dataConsultatie, c->numeMedic, c->specialitate, c->diagnostic, c->pretConsultatie);
}

Consultatie *createConsultatie(char *dataConsultatie,
                               char *numeMedic,
                               char *specialitate,
                               char *diagnostic,
                               int pretConsultatie)
{
  Consultatie *c = (Consultatie *)malloc(sizeof(Consultatie));
  if (c)
  {
    c->dataConsultatie = (char *)malloc(strlen(dataConsultatie) + 1);
    if (c->dataConsultatie)
      strcpy_s(c->dataConsultatie, strlen(dataConsultatie) + 1, dataConsultatie);
    c->numeMedic = (char *)malloc(strlen(numeMedic) + 1);
    if (c->numeMedic)
      strcpy_s(c->numeMedic, strlen(numeMedic) + 1, numeMedic);
    c->specialitate = (char *)malloc(strlen(specialitate) + 1);
    if (c->specialitate)
      strcpy_s(c->specialitate, strlen(specialitate) + 1, specialitate);
    c->diagnostic = (char *)malloc(strlen(diagnostic) + 1);
    if (c->diagnostic)
      strcpy_s(c->diagnostic, strlen(diagnostic) + 1, diagnostic);
    c->pretConsultatie = pretConsultatie;
  }
  return c;
}

NodS *createNodS(Consultatie *c)
{
  NodS *n = (NodS *)malloc(sizeof(NodS));
  if (n)
  {
    n->info = c;
    n->next = NULL;
  }
  return n;
}

NodP *createNodP(NodS *s)
{
  NodP *n = (NodP *)malloc(sizeof(NodP));
  if (n)
  {
    n->head = s;
    n->next = NULL;
  }
  return n;
}

void insertListS(NodS **h, NodS *n)
{
  if (!*h)
  {
    *h = n;
  }
  else
  {
    NodS *aux = *h;
    while (aux->next)
    {
      aux = aux->next;
    }
    aux->next = n;
  }
}

void insertListP(NodP **h, NodS *n)
{
  if (!*h)
  {
    *h = createNodP(n);
  }
  else
  {
    int found = 0;
    NodP *aux = *h;
    while (aux)
    {
      if (strcmp(aux->head->info->specialitate, n->info->specialitate) == 0)
      {
        found = 1;
        break;
      }
      if (aux->next == NULL)
        break;
      aux = aux->next;
    }
    if (found == 1)
    {
      insertListS(&(aux->head), n);
    }
    else
    {
      aux->next = createNodP(n);
    }
  }
}

void valoareConsultatiiSpecialitate(NodP *h, char *s)
{
  int found = 0;
  NodP *aux = h;
  while (aux)
  {
    if (strcmp(aux->head->info->specialitate, s) == 0)
    {
      found = 1;
      break;
    }
    if (aux->next == NULL)
      break;
    aux = aux->next;
  }
  if (found != 1) {
    printf("Specialitatea cautata nu exista\n");
  } else {
    NodS* h = aux->head;
    int res = 0;
    while (h) {
      res += h->info->pretConsultatie;
      h = h->next;
    }
    printf("Val totala pt %s este %d\n", s, res);
  }
}

void parseFile(NodP **h)
{
  FILE *f = fopen("data.txt", "r");
  if (!f)
    return;

  char buffer[128];

  while (fgets(buffer, 128, f))
  {

    char *dataConsultatie = strtok(buffer, ","), *numeMedic = strtok(NULL, ","), *specialitate = strtok(NULL, ","), *diagnostic = strtok(NULL, ",");
    int pretConsultatie = atoi(strtok(NULL, "\n"));

    insertListP(h, createNodS(createConsultatie(dataConsultatie, numeMedic, specialitate, diagnostic, pretConsultatie)));
  }
  fclose(f);
}

void printListS(NodS *h)
{
  if (!h)
    return printf("Sublista goala\n");
  while (h)
  {
    printConsultatie(h->info);
    h = h->next;
  }
}

void printListP(NodP *h)
{
  if (!h)
    return printf("Lista de liste goala\n");
  while (h)
  {
    printListS(h->head);
    h = h->next;
  }
}

void modificaPretData(NodP* h, char* data, int p) {
  if (!h) return;
  while (h) {
    NodS *hs = h->head;
    while (hs)
    {
      if (strcmp(data, hs->info->dataConsultatie) == 0) {
        hs->info->pretConsultatie = p;
      }
      hs= hs->next;
    }
    
    h = h->next;
  }
}

Consultatie* deepCloneConsultatie(Consultatie* c) {
  return createConsultatie(c->dataConsultatie, c->numeMedic, c->specialitate, c->diagnostic, c->pretConsultatie);
}

typedef struct Vector {
  Consultatie** v;
  int n;
} Vector;

void insertInVector(Vector **v, Consultatie *c) {
  (*v)->v = (Consultatie**)realloc((*v)->v, ((*v)->n + 1) * sizeof(Consultatie*));
  (*v)->v[(*v)->n] = c;
  (*v)->n += 1;
}

void convertToVector(NodP*h, Vector**v, int p) {
  *v = (Vector*)malloc(sizeof(Vector));
  (*v)->v = NULL;
  (*v)->n = 0;

  if (*v) {
    while (h) {
      NodS* hs = h->head;
      while (hs) {
        if (hs->info->pretConsultatie > p) {
          insertInVector(v, deepCloneConsultatie(hs->info));
        }
        hs = hs->next;
      }
      h = h->next;
    }
  }
}

void deleteConsultatie(Consultatie** c) {
  free((*c)->dataConsultatie);
  free((*c)->numeMedic);
  free((*c)->specialitate);
  free((*c)->diagnostic);
  free(*c);
  *c = NULL;
}

void deleteConsultatii(NodP **h, char* d) {
  NodP* aux = *h;
  while (aux)
  {
    NodS* hs = aux->head;
    while (hs) {
      NodS *next = hs->next;
      if (strcmp(d, hs->info->diagnostic) == 0) {
        NodS* curr = hs, * prev = hs;
        if (curr == aux->head) {
          aux->head = curr->next;
        } else {
          while (prev->next != curr)
          {
            prev = prev->next;
          }
          prev->next = curr->next;
        }
        deleteConsultatie(&curr->info);
        free(curr);
        curr = NULL;
      }
      hs = next;
    }
    aux = aux->next;
  }

  aux = *h;

  while (aux)
  {
    NodP *next = aux->next;
    if (!aux->head) {
      NodP* curr = aux, * prev = aux;
        if (curr == *h) {
          *h = curr->next;
        } else {
          while (prev->next != curr)
          {
            prev = prev->next;
          }
          prev->next = curr->next;
        }
        free(curr);
        curr = NULL;
    }
    aux = next;
  }
  
  
}

void main()
{
  NodP *head = NULL;
  parseFile(&head);
  printListP(head);
  valoareConsultatiiSpecialitate(head, "Ortopedie");
  modificaPretData(head, "22.05.2023", 69);
  printListP(head);
  Vector *c = NULL;
  convertToVector(head, &c, 69);
  printf("Afisare Vector\n");
  for (int i = 0; i < c->n; i++)
  {
    printConsultatie(c->v[i]);
  }
  // printf("%p\n", head);
  deleteConsultatii(&head, "Apa la plamani");
  printf("Dupa delete\n");
  // printf("%p\n", head);
  printListP(head);
}