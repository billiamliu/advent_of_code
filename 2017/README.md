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

## 06.c
Use a Hash Map to detect duplicate as well as the position of where the duplicate occours. Same approach in JS & C.
Lang | ms
--- | ---:
JavaScript | 102
C | 3

## 07.js
### small
Scan through all entries in linear time and use a Map to keep count of occurance; the head only appears once, a child appears in its parent's children list, as well as on its own as a node.
- time: linear
### big
DFS with early return, no need to build a tree when accessing using the Map.
- time: linear

## 08.js
Fairly straightforward, using a Set to keep count of registers as they are encountered.

## 09.js
Simple loop with some flags and early `continue` clauses.

## 10.c
Implemented by following instructions, nothing special of note.

## 11.js
Using a 3-axis coordinate system to map hex grids.

## 12.js
DFS on an adjacency list.

## 13.rb + .js
OOP lend it self naturally for part one, then part 2 in JS because Ruby takes too long to implement.

## 14.c
### small
Follow instructions and use the Knot Hex generator from Day 10.
### large
Construct a matrix and then DFS.

## 15.c
Follow instructions, haven't thought of a clever number theory trick yet. Perhaps along the lines of GCD?

## 16.js
16! ≈ 21B combinations, but given 1B iterations, there must a cycle somewhere. Once cycle detection is implemented, it was found at iter 60.

## 17.js
Trick for the second part was that, only the number after `0` was of interest, and `0` happens to always be the first element in the array. There was no need to keep track of an actual buffer, the math could be simulated.

## 18.js
Following instructions, be careful as both the 2nd and 3rd part of the instructions can be either letters or numbers. `1` can look awefully similar to `l`.

## 19.c
Following instructions.

## 20.js
Since acceleration is constant, the closest pariticle for part 1 could be easily figured out by sorting: acceleration, velocity, and then distance. Part two _could_ be numerically calculated at O(n^2) to compute which particles will eventually collide, but for purposes of this puzzle where iteration is designed to be small, it's easier to just simulate.

## 22.js
Direction of `y` can be tricky, as "moving up" in `y` is moving _down_ in y index.
