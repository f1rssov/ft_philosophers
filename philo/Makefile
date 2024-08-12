NAME = philo

LIST_NAME = ft_atoi.c philo.c create_pthread.c \
			algorithm.c init.c utils.c waiter.c \
			utils2.c
			

OBJ_NAME= $(patsubst %.c,%.o,$(LIST_NAME))

CC = gcc #-fsanitize=thread

CFLAGS = -Wall -Wextra -Werror

INC = philo.h

all : $(NAME)

$(NAME) : $(OBJ_NAME) $(INC)
	$(CC) $(CFLAGS) $(OBJ_NAME) -o $(NAME) -lpthread

clean :
	@rm -f $(OBJ_NAME)
fclean : clean
	@rm -f $(NAME) $(OBJ_NAME)
re : fclean all
.PHONY : all clean fclean re