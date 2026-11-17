#include "../push_swap.h"

static int	next_char(char *c)
{
	static char	buf[4096];
	static int	len;
	static int	pos;

	if (pos >= len)
	{
		len = read(STDIN_FILENO, buf, sizeof(buf));
		pos = 0;
		if (len <= 0)
			return (len);
	}
	*c = buf[pos++];
	return (1);
}

/*
** Reads one instruction (without the '\n') into line.
** Returns 1 for a line, 0 at end of input and -1 on a read error.
** Lines that do not fit are cut, so they never match a valid name.
*/
static int	read_line(char *line, int max)
{
	int		len;
	int		ret;
	char	c;

	ret = next_char(&c);
	if (ret <= 0)
		return (ret);
	len = 0;
	while (ret > 0 && c != '\n')
	{
		if (len < max - 1)
			line[len] = c;
		len++;
		ret = next_char(&c);
	}
	if (ret < 0)
		return (-1);
	if (len >= max)
		len = max - 1;
	line[len] = '\0';
	return (1);
}

static int	print_result(t_ps *ps)
{
	if (is_sorted(&ps->a) && ps->b.size == 0)
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
	free_ps(ps);
	return (0);
}

int	main(int argc, char **argv)
{
	t_ps	ps;
	char	line[8];
	int		ret;
	int		op;

	if (argc < 2)
		return (0);
	if (!load_input(&ps, argc, argv))
		return (put_error(&ps));
	ret = read_line(line, sizeof(line));
	while (ret > 0)
	{
		op = parse_op(line);
		if (op < 0)
			return (put_error(&ps));
		apply_op(&ps, op);
		ret = read_line(line, sizeof(line));
	}
	if (ret < 0)
		return (put_error(&ps));
	return (print_result(&ps));
}
