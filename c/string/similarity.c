/**
 * Beauty of Programming 3.3
 * Compute similarity of two strings as following:
 *     1. replace one char ('a' -> 'b')
 *     2. add one char ('abc' -> 'abcd')
 *     3. remove one char ('travelling' -> 'traveling')
 * similarity = 1 / (changes + 1)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIN(x,y) x<y?x:y

int distance(char* s1, int begin1, int end1, char* s2, int begin2, int end2) {

    // s2 is longer than s1
    if (begin1 > end1) {
        if (begin2 > end2)
            return 0;
        else
            return end2 - begin2 + 1;
    }

    // s1 is longer than s2
    if (begin2 > end2) {
        if (begin1 > end1)
            return 0;
        else
            return end1 - begin1 + 1;
    }

    if (s1[begin1] == s2[begin2]) {
        return distance(s1, begin1 + 1, end1, s2, begin2 + 1, end2);
    } else {
        int d1 = distance(s1, begin1, end1, s2, begin2 + 1, end2);
        int d2 = distance(s1, begin1 + 1, end1, s2, begin2, end2);
        int d3 = distance(s1, begin1 + 1, end1, s2, begin2 + 1, end2);
        return MIN(MIN(d1, d2), d3) + 1;
    }
}

double similarity(char* s1, char* s2) {
    int d = distance(s1, 0, strlen(s1) - 1, s2, 0, strlen(s2) - 1);
    return 1.0 / (d + 1);
}

int main() {
    char* s1 = "hello";
    char* s2 = "hellooo";
    char* s3 = "hellp";
    printf("similarity between %s, %s is %f\n", s1, s2, similarity(s1, s2));
    printf("similarity between %s, %s is %f\n", s1, s3, similarity(s1, s3));
    return 0;
}

