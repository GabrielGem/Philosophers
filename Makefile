NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
THDFLAG = -lpthread

SOURCES = 

OBJSDIR = objs/
OBJS = $(addprefix $(OBJSDIR), $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(THDFLAG)

$(OBJS): | $(OBJSDIR)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(OBJSDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re
