#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Factura
{
  int codFactura;
  int nrZileScadenta;
  float pret;
} Factura;

typedef struct NodH {
  Factura** el;
  int size;
} NodH;

Factura *createFactura(int codFactura, int nrZileScadenta, float pret) {
  Factura* f = (Factura*)malloc(sizeof(Factura));
  if (f) {
    f->codFactura = codFactura;
    f->nrZileScadenta = nrZileScadenta;
    f->pret = pret;
  }
  return f;
}

Factura* deepCloneFactura(Factura*f) {
  return createFactura(f->codFactura, f->nrZileScadenta, f->pret);
}

NodH *initHeap() {
  NodH* h = (NodH*)malloc(sizeof(NodH));
  if (h) {
    h->el = NULL;
    h->size = 0;
  }
  return h;
}

void swapFactura(Factura** f1, Factura** f2) {
  Factura* temp = *f1;
  *f1 = *f2;
  *f2 = temp;
}

void heapify(NodH* h, int i) {
  int parinte = i;

  int fiuS = (2*i) + 1, fiuD = (2*i) + 2;

  if (fiuS < h->size && h->el[fiuS]->nrZileScadenta < h->el[parinte]->nrZileScadenta) {
    parinte = fiuS;
  }

  if (fiuD < h->size && h->el[fiuD]->nrZileScadenta < h->el[parinte]->nrZileScadenta) {
    parinte = fiuD;
  }

  if (parinte != i) {
    swapFactura(&(h->el[parinte]), &(h->el[i]));
    heapify(h, parinte);
  }
}

void insertHeap(NodH* h, Factura* f) {

  h->el = (Factura**)realloc(h->el, (h->size + 1) * sizeof(Factura));
  h->el[h->size] = f;
  h->size++;

  for (int i = (h->size - 1) / 2; i >= 0; i--)
  {
    heapify(h, i);
  }

}

void parseFile(NodH* h) {
  FILE *f = fopen("data.txt", "r");
  if (!f) return;
  char buffer[128];
  while (fgets(buffer, 128, f))
  {
    char* codFactura = strtok(buffer, ","), *nrZileScadenta = strtok(NULL, ","), *pret = strtok(NULL, "\n");
    insertHeap(h, createFactura(atoi(codFactura), atoi(nrZileScadenta), atof(pret)));
  }
  fclose(f);
}

void printFactura(Factura* f) {
  if (!f) return;
  printf("Cod factura: %d, nr zile pana la scadenta: %d, pret factura: %.2f\n", f->codFactura, f->nrZileScadenta, f->pret);
}

void printHeap(NodH*h) {
  for (int i = 0; i < h->size; i++)
  {
    if (2*i+1 < h->size) {
      printFactura(h->el[i]);
      printf("  ");
      printFactura(h->el[2*i+1]);
    } else {
      break;
    }
    if (2*i+2 < h->size) {
      printf("  ");
      printFactura(h->el[2*i+2]);
    }
  }
  
}

void deleteNode(NodH *h) {
  Factura** copy = (Factura**)malloc(sizeof(Factura) * (h->size - 1));
  swapFactura(&(h->el[0]), &(h->el[h->size-1]));
  for (int i = 0; i < h->size - 1; i++)
  {
    copy[i] = h->el[i];
  }
  free(h->el);
  h->size--;
  h->el = copy;
  for (int i = (h->size - 1)/2; i >= 0; i--)
  {
    heapify(h, i);
  }
  
}

void deleteNodesZileScadentaSub(NodH* h, int n) {
  for (int i = 0; i < h->size; i++)
  {
    if (h->el[i]->nrZileScadenta < 3) {
      deleteNode(h);
      i--;
    }
  }
  
}

typedef struct NodT {
  Factura* info;
  struct NodT *left, *right;
} NodT;

NodT *createNodT(Factura* f) {
  NodT *n = (NodT*)malloc(sizeof(NodT));
  if (n) {
    n->info = f;
    n->left = n->right = NULL;
  }
  return n;
}

void insertBST(NodT** h, NodT *n) {
  if (!*h) {
    *h = n;
    return;
  }
  if (n->info->codFactura < (*h)->info->codFactura) {
    insertBST(&((*h)->left), n);
  } else if (n->info->codFactura > (*h)->info->codFactura) {
    insertBST(&((*h)->right), n);
  }
}

void convertHeapBST(NodH* h, NodT** r) {
  for (int i = 0; i < h->size; i++)
  {
    insertBST(r, createNodT(deepCloneFactura(h->el[i])));
  }
}

void inordine(NodT *r) {
  if (!r) return;
  printFactura(r->info);
  inordine(r->left);
  inordine(r->right);
}

typedef struct NodL {
  Factura* info;
  struct NodL *next;
} NodL;

NodL *createNodL(Factura *f) {
  NodL *n = (NodL*)malloc(sizeof(NodL));
  if (n) {
    n->info = f;
    n->next = NULL;
  }
  return n;
}

void insertList(NodL **l, NodL *n) {
  if (!*l) {
    *l = n;
    return;
  }
  NodL* aux = *l;
  while (aux->next)
  {
    aux = aux->next;
  }
  aux->next = n;
}

int doesElExist(NodT*r, int c) {
  if (!r) return 0;
  return (r->info->codFactura == c ? 1 : 0) + (r->left ? doesElExist(r->left, c) : 0) + (r->right ? doesElExist(r->right, c) : 0);
}

void convertBSTL(NodT *r, NodL** l, int c) {
  if (!doesElExist(r,c)) return;
  insertList(l, createNodL(deepCloneFactura(r->info)));
  if (c < r->info->codFactura)
    convertBSTL(r->left, l, c);
  else 
    convertBSTL(r->right, l, c);
}

void printList(NodL *l) {
  if (!l) return;
  printFactura(l->info);
  printList(l->next);
}

void deallocateHeap(NodH** h) {
  for (int i = 0; i < (*h)->size; i++)
  {
    free((*h)->el[i]);
  }
  free((*h)->el);
  free(*h);
  *h = NULL;
}

void deallocateBST(NodT** r) {
  if (!*r) return;
  NodT* left = (*r)->left, *right = (*r)->right;
  free((*r)->info);
  free(*r);
  *r = NULL;
  deallocateBST(&left);
  deallocateBST(&right);
}

void deallocateList(NodL**l) {
  if (!*l) return;
  NodL* next = (*l)->next;
  free((*l)->info);
  free(*l);
  *l = NULL;
  deallocateList(&next);
}

void main()
{
  NodH* h = initHeap();
  parseFile(h);
  printHeap(h);
  printf("\n");
  deleteNodesZileScadentaSub(h, 3);
  printHeap(h);
  NodT* r = NULL;
  convertHeapBST(h,&r);
  inordine(r);
  printf("\n");
  NodL*l = NULL;
  convertBSTL(r, &l, 10);
  printList(l);
  deallocateHeap(&h);
  deallocateBST(&r);
  deallocateList(&l);
}