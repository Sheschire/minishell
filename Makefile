YELLOW			= \033[1;33m
GREEN			= \033[1;32m

SRCS			= srcs/minishell.c\
				  srcs/get_next_line.c\
				  srcs/list_utils.c\
				  srcs/parser.c\
				  srcs/parser_utils.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes -lreadline

NAME			= minishell

all:			$(NAME)

%.o: %.c
				@$(CC) -I. -o $@ -c $? $(FLAGS)

$(NAME):		$(OBJS)
				@echo "\n${GREEN} |   Compiling libft"
				@make all -C libft/
				@echo "${YELLOW}          [OK]"
				@echo "\n${GREEN} |   Compiling Minishell"
				@gcc ${CFLAGS} -o ${NAME} ${OBJS} ./libft/libft.a
				@echo "${YELLOW}          [OK]\n"

clean:
				@echo "\n${GREEN} |   Cleaning Files"
				@$(RM) $(OBJS)
				@make clean -C libft/
				@echo "${YELLOW}          [OK]\n"

fclean:			clean
				@$(RM) $(NAME) libft.a
				@make fclean -C libft/

re:				fclean all

.PHONY:			all clean fclean re