NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iheaders
SRCS 	= 	utils/cooldown.c \
			utils/display_output.c \
			utils/error_handle.c \
			utils/get_time_util.c \
			utils/monitor.c \
			utils/parsing.c \
			utils/safe_malloc.c \
			utils/setter_getter.c \
			utils/simulation.c \
			utils/synchronisation.c \
			thread/init_threads.c \
			main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all