#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int nums[32768], dp[32768];
    int count = 0;
    while (cin >> nums[0], nums[0] != -1) {
        int n = 1, ans = 0;
        while (cin >> nums[n], nums[n++] != -1)
            ;
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[i] < nums[j] && dp[i] <= dp[j])
                    dp[i] = dp[j] + 1;
            }
            ans = max(ans, dp[i]);
        }

        printf("Test #%d:\n  maximum possible interceptions: %d\n\n" , count++, ans-1);
    }
    return 0;
}


