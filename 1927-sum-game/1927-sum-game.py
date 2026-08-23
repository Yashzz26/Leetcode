class Solution:
    def sumGame(self, num: str) -> bool:
        n = len(num) // 2

        diff = 0
        q = 0

        for i, ch in enumerate(num):
            if ch == '?':
                q += 1 if i < n else -1
            else:
                diff += int(ch) if i < n else -int(ch)

        # Bob can win only if:
        # 1. The number of ? is even, and
        # 2. The existing difference can be exactly compensated.
        if q % 2 != 0:
            return True

        return diff != -9 * q // 2
        