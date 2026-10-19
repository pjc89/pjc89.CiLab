#include <stdio.h>
#include <zlib.h>

int main(void) {
    printf("cilab ok, zlib %s\n", zlibVersion());
    return 0;
}
