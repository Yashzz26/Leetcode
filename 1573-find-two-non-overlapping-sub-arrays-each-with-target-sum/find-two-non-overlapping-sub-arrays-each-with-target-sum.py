from typing import List

class Solution:
    def minSumOfLengths(self, A: List[int], k: int) -> int:
        n = len(A)
        res = n + 1
        tot = 0
        i = 0

        dp = [n] * (n + 1)

        for j in range(n):
            tot += A[j]

            while tot > k:
                tot -= A[i]
                i += 1

            dp[j + 1] = dp[j]

            if tot == k:
                length = j - i + 1

                res = min(res, length + dp[i])
                dp[j + 1] = min(dp[j], length)

        return -1 if res == n + 1 else res