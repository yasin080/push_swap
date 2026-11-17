#include "push_swap.h"

/*
** Replaces every value by its position in sorted order (0 .. n - 1).
** The algorithm only needs the order, and two equal values mean a duplicate.
*/
static bool	to_ranks(int *nums, int *ranks, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		ranks[i] = 0;
		j = 0;
		while (j < n)
		{
			if (i != j && nums[j] == nums[i])
				return (false);
			if (nums[j] < nums[i])
				ranks[i]++;
			j++;
		}
		i++;
	}
	return (true);
}

bool	load_input(t_ps *ps, int argc, char **argv)
{
	int	*nums;
	int	n;

	ps->a.v = NULL;
	ps->b.v = NULL;
	nums = parse_args(argc, argv, &n);
	if (!nums)
		return (false);
	ps->a.v = malloc(sizeof(int) * n);
	ps->b.v = malloc(sizeof(int) * n);
	ps->a.size = n;
	ps->b.size = 0;
	if (!ps->a.v || !ps->b.v || !to_ranks(nums, ps->a.v, n))
	{
		free(nums);
		return (false);
	}
	free(nums);
	return (true);
}

void	free_ps(t_ps *ps)
{
	free(ps->a.v);
	free(ps->b.v);
	ps->a.v = NULL;
	ps->b.v = NULL;
}

bool	is_sorted(t_stack *s)
{
	int	i;

	i = 1;
	while (i < s->size)
	{
		if (s->v[i - 1] > s->v[i])
			return (false);
		i++;
	}
	return (true);
}

int	min_index(t_stack *s)
{
	int	i;
	int	best;

	best = 0;
	i = 1;
	while (i < s->size)
	{
		if (s->v[i] < s->v[best])
			best = i;
		i++;
	}
	return (best);
}
