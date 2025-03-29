#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct {
    int capacity;
    int arr[CAPACITY];
    int top;
} STACK;

void InitStack(STACK *stack) { stack->top = -1; }

bool isEmpty(STACK *stack) { return stack->top == -1; }

bool isFull(STACK *stack) { return stack->top == CAPACITY - 1; }

void Push(STACK *stack, int value) {
    if (isFull(stack)) {
        printf("cannot push to the stack , stack is full\n");
        return;
    }
    // if the stack is not full, push the items to the top of the stack
    stack->arr[++(stack->top)] = value;
}

int pop(STACK *s) {
    if (isEmpty(s)) {
        printf("stack cxurrently is empty ,nothing to delete\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

int peek(STACK *s) {
    if (isEmpty(s)) {
        printf("stack cxurrently is empty ,nothing to delete\n");
        return -1;
    }
    return s->arr[s->top];
}

int main() {
    STACK s;

    InitStack(&s);
    Push(&s, 33);
    Push(&s, 34);
    Push(&s, 35);
    printf("the top of the stack is %d\n", peek(&s));
    printf("removing from the top of the stack %d\n", pop(&s));
    printf("the top of the stack is %d\n", peek(&s));
    printf("removing from the top of the stack %d\n", pop(&s));
    printf("the top of the stack is %d\n", peek(&s));
    return 0;
}
