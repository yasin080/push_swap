#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
}	t_op;

/* v[0] is the top of the stack */
typedef struct s_stack
{
	int	*v;
	int	size;
}	t_stack;

typedef struct s_ps
{
	t_stack	a;
	t_stack	b;
}	t_ps;

/* Rotations to apply: > 0 means ra/rb, < 0 means rra/rrb. */
typedef struct s_move
{
	int	a;
	int	b;
	int	cost;
}	t_move;

/* parse.c */
int		*parse_args(int argc, char **argv, int *count);

/* stack.c */
bool	load_input(t_ps *ps, int argc, char **argv);
void	free_ps(t_ps *ps);
bool	is_sorted(t_stack *s);
int		min_index(t_stack *s);
int		put_error(t_ps *ps);

/* ops.c / ops_names.c */
void	apply_op(t_ps *ps, t_op op);
void	do_op(t_ps *ps, t_op op);
int		parse_op(const char *name);

/* sort_small.c */
void	sort_three(t_ps *ps);
void	sort_small(t_ps *ps);
void	rotate_a_to(t_ps *ps, int index);

/* sort_large.c / cost.c */
void	sort_large(t_ps *ps);
t_move	best_move(t_ps *ps);

#endif
