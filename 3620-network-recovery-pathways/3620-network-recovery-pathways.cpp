class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges,
                         vector<bool>& online,
                         long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> g(n);
        vector<int> indeg(n, 0);
        vector<int> vals;

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});
            indeg[v]++;
            vals.push_back(w);
        }

        // Topological order
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, w] : g[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }

        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        auto feasible = [&](int need) {
            const long long INF = (1LL << 62);
            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF) continue;

                for (auto &[v, w] : g[u]) {
                    if (w < need) continue;
                    if (v != n - 1 && !online[v]) continue;

                    long long nd = dist[u] + w;
                    if (nd < dist[v]) {
                        dist[v] = nd;
                    }
                }
            }

            return dist[n - 1] <= k;
        };

        if (!feasible(0)) return -1;

        int lo = 0, hi = (int)vals.size() - 1;
        int ans = 0;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;

            if (feasible(vals[mid])) {
                ans = vals[mid];
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};