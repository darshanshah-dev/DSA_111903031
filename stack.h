#include<stdio.h>
#include"list.h"

/*	Stack to store numbers.
*	
*
*/

typedef struct inode{

	struct inode* i;
	number *a;
}inode;


typedef struct istack{
	
	inode* top;
	int size;	

}istack;


void initIstack(istack *s);
void istackPush(istack *s, number *a);
number* istackPop(istack *s);
number* istackTop(istack s);
int istackEmpty(istack s);



typedef struct cnode{

	struct cnode* i;
	char a;

}cnode;

typedef struct cstack{
	
	cnode *top;
	int size;
	
}cstack;

void initCstack(cstack *s);
void cstackPush(cstack *s,char a);
char cstackPop(cstack *s);
char cstackTop(cstack s);
int cstackEmpty(cstack s);



