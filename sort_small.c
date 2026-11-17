#include "push_swap.h"

void	sort_three(t_ps *ps)
{
	int	*v;

	v = ps->a.v;
	if (v[0] > v[1] && v[0] > v[2])
		do_op(ps, OP_RA);
	else if (v[1] > v[0] && v[1] > v[2])
		do_op(ps, OP_RRA);
	if (v[0] > v[1])
		do_op(ps, OP_SA);
}

void	rotate_a_to(t_ps *ps, int index)
{
	if (index <= ps->a.size / 2)
	{
		while (index-- > 0)
			do_op(ps, OP_RA);
	}
	else
	{
		while (index++ < ps->a.size)
			do_op(ps, OP_RRA);
	}
}

/* Up to 5 numbers: move the smallest ones to b, sort 3, bring them back. */
void	sort_small(t_ps *ps)
{
	if (ps->a.size == 2)
	{
		if (ps->a.v[0] > ps->a.v[1])
			do_op(ps, OP_SA);
		return ;
	}
	while (ps->a.size > 3)
	{
		rotate_a_to(ps, min_index(&ps->a));
		do_op(ps, OP_PB);
	}
	sort_three(ps);
	while (ps->b.size > 0)
		do_op(ps, OP_PA);
}
