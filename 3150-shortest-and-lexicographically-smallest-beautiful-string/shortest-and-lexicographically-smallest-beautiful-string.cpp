class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> ones;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '1')
                ones.push_back(i);
        }

        if (ones.size() < k)
            return "";

        int bestLen = INT_MAX;
        string ans = "";

        for (int i = 0; i + k - 1 < ones.size(); ++i) {
            int start = ones[i];
            int end = ones[i + k - 1];

            int len = end - start + 1;
            string cur = s.substr(start, len);

            if (len < bestLen) {
                bestLen = len;
                ans = cur;
            } else if (len == bestLen && cur < ans) {
                ans = cur;
            }
        }

        return ans;
    }
};