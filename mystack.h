#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 50

typedef enum {OK = 0, ERROR = -1} Status;
typedef enum {NUM = 0, CHAR = 1} Choice;

typedef union {
    float num;
    char operator;
} unit;

typedef struct {
    unit Unit;
    Choice kind;
} Elem;

typedef struct {
    Elem expr[STACK_SIZE];
    int top;
} SqStack;



// Function declaration

/* Initiate an empty stack */
SqStack InitStack(void);

/* Clear a stack that is not empty, if empty, returns ERROR. */
Status ClearStack(SqStack *stack);

/* Push element with value e into stack */
Status Push(SqStack *stack, Elem e);

/* Pop stack top and store in a variable */
Status Pop(SqStack *stack, Elem *e);

/* Discard the stack top element */
Status DiscardStackTop(SqStack *stack);

bool IsStackEmpty(SqStack *stack);

bool IsStackFull(SqStack *stack);

#endif