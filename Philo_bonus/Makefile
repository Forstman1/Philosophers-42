

CFILES  = philo_routine.c  parsing.c philo_utils.c checkdeath.c

OFILES	= $(CFILES:.c=.o)

CC	= gcc
INT	= philo_bonus.h
NAME = philo_bonus

all : $(NAME)

$(NAME) : $(OFILES) philosophers_bonus.c
	@$(CC) $(FLAGS) philosophers_bonus.c $(OFILES) -o philo_bonus

%.o:%.c
	@$(CC) -o $@ -c $<

clean:
	@rm -f $(OFILES)

fclean:	clean
	@rm -f $(NAME) 

re: fclean all


execute: re all philosophers_bonus.c
	@./philo_bonus 4 410 200 200 2