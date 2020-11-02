#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"list.h"

void init(number*a){
	a->head = NULL;
	a->tail = NULL;
	a->sign = PLUS;
	a->decimal = 0;
}
