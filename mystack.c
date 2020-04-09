#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mystack.h"

/* Initiate a stack */
SqStack InitStack(void)
{
    SqStack newStack;
    newStack.top = -1;

    for (int i=0; i<STACK_SIZE; i++) {
        newStack.expr[i].Unit.num = 0;
        newStack.expr[i].kind = NUM;
    }
    return newStack;
}

/* returns true if stack is empty */
bool IsStackEmpty(SqStack *stack)
{
    return (stack->top == -1) ? true : false;
}

/* returns true if stack is full */
bool IsStackFull(SqStack *stack)
{
    return (stack->top == STACK_SIZE-1) ? true : false;
}

Status ClearStack(SqStack *stack)
{
    if (IsStackEmpty(stack)) return ERROR;
    for (int i=0; i<STACK_SIZE; i++) {
        stack->expr[i].Unit.num = 0;
        stack->top = -1;
    }

    return OK;
}

Status Push(SqStack *stack, Elem e)
{
    if (IsStackFull(stack)) {
        fprintf(stderr, "ERROR: Stack overflow!\n");
        return ERROR;
    }
    stack->expr[++(stack->top)] = e;
    
    return OK;
}

Status Pop(SqStack *stack, Elem *e)
{
    if (IsStackEmpty(stack)) {
        fprintf(stderr, "ERROR: Stack Underflow!\n");
        return ERROR;
    }
    *e = stack->expr[stack->top--];

    return OK;
}

Status DiscardStackTop(SqStack *stack)
{
    if (IsStackEmpty(stack)) return ERROR;

    stack->top--;

    return OK;
}