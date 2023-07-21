#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define LINE_SIZE 128

// do not modify the code under this line
// --------------------------------------------

union Reference
{
  unsigned char intRef;
  unsigned short extRef; // 0000 0000 university <=|=> id_stud 0000 0000
};

typedef union Reference RefInfo;

struct Student
{
  char *name;
  double income;
  RefInfo reference;
};

typedef struct Student StudentInfo;

// --------------------------------------------
// do not modify the code above this line

// here will add structs declarations
// --------------------------------------------

struct Node
{
  StudentInfo *info;
  struct Node *next;
};

typedef struct Node Node;

// --------------------------------------------

// here will add data structure fn declarations
// --------------------------------------------

void addToDataStructure(Node **list, StudentInfo *student, void (*func)(Node **, Node *));

Node *createNode(StudentInfo *);
Node *copyNode(Node *);
void deleteNode(Node **);

int length(Node *);

void addToStartOfList(Node **, Node *);
void addToPos(Node **, Node *, int);
void addBeforeKey(Node **, Node *, char const *);
void addAfterKey(Node **, Node *, char const *);
void addAtTheMiddle(Node*, Node *);
void addToEndOfList(Node **, Node *);

void deleteStartNode(Node **);
void deleteAtPos(Node **, int);
void deleteByKey(Node **, char const *);
void deleteEndNode(Node **);

void displayList(Node *);
void deleteList(Node **);

void reverseList(Node **);
void splitList(Node *, Node **);

void swap(Node *, Node *);
void sort(Node *);

int search(Node *, char const *);
// --------------------------------------------

// do not modify the code under this line
// --------------------------------------------

StudentInfo *createStudentInfo(const char *name, double income, unsigned short ref)
{
  StudentInfo *res = NULL;

  res = (StudentInfo *)malloc(sizeof(StudentInfo) * 1);

  if (res != NULL)
  {
    res->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    if (res->name != NULL)
    {
      strcpy_s(res->name, strlen(name) + 1, name);
    }
    res->income = income;
    res->reference.extRef = ref;
  }

  return res;
}

void deleteStudentInfo(StudentInfo **stud)
{
  if (*stud != NULL)
  {
    free((*stud)->name);
    free(*stud);
  }
  *stud = NULL;
}

// done by me
// --------------------------------------------

void adaugaStudent(StudentInfo ***agenda, int *noEl, StudentInfo *stud)
{
  *agenda = (StudentInfo **)realloc(*agenda, (*noEl + 1) * sizeof(StudentInfo *));
  (*agenda)[*noEl] = stud;
  *noEl = *noEl + 1;
}

void readStudents(StudentInfo ***agenda, int *noEl, Node **dataStructure)
{
  char fileLineBuffer[LINE_SIZE];
  FILE *pFile = fopen("Data.txt", "r");
  char *token;
  unsigned short referinta;
  double salariu;
  char nume[LINE_SIZE];
  if (pFile)
  {
    int idx = 0;
    while (fgets(fileLineBuffer, sizeof(fileLineBuffer), pFile))
    {
      // citire nume
      token = strtok(fileLineBuffer, ",");
      strcpy(nume, token);
      // citire salariu
      token = strtok(NULL, ",");
      salariu = atof(token);
      // citire referinta
      token = strtok(NULL, "\n");
      referinta = atoi(token);
      // creare pointer la student
      // adaugare in agenda (dinamic)
      adaugaStudent(agenda, noEl, createStudentInfo(nume, salariu, referinta));
      // adaugare in structura de date
      addToDataStructure(dataStructure, createStudentInfo(nume, salariu, referinta), addToEndOfList);
    }
    fclose(pFile);
  }
}

void deleteStudents(StudentInfo ***agenda, int *noEl)
{
  for (int i = 0; i < *noEl; i++)
  {
    deleteStudentInfo(&(*agenda)[i]);
  }
  free(*agenda);
  *agenda = NULL;
  *noEl = 0;
}

// --------------------------------------------
// done by me (to keep the main fn clean)

void displayStudent(StudentInfo *stud)
{
  if (stud)
  {
    printf("Name: %s, income: %.2f\n", stud->name, stud->income);
    if (stud->reference.extRef >> 15 == 1)
    {
      short uid = stud->reference.extRef >> 8 & 127;
      printf("University ref: %d\n", uid);
      printf("External ref: %d\n", stud->reference.extRef & 255);
    }
    else
    {
      printf("Internal ref: %d\n", stud->reference.intRef);
    }
  }
}

void displayStudents(StudentInfo **agenda, int noEl)
{
  for (int i = 0; i < noEl; i++)
  {
    displayStudent(agenda[i]);
  }
}

// --------------------------------------------
// do not modify the code above this line

void main()
{
  StudentInfo **agenda = NULL;
  int noEl = 0;

  Node *list = NULL;

  readStudents(&agenda, &noEl, &list);

  // printf("Nr of students: %d\n", noEl); // should comment this line (debug)
  // printf("Agenda: %p\n", agenda);      // should comment this line (debug)
  // displayStudents(agenda, noEl);      // should comment this line (debug)

  // here will add data structure fn calls (playground (￣y▽￣)╭ Ohohoho.....)
  // --------------------------------------------

  // for (int i = 0; i < 2; i++)
  // {
  //   deleteStartNode(&list);
  // }

  printf("The length of the list is %d.\n", length(list));

  displayList(list);

  printf("\n");

  printf("Position of Antonescu Robert is %d\n", search(list, "Antonescu Robert"));

  // deleteAtPos(&list, search(list, "Calinescu Elena"));

  // addToPos(&list, createNode(createStudentInfo("Edi Popescu", 1000, 125)), length(list));

  // addAtTheMiddle(list, createNode(createStudentInfo("Edi Popescu", 1000, 125)));

  sort(list);

  displayList(list);

  // reverseList(&list);

  // displayList(list);

  // Node* secondList = NULL;

  // splitList(list, &secondList);

  // printf("first list\n");
  // displayList(list);
  // printf("second list\n");
  // displayList(secondList);

  deleteList(&list);
  // deleteList(&secondList);
  // --------------------------------------------

  deleteStudents(&agenda, &noEl);

  // printf("Nr of students: %d\n", noEl); // should comment this line (debug)
  // printf("Agenda: %p\n", agenda);      // should comment this line (debug)
}

// here will add data structure fn definitions

// --------------------------------------------

void addToDataStructure(Node **list, StudentInfo *student, void (*func)(Node **, Node *))
{
  if (!func)
    return;
  return func(list, createNode(student));
}

Node *createNode(StudentInfo *info)
{
  Node *node = (Node *)malloc(sizeof(Node));
  if (node)
  {
    node->info = info;
    node->next = NULL;
  }
  return node;
}

void deleteNode(Node **node)
{
  if (!*node)
    return;
  deleteStudentInfo(&((*node)->info));
  free(*node);
  *node = NULL;
}

int length(Node *list)
{
  if (!list)
    return 0;
  return 1 + length(list->next);
}

// void length_iterative(Node *list) {
//   int result = 0;
//   if(!list)
//     return result;
//   while(list->next){
//     result++;
//     list=list->next;
//   }
//   result++;
//   return result;
// }

void addToStartOfList(Node **list, Node *node)
{
  node->next = *list;
  *list = node;
}

void addToPos(Node **list, Node *node, int pos)
{
  if (pos < 0 || pos > length(*list))
    return;
  if (pos == 0)
  {
    addToStartOfList(list, node);
  }
  else
  {
    int idx = 0;
    Node *aux = *list;
    while ((*list)->next && idx < pos - 1)
    {
      idx++;
      *list = (*list)->next;
    }
    if (!(*list)->next)
    {
      addToEndOfList(list, node);
    }
    else
    {
      node->next = (*list)->next;
      (*list)->next = node;
    }
    *list = aux;
  }
}

void addBeforeKey(Node **list, Node *node, char const *key)
{
  return addToPos(list, node, search(*list, key));
}

void addAfterKey(Node **list, Node *node, char const *key)
{
  int pos = search(*list, key);
  pos++;
  return addToPos(list, node, pos);
}

void addAtTheMiddle(Node* list, Node * node) {
  Node *fast = list, *slow = list;
  while (fast->next && fast->next->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  node->next = slow->next;
  slow->next = node;
}

void addToEndOfList(Node **list, Node *node)
{
  if (!*list)
  {
    *list = node;
  }
  else
  {
    Node *aux = *list;
    while ((*list)->next)
    {
      *list = (*list)->next;
    }
    (*list)->next = node;
    (*list) = aux;
  }
}

void deleteStartNode(Node **list)
{
  if (!*list)
  {
    return;
  }
  Node *firstNode = *list;
  if ((*list)->next)
  {
    *list = (*list)->next;
    deleteNode(&firstNode);
  }
  else
  {
    deleteNode(&(*list));
  }
}

void deleteAtPos(Node **list, int pos)
{
  if (pos < 0 || pos > length(*list))
    return;
  if (pos == 0)
  {
    deleteStartNode(list);
  }
  else
  {
    int idx = 0;
    Node *aux = *list;
    while ((*list)->next && idx < pos - 1)
    {
      idx++;
      *list = (*list)->next;
    }
    if (!(*list)->next)
    {
      deleteEndNode(list);
    }
    else
    {
      Node *nodeToDelete = (*list)->next;
      (*list)->next = (*list)->next->next;
      deleteNode(&nodeToDelete);
    }
    *list = aux;
  }
}

void deleteByKey(Node **list, char const *key)
{
  int pos = search(*list, key);
  pos++;
  return deleteAtPos(list, pos);
}

void deleteEndNode(Node **list)
{
  if (!*list)
  {
    return;
  }
  Node *lastNode = NULL, *aux = *list;
  while ((*list)->next)
  {
    lastNode = *list;
    *list = (*list)->next;
  }
  if (lastNode->next)
  {
    *list = aux;
    deleteNode(&(lastNode->next));
  }
  else
  {
    deleteNode(&(*list));
  }
}

void displayList(Node *list)
{
  if (!list)
    return;
  while (list->next)
  {
    displayStudent(list->info);
    list = list->next;
  }
  displayStudent(list->info);
}

void deleteList(Node **list)
{
  int nr = length(*list);
  for (int i = 0; i < nr; i++)
  {
    deleteStartNode(list);
  }
}

void reverseList(Node **list)
{
  Node *prev = NULL, *curr = *list, *next = NULL;
  while (curr)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  *list = prev;
}

void splitList(Node *source, Node **secondList)
{
  // helps you visualize it
  // 1 -> 2 -> 3 -> 4 -> 5 -> NULL
  Node *fast = source, *slow = source;
  while (fast->next && fast->next->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  *secondList = slow->next;
  slow->next = NULL;
}

void swap(Node *a, Node *b)
{
  StudentInfo *info = a->info;
  a->info = b->info;
  b->info = info;
}

void sort(Node *list)
{
  if (!list || !list->next)
    return;
  Node *aux = NULL; // initialize to NULL
  while (aux != list->next) // continue until aux->next is NULL
  {
    Node *current = list;
    while (current->next != aux)
    {
      if (current->info->income > current->next->info->income)
      {
        swap(current, current->next);
      }
      current = current->next;
    }
    aux = current;
  }
}

// recursive, should return position of the node
int search(Node *list, char const *key)
{
  if (!key || !list)
    return -1;
  if (strcmp(list->info->name, key) == 0)
  {
    return 0;
  }
  int idx = search(list->next, key);
  if (idx == -1)
    return -1;
  return 1 + idx;
}

// int search_iterative(Node *list, char const *key)
// {
//   if(!key || !list)
//     return -1;
//   int idx = 0;
//   while(list->next) {
//     if (strcmp(list->info->name, key) == 0) {
//       return idx;
//     }
//     idx++;
//     list = list->next;
//   }
//   idx++;
//   if (strcmp(list->info->name, key) == 0) {
//       return idx;
//   }
//   return -1;
// }

// --------------------------------------------