class Solution:
    def smallestPalindrome(self, s: str) -> str:
        freq = [0] * 26

        # Count frequency of each character
        for ch in s:
            freq[ord(ch) - ord('a')] += 1

        left = []
        middle = ""

        # Build smallest possible left half
        for i in range(26):
            ch = chr(ord('a') + i)

            left.append(ch * (freq[i] // 2))

            # Odd frequency character goes in the middle
            if freq[i] % 2 == 1:
                middle = ch

        left = ''.join(left)

        return left + middle + left[::-1]