#You must produce one binary with only your containers and one with the same
#testing with STL containers

#Attention pour l'instant j ai plusieurs mains
#Seulement les cpp de tests font partie des SRCS
SRCS		=	./tests/iterator_traits.cpp \
				./tests/lexicographical_compare.cpp \
				./tests/make_pair.cpp \
				./tests/reverse_iterator.cpp \
				./tests/utils.cpp \
				./tests/vector_iterator.cpp \
				./tests/vector.cpp \
				./main.cpp

NAME_FT		=	ft_containers
NAME_STD	=	std_containers

#Les sujets ont recemment ete mis a jour et le compilateur utilise devrait etre c++
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g3

OBJS		= ${SRCS:.cpp=.o}

#A revoir
#STD		=	-D STD=1
#TEST		=	-D TEST=1

.cpp.o:
			$(CC) $(CFLAGS) -c $< -o $(<.cpp=.o)

#Ajouter une regle pour verifier le timing + diff
all: 		$(NAME_FT) $(NAME_STD)

$(NAME_FT):		ft
				./$(NAME_FT) > $(NAME_FT).txt

$(NAME_STD):	std
				./$(NAME_STD) > $(NAME_STD).txt

bonus: 			all

ft: 			fclean $(OBJ_FT)
				$(CC) $(CFLAGS) $(OBJ_FT) -o $(NAME_FT)

std:			fclean $(OBJ_STD)
				$(CC) $(CFLAGS) $(OBJ_STD) -o $(NAME_STD)

clean:
				rm -f $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean:			clean
				rm -f $(NAME) $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt

re:				fclean all

.PHONY: clean fclean all re bonus test ft std