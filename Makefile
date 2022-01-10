NAME			=		ft_containers

SOURCES_FOLDER	= 		./srcs/tests

SOURCES			=		main.cpp \
						./vector/assign.cpp \

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
