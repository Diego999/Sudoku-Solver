# Sudoku-Solver

Sudoku solver using depth first search as searching method, and using heuristic of the unit which has the minimum numbers of possiblities. Inside the minimum unit, take the first block which appears with multiple possibilities.

#Efficiency

It solves the hardest sudoku in 0.03 ms. During the search phase, each time a copy of array<array<Block>> happens, which is quite slow. The purpose was to use OO to have a proper solution rather than other data-structure (like string) which would have been more difficult to understand.