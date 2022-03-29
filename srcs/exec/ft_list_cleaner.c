/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:46 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/29 13:29:21 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_create_redirin(t_node *node, t_global *g, char *hook, int ret)
{
	t_node	*tmp;

	node->here_doc = 0;
	tmp = node;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		if (tmp->token_type == 8 || tmp->token_type == 10)
		{
			hook = tmp->n->s;
			if (tmp->token_type == L_FLUX_CREATE)
			{
				node->here_doc = 0;
				ret = open(tmp->n->s, O_RDONLY);
				if (ret == -1)
					no_such_file(hook, node);
				if (node->limiter)
					ft_useless_here_doc(node->limiter);
				end_of_filein_check(node, ret, hook);
			}
			else if (tmp->token_type == L_FLUX_APPEND)
				handling_append(node, tmp, hook, g);
		}
		tmp = tmp->n;
	}	
	return (print_no_such_file(node));
}

void	count_create_redirout(t_node *node)
{
	t_node	*tmp;
	char	*hook;

	tmp = node;
	node->fileout = NULL;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		if (tmp->token_type == 7 || tmp->token_type == 9)
		{
			hook = tmp->n->s;
			if (tmp->token_type == R_FLUX_CREATE)
			{
				open(tmp->n->s, O_WRONLY | O_CREAT | O_TRUNC, 0755);
				node->after = R_FLUX_CREATE;
			}
			else
			{
				open(tmp->n->s, O_WRONLY | O_CREAT | O_APPEND, 0755);
				node->after = R_FLUX_APPEND;
			}
		}
		tmp = tmp->n;
	}
	node->fileout = hook;
	return ;
}

int	ft_list_cleaner(t_node *node, t_global *g)
{
	t_node	*tmp;
	char	*hook;
	int		ret;

	hook = NULL;
	ret = 0;
	tmp = node;
	while (tmp->n || tmp->token_type == CMD)
	{
		if (tmp->token_type == CMD)
		{
			if (tmp->cmd[0] == NULL)
				return (0);
			if (!count_create_redirin(tmp, g, hook, ret))
				count_create_redirout(tmp);
			if (tmp->signal_here_doc)
				return (0);
		}
		if (tmp->n)
			tmp = tmp->n;
		else
			break ;
	}
	return (1);
}
