# Latin Square Puzzle Game

A C program that implements an interactive Latin square puzzle solver.

## What is a Latin Square?
A Latin square is an n×n grid filled with n different symbols, each occurring exactly once in each row and exactly once in each column.

## Features
- Read puzzle from input file
- Interactive puzzle solving with visual display
- Input validation and error checking
- Save completed puzzle to output file

## Compilation
```bash
gcc -o latinsquare latinsquare.c -lm
```

## Usage
```bash
./latinsquare <input-file>
```

## Input File Format
```
4
1 2 0 4
0 4 1 2
2 0 4 1
4 1 2 0
```
First line: size of square (n)
Following lines: puzzle grid (0 = empty cell, negative = fixed clue)

## Game Commands
- `i,j=val` - Enter value at position (i,j)
- `i,j=0` - Clear cell (i,j)
- `0,0=0` - Save and exit

Position numbering starts from 1.

## Output
Completed puzzles are saved as `out-<filename>`.