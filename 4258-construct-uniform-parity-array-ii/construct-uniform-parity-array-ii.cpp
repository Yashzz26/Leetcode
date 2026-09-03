class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX;
        int minEven = INT_MAX;

        for (int x : nums1) {
            if (x % 2 == 0)
                minEven = min(minEven, x);
            else
                minOdd = min(minOdd, x);
        }

        // All numbers are even
        if (minOdd == INT_MAX)
            return true;

        // To make everything odd, an odd number
        // must be smaller than every even number.
        if (minEven != INT_MAX && minOdd < minEven)
            return true;

        // All numbers are odd
        if (minEven == INT_MAX)
            return true;

        return false;
    }
};