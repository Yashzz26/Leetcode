
class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    // Return true if a is better than b.
    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;   // lexicographically smaller
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint.
        sort(a.begin(), a.end(), [](auto& x, auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[0] < y[0];
        });

        // For each interval i, find the number of intervals
        // whose right endpoint is before a[i].left.
        vector<int> prev(n);

        vector<long long> rights(n);
        for (int i = 0; i < n; i++)
            rights[i] = a[i][1];

        for (int i = 0; i < n; i++) {
            // Need right < current left.
            prev[i] = lower_bound(
                rights.begin(),
                rights.begin() + i,
                a[i][0]
            ) - rights.begin() - 1;
        }

        // dp[k][i] = best answer using first i intervals
        // (indices 0 ... i-1).
        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int k = 1; k <= 4; k++) {
            for (int i = 1; i <= n; i++) {

                // Option 1: don't take interval i-1.
                dp[k][i] = dp[k][i - 1];

                // Option 2: take interval i-1.
                int idx = i - 1;

                State take = dp[k - 1][prev[idx] + 1];

                take.score += a[idx][2];
                take.ids.push_back((int)a[idx][3]);

                // Sort chosen original indices because the answer
                // must be lexicographically compared.
                sort(take.ids.begin(), take.ids.end());

                if (better(take, dp[k][i]))
                    dp[k][i] = take;
            }
        }

        return dp[4][n].ids;
    }
};