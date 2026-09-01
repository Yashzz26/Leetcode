from collections import deque

class Solution:
    def minMoves(self, classroom, energy):
        m, n = len(classroom), len(classroom[0])

        start = None
        litter_id = {}

        # Find start and assign each litter a bit.
        for r in range(m):
            for c in range(n):
                if classroom[r][c] == 'S':
                    start = (r, c)
                elif classroom[r][c] == 'L':
                    litter_id[(r, c)] = len(litter_id)

        k = len(litter_id)
        target = (1 << k) - 1

        # Already collected everything.
        if k == 0:
            return 0

        # (row, col, mask, remaining_energy, moves)
        q = deque()
        q.append((start[0], start[1], 0, energy, 0))

        visited = {(start[0], start[1], 0, energy)}

        directions = [
            (1, 0),
            (-1, 0),
            (0, 1),
            (0, -1)
        ]

        while q:
            r, c, mask, e, moves = q.popleft()

            for dr, dc in directions:
                nr, nc = r + dr, c + dc

                # Outside grid
                if not (0 <= nr < m and 0 <= nc < n):
                    continue

                # Obstacle
                if classroom[nr][nc] == 'X':
                    continue

                # Can't make a move without energy
                if e == 0:
                    continue

                ne = e - 1
                nmask = mask

                # Collect litter
                if classroom[nr][nc] == 'L':
                    nmask |= 1 << litter_id[(nr, nc)]

                # Reset energy
                if classroom[nr][nc] == 'R':
                    ne = energy

                # All litter collected
                if nmask == target:
                    return moves + 1

                state = (nr, nc, nmask, ne)

                if state not in visited:
                    visited.add(state)
                    q.append((nr, nc, nmask, ne, moves + 1))

        return -1