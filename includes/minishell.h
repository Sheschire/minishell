/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:33:26 by tlemesle          #+#    #+#             */
/*   Updated: 2021/12/02 15:18:05 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>

# include "../libft/libft.h"
# include "../includes/get_next_line.h"

#define TOKEN_LITERAL  1
#define TOKEN_PIPE  2
#define TOKEN_FLUX  3
#define TOKEN_OPTION 4
#define TOKEN_COMMAND 5
#define	TOKEN_FILE 6
#define R_FLUX_CREATE 7
#define L_FLUX_CREATE 8
#define R_FLUX_APPEND 9
#define L_FLUX_APPEND 10
#define SINGLE_QUOTE_NODE 11
#define DOUBLE_QUOTE_NODE 12
#define TOKEN_ARG 13

#define ERROR_STDR 1
#define CMD_NOT_FND 127
#define WRNG_ARG 128

typedef struct s_global
{
	char			**env;
	char			**path;
	int				_pipe[2][2];
	t_node			*node;
	int				cmd_nbr;
	int				status;
}					t_global;

typedef struct s_node
{
	char            *s;
	int             token_type;
	struct s_node	*n;
}                   t_node;

// PARSER 
void	input_parser(char *line);
void	analyse_literal_token(t_node *tmp, int command_up);
void    find_flux_direction(t_node *tmp);
char	*create_option_node(char *line, t_node **list);
char    *create_quote_node(char *line, t_node **list);
int		find_token_type(char c);

// LIST UTILS
t_node	*newnode(char *s, int token_type);
t_node	*getlast(t_node *s);
void	add_back(t_node **s, t_node *new);
void	add_front(t_node **s, t_node *new);
void	free_list(t_node **s);
void	print_list(t_node **node);
void	newnode_add_back(char *s, int token_type, t_node **list);
int		build_command_array(t_node **list, char ** command_array);
int		found_token_flux(t_node **list);

// BUILTIN UTILS
int		ft_are_digits(char *str);

#endif
