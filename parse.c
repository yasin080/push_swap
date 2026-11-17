#include "push_swap.h"

static bool	is_sep(char c)
{
	return (c == ' ' || c == '\t');
}

/* Counts numbers in all arguments. An argument without any is an error. */
static int	count_numbers(int argc, char **argv)
{
	int		count;
	int		words;
	char	*s;
	int		i;

	count = 0;
	i = 1;
	while (i < argc)
	{
		s = argv[i++];
		words = 0;
		while (*s)
		{
			if (!is_sep(*s) && (s == argv[i - 1] || is_sep(s[-1])))
				words++;
			s++;
		}
		if (words == 0)
			return (-1);
		count += words;
	}
	return (count);
}

static bool	read_number(char **s, int *out)
{
	long	n;
	int		sign;

	sign = 1;
	if (**s == '+' || **s == '-')
		if (*(*s)++ == '-')
			sign = -1;
	if (**s < '0' || **s > '9')
		return (false);
	n = 0;
	while (**s >= '0' && **s <= '9')
	{
		n = n * 10 + (*(*s)++ - '0');
		if (n > (long)INT_MAX + (sign == -1))
			return (false);
	}
	if (**s && !is_sep(**s))
		return (false);
	*out = (int)(n * sign);
	return (true);
}

static bool	fill_numbers(int argc, char **argv, int *nums)
{
	char	*s;
	int		n;
	int		i;

	n = 0;
	i = 1;
	while (i < argc)
	{
		s = argv[i++];
		while (*s)
		{
			if (is_sep(*s))
				s++;
			else if (!read_number(&s, &nums[n++]))
				return (false);
		}
	}
	return (true);
}

int	*parse_args(int argc, char **argv, int *count)
{
	int	*nums;

	*count = count_numbers(argc, argv);
	if (*count <= 0)
		return (NULL);
	nums = malloc(sizeof(int) * *count);
	if (!nums)
		return (NULL);
	if (!fill_numbers(argc, argv, nums))
	{
		free(nums);
		return (NULL);
	}
	return (nums);
}
