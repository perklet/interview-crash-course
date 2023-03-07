/**
 * determine if two strings are anagrams
 * https://leetcode.com/problems/valid-anagram/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_anagram(char* s, char* t) {
    char ss[26] = {0};
    char ts[26] = {0};
    while (*s) {
        ss[*s - 'a']++;
        s++;
        ts[*t - 'a']++;
        t++;
    }
    if (*t) return false;
    return memcmp(ss, ts, sizeof(ss)) == 0;
}

int main() {
    char* s = "hello";
    char* t = "hello";
    is_anagram(s, t) ? puts("yes") : puts("no");
    return 0;

}
