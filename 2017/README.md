## 01.c
### small
- time: linear
- space: constant
### large
- time: linear (1/2n)
- space: constant

## 02.c
### small
- time: linear
- space: constant
### large
- time: quadratic
- space: constant

## 03.C
### small
Solve by hand, pattern was that each bottom right is a perfect square.
- width of grid `w = sqrt(n).ceil`
- bottom right `br = = w^2` (because of prev ceil, this br >= n)
- grid radius (one axis of the Manhattan dist) `r = w / 2` (floored)
Using bottom right as a starting point, each `corner_i = br - w * i`, the other axis of the Manhattan distance is simply `n - k`, where `k` is the distance between `n` and the midpoint of the side of the matrix it's on (between two corners).
### large
Follow instructions, implement exactly as described, for each `n + i` in the spiral, calculate its 8 neighbours.
- time linear
- space: linear
