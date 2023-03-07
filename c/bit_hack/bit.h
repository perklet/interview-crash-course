/**
 * this file implements common bit hacks
 */
#ifndef BIT_H
#define BIT_H

inline bool is_even(int n) {
    return n & 0x01 == 0;
}

inline bool nth_bit_set(int n) {
    return n & (1 << n);
}

inline int set_nth_bit(int x, int n) {
    return x | (1 << n);
}

inline int unset_nth_bit(int x, int n) {
    return x & ~(1 << n);
}

inline int toggle_nth_bit(int x, int n) {
    return x ^ (1 << n);
}

inline int unset_rightmost(int x) {
    return x & (x - 1);
}

inline int set_rightmost(int x) {
    return x | (x + 1);
}

inline bool is_power2(int n) {
    return n & (n - 1) == 0;
}

inline int isolate_rightmost_1(int x) {
    return x & (-x);
}

inline int isolate_rightmost_0(int x) {
    return ~x & (x + 1);
}

inline int pad_rightmost(int x) {
    return x | (x - 1);
}

int count_1bits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}
#endif
