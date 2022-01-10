NAME			=		containers
NAME_FT			=		ft_containers

OBJ 			=		$(SRC:.cpp=.o)
OBJ_FT 			=		$(SRC:.cpp=.o)

STD				=		-D STD=1
TEST			=		-D TEST=1

SRC				=		./srcs/tests/main.cpp \
						./srcs/tests/vector/my_vector_tests.cpp \

						# ./srcs/tests/vector/my_vector_assign.cpp \
						# ./srcs/tests/vector/my_vector_at_const.cpp \
						# ./srcs/tests/vector/my_vector_at.cpp \
						# ./srcs/tests/vector/my_vector_bidirect_it.cpp \
						# ./srcs/tests/vector/my_vector_copy_construct.cpp \
						# ./srcs/tests/vector/my_vector_erase.cpp \
						# ./srcs/tests/vector/my_vector_insert.cpp \
						# ./srcs/tests/vector/my_vector_insert2.cpp \
						# ./srcs/tests/vector/my_vector_ite_arrow.cpp \
						# ./srcs/tests/vector/my_vector_ite_n0.cpp \
						# ./srcs/tests/vector/my_vector_ite_n00.cpp \
						# ./srcs/tests/vector/my_vector_ite_n1.cpp \
						# ./srcs/tests/vector/my_vector_ite.cpp \
						# ./srcs/tests/vector/my_vector_push_pop.cpp \
						# ./srcs/tests/vector/my_vector_relational_ope.cpp \
						# ./srcs/tests/vector/my_vector_rev_ite_construct.cpp \
						# ./srcs/tests/vector/my_vector_rite_arrow.cpp \
						# ./srcs/tests/vector/my_vector_rite_eq_ope.cpp \
						# ./srcs/tests/vector/my_vector_rite.cpp \
						# ./srcs/tests/vector/my_vector_rite2.cpp \
						# ./srcs/tests/vector/my_vector_size.cpp \
						# ./srcs/tests/vector/my_vector_swap.cpp \
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

RM				=		rm -rf
CC				=		clang++
CFLAGS			=		-D DEBUG=0 -Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address

ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

all: 	ft
		@echo "${GREEN}Successfully compiled test sources.${RESET}"

ft: 	fclean $(OBJ_FT)
		@$(CC) $(CFLAGS) $(OBJ_FT) -o $(NAME_FT)

%.o: %.cpp
		@$(CC) $(CFLAGS) $(TEST) -c $< -o $@

%.o: %.cpp
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJ) $(OBJ_FT)
		@echo "${GREEN}Cleaned all .o files.${RESET}"

fclean: clean 
		@$(RM) $(NAME) $(NAME_FT)
		@echo "${GREEN}Cleaned all .o files and ft executable.${RESET}"

re: 	fclean all
		@echo "${GREEN}Make re OK !${RESET}"

.PHONY: clean fclean all re bonus test ft std
