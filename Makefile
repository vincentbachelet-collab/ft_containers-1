#You must produce one binary with only your containers and one with the same
#testing with STL containers

SRCS		=	./tests/algorithm/lexicographical_compare.cpp \
				#./tests/containers/map/binary_tree.cpp \
				#./tests/containers/map/map_iterator.cpp \
				#./tests/containers/map/map.cpp \
				#./tests/containers/map/node.cpp \
				./tests/containers/map/pair.cpp \
				#./tests/containers/stack/stack.cpp \
				./tests/containers/vector/vector_iterator.cpp \
				#./tests/containers/vector/vector.cpp \
				./tests/utils/iterator_traits.cpp \
				./test/utils/make_pair.cpp \
				./test/utils/reverse_iterator.cpp \
				./test/utils/utils.cpp \
				./main.cpp \

NAME		=	test

NAME_FT		=	ft_containers
NAME_STD	=	std_containers

#Les sujets ont recemment ete mis a jour et le compilateur utilise devrait etre c++
CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g3

OBJS 		=	${SRCS:.cpp=.o}

#A revoir
#STD		=	-D STD=1
#TEST		=	-D TEST=1

.cpp.o:
					$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

#Ajouter une regle pour verifier le timing + diff
all: 		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

#ft: 			fclean $(OBJ_FT)
#				$(CC) $(CFLAGS) $(OBJ_FT) -o $(NAME_FT)

#std:			fclean $(OBJ_STD)
#				$(CC) $(CFLAGS) $(OBJ_STD) -o $(NAME_STD)

clean:
				rm -f $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean:			clean
				rm -f $(NAME) $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt

re:				fclean all

.PHONY: clean fclean all re bonus test ft std