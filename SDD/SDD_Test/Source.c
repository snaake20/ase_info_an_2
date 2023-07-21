#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

union Reference
{
  unsigned char intRef;
  unsigned short extRef;
};

typedef union Reference RefInfo;

struct Student
{
  char* name;
  double income;
  RefInfo reference;
};

typedef struct Student StudentInfo;

struct Node
{
  StudentInfo* info;
  struct Node* next;
};

typedef struct Node ListNode;

// useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayExternalPositions(ListNode**, int);
void displayStudent(StudentInfo*);

// related to Nodes

ListNode* createNode(StudentInfo*);
void deleteNode(ListNode*);
void addToTable(ListNode**, ListNode*);
void displayStudents(ListNode**, int);

#define LINE_SIZE 128
#define AGENDA_SIZE 26
void main()
{
  FILE* pFile = fopen("Data.txt", "r");
  if (pFile)
  {
    ListNode* agenda[AGENDA_SIZE];
    memset(agenda, 0, AGENDA_SIZE * sizeof(ListNode*));

    char* token;
    char delimiter[] = ",\n";
    double income;
    unsigned short ref;
    char lineBuffer[LINE_SIZE], name[LINE_SIZE];
    while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
    {
      token = strtok(lineBuffer, delimiter);
      strcpy(name, token);
      token = strtok(NULL, delimiter);
      income = atof(token);
      token = strtok(NULL, delimiter);
      ref = atoi(token);
      StudentInfo* stud = createStudentInfo(name, income, ref);
      addToTable(agenda, createNode(stud));
    }
    displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
    printf("\n");
    displayExternalPositions(agenda, sizeof(agenda) / sizeof(StudentInfo*));
    fclose(pFile);
  }
}
void displayStudent(StudentInfo* stud)
{
  if (stud)
  {
    printf("Name: %s, income: %f\n", stud->name, stud->income);
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
// doar listele care au studenti externi
void displayExternalPositions(ListNode** agenda, int noEl)
{
  for (int i = 0; i < noEl; i++)
  {
    int check = 1;
    ListNode* current = agenda[i], *head = agenda[i];
    while (current != NULL)
    {
      if (current->next == head) {
        if (current->info->reference.extRef >> 15 != 1) {
          check = 0;
        }
        break;
      }
      if (current->info->reference.extRef >> 15 != 1) {
        check = 0;
        break;
      }
      current = current->next;
    }
    if (check) {
      current = agenda[i];
      while (current != NULL)
      {
        if (current->next == head) {
          displayStudent(current->info);
          break;
        }
        displayStudent(current->info);
        current = current->next;
      }
    }
  }
}
void displayStudents(ListNode** agenda, int noEl)
{
  for (int i = 0; i < noEl; i++)
  {
    ListNode* current = agenda[i], *head = agenda[i];
    while (current != NULL)
    {
      if (current->next == head) {
        displayStudent(current->info);
        break;
      }
      displayStudent(current->info);
      current = current->next;
    }
  }
}
void* deleteStudentInfo(StudentInfo* stud)
{
  if (stud != NULL)
  {
    free(stud->name);
    free(stud);
  }
  return NULL;
}

StudentInfo* createStudentInfo(const char* name, double income, unsigned short ref)
{
  StudentInfo* result = NULL;
  result = (StudentInfo*)malloc(sizeof(StudentInfo));
  result->name = (char*)malloc(strlen(name) + 1);
  strcpy(result->name, name);
  result->income = income;
  result->reference.extRef = ref;
  return result;
}

//creates a node with StudentInfo* as a parameter
ListNode* createNode(StudentInfo* student)
{
  ListNode* node = NULL;
  node = (ListNode*)malloc(sizeof(ListNode));
  if (node != NULL)
  {
    node->info = student;
    node->next = NULL;
  }
  return node;
}

//void deleteNode(ListNode** node) {
//  if (*node) {
//    deleteStudentInfo((*node)->info);
//    (*node)->next = NULL;
//    free(*node);
//    *node = NULL;
//  }
//}

void addToTable(ListNode** table, ListNode* node)
{
  int index = node->info->name[0] - 'A';
  if (table[index] == NULL)
  {
    table[index] = node;
    table[index]->next = node;
  }
  else
  {
    ListNode* current = table[index], *head = table[index];
    while (current->next != head)
    {
      current = current->next;
    }
    node->next = head;
    current->next = node;
  }

}