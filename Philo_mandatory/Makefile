

CFILES  = philo_utils.c philo_routine.c philo_utils2.c parsing.c

OFILES	= $(CFILES:.c=.o)

CC	= gcc
INT	= philo.h
FLAGS = -Wall -Wextra -Werror
NAME = philo

all : $(NAME)

$(NAME) : $(OFILES) philosophers.c
	@$(CC) $(FLAGS) philosophers.c $(OFILES) -o philo 

%.o:%.c
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OFILES)

fclean:	clean
	@rm -f $(NAME) 

re: fclean all

execute: re all philosophers.c
	@./philo 4 410 200 200