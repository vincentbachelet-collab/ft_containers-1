NAME		=	containers
NAME_FT		=	ft_containers
NAME_STD	=	std_containers
CC			=	clang++#--verbose
OBJDIR		=	objects
OBJDIR_FT	=	ft_objects
OBJDIR_STD	=	std_objects
SRC			=	main.cpp 

OBJ 		=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
OBJ_FT 		=	$(addprefix $(OBJDIR_FT)/, $(SRC:.cpp=.o))
OBJ_STD		=	$(addprefix $(OBJDIR_STD)/, $(SRC:.cpp=.o))
CFLAGS		=	-Wall -Wextra -Werror -std=c++98#-fsanitize=address -g
STD			=	-D STD=1
TEST		=	-D TEST=1

all: ft std
	@./$(NAME_FT) > $(NAME_FT).txt
	@./$(NAME_STD) > $(NAME_STD).txt
	@echo "Executing Program and Exporting Difference"

#diff $(NAME_FT).txt $(NAME_STD).txt > diff.txt
#cat diff.txt
	
bonus: all

ft: fclean $(OBJ_FT)
	@$(CC) $(CFLAGS) $(OBJ_FT) -o $(NAME_FT)
	@echo "Compilation Done [ft]"

std: fclean $(OBJ_STD)
	@$(CC) $(CFLAGS) $(OBJ_STD) -o $(NAME_STD)
	@echo "ompilation Done [std]"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(TEST) -c $< -o $@

$(OBJDIR_FT)/%.o: %.cpp
	@mkdir -p $(OBJDIR_FT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_STD)/%.o: %.cpp
	@mkdir -p $(OBJDIR_STD)
	@$(CC) $(CFLAGS) $(STD) -c $< -o $@

clean:
			@rm -rf $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean:		clean
			@rm -rf $(NAME) $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt \
			ft_objects std_objects 

re: 		fclean all

.PHONY: clean fclean all re bonus test ft std