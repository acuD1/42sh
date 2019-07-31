NAME			=	21sh

INC 			= 	-I ./inc		\
				-I ./libft		\

LIB			=	./libft/libft.a

CC			=	gcc -g -fsanitize=address

FLAGS			+=	-Wall -Wextra -Werror

PINK			=	\033[35;5;108m
PURPLE			=	\033[38;5;141m
MAGENTA			=	\033[38;5;177m
END			=	\033[0m

CR_UP			=	\033[A
CLEAR			=	\033[K

SRC_CMDLINE		= 	$(shell ls ./srcs/commandline/ | grep -E ".+\.c")
SRC_INIT		= 	$(shell ls ./srcs/init/ | grep -E ".+\.c")
SRC_EXEC		= 	$(shell ls ./srcs/exec/ | grep -E ".+\.c")
SRC_BUILTINS		= 	$(shell ls ./srcs/builtins/ | grep -E ".+\.c")

SRCS_CMDLINE		=	$(addprefix ./srcs/commandline/, $(SRC_CMDLINE))
SRCS_INIT		=	$(addprefix ./srcs/init/, $(SRC_INIT))
SRCS_EXEC		=	$(addprefix ./srcs/exec/, $(SRC_EXEC))
SRCS_BUILTINS		=	$(addprefix ./srcs/builtins/, $(SRC_BUILTINS))

SRCS			= 	main.c			\
				$(SRCS_CMDLINE)		\
				$(SRCS_INIT)		\
				$(SRCS_EXEC)		\
				$(SRCS_BUILTINS)	\

OBJS			= 	$(SRCS:.c=.o)

all			:	$(LIB) $(NAME)


$(NAME)			:	$(OBJS)
				$(CC) $(INC) -o $(NAME) $(OBJS) ./libft/libft.a -ltermcap
				@echo "${PINK}21SH IS READY ✓${END}"


$(LIB)			:	
				@make -C libft/
				@echo "${MAGENTA}LIBRARY COMPILED ✓${END}"

$(OBJ_DIR)		:
				@mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/%.o:$(SRCS)/%.c
				@echo "${MAGENTA}[$@]${END}"
				@$(CC) $(INC) -c -o $@ $< $(FLAGS)
				@printf "${CR_UP}${CLEAR}"

clean:
				@rm -rf $(OBJS)
				@rm -f *.o 2> /dev/null
				@make clean -C  libft/
				@echo "${PURPLE}clean objs ✗${END}"

fclean:				clean
				@rm -f $(NAME)
				@make fclean -C libft/
				@echo "${PURPLE}clean $(NAME) ✗${END}"

re:				fclean all

.PHONY:	all clean fclean re
