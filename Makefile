YELLOW			= \033[1;33m
GREEN			= \033[1;32m

SRCS			= srcs/minishell.c\
				  srcs/get_next_line/get_next_line.c\
				  srcs/get_next_line/get_next_line_utils.c\
				  srcs/parsing/list_utils.c\
				  srcs/parsing/parser.c\
				  srcs/parsing/parser_utils.c\
				  srcs/parsing/print_syntax_err.c\
				  srcs/parsing/redir_utils.c\
				  srcs/parsing/expand_variables.c\
				  srcs/parsing/expand_utils.c\
				  srcs/parsing/reorganise_commandline.c\
				  srcs/parsing/dequote.c\
				  srcs/free_utils.c\
				  srcs/init.c\
				  srcs/signals.c\
				  srcs/signals_here_doc.c\
				  srcs/parsing/group_nodes_into_commands.c\
				  srcs/exec/pipex.c\
				  srcs/exec/pipex_utils.c\
				  srcs/exec/here_doc.c\
				  srcs/exec/here_doc_expand.c\
				  srcs/exec/ft_list_cleaner.c\
				  srcs/exec/ft_cleaner_utils.c\
				  srcs/exec/ft_errors_manager.c\
				  srcs/exec/cmd_path_builder.c\
				  srcs/builtin/ft_cd.c\
				  srcs/builtin/ft_env.c\
				  srcs/builtin/ft_exit.c\
				  srcs/builtin/ft_pwd.c\
				  srcs/builtin/ft_export.c\
				  srcs/builtin/ft_export_declare.c\
				  srcs/builtin/ft_echo.c\
				  srcs/builtin/ft_unset.c\
				  srcs/builtin/builtin_utils.c\
				  srcs/exec/ft_dupper.c\
				  srcs/exec/ft_parent_process.c\
				  srcs/exec/ft_child_process.c

OBJS			= $(SRCS:.c=.o)

CC				= clang
RM				= rm -f
INCLUDE			= -I ./includes/
CFLAGS			= -Wall -Wextra -Werror -I./includes -g3

NAME			= minishell

all:			$(NAME)

.c.o:
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				@echo "\n${GREEN} |   Compiling libft"
				@make all -C libft/
				@echo "${YELLOW}          [OK]"
				@echo "\n${GREEN} |   Compiling Minishell"
				@${CC} ${CFLAGS} -lreadline  ${INCLUDE} -o ${NAME} ${OBJS} ./libft/libft.a
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
