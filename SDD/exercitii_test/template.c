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
  struct Node *next; // modify this struct as you wish
};

typedef struct Node Node;

// --------------------------------------------

// here will add data structure fn declarations
// --------------------------------------------

void addToDataStructure(Node **list, StudentInfo *student, void (*func)(Node **, Node *));

Node *createNode(StudentInfo *);

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
      // adaugare in agenda (dinamic)
      adaugaStudent(agenda, noEl, createStudentInfo(nume, salariu, referinta));
      // adaugare in structura de date
      addToDataStructure(dataStructure, createStudentInfo(nume, salariu, referinta), NULL); // replace here null with the function you will use to add to the ds
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

  Node *dataStructure = NULL;

  readStudents(&agenda, &noEl, &dataStructure);

  printf("Nr of students: %d\n", noEl); // should comment this line (debug)
  printf("Agenda: %p\n", agenda);       // should comment this line (debug)
  displayStudents(agenda, noEl);        // should comment this line (debug)

  // here will add data structure fn calls (playground (￣y▽￣)╭ Ohohoho.....)
  // --------------------------------------------

  // --------------------------------------------

  deleteStudents(&agenda, &noEl);

  printf("Nr of students: %d\n", noEl); // should comment this line (debug)
  printf("Agenda: %p\n", agenda);       // should comment this line (debug)
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

// --------------------------------------------