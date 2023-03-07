class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        
        for (int i = 0; i < strs[0].size(); ++i) {
            for (int j = 0; j < strs.size(); ++j) {
                if (strs[j][i] != strs[0][i]) return strs[0].substr(0, i);
            }
        }
        
        return strs[0];
    }
};
