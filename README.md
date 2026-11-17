# push_swap

42 project: sort a list of integers using two stacks and a small set of
operations, printing as few operations as possible.

Stack `a` starts with the numbers, stack `b` is empty. Allowed operations:

| Op | Effect |
|----|--------|
| `sa` / `sb` / `ss` | swap the two top elements of a / b / both |
| `pa` / `pb` | move the top of b to a / the top of a to b |
| `ra` / `rb` / `rr` | rotate a / b / both (top goes to the bottom) |
| `rra` / `rrb` / `rrr` | reverse rotate a / b / both (bottom goes to the top) |

## Usage

```bash
make            # push_swap
make bonus      # checker
./push_swap 4 67 3 87 10
./push_swap "4 67 3" 87 10 | ./checker 4 67 3 87 10    # prints OK or KO
```

Invalid input (non numbers, values outside `int`, duplicates, empty
arguments) prints `Error` on stderr and exits with status 1. Already sorted
input prints nothing.

## Algorithm

- The values are replaced by their rank (0 .. n-1). Only the order matters
  and duplicates show up while ranking.
- 2 to 5 numbers: push the smallest ones to `b`, sort the last three in place
  (at most 2 operations) and push them back.
- More than 5:
  1. Push everything except the three biggest values to `b`. Values from the
     lower half are rotated to the bottom of `b`, so `b` ends up roughly split
     in two.
  2. Sort the three values left in `a`.
  3. For every element of `b`, find where it belongs in `a` and how many
     rotations it takes to bring both to the top. There are four ways
     (`ra`/`rra` combined with `rb`/`rrb`). When both go the same way they
     share `rr`/`rrr`. Move the cheapest element and repeat until `b` is
     empty.
  4. Rotate `a` until the smallest value is on top.

## Results

Measured with 60 random inputs for each size:

| Numbers | Average ops | Worst ops | 42 limit for full score |
|---------|-------------|-----------|-------------------------|
| 3 | 1 | 2 | 3 |
| 5 | 7 | 9 | 12 |
| 100 | ~580 | 628 | 700 |
| 500 | ~4550 | 4828 | 5500 |

## Files

| File | Purpose |
|------|---------|
| `main.c` | entry point, picks the small or large sort |
| `parse.c` | splits and validates the arguments |
| `stack.c` | builds the stacks, ranking, helpers |
| `ops.c`, `ops_names.c` | the 11 operations, printing and parsing their names |
| `sort_small.c` | 2 to 5 numbers |
| `sort_large.c`, `cost.c` | the cost based algorithm |
| `bonus/checker.c` | reads operations from stdin and checks the result |

## What I'd improve

- Rotating `a` and `b` at the same time during the first phase (some `ra` +
  `rb` pairs could be `rr`).
- The cost search is O(n²) per move; fine for 500 numbers, slow for much
  bigger inputs.

Author: ybahri (42)
