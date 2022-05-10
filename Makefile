



CFILES  = philo_utils.c 

OFILES	= $(CFILES:.c=.o)

CC	= gcc
INT	= philo.h
NAME = philo.a

all : $(NAME)

$(NAME) : $(OFILES) philosophers.c
	@ar -rc $(NAME) $(OFILES)

%.o:%.c
	@$(CC) -o $@ -c $<

clean:
	@rm -f $(OFILES)

fclean:	clean
	@rm -f $(NAME)

re: fclean all


execute: re all philosophers.c
	@$(CC) $(FLAGS) philosophers.c philo.a -o philo 
	@./philo 4 1 1 1