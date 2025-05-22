#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Character;

// typedef void (*reallocate)(void *where, unsigned long size);

typedef struct Character {

  // reallocate ralloc;

  enum { Laser, Shadow, Wind, Fire } Ability;

  union {
    char *power;
    int level;
    float stealth;
    char *hidden;
  } Ability_info;

} Character;

/* Character *char_state_before_realloc() {

  void *b_alloc = malloc(sizeof(Character));
  if (!b_alloc) {
    perror("allocation\n");
    return NULL;
  }
  return b_alloc;
} */

// make a reallocation function
/* void *realloca(void *where, unsigned long size) {

  // make allocation
  void *new_ptr = realloc(where, size);
  if (!new_ptr) {
    perror("realocation failed\n");
    return NULL;
  }
  return new_ptr;
} */

Character *create_character() {

  // init a new char instance
  Character *cnc = malloc(sizeof(Character));
  if (!cnc) {
    perror("allocation\n");
    return NULL;
  }

  // make default ability
  cnc->Ability = Fire;

  // init the enum
  switch (cnc->Ability) {
  case (Fire):
    cnc->Ability_info.power = strdup("fire");
    /* cnc->Ability_info.level = 10000;
    cnc->Ability_info.stealth = 10.00;
    strcpy(cnc->Ability_info.hidden, "Jump high asf\0"); */

    printf("selected power type: `fire`\n");
    break;
  case (Shadow):
    cnc->Ability_info.power = strdup("shadow");
    /* cnc->Ability_info.level = 100;
    cnc->Ability_info.stealth = 10000.00;
    strcpy(cnc->Ability_info.hidden, "Jump high asf\0"); */

    printf("selected power type: `shadow`\n");
    break;
  case (Wind):
    cnc->Ability_info.power = strdup("wind");
    /* cnc->Ability_info.level = 1000;
    cnc->Ability_info.stealth = 100.00;
    strcpy(cnc->Ability_info.hidden, "Jump high asf\0"); */

    printf("selected power type: `wind`\n");
    break;
  case (Laser):
    cnc->Ability_info.power = strdup("Laser");
    /* cnc->Ability_info.level = 100;
    cnc->Ability_info.stealth = 10000.00;
    strcpy(cnc->Ability_info.hidden, "penetrate\0"); */

    printf("selected power type: `laser`\n");
    break;

  default:
    printf("choose one of the powers and try again\n");
  }
  return cnc;
}

void destroy_ch(Character *c) {
  if (c) {
    free(c->Ability_info.power);
    free(c);
  }
}

int main() {

  Character *c = create_character();
  if (!c) {
    perror("character creation\n");
    return 1;
  }

  c->Ability = Fire;
  destroy_ch(c);

  return 0;
}
