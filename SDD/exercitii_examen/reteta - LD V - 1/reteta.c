#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Reteta
{
  unsigned int nrRetetei;
  unsigned char nrMedicamente;
  char** denumireMedicament;
  unsigned char* cantitateMedicament;
  float* pretMedicament;
  unsigned char* procentCompensare;
  char* numeMedic;
} Reteta;

typedef struct Node
{
  struct Node* prev;
  Reteta* info;
  struct Node* next;
} Node;

Reteta* createReteta(unsigned int nrRetetei,
  unsigned char nrMedicamente,
  char** denumireMedicament,
  unsigned char* cantitateMedicament,
  float* pretMedicament,
  unsigned char* procentCompensare,
  char* numeMedic)
{
  Reteta* r = (Reteta*)malloc(sizeof(Reteta));
  if (r)
  {
    r->nrRetetei = nrRetetei;
    r->nrMedicamente = nrMedicamente;

    r->denumireMedicament = (char**)malloc(sizeof(char*) * nrMedicamente);
    if (r->denumireMedicament)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        r->denumireMedicament[i] = (char*)malloc(strlen(denumireMedicament[i]) + 1);
        if (r->denumireMedicament[i])
        {
          strcpy_s(r->denumireMedicament[i], strlen(denumireMedicament[i]) + 1, denumireMedicament[i]);
        }
      }
    }

    r->cantitateMedicament = (unsigned char*)malloc(sizeof(unsigned char) * nrMedicamente);
    if (r->cantitateMedicament)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        r->cantitateMedicament[i] = cantitateMedicament[i];
      }
    }

    r->pretMedicament = (float*)malloc(sizeof(float) * nrMedicamente);
    if (r->pretMedicament)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        r->pretMedicament[i] = pretMedicament[i];
      }
    }

    r->procentCompensare = (unsigned char*)malloc(sizeof(unsigned char) * nrMedicamente);
    if (r->procentCompensare)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        r->procentCompensare[i] = procentCompensare[i];
      }
    }

    r->numeMedic = (char*)malloc(strlen(numeMedic) + 1);
    if (r->numeMedic)
      strcpy_s(r->numeMedic, strlen(numeMedic) + 1, numeMedic);
  }
  return r;
}

Node* createNode(Reteta* r)
{
  Node* node = (Node*)malloc(sizeof(Node));
  if (node)
  {
    node->info = r;
    node->prev = node->next = NULL;
  }
  return node;
}

Reteta* deepCloneReteta(Reteta* r)
{
  return createReteta(r->nrRetetei, r->nrMedicamente, r->denumireMedicament, r->cantitateMedicament, r->pretMedicament, r->procentCompensare, r->numeMedic);
}

void addToList(Node** h, Node** t, Node* n)
{
  if (!*h)
  {
    *h = *t = n;
  }
  else
  {
    Node* aux = *h;
    while (aux->next)
    {
      aux = aux->next;
    }
    n->prev = aux;
    aux->next = n;
    *t = n;
  }
}

void parseFile(Node** h, Node** t)
{
  FILE* f = fopen("data.txt", "r");

  char* token, * arrayDenumiri, * arrayCantitati, *arrayPreturi, *arrayProcente, *nume;

  char buffer[128];

  while (fgets(buffer, 128, f))
  {
    token = strtok(buffer, ";");
    int nrReteta = atoi(token);
    token = strtok(NULL, ";");
    char nrMedicamente = token[0];

    arrayDenumiri = strtok(NULL, ";");
    
    arrayCantitati = strtok(NULL, ";");

    arrayPreturi = strtok(NULL, ";");

    arrayProcente = strtok(NULL, ";");

    nume = strtok(NULL, "\n");

    char** denumireMedicament = (char**)malloc(sizeof(char*) * nrMedicamente);
    if (denumireMedicament)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        if (i == 0)
        {
          token = strtok(arrayDenumiri, ",");
        }
        else
        {
          token = strtok(NULL, ",");
        }
        denumireMedicament[i] = (char*)malloc(strlen(token) + 1);
        if (denumireMedicament[i])
          strcpy_s(denumireMedicament[i], strlen(token) + 1, token);
      }
    }

    unsigned char* cantitateMedicament = (unsigned char*)malloc(sizeof(unsigned char) * nrMedicamente);
    if (cantitateMedicament)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        if (i == 0)
        {
          token = strtok(arrayCantitati, ",");
        }
        else
        {
          token = strtok(NULL, ",");
        }
        cantitateMedicament[i] = token[0];
      }
    }

    float* pretMedicament = (float*)malloc(sizeof(float) * nrMedicamente);
    if (pretMedicament)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        if (i == 0)
        {
          token = strtok(arrayPreturi, ",");
        }
        else
        {
          token = strtok(NULL, ",");
        }
        pretMedicament[i] = atof(token);
      }
    }

    unsigned char* procentCompensare = (unsigned char*)malloc(sizeof(unsigned char) * nrMedicamente);
    if (procentCompensare)
    {
      for (char i = 0; i < nrMedicamente - '0'; i++)
      {
        if (i == 0)
        {
          token = strtok(arrayProcente, ",");
        }
        else
        {
          token = strtok(NULL, ",");
        }
        procentCompensare[i] = token[0];
      }
    }

    char* numeMedic = (char*)malloc(strlen(nume) + 1);
    if (numeMedic)
    {
      strcpy_s(numeMedic, strlen(nume) + 1, nume);
    }

    addToList(h, t, createNode(createReteta(nrReteta, nrMedicamente, denumireMedicament, cantitateMedicament, pretMedicament, procentCompensare, numeMedic)));

    for (char i = 0; i < nrMedicamente - '0'; i++)
    {
      free(denumireMedicament[i]);
    }
    free(denumireMedicament);

    free(cantitateMedicament);
    free(pretMedicament);
    free(procentCompensare);
    free(numeMedic);
  }

  fclose(f);
}

void printReteta(Reteta* r)
{
  printf("Nr: %d; nr. medicamente: %d; nume medic: %s \n", r->nrRetetei, r->nrMedicamente - '0', r->numeMedic);
  for (char i = 0; i < r->nrMedicamente - '0'; i++)
  {
    printf("Denumire: %s, Cantitate: %d, Pret: %.2f, Procent Compensat: %d\n", r->denumireMedicament[i], r->cantitateMedicament[i] - '0', r->pretMedicament[i], r->procentCompensare[i] - '0');
  }
}

void printList(Node* l)
{
  if (l) {
    if (!l->prev) {
      printf("Lista de la cap\n");
      while (l)
      {
        printReteta(l->info);
        l = l->next;
      }
    }
    else {
      printf("Lista de la coada\n");
      while (l)
      {
        printReteta(l->info);
        l = l->prev;
      }
    }
  }
  else {
    printf("Empty List");
  }
}

void incasariMedicament(Node* h, char* d) {
  float res = 0.0f;
  while (h) {
    for (char i = 0; i < h->info->nrMedicamente - '0'; i++)
    {
      if (strcmp(h->info->denumireMedicament[i], d) == 0) {
        res += h->info->pretMedicament[i] * h->info->cantitateMedicament[i];
      }
    }
    h = h->next;
  }
  printf("Pentru medicamentul: %s incasarile totale sunt %.2f\n",d, res);
}

void reteteDupaNume(Node* h, char* n, Reteta*** r, int* nr) {

  Node* aux = h;
  while (aux)
  {
    if (strcmp(aux->info->numeMedic, n) == 0) {
      (*nr)++;
    }
    aux = aux->next;
  }

  *r = (Reteta**)malloc(sizeof(Reteta*) * (*nr));
  int idx = 0;
  if (r) {
    while (h)
    {
      if (strcmp(h->info->numeMedic, n) == 0) {
        *r[idx++] = deepCloneReteta(h->info);
      }
      h = h->next;
    }
  }
}

void valoareCompensataTotala(Reteta** r, int n) {
  if (n < 0 || r == NULL) return;
  float res = 0.0f;
  for (int i = 0; i < n; i++)
  {
    for (int  j = 0; j < r[i]->nrMedicamente - '0'; j++)
    {
      res += r[i]->cantitateMedicament[j] * r[i]->pretMedicament[j] * r[i]->procentCompensare[j] / 100;
    }
  }
  printf("Valoare compensata totala a retetelor de la %s este %.2f\n", r[0]->numeMedic, res);
}

void cantitateMedicamentVanduta(Node* h, char* n) {
  int cant = 0;

  while (h) {

    for (char i = 0; i < h->info->nrMedicamente - '0'; i++)
    {
      if (strcmp(n, h->info->denumireMedicament[i]) == 0) {
        cant += h->info->cantitateMedicament[i];
      }
    }
    h = h->next;
  }
  printf("Cantitatea totala vanduta din %s este %d\n", n, cant);
}

void deleteReteta(Reteta** r) {
  if (*r) {
    for (char i = 0; i < (*r)->nrMedicamente - '0'; i++)
    {
      free((*r)->denumireMedicament[i]);
      (*r)->denumireMedicament[i] = NULL;
    }
    free((*r)->denumireMedicament);

    free((*r)->cantitateMedicament);
    free((*r)->pretMedicament);
    free((*r)->procentCompensare);
    free((*r)->numeMedic);
    (*r)->numeMedic = NULL;
    free(*r);
    *r = NULL;
  }
}

void deleteNode(Node** n) {
  if (*n) {
    deleteReteta(&((*n)->info));
    free(*n);
    *n = NULL;
  }
}

void deallocateList(Node** h) {
  if (*h) {
    deallocateList(&((*h)->next));
    deleteNode(h);
  }
}

void deallocateVector(Reteta*** r, int n) {
  for (int i = 0; i < n; i++)
  {
    deleteReteta(&(*r[i]));
  }
  free(*r);
  *r = NULL;
}

void main()
{
  Node* head = NULL, * tail = NULL;
  parseFile(&head, &tail);
  printList(head);
  printList(tail);
  incasariMedicament(head, "THC");
  Reteta** retete = NULL;
  int nrRetete = 0;

  reteteDupaNume(head, "Stan", &retete, &nrRetete);

  for (int i = 0; i < nrRetete; i++)
  {
    printReteta(retete[i]);
  }

  valoareCompensataTotala(retete, nrRetete);

  cantitateMedicamentVanduta(head, "THC");

  deallocateList(&head);

  deallocateVector(&retete, nrRetete);
  
  printf("press enter to exit...");
  getchar();
}