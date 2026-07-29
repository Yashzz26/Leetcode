from collections import Counter

class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        n = len(s)
        freq = Counter(s)

        # Build counts needed for the left half
        cnt = {ch: freq[ch] // 2 for ch in freq}
        half_len = n // 2

        # Middle character for odd-length palindrome
        middle = ""
        if n % 2:
            for ch in freq:
                if freq[ch] % 2:
                    middle = ch
                    break

        # We never need counts larger than k
        LIMIT = k

        def count_permutations(counts, length):
            """
            Number of distinct permutations of the remaining characters,
            capped at LIMIT.
            """
            if length == 0:
                return 1

            result = 1
            used = 0

            for ch in sorted(counts):
                c = counts[ch]

                for i in range(1, c + 1):
                    used += 1
                    result = result * used // i

                    if result > LIMIT:
                        return LIMIT

            return min(result, LIMIT)

        # Check whether k is possible
        if count_permutations(cnt, half_len) < k:
            return ""

        left = []

        # Construct the kth lexicographically smallest half
        for pos in range(half_len):
            remaining = half_len - pos - 1

            for ch in "abcdefghijklmnopqrstuvwxyz":
                if cnt.get(ch, 0) == 0:
                    continue

                # Try putting ch here
                cnt[ch] -= 1

                ways = count_permutations(cnt, remaining)

                if k > ways:
                    # Skip all permutations beginning with this choice
                    k -= ways
                    cnt[ch] += 1
                else:
                    # kth permutation is in this group
                    left.append(ch)
                    break

        left = "".join(left)

        return left + middle + left[::-1]