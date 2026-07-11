class Solution {
public:
    int count = 0;

    void solve(int row,
               int n,
               vector<bool>& col,
               vector<bool>& diag,
               vector<bool>& antiDiag) {
        
        // All n queens have been placed.
        if (row == n) {
            count++;
            return;
        }

        for (int c = 0; c < n; c++) {
            int d = row - c + n - 1;
            int ad = row + c;

            if (col[c] || diag[d] || antiDiag[ad]) {
                continue;
            }

            // Place queen.
            col[c] = true;
            diag[d] = true;
            antiDiag[ad] = true;

            solve(row + 1, n, col, diag, antiDiag);

            // Backtrack: remove queen.
            col[c] = false;
            diag[d] = false;
            antiDiag[ad] = false;
        }
    }

    int totalNQueens(int n) {
        vector<bool> col(n, false);
        vector<bool> diag(2 * n - 1, false);
        vector<bool> antiDiag(2 * n - 1, false);

        solve(0, n, col, diag, antiDiag);

        return count;
    }
};