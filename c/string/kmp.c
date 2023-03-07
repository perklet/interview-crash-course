/**
 * KMP algorithm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void construct(char* pattern, int* lps) {

    int n = strlen(pattern);
    lps[0] = 0;
    int i = 1, len = 0;
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
}

void kmp(char* needle, char* haystack) {

    int n = strlen(needle);
    int m = strlen(haystack);

    int* lps = malloc(sizeof(int) * n);
    construct(needle, lps);

    int i = 0, j = 0;
    while (i < m) {
        if (haystack[i] == needle[j])
            i++, j++;
        if (j == n) {
            printf("`%s` found at %d\n", needle, i - n);
            j = lps[j - 1];
        } else if (i < m && needle[j] != haystack[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    free(lps);
}

int main() {

    char* s = "baidu is fine, google is better.";

    kmp("baidu", s);
    kmp("is", s);
    kmp("google", s);

    return 0;
}

