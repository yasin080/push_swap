#include "push_swap.h"

/* Index in a where value has to be inserted to keep a sorted (circularly). */
static int	target_index(t_stack *a, int value)
{
	int	best;
	int	i;

	best = -1;
	i = 0;
	while (i < a->size)
	{
		if (a->v[i] > value && (best == -1 || a->v[i] < a->v[best]))
			best = i;
		i++;
	}
	if (best == -1)
		return (min_index(a));
	return (best);
}

static int	max_abs(int x, int y)
{
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if (x > y)
		return (x);
	return (y);
}

static t_move	option(int ra, int rb)
{
	t_move	m;

	m.a = ra;
	m.b = rb;
	if ((ra >= 0) == (rb >= 0))
		m.cost = max_abs(ra, rb);
	else
		m.cost = max_abs(ra, 0) + max_abs(rb, 0);
	return (m);
}

/*
** Each stack can be rotated up or down, so there are four ways to bring
** both elements to the top. Same direction moves share rr / rrr.
*/
static t_move	cheapest_way(int ia, int ib, int size_a, int size_b)
{
	t_move	best;
	t_move	m;

	best = option(ia, ib);
	m = option(ia - size_a, ib - size_b);
	if (m.cost < best.cost)
		best = m;
	m = option(ia, ib - size_b);
	if (m.cost < best.cost)
		best = m;
	m = option(ia - size_a, ib);
	if (m.cost < best.cost)
		best = m;
	return (best);
}

t_move	best_move(t_ps *ps)
{
	t_move	best;
	t_move	m;
	int		i;

	best.cost = INT_MAX;
	i = 0;
	while (i < ps->b.size && best.cost > 0)
	{
		m = cheapest_way(target_index(&ps->a, ps->b.v[i]), i,
				ps->a.size, ps->b.size);
		if (m.cost < best.cost)
			best = m;
		i++;
	}
	return (best);
}
