#include <stdio.h>
#include <string.h>

#define BUF_LEN 20

int main() {
    char buffer[BUF_LEN];
    char *p = memset(buffer, 'A', sizeof(buffer));
    printf("after memset\n");
    for (int i = 0; i < 20; i++) {
        printf("%c", *p);
    }
    return 0;
}
