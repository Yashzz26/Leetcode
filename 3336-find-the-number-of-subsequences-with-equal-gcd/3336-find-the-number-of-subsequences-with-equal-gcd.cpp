class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        static constexpr int MOD = 1'000'000'007;
        static constexpr int MAX_VAL = 200;

        vector<vector<int>> dp(MAX_VAL + 1,
                               vector<int>(MAX_VAL + 1, 0));

        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> next(MAX_VAL + 1,
                                     vector<int>(MAX_VAL + 1, 0));

            for (int g1 = 0; g1 <= MAX_VAL; ++g1) {
                for (int g2 = 0; g2 <= MAX_VAL; ++g2) {
                    if (dp[g1][g2] == 0)
                        continue;

                    int ways = dp[g1][g2];

                    // 1. Put x in neither subsequence
                    next[g1][g2] =
                        (next[g1][g2] + ways) % MOD;

                    // 2. Put x in seq1
                    int ng1 = gcd(g1, x);
                    next[ng1][g2] =
                        (next[ng1][g2] + ways) % MOD;

                    // 3. Put x in seq2
                    int ng2 = gcd(g2, x);
                    next[g1][ng2] =
                        (next[g1][ng2] + ways) % MOD;
                }
            }

            dp = move(next);
        }

        long long ans = 0;

        for (int g = 1; g <= MAX_VAL; ++g) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};