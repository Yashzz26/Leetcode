class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // next[i][c] = first position >= i containing c.
        vector<array<int, 26>> next(n + 1);
        next[n].fill(n);

        for (int i = n - 1; i >= 0; --i) {
            next[i] = next[i + 1];
            next[i][word1[i] - 'a'] = i;
        }

        // prev[i][c] = last position <= i containing c.
        vector<array<int, 26>> prev(n);

        array<int, 26> last;
        last.fill(-1);

        for (int i = 0; i < n; ++i) {
            last[word1[i] - 'a'] = i;
            prev[i] = last;
        }

        /*
         * exact[k]:
         *   rightmost possible index of word2[k:]
         *   when every character must match.
         *
         * almost[k]:
         *   rightmost possible index of word2[k:]
         *   when at most one mismatch is allowed.
         *
         * -1 means impossible.
         *
         * For the empty suffix, the "starting position" is n.
         */
        vector<int> exact(m + 1, -1);
        vector<int> almost(m + 1, -1);

        exact[m] = n;
        almost[m] = n;

        for (int k = m - 1; k >= 0; --k) {
            int c = word2[k] - 'a';

            // Match word2[k], then match the rest exactly.
            if (exact[k + 1] != -1) {
                int limit = exact[k + 1] - 1;

                if (limit >= 0)
                    exact[k] = prev[limit][c];
            }

            // Case 1:
            // Match word2[k], and use the mismatch later.
            if (almost[k + 1] != -1) {
                int limit = almost[k + 1] - 1;

                if (limit >= 0)
                    almost[k] = prev[limit][c];
            }

            // Case 2:
            // Use the one mismatch at position k,
            // then the rest must match exactly.
            if (exact[k + 1] != -1) {
                int limit = exact[k + 1] - 1;

                if (limit >= 0) {
                    for (int d = 0; d < 26; ++d) {
                        if (d == c)
                            continue;

                        almost[k] = max(almost[k], prev[limit][d]);
                    }
                }
            }
        }

        // No valid sequence.
        if (almost[0] == -1)
            return {};

        vector<int> ans;
        ans.reserve(m);

        int pos = 0;
        bool usedMismatch = false;

        for (int k = 0; k < m; ++k) {
            int c = word2[k] - 'a';
            int best = n;

            /*
             * Try taking an exact match here.
             *
             * If mismatch has already been used, the remainder
             * must be exact.
             *
             * Otherwise, the remainder may use the mismatch.
             */
            int suffixStart =
                usedMismatch ? exact[k + 1] : almost[k + 1];

            int j = next[pos][c];

            if (j < n &&
                (k == m - 1 || suffixStart > j)) {
                best = j;
            }

            /*
             * Try using the mismatch at the current position.
             */
            if (!usedMismatch) {
                int mismatchPos = n;

                for (int d = 0; d < 26; ++d) {
                    if (d == c)
                        continue;

                    mismatchPos = min(mismatchPos, next[pos][d]);
                }

                // After using the mismatch, remainder must match exactly.
                if (mismatchPos < n &&
                    (k == m - 1 || exact[k + 1] > mismatchPos)) {
                    best = min(best, mismatchPos);
                }
            }

            if (best == n)
                return {};

            if (word1[best] != word2[k])
                usedMismatch = true;

            ans.push_back(best);
            pos = best + 1;
        }

        return ans;
    }
};