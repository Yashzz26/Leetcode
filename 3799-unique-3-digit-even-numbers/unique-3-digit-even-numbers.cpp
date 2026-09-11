class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        set<int> possible;

        for (int i = 0; i < digits.size(); i++) {
            for (int j = 0; j < digits.size(); j++) {
                for (int k = 0; k < digits.size(); k++) {
                    if (i == j || i == k || j == k) continue;

                    if (digits[i] == 0) continue;       // no leading zero
                    if (digits[k] % 2 != 0) continue;   // must be even

                    int num = digits[i] * 100 +
                              digits[j] * 10 +
                              digits[k];

                    possible.insert(num);
                }
            }
        }

        return possible.size();
    }
};