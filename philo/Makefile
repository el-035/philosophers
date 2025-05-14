CC = cc

CFILES = philo.c more_utils.c routine.c monitoring.c init_free.c

#creates object files from the c files given
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

NAME = philo

# this sets the rule to compile all c files into o files $< is the prerequisite (aka the c files) and $@ is the target (aka the o files)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# all compiles all the c files into o files and archive them into libft.a
all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) utils.c lonely_philo.c

#gets rid of all o files after creating application
clean:
	rm -f $(OFILES)

#removes o files and library
fclean: clean
	rm -f $(NAME)

#to rebuild the whole project after cleaning everything
re: fclean all

#tells make that all, clean, re, and fclean should always be treated as commands and not as files to be created.
.PHONY: all clean re fclean