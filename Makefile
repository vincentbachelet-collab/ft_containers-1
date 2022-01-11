NAME			=	containers
NAME_FT			=	ft_containers
NAME_STD		=	std_containers
CC				=	clang++
#OBJDIR			=	objects
#OBJDIR_FT		=	ft_objects
#OBJDIR_STD		=	std_objects
#SRC				=	main.cpp
#OBJ 			=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
#OBJ_FT 			=	$(addprefix $(OBJDIR_FT)/, $(SRC:.cpp=.o))
#OBJ_STD			=	$(addprefix $(OBJDIR_STD)/, $(SRC:.cpp=.o))

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

						# ./srcs/tests/vector/my_vector_bidirect_it.cpp \
						# ./srcs/tests/vector/my_vector_insert2.cpp \
						# ./srcs/tests/vector/my_vector_ite_arrow.cpp \
						# ./srcs/tests/vector/my_vector_ite_n0.cpp \
						# ./srcs/tests/vector/my_vector_ite_n00.cpp \
						# ./srcs/tests/vector/my_vector_ite_n1.cpp \
						# ./srcs/tests/vector/my_vector_ite.cpp \
						# ./srcs/tests/vector/my_vector_relational_ope.cpp \
						# ./srcs/tests/vector/my_vector_rev_ite_construct.cpp \
						# ./srcs/tests/vector/my_vector_rite_arrow.cpp \
						# ./srcs/tests/vector/my_vector_rite_eq_ope.cpp \
						# ./srcs/tests/vector/my_vector_rite.cpp \
						# ./srcs/tests/vector/my_vector_rite2.cpp \
						# ./srcs/tests/stack/my_stack_default_copy.cpp \
						# ./srcs/tests/stack/my_stack_default.cpp \
						# ./srcs/tests/stack/my_stack_list_copy.cpp \
						# ./srcs/tests/stack/my_stack_relational_ope_list.cpp \
						# ./srcs/tests/stack/my_stack_relational_ope.cpp \
						# ./srcs/tests/map/my_map_bouds.cpp \
						# ./srcs/tests/map/my_map_comp.cpp \
						# ./srcs/tests/map/my_map_copy_construct.cpp \
						# ./srcs/tests/map/my_map_empty.cpp \
						# ./srcs/tests/map/my_map_erase.cpp \
						# ./srcs/tests/map/my_map_erase2.cpp \
						# ./srcs/tests/map/my_map_find_count.cpp \
						# ./srcs/tests/map/my_map_insert.cpp \
						# ./srcs/tests/map/my_map_insert2.cpp \
						# ./srcs/tests/map/my_map_ite_arrow.cpp \
						# ./srcs/tests/map/my_map_ite_n0.cpp \
						# ./srcs/tests/map/my_map_ite_n1.cpp \
						# ./srcs/tests/map/my_map_ite_type.cpp \
						# ./srcs/tests/map/my_map_more.cpp \
						# ./srcs/tests/map/my_map_op_sqbr.cpp \
						# ./srcs/tests/map/my_map_relational_ope.cpp \
						# ./srcs/tests/map/my_map_rev_ite_construct.cpp \
						# ./srcs/tests/map/my_map_rite_arrow.cpp \
						# ./srcs/tests/map/my_map_rite.cpp \
						# ./srcs/tests/map/my_map_swap.cpp \
						# ./srcs/tests/map/my_map_tricky_construct.cpp \
						# ./srcs/tests/map/my_map_tricky_erase.cpp \


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