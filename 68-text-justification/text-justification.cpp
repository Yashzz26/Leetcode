class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int n = words.size();

        int i = 0;

        while (i < n) {
            int j = i;
            int totalChars = 0;

            // Find words that fit in the current line
            while (j < n &&
                   totalChars + words[j].size() + (j - i) <= maxWidth) {
                totalChars += words[j].size();
                j++;
            }

            int wordCount = j - i;
            int totalSpaces = maxWidth - totalChars;

            string line;

            // Last line or only one word
            if (j == n || wordCount == 1) {

                for (int k = i; k < j; k++) {
                    line += words[k];

                    if (k != j - 1)
                        line += ' ';
                }

                // Remaining spaces at the end
                line += string(maxWidth - line.size(), ' ');
            }
            else {
                // Fully justified line
                int gaps = wordCount - 1;

                int spacesPerGap = totalSpaces / gaps;
                int extraSpaces = totalSpaces % gaps;

                for (int k = i; k < j; k++) {
                    line += words[k];

                    if (k != j - 1) {
                        int spaces = spacesPerGap;

                        // Left gaps get the extra spaces
                        if (k - i < extraSpaces)
                            spaces++;

                        line += string(spaces, ' ');
                    }
                }
            }

            ans.push_back(line);
            i = j;
        }

        return ans;
    }
};