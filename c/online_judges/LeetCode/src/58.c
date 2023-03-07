
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int lengthOfLastWord(char* s) {

    int length = 0;
    int inWord = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            if (inWord) {
                length++;
            } else {
                inWord = 1;
                length = 1;
            }
        } else {
            inWord = 0;
        }
    }
    return length;
}


