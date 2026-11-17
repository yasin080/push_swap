#include "push_swap.h"

static const char	*op_name(t_op op)
{
	static const char	*names[] = {"sa", "sb", "ss", "pa", "pb", "ra",
		"rb", "rr", "rra", "rrb", "rrr"};

	return (names[op]);
}

static int	str_eq(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == *b);
}

void	do_op(t_ps *ps, t_op op)
{
	const char	*name;
	int			len;

	apply_op(ps, op);
	name = op_name(op);
	len = 0;
	while (name[len])
		len++;
	write(STDOUT_FILENO, name, len);
	write(STDOUT_FILENO, "\n", 1);
}

int	parse_op(const char *name)
{
	int	op;

	op = OP_SA;
	while (op <= OP_RRR)
	{
		if (str_eq(name, op_name(op)))
			return (op);
		op++;
	}
	return (-1);
}

int	put_error(t_ps *ps)
{
	free_ps(ps);
	write(STDERR_FILENO, "Error\n", 6);
	return (1);
}
