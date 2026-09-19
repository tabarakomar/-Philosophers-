CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g
NAME = philo
SRC=main.c parsing.c  start.c  utils.c simu.c doing.c protect.c init.c norm.c
OBJ = $(SRC:.c=.o)

all: $(NAME)  

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
fclean:clean
	@rm -f $(NAME)
re:fclean all

.PHONY: all clean fclean re