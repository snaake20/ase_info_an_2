#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct DosarCandidat
{
  char *numeCandidat;
  char *programStudiu;
  float medieBac;
  int codDosar;
} DosarCandidat;

typedef struct HashTable
{
  DosarCandidat **dosar;
  int size;
} HashTable;

DosarCandidat *initDosar(char *numeCandidat, char *programStudiu, float medieBac, int codDosar) {
  DosarCandidat* d = (DosarCandidat*)malloc(sizeof(DosarCandidat));
  if (d) {
    d->numeCandidat = (char*)malloc(strlen(numeCandidat) + 1);
    if (d->numeCandidat)
      strcpy_s(d->numeCandidat, strlen(numeCandidat) + 1, numeCandidat);
    d->programStudiu = (char*)malloc(strlen(programStudiu) + 1);
    if (d->programStudiu)
      strcpy_s(d->programStudiu, strlen(programStudiu) + 1, programStudiu);
    d->medieBac = medieBac;
    d->codDosar = codDosar;
  }
  return d;
}

void initHashTable(HashTable** t, int n) {
  *t = (HashTable*)malloc(sizeof(HashTable));
  if (*t) {
    (*t)->dosar = (DosarCandidat**)calloc(n, sizeof(DosarCandidat*));
    (*t)->size = n;
  }
}

int hash(char* n, int s) {
  int res = 0;
  for (int i = 0; i < strlen(n); i++)
  {
    res+=n[i];
  }
  return res % s;
}

void insertIntoTable(HashTable **t, DosarCandidat* d) {
  if (!(*t)->dosar) return;
  int pos = hash(d->numeCandidat, (*t)->size);
  if ((*t)->dosar[pos] != NULL) {
    int gasit = 0;
    int index = 1;
    while (pos + index < (*t)->size)
    {
      if ((*t)->dosar[pos + index] == NULL) {
        gasit = 1;
        (*t)->dosar[pos - index] = d;
        break;
      }
      index++;
    }
    if (gasit == 0) {
      index = 1;
      while (pos - index >= 0)
      {
        if ((*t)->dosar[pos - index] == NULL) {
          (*t)->dosar[pos - index] = d;
          break;
        }
        index--;
      }
    }
  } else {
    (*t)->dosar[pos] = d;
  }
}

void parseFile(HashTable **t) {
  FILE* f = fopen("data.txt", "r");
  if (f) {

    char buffer[128];

    int gasitNrInreg = 0;

    while (fgets(buffer, 128, f))
    {
      if (gasitNrInreg == 0) {
        initHashTable(t, atoi(strtok(buffer, "\n")));
        gasitNrInreg = 1;
      } else {
        char *numeCandidat = strtok(buffer, ","), *programStudiu = strtok(NULL, ","), *medie = strtok(NULL, ","), *codDosar = strtok(NULL, "\n");
        insertIntoTable(t, initDosar(numeCandidat, programStudiu, atof(medie), atoi(codDosar)));
      }
    }

    fclose(f);
  }
}

void printDosarCandidat(DosarCandidat* d) {
  printf("nume candidat: %s, program studiu: %s, medie bac: %.2f, cod dosar: %d\n", d->numeCandidat, d->programStudiu, d->medieBac, d->codDosar);
}

void printTable(HashTable* t) {
  for (int i = 0; i < t->size; i++)
  {
    if (t->dosar[i]) {
      printf("Pozitie: %d, ", i);
      printDosarCandidat(t->dosar[i]);
    }
  }
}

void nrCandidatiProgram(HashTable* t, char* s) {
  int res = 0;
  for (int i = 0; i < t->size; i++)
  {
    if (t->dosar[i] && strcmp(s, t->dosar[i]->programStudiu) == 0) {
      res++;
    }
  }
  printf("Specializarea %s are %d candidati\n", s, res);
}

typedef struct NodS {
  DosarCandidat* info;
  struct NodS* next;
} NodS;

typedef struct NodP {
  NodS* head;
  struct NodP* next;
} NodP;

NodS *initNodS(DosarCandidat* d) {
  NodS* s = (NodS*)malloc(sizeof(NodS));
  if (s) {
    s->info = d;
    s->next = NULL;
  }
  return s;
}

NodP *initNodP(NodS* n) {
  NodP* p = (NodP*)malloc(sizeof(NodP));
  if (p) {
    p->head = n;
    p->next = NULL;
  }
  return p;
}

void insertListS(NodS**h, NodS* n) {
  if (!*h) {
    *h = n;
  } {
    NodS* aux = *h;
    while (aux->next)
    {
      aux = aux->next;
    }
    aux->next = n;
  }
}

void inserListP(NodP**h, NodS*n) {
  if (!*h) {
    *h = initNodP(n);
  } else {
    NodP* aux = *h;
    int gasit = 0;
    while (aux)
    {
      if (strcmp(n->info->programStudiu, aux->head->info->programStudiu) == 0) {
        gasit = 1;
        break;
      }
      if (aux->next == NULL) break;
      aux = aux->next;
    }
    if (gasit == 0) {
      aux->next = initNodP(n);
    } else {
        insertListS(&(aux->head), n);
    }
  }
}

DosarCandidat* deepCloneDosar(DosarCandidat* d) {
  return initDosar(d->numeCandidat, d->programStudiu, d->medieBac, d->codDosar);
}

void convertToLL(HashTable* t, NodP **h, float m) {
  for (int i = 0; i < t->size; i++)
  {
    if (t->dosar[i] && t->dosar[i]->medieBac < m) {
      inserListP(h, initNodS(deepCloneDosar(t->dosar[i])));
    }
  }
}

void printListS(NodS *h) {
  while (h)
  {
    printDosarCandidat(h->info);
    h = h->next;
  }
  
}

void printListP(NodP *h) {
  while (h)
  {
    printListS(h->head);
    h = h->next;
  }
}

void deleteDosar(DosarCandidat** d) {
  free((*d)->numeCandidat);
  (*d)->numeCandidat = NULL;
  free((*d)->programStudiu);
  (*d)->programStudiu = NULL;
  free((*d));
  *d = NULL;
}

void deleteNodS(NodS** n) {
  deleteDosar(&(*n)->info);
  free((*n));
  *n = NULL;
}

void deleteNodP(NodP** n) {
  if ((*n)->head != NULL) {
    deleteNodS(&((*n)->head));
  }
  free((*n));
  *n = NULL;
}

void deleteMinMedie(NodP **h) {
  NodP* aux = *h;
  float min = aux->head->info->medieBac;
  while (aux)
  {
    NodS* hs = aux->head; 
    while(hs) {
      if (hs->info->medieBac < min) {
        min = hs->info->medieBac;
      }
      hs = hs->next;
    }
    aux = aux->next;
  }
  aux = *h;

  while (aux)
  {
    NodS* hs = aux->head;
    while (hs)
    {
      NodS *next = hs->next;
      if (hs->info->medieBac == min) {
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
        deleteNodS(&curr);
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
        deleteNodP(&curr);
    }
    aux = next;
  }
  

}

void main()
{
  HashTable* t = NULL;
  parseFile(&t);
  printTable(t);
  nrCandidatiProgram(t, "Master");
  NodP* h = NULL;
  convertToLL(t, &h, 9.00f);
  printListP(h);
  deleteMinMedie(&h);
  printListP(h);
}