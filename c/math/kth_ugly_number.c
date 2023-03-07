/**
 * get nth ugly number
 * https://leetcode.com/problems/ugly-number-ii/
 */

#define MIN(a,b) ((a)<(b)?(a):(b))

/**
 * Using merge-sort-like method
 */
int kth_ugly_number(int k) {
    if (k <= 0)
        return -1;
    if (k < 6)
        return n;

    int s2 = 0, s3 = 0, s5 = 0;
    int* uglies = malloc(sizeof(int) * k);
    uglies[0] = 1;
    for (int i = 1; i < k; i++) {
        uglies[i] = MIN(uglies[s2]*2, MIN(uglies[s3]*3, uglies[s5]*5));
        if (uglies[i] == uglies[s2] * 2) s2++;
        if (uglies[i] == uglies[s3] * 3) s3++;
        if (uglies[i] == uglies[s5] * 5) s5++;
    }

    return uglies[k-1];
}

