#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

#include <stdbool.h>
typedef struct{

    int arr[MAX_SIZE];
    int top;
}Stack;


void initializeStack(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, int value);
int peek(Stack *stack);
int pop(Stack *stack);
#endif


