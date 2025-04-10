#include <stdint.h>
#include <stdio.h>

int main() {
    uint8_t value = 0x3A;
    uint8_t mask = 0x0F;
    uint8_t result = value & mask;

    if (value & (1 << 3)) {
        printf("bit 3 is  set");
    }
    printf("%ld\n", sizeof(value));

    return 0;
}
