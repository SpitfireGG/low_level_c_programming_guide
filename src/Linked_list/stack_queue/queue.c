#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include <stdlib.h>

struct Queue {
    int *arr;
    int head;
    int tail;
    int size;
    int cap;
};

bool isEmpty(struct Queue *q) {
    if (q->head == -1) {
        printf("the queue is currently empty , try adding\n");
    }
    return (q->head == -1);
}

bool isFull(struct Queue *q) { return (q->tail == q->cap - 1); }

void initQueue(struct Queue *q, int cap) {
    q->arr = (int *)malloc(q->cap * (sizeof(int)));
    q->head = -1;
    q->tail = -1;
    q->size = 0;
    q->cap = cap;
}

// insert at the tail
void Enqueue(struct Queue *q, int value) {
    if (isFull(q)) {
        printf("FULL !!!\n");
        return;
    }
    if (isEmpty(q)) {
        q->head = 0;
    }
    q->arr[++(q->tail)] = value;
    q->size++; // incrementing the size of the items  in the array  ,cuz  we
               // just added an element
}

// remove form the head
int Dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("empty\n");
        return -1;
    }
    int removedVal =
        q->arr[q->head++]; // removedval will be the value of head++ now
    q->size--;

    if (q->size == 0) {
        q->head = -1;
        q->tail = -1;
    }
    return removedVal;
}
int peek(struct Queue *q) {

    if (isEmpty(q)) {
        printf("empty\n");
        return -1;
    }

    return q->arr[q->head];
}

int main() {
    struct Queue q;
    initQueue(&q, 190);
    Enqueue(&q, 44);
    Enqueue(&q, 54);
    Enqueue(&q, 56);
    for (int i = 0; i < q.size; i++) {
        printf("[%d]-> ", q.arr[i]);
    }
    printf("NULL\n");
    Dequeue(&q);
    printf("After removing the element from the list\n");
    for (int i = 0; i < q.size; i++) {
        printf("[%d]-> ", q.arr[i]);
    }
    return 0;
}
