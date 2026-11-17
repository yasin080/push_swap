NAME		= push_swap
BONUS		= checker
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
HEADER		= push_swap.h

COMMON		= parse.c \
			  stack.c \
			  ops.c \
			  ops_names.c
SRCS		= main.c \
			  sort_small.c \
			  sort_large.c \
			  cost.c
BONUS_SRCS	= bonus/checker.c

COMMON_OBJS	= $(COMMON:.c=.o)
OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(COMMON_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(BONUS)

$(BONUS): $(COMMON_OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_OBJS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
