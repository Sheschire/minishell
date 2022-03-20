/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:02:46 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/20 13:23:16 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_flux(t_node *node, char *hook, t_global *g, int flag)
{
	if (flag == 1)
	{
		node->filein = NULL;
		node->here_doc = 1;
		if (node->limiter)
			ft_useless_here_doc(node->limiter, g);
		node->limiter = hook;
	}
	else
	{
		node->limiter = NULL;
		node->filein = hook;
	}
}

int	error_in_redir(char *hook, t_node *node)
{
	node->_error = 1;
	ft_putstr_fd(hook, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

int	count_create_redirin(t_node *node, t_global *g, int ret, char *hook)
{
	t_node	*tmp;

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
					return (error_in_redir(hook, node));
				if (node->limiter)
					ft_useless_here_doc(node->limiter, g);
				handling_flux(node, hook, g, 2);
				close(ret);
			}
			else if (tmp->token_type == L_FLUX_APPEND)
				handling_flux(node, hook, g, 1);
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
Here we wants to check every redirout and redirin for each CMD.
We first check the redirin. If there is a file missing, 
it does not create the files
for the redirout like bash does. If there are multiple 
here_docs they will all be called.
BUT only the last one of the redirin is considered the entry of the CMD.
Each redirout files are created with the right flag O_TRUNC / O_APPEND
depending on the flux type.
*/

void	ft_list_cleaner(t_node *node, t_global *g)
{
	t_node	*tmp;
	int		ret;
	char	*hook;

	hook = NULL;
	ret = 0;
	tmp = node;
	while (tmp->n)
	{
		if (tmp->token_type == CMD)
		{
			node->here_doc = 0;
			if (count_create_redirin(tmp, g, ret, hook))
				count_create_redirout(tmp);
		}
		if (tmp->token_type == CMD && tmp->n->token_type == TOKEN_PIPE)
			tmp->after = TOKEN_PIPE;
		tmp = tmp->n;
	}
	return ;
}
