#include <stdio.h>

#define BUF 12

typedef enum { TYPE_INT, TYPE_CHAR } G_TYPE;

// generic memset
void *custom_memset(void *buffer, const void *s, unsigned int n, G_TYPE type) {

    // castig the void pointer buf into unsiged char
    unsigned char *buf = (unsigned char *)buffer;

    switch (type) {
    case TYPE_CHAR: {

        unsigned char val = *(const unsigned char *)s;
        for (unsigned int i = 0; i < n; i++) {

            (*buf++) = val;
        }
        break;
    }
    case TYPE_INT: {

        unsigned int val = *(const unsigned int *)s;
        for (unsigned int i = 0; i < n; i++) {
            (*buf++) = val;
        }
        break;
    }
    default: {
        printf("the type definition was not detected\n");
        return NULL;
    }
    }
    return buf;
}

int main() {
    char buffer[BUF] = "somethingisd";
    printf("testing !!!!\n");

    char cval = 'A';
    custom_memset(buffer, &cval, sizeof(buffer), TYPE_INT);

    printf("After custom_memset ");

    for (int i = 0; i < BUF; i++) {
        printf("%c\n", buffer[i]);
    }
    printf("\n");

    int ival = 10;
    custom_memset(buffer, &ival, sizeof(buffer), TYPE_INT);

    printf("After custom_memset ");

    for (int i = 0; i < BUF; i++) {
        printf("%d\n", buffer[i]);
    }
    printf("\n");

    return 0;
}
