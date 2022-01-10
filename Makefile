NAME			=		ft_containers

SOURCES_FOLDER	= 		./srcs/tests

SOURCES			=		main.cpp \
						./vector/my_vector_assign.cpp \
						./vector/my_vector_at_const.cpp \
						./vector/my_vector_at.cpp \
						./vector/my_vector_bidirect_it.cpp \
						./vector/my_vector_copy_construct.cpp \
						./vector/my_vector_erase.cpp \
						./vector/my_vector_insert.cpp \
						./vector/my_vector_insert2.cpp \
						./vector/my_vector_ite_arrow.cpp \
						./vector/my_vector_ite_n0.cpp \
						./vector/my_vector_ite_n00.cpp \
						./vector/my_vector_ite_n1.cpp \
						./vector/my_vector_ite.cpp \
						./vector/my_vector_push_pop.cpp \
						./vector/my_vector_relational_ope.cpp \
						./vector/my_vector_rev_ite_construct.cpp \
						./vector/my_vector_rite_arrow.cpp \
						./vector/my_vector_rite_eq_ope.cpp \
						./vector/my_vector_rite.cpp \
						./vector/my_vector_rite2.cpp \
						./vector/my_vector_size.cpp \
						./vector/my_vector_swap.cpp \
						./stack/my_stack_default_copy.cpp \
						./stack/my_stack_default.cpp \
						./stack/my_stack_list_copy.cpp \
						./stack/my_stack_relational_ope_list.cpp \
						./stack/my_stack_relational_ope.cpp \
						./map/my_map_bouds.cpp \
						./map/my_map_comp.cpp \
						./map/my_map_copy_construct.cpp \
						./map/my_map_empty.cpp \
						./map/my_map_erase.cpp \
						./map/my_map_erase2.cpp \
						./map/my_map_find_count.cpp \
						./map/my_map_insert.cpp \
						./map/my_map_insert2.cpp \
						./map/my_map_ite_arrow.cpp \
						./map/my_map_ite_n0.cpp \
						./map/my_map_ite_n1.cpp \
						./map/my_map_ite_type.cpp \
						./map/my_map_more.cpp \
						./map/my_map_op_sqbr.cpp \
						./map/my_map_relational_ope.cpp \
						./map/my_map_rev_ite_construct.cpp \
						./map/my_map_rite_arrow.cpp \
						./map/my_map_rite.cpp \
						./map/my_map_swap.cpp \
						./map/my_map_tricky_construct.cpp \
						./map/my_map_tricky_erase.cpp \

RM				=		rm -rf
CC				=		clang++
FLAGS			=		-Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address

OBJECTS_FOLDER	=		./srcs/tests/
OBJECT			=		${SOURCES:.cpp=.o}
OBJECTS			=		${addprefix ${OBJECTS_FOLDER}, ${OBJECT}}

$(OBJECTS_FOLDER)%.o :	$(SOURCES_FOLDER)%.cpp
						@mkdir -p	$(OBJECTS_FOLDER)
						@echo "Compiling: $<"
						@ ${CC} $(FLAGS) -c $< -o $@

$(NAME): 				$(OBJECTS)
						@ echo "Creating the executable."
						@ ${CC} $(FLAGS) -o $(NAME) $(OBJECTS)

all: 					$(NAME)

clean:
						@echo "Cleaning: $(OBJECTS_FOLDER)"
						@$(RM) $(OBJECTS)

fclean: 				clean
						@echo "Cleaning: $(NAME)"
						@rm -f $(NAME)

re: 					fclean all

run: 					$(NAME)
						@./$(NAME)
