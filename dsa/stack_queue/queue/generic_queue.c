#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Enum to indicate data type
typedef enum {
    TYPE_INT,   // For integers
    TYPE_STRING // For strings (char *)
} DataType;

struct Queue_Node {
    void *data;    // Generic pointer to data
    DataType type; // Type indicator
    struct Queue_Node *next;
};

typedef struct Queue_Node Qnode;

typedef struct Queue {
    Qnode *head, *tail;
} Queue;

void InitQueue(Queue *q) { q->head = q->tail = NULL; }

void Enqueue(Queue *q, void *data, DataType type) {
    Qnode *newNode = (Qnode *)malloc(sizeof(Qnode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data; // Store the pointer
    newNode->type = type; // Store the type
    newNode->next = NULL;
    if (q->tail == NULL) { // if the tail is empty, add the same node as the
                           // head and the tail
        q->head = q->tail = newNode;
    } else { // Non-empty queue
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void *Dequeue(Queue *q) {
    if (q->head == NULL) {
        return NULL;
    }

    Qnode *temp = q->head;
    void *value = temp->data; // Return the data pointer
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
        switch (current->type) {
        case TYPE_INT:
            printf("%d -> ", *(int *)current->data); // Dereference int*
            break;
        case TYPE_STRING:
            printf("%s -> ", (char *)current->data); // Cast to char*
            break;
        default:
            printf("Unknown type -> ");
            break;
        }
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Queue q;
    InitQueue(&q);

    int *num = malloc(sizeof(int));
    *num = 44;

    Enqueue(&q, "string", TYPE_STRING);   // String literal
    Enqueue(&q, num, TYPE_INT);           // Pointer to int
    Enqueue(&q, "stringer", TYPE_STRING); // String literal

    peek(&q);

    void *data;
    while ((data = Dequeue(&q)) != NULL) {
        if (data == num) {
            free(data);
        }
    }
    destroyQ(&q);

    return 0;
}
