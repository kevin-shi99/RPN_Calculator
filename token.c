#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "mystack.h"
#include "calc.h"
#include "token.h"


SqStack stack_rpn;


/* Prototypes */
bool IsSuperior(char operator);



void convert_to_rpn(Elem *origin, Elem *rpn)
{
    Elem *p = origin, *q = rpn;

    stack_rpn = InitStack();
    for (; (p->Unit.operator != '\0' && p->kind == CHAR) || p->kind == NUM; p++) {
        // if is a number, output directly
        if (p->kind == NUM) {
            *q++ = *p;
        }
        // if is a left bracket, push into stack
        else if (p->kind == CHAR && p->Unit.operator == '(') {
            Push(&stack_rpn, *p);
        }
        // if is a right bracket, pop out characters until meets left bracket
        else if (p->kind == CHAR && p->Unit.operator ==')') {
            while (stack_rpn.expr[stack_rpn.top].Unit.operator != '(') {
                Pop(&stack_rpn, q++);
            }
            DiscardStackTop(&stack_rpn); // Discard the left bracket
        }
        else if (IsOperator(p->Unit.operator)) {
            // If the  current operator is superior to the stacktop operator, push the current operator into stack
            if (IsSuperior(p->Unit.operator)) {
                Push(&stack_rpn, *p);
            }
            else {
                // If is not superior, pop until current operator is superior to that of stacktop. That is to say, pop while is not superior to stack top.
                while (!IsSuperior(p->Unit.operator)) {
                    Pop(&stack_rpn, q++);
                }
                Push(&stack_rpn, *p);
            }
        }
    }
    while (!IsStackEmpty(&stack_rpn)) {
        Pop(&stack_rpn, q++);
    }
    // Append a null character at the end of array
    q->kind = CHAR;
    q->Unit.operator = '\0';
}

bool IsSuperior(char operator)
{
    char stackTop;
    stackTop = stack_rpn.expr[stack_rpn.top].Unit.operator;
    if (IsStackEmpty(&stack_rpn)) {
        return true;
    }
    else if (stackTop == '(') {
        // '(' is inferior to all operator so that other operators can get in the stack
        return true;
    }
    switch (operator) {
        case '+':
        case '-': return false;
        case '*':
        case '/':
            if (stackTop == '+' || stackTop == '-') return true;
            else return false;
        default: return true;
    }
}