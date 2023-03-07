class Solution {
public:
    const vector<string> keyboard {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    
    vector<string> letterCombinations(string digits) {
        vector<string> result(1, "");
        for (auto& digit : digits) {
            int n = result.size();
            int m = keyboard[digit - '0'].size();
            
            result.resize(n * m); // resize for next digit
            for (int i = 0; i < m; ++i) {
                copy(result.begin(), result.begin() + n, result.begin() + n*i); // duplicate existing combinations
            }
            
            for (int i = 0; i < m; ++i) {
                auto begin = result.begin();
                for (int j = 0; j < n; ++j) {
                    result[n * i + j] += keyboard[digit - '0'][i];
                }
            }
        }
        
        if (digits.empty()) result.resize(0);
        return result;
    }
};
