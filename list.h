#include<stdio.h>
#define PLUS 1
#define MINUS -1

typedef struct node{
	
	int num;
	struct node* prev;
	struct node* next;
	
}node;

typedef struct number{
	node* head;
	node* tail;
	int decimal;
	int sign;
}number;
hi
