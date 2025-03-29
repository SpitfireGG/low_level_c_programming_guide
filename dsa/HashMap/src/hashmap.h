#include <stddef.h>
#include <stdio.h>

#define TABLE_SIZE 16

typedef struct {
  char *key;
  char *value;
  struct bucket *next;
} hashmap_item;

typedef struct {
  hashmap_item **items;
  int count;
  size_t size;
} hashmap_table;
