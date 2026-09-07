class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;
        
        vector<long long> end(26, 0);

        for (char ch : s) {
            int c = ch - 'a';

            long long total = 1; // empty subsequence

            for (int j = 0; j < 26; j++) {
                total = (total + end[j]) % MOD;
            }

            end[c] = total;
        }

        long long ans = 0;
        for (long long x : end) {
            ans = (ans + x) % MOD;
        }

        return ans;
    }
};