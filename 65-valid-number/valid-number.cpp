class Solution {
public:
    bool isNumber(string s) {
        int n = s.size();
        int i = 0;

        // Optional sign
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            i++;
        }

        bool hasDigit = false;

        // Digits before '.'
        while (i < n && isdigit(s[i])) {
            hasDigit = true;
            i++;
        }

        // Optional decimal part
        if (i < n && s[i] == '.') {
            i++;

            // Digits after '.'
            while (i < n && isdigit(s[i])) {
                hasDigit = true;
                i++;
            }
        }

        // Must have at least one digit in the mantissa
        if (!hasDigit) {
            return false;
        }

        // Optional exponent
        if (i < n && (s[i] == 'e' || s[i] == 'E')) {
            i++;

            // Exponent can have a sign
            if (i < n && (s[i] == '+' || s[i] == '-')) {
                i++;
            }

            bool exponentDigit = false;

            while (i < n && isdigit(s[i])) {
                exponentDigit = true;
                i++;
            }

            // Exponent must contain at least one digit
            if (!exponentDigit) {
                return false;
            }
        }

        // Everything must have been consumed
        return i == n;
    }
};