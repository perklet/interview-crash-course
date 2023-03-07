#include <vector>
#include <iostream>
#include <cmath>

using namespace std;


class Solution {
    public:
        int countPrimes(int n) {
            vector<bool> primes(n);
            primes[0] = false;
            primes[1] = false;

            for (int i = 2; i < n; ++i) {
                primes[i] = true;
            }

            int limit = sqrt(n);
            for (int i = 2; i * i < n; ++i) {
                if (primes[i]) {
                    for (int j = i * i; j < n; j += i) {
                        primes[j] = false;
                    }
                }
            }

            int count = 0;
            for (int i = 2; i < n; ++i) {
                cout << primes[i];
                if (primes[i])
                    ++count;
            }

            return count;

        }
};

int main ()
{
    Solution s;
    cout << s.countPrimes(7) << endl;
    cout << s.countPrimes(5) << endl;
    cout << s.countPrimes(10) << endl;
    cout << s.countPrimes(17) << endl;
    
    return 0;
}
