/**
 * Beauty of Programming 3.1
 * determine if a string s1 is contained in a string s2 or its rotation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool rotate_contain(char* haystack, char* needle) {
    int size = sizeof(char) * strlen(haystack) * 2 + 1;
    char* double_haystack = malloc(size);
    strcpy(double_haystack, haystack);
    strcat(double_haystack, haystack);
    bool result = (strstr(double_haystack, needle) != NULL);
    free(double_haystack);
    return result;
}

int main() {

    char* needle1 = "dhe";
    char* needle2 = "hello";
    char* needle3 = "lll";
    char* haystack = "helloworld";

    printf("%s in %s: %s\n", needle1, haystack, rotate_contain(haystack, needle1) ? "yes" : "no");
    printf("%s in %s: %s\n", needle2, haystack, rotate_contain(haystack, needle2) ? "yes" : "no");
    printf("%s in %s: %s\n", needle3, haystack, rotate_contain(haystack, needle3) ? "yes" : "no");

    return 0;
}
