class Solution:
    def longestSubsequence(self, nums):
        totalXor = 0
        hasNonZero = False

        for x in nums:
            totalXor ^= x
            if x != 0:
                hasNonZero = True

        if totalXor != 0:
            return len(nums)

        if not hasNonZero:
            return 0

        return len(nums) - 1