# SRCS_TEST 	=

NAME		=		test

NAME_FT		=		ft_containers
NAME_STD	=		std_containers

# Verifier le compilateur demande
CC			=		c++
CFLAGS		=		-Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

# OBJS 		=		${SRCS_TEST:.cpp=.o}

.cpp.o:
					$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

all: 				$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
					rm -f $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean:				clean
					rm -f $(NAME) $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt

re:					fclean all

.PHONY: 			clean fclean all re bonus test ft std
