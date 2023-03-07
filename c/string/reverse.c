#include <stdio.h>
#include <string.h>
#define swap(a, b) do {int t=a; a=b; b=t;} while (0)

/*
void reverse(char* s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}
*/
void reverse(char* begin, char* end) {
    while (begin < end) {
        swap(*begin++, *end++);
    }
}


int main() {
    char s[] = "helloworld";
    reverse(s, s + 9);
    puts(s);
}
