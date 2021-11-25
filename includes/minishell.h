/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:33:26 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/25 12:45:17 by tlemesle         ###   ########.fr       */
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

# include "../libft/libft.h"
# include "../includes/get_next_line.h"

#define TOKEN_WORD  1
#define TOKEN_NUM   2
#define TOKEN_PIPE  3
#define TOKEN_FLUX  4

typedef struct s_node
{
	char            *s;
	int             token_type;
	struct s_node	*n;
}                   t_node;

// PARSER
void	input_parser(char *line);

// LIST UTILS
t_node	*newnode(char *s, int token_type);
t_node	*getlast(t_node *s);
void	add_back(t_node **s, t_node *new);
void	add_front(t_node **s, t_node *new);
void	free_list(t_node **s);
void	print_list(t_node **node);

#endif