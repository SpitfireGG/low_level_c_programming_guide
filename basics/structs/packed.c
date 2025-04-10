#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push, 1) // set byte alignment to 1
typedef struct {      // alignment after byte padding
    int length;       // default byte : 4
    char *data;       // default byte : 4 in 32bit arch and 8 in 68bit arch
    char a;           // default: 1 byte in the memory
    int size;         // default byte : 4
} Header; // total : 4x3+1 = 13 bytes in the memory , if the byte alignment was
          // not set then it would have been 16 bytes
#pragma pack(pop) // restore the default alignment oppsosed by the cpu

int main() {
    const char *str = "somefucking string";
    Header header = {43, (char *)str, 212};
    FILE *file = fopen("cookies.bin", "wb");
    if (!file) {
        perror("failed to open file");
        exit(1);
    }

    size_t written = fwrite(&header, sizeof(header), 1, file);
    if (written != 1) {
        perror("file has been written");
        fclose(file);
        exit(1);
    };

    size_t str_len = strlen(header.data) + 1;
    written = fwrite(header.data, 1, str_len, file);
    if (written != str_len) {
        perror("failed to write");
        fclose(file);
        exit(1);
    }
    printf("Wrote %zu bytes (struct) + %zu bytes (string)\n", sizeof(header),
           str_len);
    fclose(file);
    return 0;

    return 0;
}
