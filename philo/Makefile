NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Iheaders
RM		= rm -f

SRCS_NAMES = main.c validate_input.c
SRCS = $(addprefix sources/, $(SRCS_NAMES))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
