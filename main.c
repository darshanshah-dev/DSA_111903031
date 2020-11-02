#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
//#include"list.h"
#include"stack.h"

#define maxLen 2001

#define OPERAND 100
#define OPERATOR 200
#define ERR 300
#define END 400

typedef struct token {

	int type;
	number *num;
	char op;


}token;
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };
/*	This is the function which seperates the operands and operators
*	This function will also detect the error in the expression
*	eg. if any character other than operator and operand like 'a',
*	'&' appears it will detect it.
*
*	Also any extra whitespaces are removed.
*   	operands and operators are seperated by zero or more spaces;
*	operand-operand are seperated by atleast one space
*/
token getNext(char *exp, int *reset){

	static int i=0;
	static enum state currState = SPC;
	number *a = (number*)malloc(sizeof(number));
	//init(a);
	token t;
	enum state nextState;
	if(*reset == 1){
	
		currState = SPC;
		*reset = 0;
		i = 0;
	}
	char currChar;
	while(1){
	
		currChar = exp[i];
		switch(currState){

			case NUMBER:
				switch(currChar){
			
					case '0': case '1': case '2':
					case '3': case '4': case '5':
					case '6': case '7': case '8':
					case '9':
						nextState = NUMBER;
						//addDigit(a,currChar);
						i++;	
						break;
					
					case '+': case '-': case '/':
					case '*':
						t.type = OPERAND;
						t.num  = a;
						i++;
						nextState = OP;
						currState = nextState;
						return t;
						break;
						
						
					case '\0':
						t.type = OPERAND;
						t.num  = a;
						nextState = FINISH;
						currState = nextState;
						return t;
						break;
						
					case ' ':
						t.type = OPERAND;
						t.num  = a;
						i++;						
						nextState = SPC;
						currState = nextState;
						return t;
						break;
						
					case '.':
						nextState = DOT;
						i++;
						currState = nextState;
						break;			
			
					default:
						nextState = ERROR;
						currState = nextState;
						t.type = OPERAND;
						t.num  = a;
						return t;
						break;
				}
				break;
				
				
			case DOT:
				switch(currChar){
				
					case '0': case '1': case '2':
					case '3': case '4': case '5':
					case '6': case '7': case '8':
					case '9':
						nextState = DOT;
						currState = nextState;
						//addDigit(a,currChar);
						a->decimal++;
						i++;
						break;
						
						
					case '+': case '-': case '/':
					case '*':
						nextState = OP;
						currState = OP;
						t.type = OPERAND;
						t.num = a;
						i++;
						return t;
						break;	
				
					case '\0':
						nextState = FINISH;
						currState = nextState;
						t.type = OPERAND;
						t.num = a;
						return t;
						break;
				
					case ' ':
						nextState = SPC;
						currState = nextState;
						t.type = OPERAND;
						t.num  = a;
						i++;						
						return t;
						break;
						
					// dot after a dot is not a valid number.	
					case '.':
						nextState = ERROR;
						currState = nextState;
						t.type = OPERAND;
						t.num = a;
						return t;
						break;
						
					default:
						nextState = ERROR;
						currState = nextState;
						t.type = OPERAND;
						t.num = a;
						return t;
						break;
				}
				break;
			case OP:
				switch(currChar){
				
					case '0': case '1': case '2':
					case '3': case '4': case '5':
					case '6': case '7': case '8':
					case '9':
						nextState = NUMBER;
						currState = nextState;
						t.type    = OPERATOR;
						t.op      = exp[i-1];
						//here we dont increase i because we have to retain the number.
						//i++;
						return t;
						
					case '+': case '-': case '/':
					case '*':
						nextState = OP;
						currState = nextState;
						t.type = OPERATOR;
						t.op   = exp[i-1];
						i++;
						return t;
						break;
						
					case '\0':
						nextState = FINISH;
						currState = nextState;
						t.type = OPERATOR;
						t.op = exp[i-1];
						return t;
						break;
						
					case ' ':
						nextState = SPC;
						currState = nextState;
						t.type = OPERATOR;
						t.op  = exp[i-1];
						i++;						
						return t;
						break;
						
					case '.':
						nextState = DOT;
						t.type = OPERATOR;
						t.op = exp[i -1];
						currState = nextState;
						i++;
						return t;
						break;
						
					default: 
						nextState = ERROR;
						t.type = OPERATOR;
						t.op = exp[i - 1];
						currState = nextState;
						return t;
						break;		
				
				}
				break;
				
			case FINISH:
				t.type = END;
				return t;
				break;
				
			case ERROR:
				t.type = ERR;
				return t;
				break;
				
			case SPC:
				switch(currChar){
				
				
					case '0': case '1': case '2':
					case '3': case '4': case '5':
					case '6': case '7': case '8':
					case '9':
						nextState = NUMBER;
						currState = nextState;
						//addDigit(a,currChar);
						i++;
						break;
						
					case '+': case '-': case '/':
					case '*':
						nextState = OP;
						currState = nextState;
						i++;
						break;		
						
					case '\0':
						nextState = FINISH;
						currState = nextState;
						break;
						
					case ' ':
						nextState = SPC;
						currState = nextState;
						i++;
						break;
						
					case '.':
						nextState = DOT;
						currState = DOT;
						i++;
						break;
						
					default:
						nextState = ERROR;
						break;
				}
				//if we break from here we will go into while 1 and then again for switch case.
				currState = nextState;
				break;
		}
		
	}
}


void infix(char *input){

	
}
/*
*	This function is used to take input.
*	It will read character by character and make the array a null terminated string
*	It will return the number of characters read.
*/
int readInput(char * input, int len){

	int i = 0;
	while( i <= len-2){
	
		char ch = getchar();
		if(ch == '\n'){
			
			input[i++] = '\0';
			return i-1;
			break;
		}
		else{
		
			input[i++] = ch;
		}
	
	}
	input[i++] = '\0';
	return i-1;
	

}
/*	This function is used to handle the case when we will have an operand(+ or -)
*	just after an opening bracket.
*	To handle this case we insert a 0 after the opening bracket.
*/
void edit(char *input){

	int i;
	for(i = 0; i < strlen(input); i++) {
		if(input[i] == '(') {
			int j = 1;
			while(1) {
				if(input[i + j] == ' ') {
					j++;
				}
				else {
					break;
				}
			}
			if((input[i + j] == '-') || (input[i + j] == '+')) {
				
				/*This is the case when there is a '+' or '-' without any space after '(' and 
				*the '\0' character is present at the last index in input array
				*Due to this we can't shift elements to right hand side by one position.
				* eg. if suppose the maxLen is 11
				* expression (-123+122)
				* as here we will need to shift the characters but if we shift the characters then there will be no space left to
				* add the null character at the end.
				*/
				if(j == 1 && input[maxLen] == '\0'){
				printf("Error in expression\n");
				return ;
				}
				
				int temp = strlen(input);
				while(temp >= i + j) {
					input[temp + 1] = input[temp];
					temp--;
				}
				input[i + j] = '0'; 
			} 
		}
	}


}
int main(int argc,char *argv[])
{
	printf("This is a simple bc calculator\n");
	//this takes the input , we can input having maximum length 2000.
	char input[maxLen];	
	readInput(input,maxLen);
	edit(input);
	printf("%s",input);
	infix(input);
	
	//printf("%s",input);
}
