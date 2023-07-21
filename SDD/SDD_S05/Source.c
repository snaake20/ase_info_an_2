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

struct Node {
	struct Node* prev;
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node ListNode;
//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudents(StudentInfo**, int);
void printList(ListNode*);

void displayStudent(StudentInfo*);
ListNode* createNode(StudentInfo*);

void insertNodeByPos(ListNode**, ListNode*, int);

#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	ListNode* list = NULL;
	if (pFile)
	{
		StudentInfo* agenda[10];
		memset(agenda, NULL, sizeof(agenda));
		char* token; char delimiter[] = ",\n";
		double income; unsigned short ref;
		char lineBuffer[LINE_SIZE], name[LINE_SIZE];
		int index = 0;
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile))
		{
			token = strtok(lineBuffer, delimiter);
			strcpy(name, token);
			token = strtok(NULL, delimiter);
			income = atof(token);
			token = strtok(NULL, delimiter);
			ref = atoi(token);
			StudentInfo* stud = createStudentInfo(name, income, ref);
			ListNode* node = createNode(stud);
			insertNodeByPos(&list, node, index);
			agenda[index++] = stud;
		}
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		printList(list);
		fclose(pFile);
	}
}
void displayStudents(StudentInfo** agenda, int noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		if (agenda[i])
		{
			printf("Name: %s, income: %f\n", agenda[i]->name, agenda[i]->income);
			if (agenda[i]->reference.extRef >> 15 == 1)
			{
				short uid = agenda[i]->reference.extRef >> 8 & 127;
				printf("University ref: %d\n", uid);
				printf("External ref: %d\n", agenda[i]->reference.extRef & 255);
			}
			else
			{
				printf("Internal ref: %d\n", agenda[i]->reference.intRef);
			}
		}
	}
}

ListNode* createNode(StudentInfo* stud) {
	ListNode* res = NULL;
	res = (ListNode*)malloc(sizeof(ListNode));
	res->info = stud;
	res->prev = res->next = NULL;
	return res;
}

void printList(ListNode* list) {
	while (list->next) {
		displayStudent(list->info);
		list = list->next;
	}
	displayStudent(list->info);
	while (list->prev) {
		displayStudent(list->info);
		list = list->prev;
	}
	displayStudent(list->info);
}

void displayStudent(StudentInfo* stud) {
	if (stud) {
		printf("Nume: %s, Salariu: %.2f\n", stud->name, stud->income);
		if (stud->reference.extRef >> 15 == 1) {
			printf("Contractor: %d ", stud->reference.intRef >> 8);
		}
		printf("Referinta: %d\n", stud->reference.extRef & 255);
	}
}

void insertNodeByPos(ListNode** list, ListNode* node, int pos) {
	if (pos <= 0) { // inserare la inceput
		node->next = *list;
		if (*list != NULL) {
			(*list)->prev = node;
		}
		*list = node;
		return;
	}
	else {
		int index = 0;
		ListNode* aux = *list;
		while (aux->next != NULL && index < pos - 1) // index != pos
		{
			aux = aux->next;
			index++;
		}
		if (aux->next == NULL) { // inserare la sfarsit
			aux->next = node;
			node->prev = aux;
		}
		else {
			node->prev = aux;
			node->next = aux->next;
			aux->next->prev = node; // node->next->prev = node;
			aux->next = node;
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

// tema sortare lista + implementeaza lista simpla circulara si dubla circulara