#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node node;

void ins_at_start(node **head, int data) {
    node *newNode = malloc(sizeof(node));
    if (!newNode) {
        printf("malloc failed\n");
        exit(1);
    }
    newNode->data = data; // Set data!
    if (*head == NULL) {
        printf("currently the head is empty, adding a new head\n");
        newNode->next = NULL;
        *head = newNode;
        return;
    }
    newNode->next = *head;
    *head = newNode;
}

void ins_at_end(node **head, int data) {
    node *newNode = malloc(sizeof(node));
    if (!newNode) {
        printf("malloc failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL) {
        printf("currently the head is empty, adding a new head\n");
        *head = newNode;
        return;
    }
    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void del_el(node **head, int data) {
    if (*head == NULL) {
        printf("head is empty, returning\n");
        return;
    }
    node *temp = *head;
    node *prev = NULL;
    if (temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data) { // Fixed: while
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("data could not be found\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void traverse_ll(node *head) { // Single pointer—read-only
    if (head == NULL) {
        printf("head is empty, returning\n");
        return;
    }
    node *temp = head;
    while (temp != NULL) {
        printf("[mem addr: %p] %d -> ", temp, temp->data); // Fixed: temp
        temp = temp->next;                                 // Move temp!
    }
    printf("NULL\n");
}

void free_node_allocs(node **head) { // Double pointer
    node *temp = *head;
    while (temp != NULL) {
        node *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL; // Update caller’s head
}

int main() {
    node *head = NULL;
    ins_at_start(&head, 50);
    ins_at_start(&head, 49);
    ins_at_start(&head, 48);
    ins_at_start(&head, 47);
    ins_at_start(&head, 46);
    ins_at_start(&head, 45);
    ins_at_start(&head, 44);
    ins_at_start(&head, 43);
    traverse_ll(head);
    free_node_allocs(&head); // Clean up
    return 0;
}
