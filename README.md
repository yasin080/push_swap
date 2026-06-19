# push_swap

A sorting algorithm project that arranges integers on a stack with the fewest operations possible, using only a restricted set of stack manipulations.

## The Problem

You have two stacks, **A** and **B**. Stack A starts with a random set of unsorted integers. Stack B is empty. The only allowed operations are:

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the first two elements of stack A |
| `sb` | Swap the first two elements of stack B |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Push the top element from B to A |
| `pb` | Push the top element from A to B |
| `ra` | Rotate stack A (top element goes to bottom) |
| `rb` | Rotate stack B (top element goes to bottom) |
| `rr` | `ra` and `rb` at the same time |
| `rra` | Reverse rotate A (bottom element goes to top) |
| `rrb` | Reverse rotate B (bottom element goes to top) |
| `rrr` | `rra` and `rrb` at the same time |

The goal: sort stack A in ascending order using the **minimum number of operations**.

Scoring benchmark (42 evaluation):

| Stack size | Max moves for full score |
|------------|------------------------|
| 3 | ≤ 3 |
| 5 | ≤ 12 |
| 100 | ≤ 700 |
| 500 | ≤ 5500 |

## Solution Approach

- **2 elements**: A single `sa` if unsorted.
- **3 elements**: A dedicated `tiny_sort` that identifies the highest value and rotates or swaps it into place — at most 2 operations.
- **5 elements**: Push the 2 smallest elements to B, sort the remaining 3 with `tiny_sort`, then push back from B with cost-optimal rotations — at most 12 operations.
- **5+ elements — Cost-optimization greedy algorithm**:
  1. Push elements from A to B until only 3 remain in A.
  2. Sort the 3 in A with `tiny_sort`.
  3. For each element in B, calculate its **target position** in A and the **push price** (total rotations needed, accounting for combined `rr`/`rrr` optimizations).
  4. Select the **cheapest** node and move it to A using the optimal combination of rotations.
  5. Repeat until B is empty.
  6. Rotate A until the smallest element is at the top.

The key insight: by calculating the cost of every possible move and always choosing the cheapest, we minimize total operations. Combined rotations (`rr`, `rrr`) are used whenever both stacks need rotation in the same direction.

## Usage

```bash
./push_swap 4 67 3 87 10
```

Outputs the sequence of operations needed to sort the stack:

```
pb
ra
ra
pb
rra
...
```

### With checker (bonus)

Pipe the operations into the checker to verify correctness:

```bash
./push_swap 4 67 3 87 10 | ./checker/checker 4 67 3 87 10
```

Output: `OK` (sorted) or `KO` (not sorted).

### Error handling

```bash
./push_swap 1 2 abc     # Error
./push_swap 1 2 2       # Error (duplicates)
./push_swap 1 2 3       # (no output, already sorted)
```

## Build

```bash
make                # Compile push_swap
make bonus          # Compile checker
make clean          # Remove object files
make fclean         # Remove objects and binaries
make re             # Full rebuild
```

Compiled with `gcc -Wall -Wextra -Werror -g -O2`.

## Architecture

File                        | Purpose
----------------------------|----------------------------------------------
main.c                      | Entry point, argument parsing, dispatch by stack size
stack_init.c                | Input validation, duplicate check, stack construction
split.c                     | Custom ft_split for space-separated arguments
tiny_sort.c                 | Sorting for 2, 3, and 5 elements
push_swap_command.c         | Main algorithm: cost calculation and move orchestration
push_swap_init.c            | Position, target, price, and cheapest node computation
swap_command.c              | sa, sb, ss
push_command.c              | pa, pb
rotate_command.c            | ra, rb, rr
reverse_rotate_command.c   | rra, rrb, rrr
stack_utils.c               | Stack length, find smallest, find last node
error_free.c                | Error handling, memory cleanup
push_swap.h                 | Header: types, structs, prototypes
checker/checker.c           | Bonus: reads operations from stdin and validates sort
checker/get_next_line.c     | GNL implementation for reading operations
checker/checker.h           | Checker header with BUFFER_SIZE and GNL prototypes

Author: ybahri (42)