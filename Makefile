YELLOW			= \033[1;33m
GREEN			= \033[1;32m

SRCS			= srcs/minishell.c\
				  srcs/get_next_line.c\
				  srcs/parsing/list_utils.c\
				  srcs/parsing/parser.c\
				  srcs/parsing/parser_utils.c\
				  srcs/parsing/reorganise_commandline.c\
				  srcs/free_utils.c\
				  srcs/init.c\
				  srcs/signals.c\
				  srcs/parsing/group_nodes_into_commands.c\
				  srcs/builtin/pipex.c\
				  srcs/builtin/pipex_utils.c\
				  srcs/builtin/here_doc.c\
				  srcs/builtin/ft_list_cleaner.c\
				  srcs/builtin/ft_errors_manager.c\
				  srcs/builtin/cmd_path_builder.c

OBJS			= $(SRCS:.c=.o)

CC				= clang
RM				= rm -f
CFLAGS			= -g3 -fsanitize=address -Wall -Wextra -Werror -I./includes -lreadline

NAME			= minishell

all:			$(NAME)

%.o: %.c
				@$(CC) -I. -o $@ -c $? $(FLAGS)

$(NAME):		$(OBJS)
				@echo "\n${GREEN} |   Compiling libft"
				@make all -C libft/
				@echo "${YELLOW}          [OK]"
				@echo "\n${GREEN} |   Compiling Minishell"
				@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ./libft/libft.a
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
