#include <hashmap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static hashmap_item *bucket(const char *k, const char *v) {

  hashmap_item *i = malloc(sizeof(hashmap_item));
  i->key = strdup(k);
  i->value = strdup(v);
  return i;
}

hashmap_table *newtable() {
  hashmap_table *ht = malloc(sizeof(hashmap_table));
  ht->size = 53;
  ht->count = 0;
  ht->items = calloc(sizeof(size_t), sizeof(hashmap_item));
  return ht;
}

static void ht_del_item(hashmap_item *i) {
  free(i->value);
  free(i->key);
  free(i);
}

void ht_del_hash_item(hashmap_table *ht) {
  for (int i = 0; i < ht->size; i++) {
    hashmap_item *item = ht->items[i];
    if (item != NULL) {
      ht_del_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

