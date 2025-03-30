#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Queue_Node {
    int data;
    struct Queue_Node *next;
};

typedef struct Queue_Node Qnode;

typedef struct Queue {
    Qnode *head, *tail;
} Queue;

void InitQueue(Queue *q) { q->head = q->tail = NULL; }

void Enqueue(Queue *q, int data) {
    Qnode *newNode = (Qnode *)malloc(sizeof(Qnode));
    newNode->data = data;
    newNode->next = NULL;
    if (q->tail == NULL) { // if the queue is empty then setting both the head
                           // and the tail to be the newnode
        q->head = q->tail = newNode;
    } else { // if the queue is not empty then set the next pointer to newly
             // added node

        q->tail->next = newNode; // setting q.next to newnode
        q->tail = newNode;       // updating newnode to be the tail node
    }
}

int Dequeue(Queue *q) {

    if (q->head == NULL) {
        return -1;
    }

    Qnode *temp = q->head;  // temp is the head pointer
    int value = temp->data; // value is the provided data
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(temp);
    return value;
}

void destroyQ(Queue *q) {
    while (q->head != NULL) {
        Qnode *temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    q->tail = NULL;
}

void peek(Queue *q) {

    if (q->head == NULL) {
        printf("EMPTY!!!!!\n");
        return;
    }
    Qnode *current = q->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Queue q;
    InitQueue(&q);
    Enqueue(&q, 42);
    Enqueue(&q, 44);
    Enqueue(&q, 65);
    peek(&q);
    return 0;
}
