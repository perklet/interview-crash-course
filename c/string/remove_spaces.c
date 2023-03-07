#include <stdio.h>
#include <stdlib.h>

void remove_spaces(char* str) {
    char* p1 = str, *p2 = str;
    do {
        while (*p2 == ' ')
            p2++;
    } while (*p1++ = *p2++);
}

int main() {
    char s[] = "hello  world!";
    puts(s);
    remove_spaces(s);
    puts(s);
    return 0;
}
