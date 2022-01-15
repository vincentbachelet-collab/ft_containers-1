NAME			=	containers
NAME_FT			=	ft_containers
NAME_STD		=	std_containers
CC				=	clang++

OBJ 			=	$(SRC:.cpp=.o)
OBJ_FT 			=	$(SRC:.cpp=.o)
OBJ_STD			=	$(SRC:.cpp=.o)

CFLAGS			=	-Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address
STD				=	-D STD=1
TEST			=	-D TEST=1
RM				=	rm -rf

SRC				=		./main.cpp \
						./srcs/tests/vector/my_vector_tests.cpp \
						./srcs/tests/vector/my_vector_assign.cpp \
						./srcs/tests/vector/my_vector_at.cpp \
						./srcs/tests/vector/my_vector_at_const.cpp \
						./srcs/tests/vector/my_vector_push_pop.cpp \
						./srcs/tests/vector/my_vector_copy_construct.cpp \
						./srcs/tests/vector/my_vector_erase.cpp \
						./srcs/tests/vector/my_vector_insert.cpp \
						./srcs/tests/vector/my_vector_swap.cpp \
						./srcs/tests/vector/my_vector_size.cpp \
						./srcs/tests/vector/my_vector_ite.cpp \


ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

all: 	ft std
		@./$(NAME_FT) > $(NAME_FT).txt
		@./$(NAME_STD) > $(NAME_STD).txt
		@echo "${GREEN}Executing Program and Exporting Difference${RESET}"
		@diff $(NAME_FT).txt $(NAME_STD).txt > diff.txt
		@cat diff.txt

bonus: all

test: fclean $(OBJ)
	@$(CC) $(CFLAGS) $(TEST) $(OBJ) -o $(NAME)
	@echo "${GREEN}Compilation Done & Executing Program [test]${RESET}"
	@./$(NAME)

ft: fclean $(OBJ_FT)
	@ $(CC) $(CFLAGS) $(OBJ_FT) -o $(NAME_FT)
	@echo "${GREEN}Compilation Done [ft]${RESET}"

std: fclean $(OBJ_STD)
	@ $(CC) $(CFLAGS) $(OBJ_STD) -o $(NAME_STD)
	@echo "${GREEN}Compilation Done [std]${RESET}"

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
	@rm -f $(OBJ) $(OBJ_FT) $(OBJ_STD)

fclean: clean
	@rm -f $(NAME) $(NAME_FT) $(NAME_STD) $(NAME).txt $(NAME_FT).txt $(NAME_STD).txt diff.txt

re: fclean all

.PHONY: clean fclean all re bonus test ft std