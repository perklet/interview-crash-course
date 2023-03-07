class Solution {
    public:
        string longestPalindrome(string s) {
            if (s.size() <= 1) {
                return s;
            }

            int len = s.size();
            int max_left = 0;
            int max_len = 1;
            int left, right;

            int start = 0;
            while (start < len && len - start > max_len / 2) {
                left = right = start;
                while (right < len - 1 && s[right + 1] == s[right])
                    ++right;
                start = right + 1;
                while (right < len - 1 && left > 0 && s[right + 1] == s[left - 1]) {
                    ++right;
                    --left;
                }

                if (max_len < right - left + 1) {
                    max_left = left;
                    max_len = right - left + 1;
                }
            }

            return s.substr(max_left, max_len);
        }
};
