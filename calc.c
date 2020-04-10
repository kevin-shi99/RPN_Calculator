#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "mystack.h"
#include "token.h"
#include "calc.h"

Elem reverse[MAXLINE+1]; // Array to store rpn expression
Elem original[MAXLINE+1];

// Prototypes
/* Get expression, skip whitespace, returns number of characters read in. Read in at most MAXLINE characters.*/
int readline(void);

/* convert character to number */
double StrToNum(char *str);

float calc_rpn(Elem *rpn);

Elem calculate(Elem *a, char operator, Elem *b);


// Functions
/* Calculate the value of RPN expression. */
float calc_rpn(Elem *rpn)
{
    Elem *ptr = reverse;
    Elem inter; // intermediate result
    Elem num1, num2;
    SqStack stack_num;
    stack_num.top = -1;

    while ((ptr->Unit.operator != '\0' && ptr->kind == CHAR) || ptr->kind == NUM) {
        if (ptr->kind == NUM) {
            Push(&stack_num, *ptr);
        }
        else if (ptr->kind == CHAR) {
            Pop(&stack_num, &num1);
            Pop(&stack_num, &num2);
            inter = calculate(&num2, ptr->Unit.operator, &num1);
            Push(&stack_num, inter);
        }
        ptr++;
    }
    return stack_num.expr[stack_num.top].Unit.num;
}

Elem calculate(Elem *a, char operator, Elem *b)
{
    Elem inter;
    inter.kind = NUM;

    switch (operator)
    {
    case '+':
        inter.Unit.num = a->Unit.num + b->Unit.num;
        break;
    case '-':
        inter.Unit.num = a->Unit.num - b->Unit.num;
        break;
    case '*':
        inter.Unit.num = a->Unit.num * b->Unit.num;
        break;
    case '/':
        inter.Unit.num = a->Unit.num / b->Unit.num;
        break;
    }

    return inter;
}


/* MAIN */
/*  Read in user input, print result. Dealing with abnormal situation  */
int main(int argc, char *argv[])
{
    char cmd = '\0';
    float result;

    for (;;) {
        printf("Enter command:\n\tq -- quit\n\tAny other key -- calculate\n");
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'q' || cmd == 'Q') return 0;

        printf("Enter a math expression below:\n");
        
        // Read in math expression and convert to RPN (token.c & mystack.c)
        readline();
        convert_to_rpn(original, reverse);
        // Calculate RPN expression (calc.c & mystack.c)
        result = calc_rpn(reverse);

        printf("Result: %.4f\n\n", result);
    }
    return 0;
}

int readline(void)
{
    char ch;
    char temp[10] = {'\0'};
    int cnt = 0;
    int p;

    while ((ch=getchar()) != '\n') {
        /* Initialize temp */
        for (int i=0; i<10; i++) temp[i] = '\0';
        if (cnt<MAXLINE) {
            if (IsNum(ch)) {
                temp[0] = ch;
                p = 1;
                while (IsNum(ch=getchar())) {
                    temp[p++] = ch;
                }
                original[cnt].Unit.num = StrToNum(temp);
                original[cnt++].kind = NUM;
                if (IsOperator(ch)) {
                    original[cnt].Unit.operator = ch;
                    original[cnt].kind = CHAR;
                    cnt++;
                }
            }
            else if (IsOperator(ch)) {
                original[cnt].Unit.operator = ch;
                original[cnt].kind = CHAR;
                cnt++;
            }
        }
    }
    // Append a Null character at the end of the array to mark the end
    original[cnt].kind = CHAR;
    original[cnt].Unit.operator = '\0';
    return cnt;
}

bool IsNum(char ch)
{
    if (ch>='0' && ch<='9' || ch == '.') return true;
    else return false;
}

bool IsOperator(char ch)
{
    if (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='(' || ch==')')
        return true;
    else return false;
}

double StrToNum(char *str)
{
    char *p = str, *q;
    double result = 0;
    int cnt = 0;

    for (; *p != '.' && *p != '\0'; p++) {
        cnt++;
    }
    q = p+1;
    for (int i = 0; p != str; i++) {
        result += (*(--p) - '0') * pow(10, i);
    }

    if (cnt < strlen(str)) {
        for (cnt = 0; *q != '\0'; q++) {
            cnt++;
        }
        q--;
        for (int i=cnt; i>0; i--) {
            result += (*(q--) - '0') * pow(10, 0-i);
        }
    }
    return result;
}