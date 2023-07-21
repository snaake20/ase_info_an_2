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
	struct Node* prev;
	StudentInfo* info;
	struct Node* next;
};

typedef struct Node Queue;
typedef struct Node StackNode;

struct Dummy
{
	struct Node* top;
	struct Node* base;
};

typedef struct Dummy Stack;

//useful info memory management
StudentInfo* createStudentInfo(const char*, double, unsigned short);
void* deleteStudentInfo(StudentInfo*);
void displayStudents(StudentInfo**, int);
void displayStudent(StudentInfo*);
Queue* createNode(StudentInfo*);
void putNode(Queue**, Queue*);
Queue* getNode(Queue**);
StudentInfo* peekQueue(Queue**);

#define LINE_SIZE 128

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	Queue* circularDoubleLinkedList = NULL;
	Stack stack = { .base = NULL, .top = NULL };
	//stack.base = NULL;
	//stack.top = NULL;

	if (pFile)
	{
		StudentInfo* agenda[10];
		memset(agenda, 0, sizeof(agenda));
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
			//Queue* node = createNode(stud);
			//putNode(&circularDoubleLinkedList, node);
			StackNode* node = createNode(stud);
			stack = pushStack(stack, node);
			agenda[index++] = stud;
		}
		//displayStudents(agenda, sizeof(agenda) / sizeof(StudentInfo*));
		
		Queue* node = NULL;
		while ((node = getNode(&circularDoubleLinkedList)) != NULL)
		{
			displayStudent(node->info);
			free(node->info->name);
			free(node->info);
			free(node);
		}
		fclose(pFile);
	}
}

StackNode* popStack(Stack* stack)
{
	StackNode* result = NULL;
	if (stack->top != NULL)
		result = stack->top;
	//stiva cu 1 el.
	if (stack->base == stack->top && stack->base != NULL)
	{
		stack->base = stack->top = NULL;
	}
	//stiva cu mai mult de 1 el.
	else if(stack->base != NULL)
	{
		stack->top->next->prev = stack->base;
		stack->base->next = stack->top->next;
		stack->top = stack->top->next;
	}
	return result;
}

Stack pushStack(Stack stack, StackNode* node)
{
	if (stack.top == NULL || stack.base == NULL)
	{
		stack.base = stack.top = node->next = node->prev = node;
	}
	else
	{
		node->next = stack.top;
		node->prev = stack.base;
		stack.top->prev = node;
		stack.base->next = node;
		stack.top = node;
	}
	return stack;
}

StudentInfo* peekQueue(Queue** queue)
{
	StudentInfo* result = NULL;
	if (*queue != NULL)
	{
		result = (*queue)->info;
	}
	return result;
}


Queue* getNode(Queue** queue)
{
	Queue* result = NULL;
	if (*queue != NULL)
	{
		result = *queue;
		if ((*queue)->next == (*queue))
			*queue = NULL;
		else
		{
			(*queue)->next->prev = (*queue)->prev;
			(*queue)->prev->next = (*queue)->next;
			*queue = (*queue)->next;
		}
	}
	return result;
}

void putNode(Queue** queue, Queue* node)
{
	if (*queue == NULL)
	{
		*queue = node;
		(*queue)->next = (*queue)->prev = (*queue);
	}
	else
	{
		node->next = *queue;
		node->prev = (*queue)->prev;
		
		(*queue)->prev->next = node;
		(*queue)->prev = node;

	}
}

Queue* createNode(StudentInfo* stud)
{
	Queue* result = NULL;
	result = (Queue*)malloc(sizeof(Queue));
	result->info = stud;
	result->next = result->prev = NULL;
	return result;
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
void displayStudents(StudentInfo** agenda, int noEl)
{
	for (int i = 0; i < noEl; i++)
	{
		displayStudent(agenda[i]);
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