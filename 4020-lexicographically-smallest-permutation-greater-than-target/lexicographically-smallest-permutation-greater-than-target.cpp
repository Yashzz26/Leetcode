class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Try making the answer greater at position i,
        // starting from the rightmost position.
        for (int i = n - 1; i >= 0; i--) {
            vector<int> cnt(26, 0);

            // Count all characters in s.
            for (char c : s) {
                cnt[c - 'a']++;
            }

            // Check whether target[0..i-1] can be used as prefix.
            bool possible = true;

            for (int j = 0; j < i; j++) {
                int c = target[j] - 'a';

                if (cnt[c] == 0) {
                    possible = false;
                    break;
                }

                cnt[c]--;
            }

            if (!possible)
                continue;

            // At position i, choose the smallest character
            // strictly greater than target[i].
            int cur = target[i] - 'a';

            for (int x = cur + 1; x < 26; x++) {
                if (cnt[x] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + x);

                    cnt[x]--;

                    // Put remaining characters in sorted order
                    // to make the result as small as possible.
                    for (int c = 0; c < 26; c++) {
                        ans += string(cnt[c], char('a' + c));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};