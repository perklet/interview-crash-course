class Solution {
public:
    vector<string> anagrams(vector<string>& strs) {
        vector<string> result;
        string temp;
        unordered_map<string, string> record;
        unordered_map<string, int> count;
        for (int i = 0; i < strs.size(); ++i) {
            temp = strs[i];
            sort(temp.begin(), temp.end());
            if (record.find(temp) != record.end()) { // found
                if (count[temp] == 0) {
                    result.push_back(record[temp]); // second apperance
                    ++count[temp];
                }
                result.push_back(strs[i]); 
            } else {                                 // not found
                record[temp] = strs[i];
                count[temp] = 0;
            }
        }
        return result;
    }
};
