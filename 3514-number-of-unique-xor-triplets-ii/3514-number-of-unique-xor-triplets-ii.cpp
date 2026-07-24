class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> pairXor(MAXX, false);
        vector<bool> tripletXor(MAXX, false);

        // All possible XORs of two elements.
        for (int a : nums) {
            for (int b : nums) {
                pairXor[a ^ b] = true;
            }
        }

        // Add the third element.
        for (int x = 0; x < MAXX; x++) {
            if (!pairXor[x]) continue;

            for (int a : nums) {
                tripletXor[x ^ a] = true;
            }
        }

        int ans = 0;
        for (bool possible : tripletXor) {
            if (possible) ans++;
        }

        return ans;
    }
};