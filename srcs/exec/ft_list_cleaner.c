/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:46 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/14 17:36:59 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handling_flux_append(t_node *node, char *hook, t_global *g)
{
	node->filein = NULL;
	node->here_doc = 1;
	if (node->limiter)
		ft_useless_here_doc(node->limiter, g);
	node->limiter = hook;
}

int	count_create_redirin(t_node *node, t_global *g)
{
	t_node	*tmp;
	char	*hook;
	int		ret;

	node->here_doc = 0;
	tmp = node;
	while (tmp->n && tmp->n->token_type != TOKEN_PIPE)
	{
		if (tmp->token_type == 8 || tmp->token_type == 10)
		{
			hook =  tmp->n->s;
			if (tmp->token_type == L_FLUX_CREATE)
			{
				node->here_doc = 0;
				ret = open(tmp->n->s, O_RDONLY);
				if (ret == -1)
				{
					node->_error = 1;
					printf("%s: No such file or directory\n", hook);
					return (0);
				}
				if (node->limiter)
					ft_useless_here_doc(node->limiter, g);
				node->limiter = NULL;
				node->filein = hook;
				close(ret);
			}
			else if (tmp->token_type == L_FLUX_APPEND)
				handling_flux_append(node, hook, g);
		}
		tmp = tmp->n;
	}	
	return (1);
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

/*
// Here we wants to check every redirout and redirin for each CMD.
// We first check the redirin. If there is a file missing, it does not create the files
// for the redirout like bash does. If there are multiple here_docs they will all be called.
// BUT only the last one of the redirin is considered the entry of the CMD.
// Each redirout files are created with the right flag O_TRUNC / O_APPEND
// depending on the flux type.
*/

void	ft_list_cleaner(t_node *node, t_global *g)
{
	t_node	*tmp;

	tmp = node;
	while (tmp->n)
	{
		if (tmp->token_type == CMD)
		{
			if (count_create_redirin(tmp, g))
				count_create_redirout(tmp);
		}
		if (tmp->token_type == CMD && tmp->n->token_type == TOKEN_PIPE)
			tmp->after = TOKEN_PIPE;
		tmp = tmp->n;
	}
	return ;
}
