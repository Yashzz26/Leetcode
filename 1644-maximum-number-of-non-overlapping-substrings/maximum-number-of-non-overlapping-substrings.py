from typing import List

class Solution:
    def maxNumOfSubstrings(self, s: str) -> List[str]:
        n = len(s)

        # First and last occurrence
        first = [n] * 26
        last = [-1] * 26

        for i, ch in enumerate(s):
            c = ord(ch) - ord('a')
            first[c] = min(first[c], i)
            last[c] = i

        intervals = []

        # Find smallest valid interval for each character
        for c in range(26):
            if last[c] == -1:
                continue

            L = first[c]
            R = last[c]
            i = L
            valid = True

            while i <= R:
                x = ord(s[i]) - ord('a')

                # Character occurs before L -> impossible
                if first[x] < L:
                    valid = False
                    break

                # Need to include all occurrences of this character
                R = max(R, last[x])

                i += 1

            if valid:
                intervals.append((L, R))

        # Sort by ending position
        intervals.sort(key=lambda x: x[1])

        ans = []
        prev_end = -1

        for L, R in intervals:
            if L > prev_end:
                ans.append(s[L:R + 1])
                prev_end = R

        return ans