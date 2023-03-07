/**
 * digital root is used for checksum
 * 
 * https://leetcode.com/problems/add-digits/
 */
int digital_root(int n) {
    return 1 + (n - 1) % 9; // base k, mod `k - 1`
}
