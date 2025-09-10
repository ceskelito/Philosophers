NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Iheaders -g 
RM		= rm -f
MKDIR	= mkdir -p

SRCS_DIR = sources
OBJS_DIR = objs

FILES_NAME = main input init utils threads monitor

SRCS	= $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES_NAME)))
OBJS	= $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES_NAME)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
