#include <stdio.h>
#include <string.h>

#define BUF_LEN 126

int main() {
  char *src = "some fucking string";
  char dest[BUF_LEN];
  strcpy(dest, src);
  strncpy(dest, src, 4);
  printf("%s\n", dest);
  int err = strcmp(src, dest);
  if (err == 0) {
    printf("string are equal");
  }

  char str[] = "Hello";
  char *p = strchr(str, 'l'); // p points to the first 'l' in "Hello"
  printf("printing %c\n", *p);

  char cistr[] = "Hello World";
  char *aptr = strstr(cistr, "World"); // p points to "World"

  printf("printing %s\n", aptr);

  char somefuckingstring[] = "fucking,string,some,dome";
  char *token = strtok(somefuckingstring, ",");
  while (token != NULL) {
    printf("%s\n", token);
    /*     token = strtok(NULL, ","); */
  }
}
