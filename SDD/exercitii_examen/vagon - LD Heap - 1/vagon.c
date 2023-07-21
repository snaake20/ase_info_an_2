#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

typedef struct Vagon Vagon;

struct Vagon
{
  int numarVagon;
  char* firmaTransport;
  int numarBileteVandute;
  int capacitateVagon;
};

typedef struct Tren Tren;

struct Tren
{
  Tren* vagon_prev;
  Vagon* vagon_info;
  Tren* vagon_next;
};

Vagon* creareVagon(int numarVagon, char* firmaTransport, int numarBileteVandute, int capacitateVagon)
{
  Vagon* v = (Vagon*)malloc(sizeof(Vagon));
  if (v)
  {
    v->numarVagon = numarVagon;
    v->firmaTransport = (char*)malloc(strlen(firmaTransport) + 1);
    if (v->firmaTransport)
    {
      strcpy_s(v->firmaTransport, strlen(firmaTransport) + 1, firmaTransport);
    }
    v->numarBileteVandute = numarBileteVandute;
    v->capacitateVagon = capacitateVagon;
  }
  return v;
}

Tren* createNode(Vagon* v)
{
  Tren* t = (Tren*)malloc(sizeof(Tren));
  if (t)
  {
    t->vagon_info = v;
    t->vagon_prev = t->vagon_next = NULL;
  }
  return t;
}

void inserareVagon(Tren** t, Tren* v)
{
  if (*t)
  {
    Tren* aux = *t;
    while (aux->vagon_next)
    {
      aux = aux->vagon_next;
    }
    v->vagon_prev = aux;
    aux->vagon_next = v;
  }
  else
  {
    *t = v;
  }
}

void citireFisier(Tren** t)
{
  FILE* f = fopen("data.txt", "r");
  if (f)
  {
    char* token = NULL;
    char delimiter[] = ",\n";
    char linebuffer[128], firmaTransport[128];
    int numarVagon, numarBileteVandute, capacitateVagon;
    while (fgets(linebuffer, sizeof(linebuffer), f))
    {
      token = strtok(linebuffer, delimiter);
      numarVagon = atoi(token);
      token = strtok(NULL, delimiter);
      strcpy(firmaTransport, token);
      token = strtok(NULL, delimiter);
      numarBileteVandute = atoi(token);
      token = strtok(NULL, delimiter);
      capacitateVagon = atoi(token);
      inserareVagon(t, createNode(creareVagon(numarVagon, firmaTransport, numarBileteVandute, capacitateVagon)));
    }
    fclose(f);
  }
}

float calculareGradOcupare(Vagon* v)
{
  return (float)v->numarBileteVandute / v->capacitateVagon * 100;
}

void afisareVagon(Vagon* v)
{
  printf("Vagonul nr:%d, de la firma: %s, are %d bilete cumparate din capacitatea maxima: %d = %f \n", v->numarVagon, v->firmaTransport, v->numarBileteVandute, v->capacitateVagon, calculareGradOcupare(v));
}

void traversareTren(Tren* t)
{
  if (t)
  {
    afisareVagon(t->vagon_info);
    traversareTren(t->vagon_next);
  }
}

void traversareTrenInvers(Tren* t)
{
  if (t)
  {
    afisareVagon(t->vagon_info);
    traversareTrenInvers(t->vagon_prev);
  }
}

void getCoada(Tren** t, Tren* tr)
{
  while (tr->vagon_next)
  {
    tr = tr->vagon_next;
  }
  *t = tr;
}

int minBileteVandute(Tren* t)
{
  int min = t->vagon_info->numarBileteVandute;
  while (t->vagon_next)
  {
    t = t->vagon_next;
    if (min > t->vagon_info->numarBileteVandute)
    {
      min = t->vagon_info->numarBileteVandute;
    }
  }
  return min;
}

void deleteVagon(Vagon** v)
{
  if (*v)
  {
    if ((*v)->firmaTransport)
    {
      free((*v)->firmaTransport);
      (*v)->firmaTransport = NULL;
    }
    free(*v);
    *v = NULL;
  }
}

void deleteNode(Tren** t)
{
  if (*t)
  {
    deleteVagon(&(*t)->vagon_info);
    (*t)->vagon_prev = (*t)->vagon_next = NULL;
    free(*t);
    *t = NULL;
  }
}

void eliminareNoduriCuNrDeBilMin(Tren** t)
{
  if (*t)
  {
    Tren* aux = *t;
    int min = minBileteVandute(*t);
    while (aux)
    {
      Tren* next = aux->vagon_next;
      if (aux->vagon_info->numarBileteVandute == min)
      {
        if (aux->vagon_prev)
        {
          aux->vagon_prev->vagon_next = aux->vagon_next;
        }
        if (aux->vagon_next)
        {
          aux->vagon_next->vagon_prev = aux->vagon_prev;
        }
        if (!aux->vagon_prev)
        {
          *t = aux->vagon_next;
        }
        deleteNode(&aux);
      }
      aux = next;
    }
  }
}

void deleteList(Tren** t)
{
  if (*t)
  {
    deleteList(&(*t)->vagon_next);
    deleteNode(t);
  }
}

// ------------------------------- LISTA DUBLU INLANTUITA

typedef struct Heap
{
  Vagon** vagon_info;
  int size;
} Heap;

void swapVagoane(Vagon** v1, Vagon** v2)
{
  Vagon* aux = *v1;
  *v1 = *v2;
  *v2 = aux;
}

void filtrareHeap(Heap* h, int i)
{
  int parinte = i;//nod radacina
  int indexS = 2 * i + 1;//fiul stg
  int indexD = 2 * i + 2;//fiul dreapta

  if (indexS < h->size && calculareGradOcupare(h->vagon_info[indexS]) < calculareGradOcupare(h->vagon_info[parinte]))
    parinte = indexS;//interschimbare indici
  if (indexD < h->size && calculareGradOcupare(h->vagon_info[indexD]) < calculareGradOcupare(h->vagon_info[parinte]))
    parinte = indexD;

  if (i != parinte)//interschimbare elemente din vector
  {
    swapVagoane(&(h->vagon_info[i]), &(h->vagon_info[parinte]));
    filtrareHeap(h, parinte);
  }
}

void inserareHeap(Heap* h, Vagon* v)
{
  h->vagon_info = (Vagon**)realloc(h->vagon_info, (h->size + 1) * sizeof(Vagon*));
  if (h->vagon_info)
  {
    h->vagon_info[h->size++] = v;
  }
  for (int i = (h->size-1)/2; i >= 0 ; i--)
  {
    filtrareHeap(h, i);
  }
}

// void extragereHeap(Heap**, Vagon**);

Vagon* deepCopyVagon(Vagon* v)
{
  Vagon* vagon = (Vagon*)malloc(sizeof(Vagon));
  if (vagon)
  {
    vagon->numarVagon = v->numarVagon;
    vagon->firmaTransport = (char*)malloc(strlen(v->firmaTransport) + 1);
    if (vagon->firmaTransport)
      strcpy_s(vagon->firmaTransport, strlen(v->firmaTransport) + 1, v->firmaTransport);
    vagon->numarBileteVandute = v->numarBileteVandute;
    vagon->capacitateVagon = v->capacitateVagon;
  }
  return vagon;
}

Heap* convertToHeap(Tren* t)
{
  Heap* h = (Heap*)malloc(sizeof(Heap));
  if (h)
  {
    h->size = 0;
    h->vagon_info = NULL;
    while (t)
    {
      inserareHeap(h, deepCopyVagon(t->vagon_info));
      t = t->vagon_next;
    }
  }
  return h;
};

void afisareHeap(Heap* h)
{
  if (h)
  {
    for (int i = 0; i < h->size; i++)
    {
      afisareVagon(h->vagon_info[i]);
    }
  }
  else
  {
    printf("Heap gol!\n");
  }
}

void changeNrBileteCumparate(Heap* h, char* numeVagon, int nrBilete)
{
  for (int i = 0; i < h->size; i++)
  {
    if (strcmp(h->vagon_info[i]->firmaTransport, numeVagon) == 0)
    {
      h->vagon_info[i]->numarBileteVandute = nrBilete;
    }
  }
  for (int i = (h->size - 1) / 2; i >= 0; i--)
  {
    filtrareHeap(h, i);
  }
}

void deleteHeap(Heap** h)
{
  if (*h)
  {

    for (int i = 0; i < (*h)->size; i++)
    {
      deleteVagon(&((*h)->vagon_info[i]));
    }
    free((*h)->vagon_info);

    (*h)->size = 0;

    free((*h));

    *h = NULL;
  }
}

// ------------------------------- HEAP

void main()
{
  Tren* tren = NULL, * coada = NULL;
  citireFisier(&tren);

  traversareTren(tren);

  getCoada(&coada, tren);

  // traversareTrenInvers(coada);

  int min = minBileteVandute(tren);

  printf("Nr minim de bilete vandute: %d\n", min);

  eliminareNoduriCuNrDeBilMin(&tren);

  traversareTren(tren);

  getCoada(&coada, tren);

  // traversareTrenInvers(coada);

  // printf("Lista dupa stergere:\n");

  // traversareTren(tren);

  printf("Afisare heap\n");

  Heap* h = convertToHeap(tren);

  afisareHeap(h);

  deleteList(&tren);

  printf("Dupa schimbare\n");

  changeNrBileteCumparate(h, "GDM", 1);

  afisareHeap(h);

  deleteHeap(&h);

  afisareHeap(h);

  // _CrtDumpMemoryLeaks();
}