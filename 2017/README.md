## 01.c
### small
- time: linear
### large
- time: linear (1/2n)

## 02.c
### small
- time: linear
### large
- time: quadratic

## 03.C
### small
Solve by hand, pattern was that each bottom right is a perfect square.
- width of grid `w = sqrt(n).ceil`
- bottom right `br = = w^2` (because of prev ceil, this br >= n)
- grid radius (one axis of the Manhattan dist) `r = w / 2` (floored)
Using bottom right as a starting point, each `corner_i = br - w * i`, the other axis of the Manhattan distance is simply `n - k`, where `k` is the distance between `n` and the midpoint of the side of the matrix it's on (between two corners).
### large
Follow instructions, implement exactly as described, for each `n + i` in the spiral, calculate its 8 neighbours.
- time: linear

## 04.js
### small
Use a `Set` to detect duplicate, only have to scan through the input once
- time: linear
### large
Sort and compare each word
- time: `O(n + n * mlgm)` where `m` is the width of the widest word, O(m lg m) is the cost of sorting a word

## 05.c
Lang | ms
--- | ---:
JavaScript | 306
C | 173
Ruby | 5858
