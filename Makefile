#You must produce one binary with only your containers and one with the same
#testing with STL containers

#Attention pour l'instant j ai plusieurs mains
SRCS		=	./srcs/lexicographical_compare.hpp \
				./srcs/make_pair.hpp \
				./srcs/pair.hpp \
				./srcs/reverse_iterator.hpp \
				./srcs/utils.hpp \
				./srcs/vector_iterator.hpp \
				./srcs/vector.hpp \
				./tests/iterator_traits.cpp \
				./tests/lexicographical_compare.cpp \
				./tests/make_pair.cpp \
				./tests/reverse_iterator.cpp \
				./tests/utils.cpp \
				./tests/vector_iterator.cpp \
				./tests/vector.cpp \
				./main.cpp

NAME_FT		=	ft_containers
NAME_STD	=	std_containers
CC			=	c++
OBJDIR		=	objects
SRC			=	./srcs/tests/main.cpp
CFLAGS		=	-Wall -Wextra -Werror -std=c++98#-fsanitize=address -g3

#A revoir

#STD		=	-D STD=1
#TEST		=	-D TEST=1

#Ajouter une regle pour verifier le timing
all: ft std
	./$(NAME_FT) > $(NAME_FT).txt
	./$(NAME_STD) > $(NAME_STD).txt
#Ajouter une regle pour la diff

bonus: all

ft: fclean $(OBJ_FT)
	$(CC) $(CFLAGS) $(OBJ_FT) -o $(NAME_FT)

std: fclean $(OBJ_STD)
	$(CC) $(CFLAGS) $(OBJ_STD) -o $(NAME_STD)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(TEST) -c $< -o $@

$(OBJDIR_FT)/%.o: %.cpp
	mkdir -p $(OBJDIR_FT)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_STD)/%.o: %.cpp
	mkdir -p $(OBJDIR_STD)
	$(CC) $(CFLAGS) $(STD) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean: clean
	rm -f $(NAME) $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt

re: fclean all

.PHONY: clean fclean all re bonus test ft std