#include "push_swap.h"

/*
** Everything but the three biggest values goes to b. The lower half is
** rotated to the bottom of b, which leaves b roughly split in two and
** makes the moves back to a cheaper.
*/
static void	push_to_b(t_ps *ps)
{
	int	n;

	n = ps->a.size;
	while (ps->a.size > 3)
	{
		if (ps->a.v[0] >= n - 3)
			do_op(ps, OP_RA);
		else
		{
			do_op(ps, OP_PB);
			if (ps->b.v[0] < n / 2 && ps->b.size > 1)
				do_op(ps, OP_RB);
		}
	}
}

static void	rotate_n(t_ps *ps, int *n, t_op up, t_op down)
{
	while (*n > 0)
	{
		do_op(ps, up);
		(*n)--;
	}
	while (*n < 0)
	{
		do_op(ps, down);
		(*n)++;
	}
}

static void	run_move(t_ps *ps, t_move m)
{
	int	both;

	both = 0;
	if ((m.a > 0 && m.b > 0) || (m.a < 0 && m.b < 0))
	{
		both = m.a;
		if ((m.a > 0 && m.b < m.a) || (m.a < 0 && m.b > m.a))
			both = m.b;
	}
	m.a -= both;
	m.b -= both;
	rotate_n(ps, &both, OP_RR, OP_RRR);
	rotate_n(ps, &m.a, OP_RA, OP_RRA);
	rotate_n(ps, &m.b, OP_RB, OP_RRB);
}

void	sort_large(t_ps *ps)
{
	push_to_b(ps);
	sort_three(ps);
	while (ps->b.size > 0)
	{
		run_move(ps, best_move(ps));
		do_op(ps, OP_PA);
	}
	rotate_a_to(ps, min_index(&ps->a));
}
