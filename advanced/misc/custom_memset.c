#include <stdio.h>

#define BUF 12

void *custom_memset(void *buffer, int s, unsigned int n) {

    // castig the void pointer buf into unsiged char
    unsigned char *buf = buffer;

    while (n--) {
        (*buf++) = (unsigned int)s;
    }
    return buffer;
}

int main() {
    char buffer[BUF] = "somethingisd";
    printf("testing !!!!\n");

    custom_memset(buffer, 0, sizeof(buffer));
    printf("After custom_memset ");
    for (int i = 0; i < 12; i++) {
        printf("%d\n", buffer[i]);
    }

    return 0;
}
