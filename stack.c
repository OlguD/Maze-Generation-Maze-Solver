#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

void initializeStack(Stack *stack){
    stack->top = -1;
}


bool isEmpty(Stack *stack){
    return stack->top == -1;
}

bool isFull(Stack *stack){
    return stack->top == MAX_SIZE - 1;
}


void push(Stack *stack, int value){
    if (isFull(stack)){
        printf("Stack overflow");
        return;
    }
    stack->arr[++stack->top] = value;
}

int peek(Stack *stack){
    if (isEmpty(stack)){
        printf("Stack is empty");
        return -1;
    }

    return stack->arr[stack->top];

}

int pop(Stack *stack) {
    // Check for stack underflow
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    // Return the top element
    int popped = stack->arr[stack->top];
    // decrement top pointer
    stack->top--;
    return popped;
}
