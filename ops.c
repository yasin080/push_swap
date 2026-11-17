#include "push_swap.h"

static void	swap(t_stack *s)
{
	int	tmp;

	if (s->size < 2)
		return ;
	tmp = s->v[0];
	s->v[0] = s->v[1];
	s->v[1] = tmp;
}

static void	push(t_stack *to, t_stack *from)
{
	int	i;

	if (from->size == 0)
		return ;
	i = to->size;
	while (i > 0)
	{
		to->v[i] = to->v[i - 1];
		i--;
	}
	to->v[0] = from->v[0];
	to->size++;
	i = 1;
	while (i < from->size)
	{
		from->v[i - 1] = from->v[i];
		i++;
	}
	from->size--;
}

static void	rotate(t_stack *s)
{
	int	first;
	int	i;

	if (s->size < 2)
		return ;
	first = s->v[0];
	i = 1;
	while (i < s->size)
	{
		s->v[i - 1] = s->v[i];
		i++;
	}
	s->v[s->size - 1] = first;
}

static void	reverse_rotate(t_stack *s)
{
	int	last;
	int	i;

	if (s->size < 2)
		return ;
	last = s->v[s->size - 1];
	i = s->size - 1;
	while (i > 0)
	{
		s->v[i] = s->v[i - 1];
		i--;
	}
	s->v[0] = last;
}

void	apply_op(t_ps *ps, t_op op)
{
	if (op == OP_SA || op == OP_SS)
		swap(&ps->a);
	if (op == OP_SB || op == OP_SS)
		swap(&ps->b);
	if (op == OP_PA)
		push(&ps->a, &ps->b);
	if (op == OP_PB)
		push(&ps->b, &ps->a);
	if (op == OP_RA || op == OP_RR)
		rotate(&ps->a);
	if (op == OP_RB || op == OP_RR)
		rotate(&ps->b);
	if (op == OP_RRA || op == OP_RRR)
		reverse_rotate(&ps->a);
	if (op == OP_RRB || op == OP_RRR)
		reverse_rotate(&ps->b);
}
