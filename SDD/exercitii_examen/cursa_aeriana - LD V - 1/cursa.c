#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct CursaAeriana
{
  unsigned idCursa;
  char *destinatie;
  char *dataPlecare;
  unsigned short nrMinuteIntarziere;
  unsigned char nrPasageriInregistrati;
} CursaAeriana;

typedef struct Node
{
  struct Node *prev;
  CursaAeriana *info;
  struct Node *next;
} Node;

typedef struct PasageriDestinatie {
  char* destinatie;
  unsigned nrPasageri;
} PasageriDestinatie;

CursaAeriana *createCursa(unsigned idCursa,
                          char *destinatie,
                          char *dataPlecare,
                          unsigned short nrMinuteIntarziere,
                          unsigned char nrPasageriInregistrati)
{
  CursaAeriana *c = (CursaAeriana *)malloc(sizeof(CursaAeriana));
  if (c)
  {
    c->idCursa = idCursa;
    c->destinatie = (char *)malloc(strlen(destinatie) + 1);
    if (c->destinatie)
    {
      strcpy_s(c->destinatie, strlen(destinatie) + 1, destinatie);
    }
    c->dataPlecare = (char *)malloc(strlen(dataPlecare) + 1);
    if (c->dataPlecare)
    {
      strcpy_s(c->dataPlecare, strlen(dataPlecare) + 1, dataPlecare);
    }
    c->nrMinuteIntarziere = nrMinuteIntarziere;
    c->nrPasageriInregistrati = nrPasageriInregistrati;
  }
  return c;
}

void printCursa(CursaAeriana* c) {
  printf("Id: %d, destinatie: %s, data plecare: %s, nr minute intarziere: %d, nr pasageri: %d\n", c->idCursa, c->destinatie, c->dataPlecare, c->nrMinuteIntarziere, c->nrPasageriInregistrati );
}

Node *createNode(CursaAeriana *c)
{
  Node *n = (Node *)malloc(sizeof(Node));
  if (n)
  {
    n->info = c;
    n->prev = n->next = NULL;
  }
  return n;
}

void insertNodeEnd(Node **h, Node **t, Node *n)
{
  if (!*h) {
    *h = *t = n;
  } else {
    Node* aux = *h;
    while(aux->next) {
      aux = aux->next;
    }
    n->prev = aux;
    aux->next = n;
    *t = n;
  }
}

void parseFile(Node **h, Node **t)
{
  FILE* f = fopen("data.txt", "r");
  if (f) {
    char* id, *destinatie, *dataPlecare, *minuteIntarziere, *pasageriInregistrati, buffer[128];
    while (fgets(buffer, 128, f))
    {
      id=strtok(buffer, ",");
      destinatie=strtok(NULL, ",");
      dataPlecare=strtok(NULL, ",");
      minuteIntarziere=strtok(NULL, ",");
      pasageriInregistrati=strtok(NULL, "\n");

      unsigned idCursa = atoi(id);

      unsigned short nrMinuteIntarziere = atoi(minuteIntarziere);

      unsigned char nrPasageriInregistrati = atoi(pasageriInregistrati);

      insertNodeEnd(h, t, createNode(createCursa(idCursa, destinatie, dataPlecare, nrMinuteIntarziere, nrPasageriInregistrati)));
    }
    
    fclose(f);
  }
}

void printList(Node *l) {
  if (!l) return;
  if (!l->prev) {
    printf("Lista de la cap\n");
    while(l) {
      printCursa(l->info);
      l = l->next;
    }
  } else {
    printf("Lista de la coada\n");
    while(l) {
      printCursa(l->info);
      l = l->prev;
    }
  }
}

PasageriDestinatie createStruct(char* d, unsigned n) {
  char* dest = (char*)malloc(strlen(d)+1);
  if (dest) {
    strcpy_s(dest,strlen(d)+1,d);
  }
  PasageriDestinatie p = {dest, n};
  return p;
}

void insertVector(PasageriDestinatie **v, int *n, PasageriDestinatie s) {
  if (!*v) { 
    *v = (PasageriDestinatie*)realloc(*v, sizeof(PasageriDestinatie));
    (*v)[(*n)++] = s;
  } else {
    for (int i = 0; i < *n; i++)
    {
      if (strcmp(s.destinatie, (*v)[i].destinatie) == 0) {
        (*v)[i].nrPasageri += s.nrPasageri;
        return;
      }
    }
    *v = (PasageriDestinatie*)realloc(*v, sizeof(PasageriDestinatie) * ((*n) + 1));
    (*v)[(*n)++] = s;
  }
}

void agregaPasageriDupaDestinatie(Node* h, PasageriDestinatie** v, int* n) {
  while (h)
  {
    insertVector(v,n,createStruct(h->info->destinatie, h->info->nrPasageriInregistrati));
    h = h->next;
  }
}

void main()
{
  Node* head = NULL, *tail = NULL;
  parseFile(&head, &tail);
  printList(head);
  printList(tail);

  PasageriDestinatie* v = NULL;
  int nrElem = 0;

  agregaPasageriDupaDestinatie(head, &v, &nrElem);

  for (int i = 0; i < nrElem; i++)
  {
    printf("destinatie: %s, nr pasageri: %d\n", v[i].destinatie, v[i].nrPasageri);
  }
  getchar();
}