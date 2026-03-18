NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include
THDFLAG = -lpthread

SOURCES = \
	main.c \
	ft_atoi.c \
	routine.c

SRCS := $(addprefix srcs/, $(SOURCES))

OBJSDIR = objs/
OBJS = $(addprefix $(OBJSDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(THDFLAG)

$(OBJSDIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -fsanitize=thread -g
debug: re

hel:
	valgrind --tool=helgrind ./$(NAME)

val:
	valgrind --leak-check=full --track-origins=yes \
	--show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re
