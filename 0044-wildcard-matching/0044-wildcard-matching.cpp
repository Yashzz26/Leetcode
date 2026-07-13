class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0;          // pointer for s
        int j = 0;          // pointer for p
        int star = -1;      // last '*' position
        int match = 0;      // position in s matched after '*'

        while (i < s.size()) {
            // Exact match or '?'
            if (j < p.size() && (p[j] == s[i] || p[j] == '?')) {
                i++;
                j++;
            }
            // Found '*'
            else if (j < p.size() && p[j] == '*') {
                star = j;
                match = i;
                j++;
            }
            // Mismatch: use previous '*'
            else if (star != -1) {
                j = star + 1;
                match++;
                i = match;
            }
            // No '*' available
            else {
                return false;
            }
        }

        // Remaining pattern must contain only '*'
        while (j < p.size() && p[j] == '*') {
            j++;
        }

        return j == p.size();
    }
};