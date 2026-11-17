#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	if (!load_input(&ps, argc, argv))
		return (put_error(&ps));
	if (!is_sorted(&ps.a))
	{
		if (ps.a.size <= 5)
			sort_small(&ps);
		else
			sort_large(&ps);
	}
	free_ps(&ps);
	return (0);
}
