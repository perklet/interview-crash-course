#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 16

int digitify(char* s, int* d) {
    int strTerminated = 0;
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (strTerminated) break;
        switch(s[i]) {
        case 'M':
            d[i] = 1000;
            break;
        case 'D':
            d[i] = 500;
            break;
        case 'C':
            d[i] = 100;
            break;
        case 'L':
            d[i] = 50;
            break;
        case 'X':
            d[i] = 10;
            break;
        case 'V':
            d[i] = 5;
            break;
        case 'I':
            d[i] = 1;
            break;
        case '\0':
            strTerminated = 1;
            break;
        default:
            break;
        }
    }
}

int romanToInt(char* s) {
    int result;
    int digitified[MAX_LENGTH] = {0};
    digitify(s, digitified);

    result = digitified[MAX_LENGTH-1];
    for (int i = MAX_LENGTH - 2; i >= 0; i--) {

        if (digitified[i] >= digitified[i+1]) {
            result += digitified[i];  // VI or II
        } else {
            result -= digitified[i]; // IV
        }
    }
    return result;
}
